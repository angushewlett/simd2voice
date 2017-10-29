//
//  CompilerExplorer.cpp

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

namespace MFMA
{
#include <https://raw.githubusercontent.com/angushewlett/simdtest/master/MathOps_AVX.h>
};

#define TTestClass XEQFilter<1>
#define TMathClass MFMA::MathOps<2>

void process(TTestClass::Node* node)
{
    XDSP::ProcessGlobals process_globals;
    XDSP::NodeTmpl<TTestClass>::template ProcessAllVoices<typename IOAdapter<TMathClass, TTestClass>::Worker>(process_globals, node);
}

