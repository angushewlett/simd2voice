#ifndef PREFIX_FMA_H
#define PREFIX_FMA_H

#define COMPILER_ALLOW_AVX 1

//#if MACOSX
#define DISPATCH_ATTRIBUTE_TAG __attribute__((target("avx2,fma,arch=haswell")))
//#else
//#define DISPATCH_ATTRIBUTE_TAG
//#endif

// Turn on FMA for the AVX implementation class
#define MATHOPS_AVX_FMA 1
// Set up common macros used by NodeTemplateDispatch: the MathOps wrapper namespace & the dispatch method signature
#define IMPL_MathNamespace IMPL_FMA                 // Used for MathOps
#define IMPL_DispatchMethod ProcessBuffer_FMA    // Dispatch method signature

#include <stdlib.h>
#include "XDSP.h"

// Wrap math operations for current architecture in a namespace
namespace IMPL_MathNamespace
{
#include "MathOps_AVX.h"
};

#include "IOAdapter.h"


#endif
