//
//  CompilerExplorer.cpp

// Tell other headers we're using CEX - that way they won't try to include other local headers
#define CEXCOMPILE 1

#ifdef _MSC_VER
#define WIN32 1
#else
#define MACOSX 1
#endif

#include <immintrin.h>
#include <https://raw.githubusercontent.com/angushewlett/simdtest/master/XHelpers.h>
#include <https://raw.githubusercontent.com/angushewlett/simdtest/master/XDSP.h>
#include <https://raw.githubusercontent.com/angushewlett/simdtest/master/MathOps_Common.h>
#include <https://raw.githubusercontent.com/angushewlett/simdtest/master/IOAdapter.h>
#include <https://raw.githubusercontent.com/angushewlett/simdtest/master/XBasicAmp.h>
#include <https://raw.githubusercontent.com/angushewlett/simdtest/master/XEQFilter.h>

#define MathOps_AVX_v MathOps_AVX2
#include <https://raw.githubusercontent.com/angushewlett/simdtest/master/MathOps_AVX.h>

#define TTestClass XEQFilter<1>
#define TMathClass MathOps_AVX2<4>

// This is just to check CompilerExplorer code generation: no need to initialise anything.
void process(TTestClass::Node* node, const XDSP::ProcessGlobals& process_globals)
{
    XDSP::NodeTmpl<TTestClass>::template ProcessAllVoices<typename IOAdapter<TMathClass, TTestClass>::Worker>(process_globals, node);
}

