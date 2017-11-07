
//////////////////////////////////////////////////////////
// XDispatch_FMA.cpp
// Dispatcher for FMA optimized processbuffer loops (Haswell / Broadwell)
//////////////////////////////////////////////////////////

#ifdef _MSC_VER
#define WIN32 1
#define NOMINMAX 1
class IUnknown;
#include <windows.h>
#include <stdint.h>

// System headers
WINBASEAPI VOID WINAPI Sleep(_In_ DWORD dwMilliseconds);
void sleep(int s)
{
	Sleep(s * 1000);
}

#else
#include <unistd.h>
#endif

#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fenv.h>
#include <list>
#include <algorithm>

#ifdef IACA_TEST
#include "iacaMarks.h"
#endif

// Enable additional instruction sets here
#if 1 // __SSE__
#define ENABLE_SSE 1
#endif

#if 0 //__AVX__
#define ENABLE_AVX 1
#endif

#if 0 //__AVX512__
#define ENABLE_AVX512 1
#endif

#define DISPATCHTESTCOMPILE 1
//#define EXTRA_TEMP_COPY 1

#include "XDSP.h"
#include "XHelpers.h"
#include "XStopWatch.h"
#include "XBenchmark.h"
// Macros & interleaver
#include "MathOps_Common.h"
// I/O adapter
#include "XIOAdapter.h"

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


template <class TTestClass, class TMathClass> void run_test(const char* messagePrefix)
{
    ////////
    // Basic set up
    typedef typename TTestClass::Node TNode;
    XDSP::ProcessGlobals process_globals;
    const int coalesce = 1;
    // Note - affects L1 / L2 fit for processing data.
    process_globals.block_length = 64 * coalesce;
    // nRunsPerTimer requires some hand tuning: we want the amount of iterations sampled to be
    // >10us, <100us to increase timer resolution on the one hand, but be smaller than the
    // OS scheduler quantum so that the task isn't regularly getting put to sleep.
    const int32 nRunsPerTimer = 8;
    const int32 nTotalIterations = 1 << 20; // ~1M iterations
    const int32 nTimerPasses = nTotalIterations / (nRunsPerTimer * process_globals.block_length); // /*2048*/;
    const int32 voiceCount = XDSP::kMaxVoices;
    const int32 bufferSize = XDSP::kMaxVoices * process_globals.block_length;

    // Reject interleave sizes larger than the number of voices.
    if (TMathClass::vec_elem > XDSP::kMaxVoices)
    {
        printf("%s %s%s\n", TTestClass::GetDescription(), messagePrefix ,": Failed to interleave (larger than voice count)");
        return;
    }
    
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
        for (int a = 0; a < node->AudioOutCount(); a++) node->GetVoice(i)->SetAudioOut(a, (output_buffer + i));
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
    
    node->PrepareStream(process_globals);
    Benchmarker bench;
    
    ////////
    // Run the process for (nTimerPasses * nRunsPerTimer) times
    for (int32 t = 0; t < nTimerPasses; t++)
    {
        for (int32 k = 0; k < bufferSize; k++)
        {
            input_buffer[k] = randf();
            output_buffer[k] = randf();
        }

        bench.BeginRun();
        for (int32 i = 0; i < nRunsPerTimer; i++)
        {
            // DumbWorker::WaitForCompletion();
            // Test CPU-dependent dispatching
            // node->ProcessBuffer_Dispatch(process_globals);
            
            // Test template-argument-specific dispatching
            XDSP::NodeTmpl<TTestClass>::template ProcessAllVoices<typename IOAdapter<TMathClass, TTestClass>::Worker>(process_globals, node);
        }
        bench.EndRun();
    }
    
    ////////
    // Process the results & print the average execution time.    
    float timerPassAverage = bench.GetAverageTime();
    float audioBlockAverage = (timerPassAverage  / nRunsPerTimer);          // average execution time for a single audio block
    float k10e6 = 1000000.f;
    float mIterationsPerSecond = (XDSP::kMaxVoices * process_globals.block_length * (1.0f / audioBlockAverage)) / k10e6;
    float xRealtime = (k10e6 * mIterationsPerSecond / 64.f) / 44100.f;

    // Print the result
    printf ("Average time for [ %s %s ] [%dv, %ds] bl: %0.2f us \t\t%0.2f MIt/sec\t%0.2f MOp/sec\t%0.2f MCall/sec\t%0.2f x Realtime\n",
            TTestClass::GetDescription(), messagePrefix, XDSP::kMaxVoices, process_globals.block_length, audioBlockAverage * k10e6,
            mIterationsPerSecond, mIterationsPerSecond / TMathClass::raw_vec_elem, mIterationsPerSecond / TMathClass::vec_elem, xRealtime);
    
    ////////////////
    // Sanity checks
    // printf("%f %f %f %f\n", output_buffer[0], output_buffer[7], output_buffer[63], node->GetVoiceTyped(0)->m_bandState[0].a[0]);
    // Get the sum of all times
    // float sumTimes = 0.f;
    // auto b = liTimes.begin();
    // for (int k = 0; k < liTimes.size() ; a++, k++) sumTimes += *b;                 // Ignore the first 25%
    // dbgiter /= 10e6;
    // float walltime = wallclock.GetElapsedTime() - tt0;
    // printf ("Execution time: %f s; sum time: %f s; dbg_iter 0.2%f ; MIter/s %0.2f; total samps %0.2f\n", (float)walltime, (float)sumTimes, (float)dbgiter, ((float)totalSamples/(float)walltime) / k10e6, totalSamples);
    // DumbWorker::GoToSleep();

    ////////
    // Clean up
    delete node;
    valigned_free(input_buffer);
    valigned_free(output_buffer);
}

// The test class
#include "YBasicAmp.h"
#include "YPannerAmp.h"
#include "YEQFilter.h"
#include "YFilterLadder.h"

//#define TEST_CLASS YBasicAmp
// #define TEST_CLASS YPannerAmp
// #define TEST_CLASS YFilterLadder
#define TEST_CLASS YEQFilter<4>

int main(int argc, char *argv[])
{
    //    DumbWorker::WakeUp();
    sleep(2); // Give Instruments time to attach cleanly
#if MACOSX
    fesetenv(FE_DFL_DISABLE_SSE_DENORMS_ENV);
#elif LINUX
    _mm_setcsr(_mm_getcsr() | (_MM_DENORMALS_ZERO_ON));
#elif WIN32
    _controlfp_s( NULL, _DN_FLUSH, _MCW_DN );
#endif
	run_test<TEST_CLASS, MSCL::MathOps<1>>("fpu,  1");
//	run_test<TEST_CLASS, MSCL::MathOps<1>>("fpu,  1");
    run_test<TEST_CLASS,MSCL::MathOps<1>>("fpu,  1");
    run_test<TEST_CLASS,MSCL::MathOps<2>>("fpu,  2");
    run_test<TEST_CLASS,MSCL::MathOps<4>>("fpu,  4");
    run_test<TEST_CLASS,MSCL::MathOps<8>>("fpu,  8");
    run_test<TEST_CLASS,MSCL::MathOps<16>>("fpu, 16");
//    run_test<TEST_CLASS,MSCL::MathOps<1>>("fpu,  1");
    
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
//    run_test<TEST_CLASS,MSCL::MathOps<1>>("fpu,  1");
//    run_test<TEST_CLASS,MAVX::MathOps<2>>("AVX,  2");    
//	  run_test<TEST_CLASS,MSSE::MathOps<1>>("SSE,  1");

    sleep(2); // Give Instruments time to detach cleanly
}

