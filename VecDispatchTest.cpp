//////////////////////////////////////////////////////////
// XDispatch_FMA.cpp
// Dispatcher for FMA optimized processbuffer loops (Haswell / Broadwell)
//////////////////////////////////////////////////////////

// System headers
#include <immintrin.h>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <fenv.h>
#include <list>

#ifdef IACA_TEST
#include "iacaMarks.h"
#endif

// Enable additional instruction sets here
#define ENABLE_SSE 1
#define ENABLE_AVX 1
// #define ENABLE_AVX512 1

#define DISPATCHTESTCOMPILE 1
#define EXTRA_TEMP_COPY 1

// XDSP
#include "XDSP.h"
#include "XHelpers.h"
#include "XStopWatch.h"

// Macros & interleaver
#include "MathOps_Common.h"

// I/O adapter
#include "IOAdapter.h"

// Wrap math operations for each architecture in a namespace.
// We do this externally so this can be defined in the dispatch file.

namespace MSCL
{
#include "MathOps_Scalar.h"
};

#if ENABLE_SSE
namespace MSSE
{
#include "MathOps_SSE.h"
};
#endif

#if  ENABLE_AVX
namespace MAVX
{
#include "MathOps_AVX.h"
};
#endif

#if  ENABLE_AVX512
namespace M512
{
#include "MathOps_AVX512.h"
};
#endif

// The test class
#include "XEQFilter.h"


#if MACOSX
mach_timebase_info_data_t    StopWatch::sTimebaseInfo;
#endif


template <class TTestClass, class TMathClass> void run_test(const char* messagePrefix)
{
    ////////
    // Basic set up

    typedef typename TTestClass::Node TNode;
    XDSP::ProcessGlobals process_globals;
    
    const int coalesce = 1;
//    process_globals.block_length = 32 * coalesce;
    const int32 nRunsPerTimer = 16; // This should be big enough to get an accurate timer read, small enough to make thread interrupts unlikely.
    const int32 nTimerPasses = 512 / coalesce; // /*2048*/;
    
    const int32 voiceCount = XDSP::kMaxVoices;
    const int32 bufferSize = XDSP::kMaxVoices * process_globals.block_length;

    // Reject interleave sizes larger than the number of voices.
    if (TMathClass::vec_elem > XDSP::kMaxVoices)
    {
        printf("%s %s%s\n", TTestClass::GetDescription(), messagePrefix ,": Failed to interleave (larger than voice count)");
        return;
    }
    
//    const int32 nSamplesPerTimer = bufferSize * nRunsPerTimer;
 //   const float totalSamples = (float)nRunsPerTimer * (float)nTimerPasses * XDSP::kMaxVoices * process_globals.block_length;\
    
    // Create the DSP node object to do all our processing
    TNode* node = new TNode();

    ////////
    // Set up some input and output scratch audio buffers with noise.
    float* input_buffer = (float*)valigned_malloc(bufferSize * sizeof(float), 64);
    float* output_buffer = (float*)valigned_malloc(bufferSize * sizeof(float), 64);
    
    srand (5);
    
    ////////
    // Set up for the node and its voices. (The first element for each voice is the nth element in the buffer, buffer is kMaxVoices wide).
    for (int32 i = 0; i < voiceCount; i++)
    {
        for (int a = 0; a < node->AudioInCount(); a++)
        {
            node->GetVoice(i)->SetAudioIn(a, (input_buffer + i));
        }
        for (int a = 0; a < node->AudioOutCount(); a++)
        {
            node->GetVoice(i)->SetAudioOut(a, (output_buffer + i));
        }
        node->GetVoice(i)->Reset();
    }
    
    ////////
    // Set up some control parameters for the node (these are set independently on each voice)
    float control_params[] = {1.f, 0.8f, 0.6f, 0.3f, 0.8f, 0.9f, 0.2f, 0.5f };
    float* control_buffer = (float*)valigned_malloc(XDSP::kMaxVoices * XDSP::kMaxControlPorts * sizeof(float), 64);
    for (int32 i = 0; i < 8; i++)
    {
        for (int32 v = 0; v < XDSP::kMaxVoices; v++)
        {
            control_buffer[(i * XDSP::kMaxVoices) + v] = control_params[i];
            node->GetVoice(v)->SetControlIn(i, &control_buffer[(i * XDSP::kMaxVoices) + v]);
        }
    
    }
    
    ////////
    // Set up for the timing run
    StopWatch::StaticInit();
    
    StopWatch wallclock;
    double tt0 = wallclock.GetElapsedTime();
    //  dbgiter = 0;
    
    std::list<float> liTimes;       // in msec
    node->PrepareStream(process_globals);
    
    ////////
    // Run the process for (nTimerPasses * nRunsPerTimer) times
    for (int32 t = 0; t < nTimerPasses; t++)
    {
     //   float t0 = (float)iterTimer.GetElapsedTime();
        
        for (int32 k = 0; k < bufferSize; k++)
        {
            input_buffer[k] = randf();
            output_buffer[k] = randf();
        }
        
        
        StopWatch runTimer;
    
        for (int32 i = 0; i < nRunsPerTimer; i++)
        {
            // DumbWorker::WaitForCompletion();
            // Test CPU-dependent dispatching
            // node->ProcessBuffer_Dispatch(process_globals);
            
            // Test template-argument-specific dispatching
            XDSP::NodeTmpl<TTestClass>::template ProcessAllVoices<typename IOAdapter<TMathClass, TTestClass>::Worker>(process_globals, node);
        }
        liTimes.push_back((float)runTimer.GetElapsedTime());
    }
    
    ////////
    // Process the results & print the average execution time.
    liTimes.sort();
    float topTimes = 0.f;
    auto a = liTimes.begin();
    
    // We sample the middle 50% of times.
    for (int k = 0; k < (liTimes.size() / 4); a++, k++) {};                 // Ignore the first 25%
    float loTime = *a / nRunsPerTimer;           // Get the fastest (25th percentile) time
    
    for (int32 k = 0; k < (liTimes.size() / 2); a++, k++)  topTimes += *a;  // Take the next 50%
    float hiTime = *a  / nRunsPerTimer;           // Get the slowest (75th percentile) time
    
    float timerPassAverage = topTimes / (liTimes.size() / 2.f);             // average execution time for a timer-block
    float audioBlockAverage = (timerPassAverage  / nRunsPerTimer);          // average execution time for a single audio block
   
    float k10e6 = 1000000.f;
    
    float mIterationsPerSecond = (XDSP::kMaxVoices * process_globals.block_length * (1.0f / audioBlockAverage)) / k10e6;
    float xRealtime = (k10e6 * mIterationsPerSecond / 64.f) / 44100.f;

    printf("%f %f %f %f\n", output_buffer[0], output_buffer[7], output_buffer[63], output_buffer[64]);
    // Print the result
    printf ("Average time for [ %s %s ] [%dv, %ds] bl: %0.2f us \t(%0.2f-%0.2f)\t%0.2f MIt/sec\t%0.2f MOp/sec\t%0.2f MCall/sec\t%0.2f x Realtime\n",
            TTestClass::GetDescription(), messagePrefix, XDSP::kMaxVoices, process_globals.block_length, audioBlockAverage * k10e6, loTime * k10e6, hiTime * k10e6,
            mIterationsPerSecond, mIterationsPerSecond / TMathClass::raw_vec_elem, mIterationsPerSecond / TMathClass::vec_elem, xRealtime);
    
    ////////////////
    // Sanity check
    // Get the sum of all times
    // float sumTimes = 0.f;
    // auto b = liTimes.begin();
    // for (int k = 0; k < liTimes.size() ; a++, k++) sumTimes += *b;                 // Ignore the first 25%
    // dbgiter /= 10e6;
    // float walltime = wallclock.GetElapsedTime() - tt0;
    
    // printf ("Execution time: %f s; sum time: %f s; dbg_iter 0.2%f ; MIter/s %0.2f; total samps %0.2f\n", (float)walltime, (float)sumTimes, (float)dbgiter, ((float)totalSamples/(float)walltime) / k10e6, totalSamples);
    ////////
    // Clean up
    // DumbWorker::GoToSleep();
    delete node;
    valigned_free(input_buffer);
    valigned_free(output_buffer);
}


