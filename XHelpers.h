#ifndef XHELPERS_H
#define XHELPERS_H

#include <stdlib.h>
#include <stdint.h>
#if WIN32
#include <windows.h>
#endif

////////////////////////////////
// aligned malloc() wrapper
inline void *valigned_malloc( size_t size, size_t align )
{
#if WIN32
    _aligned_malloc (size, align);
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
    _aligned_free(mem);
#else
    free(mem);
#endif
}

////////////////////////////////
// floating point (-1,1) pseudo random number generator
inline float randf()
{
    return 2.f * ((rand() / (float)RAND_MAX) - 0.5f);
};

////////////////////////////////
// aligned malloc wrapper

#endif
