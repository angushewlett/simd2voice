#ifndef XHELPERS_H
#define XHELPERS_H
////////////////////////////////
// File: XHelpers
// Helper functions for MathOps & XDSP
// Author: Angus F. Hewlett
// Copyright FXpansion Audio UK Ltd. 2012-2017
////////////////////////////////

////////////////////////////////
// This file provides:-
//
// * int32 & uint32 - integer types
// * vforceinline macro - forced inlining
// * valigned_malloc & valigned_free - x-platform aligned malloc/free
// * randf() - float pseudorandom
////////////////////////////////

#include <stdlib.h>
#include <stdint.h>
#if WIN32 && !CEXCOMPILE
#include <malloc.h>
#endif

typedef int32_t int32;
typedef uint32_t uint32;

#if WIN32
#define vforceinline __forceinline
#else
#define vforceinline __inline__ __attribute__((always_inline))
#endif

#if CEXCOMPILE
#define valigned_malloc(a, b) malloc(a)
#define valigned_free(a) free(a)
#else

#ifndef TARGET_TYPE_APP

////////////////////////////////
// aligned malloc() wrapper
inline void *valigned_malloc( size_t size, size_t align )
{
#if WIN32
    return _aligned_malloc (size, align);
#else
    void* mem = 0;
    posix_memalign(&mem, align, size);
    return mem;
#endif
}

////////////////////////////////
// aligned free() wrapper
inline void valigned_free( void *mem )
{
#if WIN32
    return _aligned_free(mem);
#else
    free(mem);
#endif
}
#endif
#endif

////////////////////////////////
// floating point (-1,1) pseudo random number generator
inline float randf()
{
    return 2.f * ((rand() / (float)RAND_MAX) - 0.5f);
};


#endif