#define TEST_CLASS XEQFilter<1>

int main(int argc, char *argv[])
{
    //    DumbWorker::WakeUp();
    sleep(2); // Give Instruments time to attach cleanly
#if MACOSX
    fesetenv(FE_DFL_DISABLE_SSE_DENORMS_ENV);
#elif LINUX
    _mm_setcsr(_mm_getcsr() | (_MM_DENORMALS_ZERO_ON));
#else
#endif

    run_test<TEST_CLASS,MSCL::MathOps<1>>("fpu,  1");
    run_test<TEST_CLASS,MSCL::MathOps<2>>("fpu,  2");
    run_test<TEST_CLASS,MSCL::MathOps<4>>("fpu,  4");
    run_test<TEST_CLASS,MSCL::MathOps<8>>("fpu,  8");
    run_test<TEST_CLASS,MSCL::MathOps<16>>("fpu, 16");
    
#if ENABLE_SSE
    run_test<TEST_CLASS,MSSE::MathOps<1>>("SSE,  1");
    run_test<TEST_CLASS,MSSE::MathOps<2>>("SSE,  2");
    run_test<TEST_CLASS,MSSE::MathOps<4>>("SSE,  4");
    run_test<TEST_CLASS,MSSE::MathOps<8>>("SSE,  8");
    run_test<TEST_CLASS,MSSE::MathOps<16>>("SSE, 16");
#endif
    
#if ENABLE_AVX
    run_test<TEST_CLASS,MAVX::MathOps<1>>("AVX,  1");
    run_test<TEST_CLASS,MAVX::MathOps<2>>("AVX,  2");
    run_test<TEST_CLASS,MAVX::MathOps<4>>("AVX,  4");
    run_test<TEST_CLASS,MAVX::MathOps<8>>("AVX,  8");
    run_test<TEST_CLASS,MAVX::MathOps<16>>("AVX,  16");
#endif
    
#if ENABLE_AVX512
    run_test<TEST_CLASS,M512::MathOps<1>>("A512,  1");
    run_test<TEST_CLASS,M512::MathOps<2>>("A512,  2");
    run_test<TEST_CLASS,M512::MathOps<4>>("A512,  4");
    run_test<TEST_CLASS,M512::MathOps<8>>("A512,  8");
#endif
 //   _controlfp_s( NULL, _DN_FLUSH, _MCW_DN );
#ifdef IACA_TEST
    IACA_START;
#endif
    
//    run_test<TEST_CLASS,MAVX::MathOps<2>>("AVX,  2");
#ifdef IACA_TEST
    IACA_END;
#endif
    
    sleep(2); // Give Instruments time to detach cleanly
}

