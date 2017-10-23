#ifndef MATHOPS_SSE_H
#define MATHOPS_SSE_H

///////////////////////////////////
// Math ops for 4-way SSE code
// Author: Angus F. Hewlett
// Copyright FXpansion Audio UK Ltd. 2012
///////////////////////////////////

////////////////////////////////
// This file provides:-
// * Typedefs for n-way SSE (8x32) containers
// ** interleave amount configured by template parameter - can be any power of 2
// ** vec_float & vec_int - float32 and int32 respectively
// * copy constructors, assignment and basic math operators for those containers
// * General intrinsic-function-style math operations for 4-way SSE data ("addps()" etc.) operating on vec_float & vec_int types
// ** (as static functions in Mathops_SSExN class - inherit to win)
// * typedefs / conversion routines for packing/unpacking to plain vectors of floats/ints
////////////////////////////////

#ifndef CEXCOMPILE
#include "MathOps_Common.h"
#include <xmmintrin.h>
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
// class Mathops_SSE
// Math operations for interleaved N-way SSE data
///////////////////////////////////////////////////////////////////////////////////////////////////


template <const int intrlv> class MathOps
{
public:
    static constexpr int raw_vec_elem = 4;
    static constexpr int raw_vec_2pow = 2;
    static constexpr int interleave = intrlv;
    static constexpr int32 vec_elem = interleave * raw_vec_elem;
    static constexpr int alignment = 16;
    
    
    typedef __m128 vec_elem_t;
    typedef __m128i vec_int_t;

    
    ARG2WRAPPER(__m128, _mm_min_ps);
    ARG2WRAPPER(__m128, _mm_max_ps);
    ARG2WRAPPER(__m128, _mm_add_ps);
    ARG2WRAPPER(__m128, _mm_sub_ps);
    ARG2WRAPPER(__m128, _mm_mul_ps);
    ARG2WRAPPER(__m128, _mm_div_ps);
    ARG2WRAPPER(__m128, _mm_or_ps);
    ARG2WRAPPER(__m128, _mm_and_ps);
    ARG2WRAPPER(__m128, _mm_andnot_ps);
    ARG2WRAPPER(__m128, _mm_xor_ps);
    ARG2WRAPPERK(__m128, _mm_cmp_ps);
    ARG1WRAPPER(__m128, _mm_rcp_ps);
    ARG1WRAPPER(__m128, _mm_sqrt_ps);
    ARG1WRAPPER(__m128, _mm_floor_ps);
    
    
    
    typedef vec_float_impl_t<MathOps, interleave> vec_float;
    typedef Interleaver<interleave, vec_float, __m128, _mm_set1_ps> Inter;
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // Intrinsic-style functions for f32 & i32 vector operations
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    
    //////////////////////////////////////
    // Initialization - zeroes, set1float, set1int
    static vforceinline vec_float  zerops()
    {
        return Inter::assignE(_mm_setzero_ps());
    };
    
    static vforceinline vec_float  set1ps(float q1)
    {
        return Inter::assignS(q1);
    };
    
    static vforceinline vec_float  loadps(const float* q1)
    {
        vec_float rv;
        if (intrlv > 0x0) rv.m[0x0] = _mm_loadu_ps(&(q1[0]));
        if (intrlv > 0x1) rv.m[0x1] = _mm_loadu_ps(&(q1[4]));
        if (intrlv > 0x2) rv.m[0x2] = _mm_loadu_ps(&(q1[8]));
        if (intrlv > 0x3) rv.m[0x3] = _mm_loadu_ps(&(q1[12]));
        if (intrlv > 0x4) rv.m[0x4] = _mm_loadu_ps(&(q1[16]));
        if (intrlv > 0x5) rv.m[0x5] = _mm_loadu_ps(&(q1[20]));
        if (intrlv > 0x6) rv.m[0x6] = _mm_loadu_ps(&(q1[24]));
        if (intrlv > 0x7) rv.m[0x7] = _mm_loadu_ps(&(q1[28]));
        if (intrlv > 0x8) rv.m[0x8] = _mm_loadu_ps(&(q1[32]));
        if (intrlv > 0x9) rv.m[0x9] = _mm_loadu_ps(&(q1[36]));
        if (intrlv > 0xA) rv.m[0xA] = _mm_loadu_ps(&(q1[40]));
        if (intrlv > 0xB) rv.m[0xB] = _mm_loadu_ps(&(q1[44]));
        if (intrlv > 0xC) rv.m[0xC] = _mm_loadu_ps(&(q1[48]));
        if (intrlv > 0xD) rv.m[0xD] = _mm_loadu_ps(&(q1[52]));
        if (intrlv > 0xE) rv.m[0xE] = _mm_loadu_ps(&(q1[56]));
        if (intrlv > 0xF) rv.m[0xF] = _mm_loadu_ps(&(q1[60]));
        return rv;
    };
    
    //////////////////////////////////////
    // Float operations - add, sub, mul, min, max, bitwise or, bitwise and, abs
    GENERATE_INTERLEAVED_FUNCTION_2ARG(mulps, wrap__mm_mul_ps);
    GENERATE_INTERLEAVED_FUNCTION_2ARG(addps, wrap__mm_add_ps);
    GENERATE_INTERLEAVED_FUNCTION_2ARG(subps, wrap__mm_sub_ps);
    GENERATE_INTERLEAVED_FUNCTION_2ARG(divps, wrap__mm_div_ps);
    GENERATE_INTERLEAVED_FUNCTION_2ARG(minps, wrap__mm_min_ps);
    GENERATE_INTERLEAVED_FUNCTION_2ARG(maxps, wrap__mm_max_ps);
    GENERATE_INTERLEAVED_FUNCTION_2ARG(orps, wrap__mm_or_ps);
    GENERATE_INTERLEAVED_FUNCTION_2ARG(andps, wrap__mm_and_ps);
    GENERATE_INTERLEAVED_FUNCTION_2ARG(andnps, wrap__mm_andnot_ps);
    GENERATE_INTERLEAVED_FUNCTION_2ARG(xorps, wrap__mm_xor_ps);
    
    GENERATE_INTERLEAVED_FUNCTION_2ARG_K(cmpgeps, wrap__mm_cmp_ps<_CMP_GE_OS>, _CMP_GE_OS);
    GENERATE_INTERLEAVED_FUNCTION_2ARG_K(cmpgtps, wrap__mm_cmp_ps, _CMP_GT_OS);
    GENERATE_INTERLEAVED_FUNCTION_2ARG_K(cmpleps, wrap__mm_cmp_ps, _CMP_LE_OS);
    GENERATE_INTERLEAVED_FUNCTION_2ARG_K(cmpltps, wrap__mm_cmp_ps, _CMP_LT_OS);
    GENERATE_INTERLEAVED_FUNCTION_2ARG_K(cmpeqps, wrap__mm_cmp_ps, _CMP_EQ_OS);
    GENERATE_INTERLEAVED_FUNCTION_2ARG_K(cmpneps, wrap__mm_cmp_ps, _CMP_NEQ_OS);
    
    GENERATE_INTERLEAVED_FUNCTION_1ARG(rcpps, wrap__mm_rcp_ps);
    GENERATE_INTERLEAVED_FUNCTION_1ARG(sqrtps, wrap__mm_sqrt_ps);
    GENERATE_INTERLEAVED_FUNCTION_1ARG(floorps, wrap__mm_floor_ps);
    
    static vforceinline vec_float  roundps(const vec_float& q1)
    {
        // this assumes ROUND_DOWN. TODO: replace with proper controlword-based rounding
        vec_float rup = (q1 + 0.5f);
        return floorps(rup);
    }
    
    static vforceinline vec_float  absps(const vec_float& q1)
    {
        return andps(q1, _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF)));
    };
    
    static vforceinline vec_float  notps(const vec_float& q1)
    {
        return xorps(q1, _mm_castsi128_ps(_mm_set1_epi32(0xFFFFFFFF)));
    };
    
    static vforceinline vec_float  clipps(const vec_float& val, const vec_float& lo_lim, const vec_float& hi_lim)
    {
        return maxps(lo_lim, minps(val, hi_lim));
    };
    
    static vforceinline vec_float  cubeps(const vec_float& q1)
    {
        return mulps(q1, mulps(q1,q1));
    };
    
    static vforceinline vec_float  clip01ps(const vec_float& q1)
    {
        return maxps(minps(q1, set1ps(1.f)), 0.f);
    };
    
    static vforceinline vec_float  maskps(const vec_float& maskee, const vec_float& conditional_mask)
    {
        return andps(maskee, conditional_mask);
    };
    
    
    //////////////////////////////////////
    // Types and conversions for extracting to raw data
    //////////////////////////////////////
    
    union vec_union_i32
    {
        vec_int_t mi[interleave];
        int32 i[vec_elem];
        float f[vec_elem];
        uint32 u[vec_elem];
        vec_elem_t m[interleave];
    };
    
    union vec_union_f
    {
        float f[vec_elem];
        uint32 u[vec_elem];
        int32 i[vec_elem];
        vec_elem_t m[interleave];
        vec_int_t mi[interleave];
        vec_float mv;
        vec_union_f() {};
        vec_union_f(const vec_float& other) { mv = other; };
        vec_union_f(const vec_union_f& other) { mv = other.mv; };
        ~vec_union_f() {};
    };
    
    
    static vforceinline void  get_union_f(const vec_float& obj, vec_union_f& result)
    {
        INTERLEAVED_INDEX_ASSIGN_T(result.m, obj.m);
    };
    
    static vforceinline vec_float  get_vector_f(const vec_union_f& obj)
    {
        vec_float result;
        INTERLEAVED_INDEX_ASSIGN_T(result.m, obj.m);
        return result;
    };
};

#endif
