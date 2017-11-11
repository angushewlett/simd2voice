//////////////////////////////////////////////////////////
// XDispatch_AVX2_XBasicAmp.cpp
// Dispatcher for optimized processing (XBasicAmp, AVX2)

// (Generic) - Common
#include "XHelpers.h"
#include "XDSP.h"
#include "XIOAdapter.h"
#include "MathOps_Common.h"

// DSP template class
#include "YBasicAmp.h"
typedef YBasicAmp TDspClass;
typedef XDSP::NodeTmpl<TDspClass> TNode;

// SIMD implementation
#define AVX_VERSION 2
#define MathOps_AVX_v MathOps_AVX2
#include "MathOps_AVX.h"

// Types for workers of specified DSP class using 1, 2, 4, 8, 16-way interleave
typedef IOAdapter<MathOps_AVX2<1>, TDspClass>::Worker TWorker1;
typedef IOAdapter<MathOps_AVX2<2>, TDspClass>::Worker TWorker2;
typedef IOAdapter<MathOps_AVX2<4>, TDspClass>::Worker TWorker4;
typedef IOAdapter<MathOps_AVX2<8>, TDspClass>::Worker TWorker8;
typedef IOAdapter<MathOps_AVX2<16>, TDspClass>::Worker TWorker16;

// (Generic) - generate and call the ProcessAllVoices function for each AVX2 worker-type
template<> void XDSP::NodeTmpl<TDspClass>::ProcessBuffer_AVX2(const ProcessGlobals& process_globals, TDspClass::Node* node)
{
    static int preferredInterleave = 2;
    switch (preferredInterleave)
    {
        case 0: TNode::ProcessAllVoices<TWorker1>(process_globals, node);   break;
        case 1: TNode::ProcessAllVoices<TWorker2>(process_globals, node);   break;
        case 2: TNode::ProcessAllVoices<TWorker4>(process_globals, node);   break;
        case 3: TNode::ProcessAllVoices<TWorker8>(process_globals, node);   break;
        case 4: TNode::ProcessAllVoices<TWorker16>(process_globals, node);  break;
    }
}
