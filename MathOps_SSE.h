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
    
    template <size_t increment> vforceinline vec_float gather(const float* base_address)
    {
        //        printf("%d\n", (const int32)increment);
        vec_float rv;
        int32 fc = increment / sizeof(float);
        const float* ba = base_address;
        
        if (intrlv > 0x0) rv.m[0x0] = _mm_set_ps(*(ba + (fc * 0x00)), *(ba + (fc * 0x01)), *(ba + (fc * 0x02)), *(ba + (fc * 0x03)));
        if (intrlv > 0x1) rv.m[0x1] = _mm_set_ps(*(ba + (fc * 0x04)), *(ba + (fc * 0x05)), *(ba + (fc * 0x06)), *(ba + (fc * 0x07)));
        if (intrlv > 0x2) rv.m[0x2] = _mm_set_ps(*(ba + (fc * 0x08)), *(ba + (fc * 0x09)), *(ba + (fc * 0x0A)), *(ba + (fc * 0x0B)));
        if (intrlv > 0x3) rv.m[0x3] = _mm_set_ps(*(ba + (fc * 0x0C)), *(ba + (fc * 0x0D)), *(ba + (fc * 0x0E)), *(ba + (fc * 0x0F)));

        if (intrlv > 0x4) rv.m[0x4] = _mm_set_ps(*(ba + (fc * 0x10)), *(ba + (fc * 0x11)), *(ba + (fc * 0x12)), *(ba + (fc * 0x13)));
        if (intrlv > 0x5) rv.m[0x5] = _mm_set_ps(*(ba + (fc * 0x14)), *(ba + (fc * 0x15)), *(ba + (fc * 0x16)), *(ba + (fc * 0x17)));
        if (intrlv > 0x6) rv.m[0x6] = _mm_set_ps(*(ba + (fc * 0x18)), *(ba + (fc * 0x19)), *(ba + (fc * 0x1A)), *(ba + (fc * 0x1B)));
        if (intrlv > 0x7) rv.m[0x7] = _mm_set_ps(*(ba + (fc * 0x1C)), *(ba + (fc * 0x1D)), *(ba + (fc * 0x1E)), *(ba + (fc * 0x1F)));

        if (intrlv > 0x8) rv.m[0x8] = _mm_set_ps(*(ba + (fc * 0x20)), *(ba + (fc * 0x21)), *(ba + (fc * 0x22)), *(ba + (fc * 0x23)));
        if (intrlv > 0x9) rv.m[0x9] = _mm_set_ps(*(ba + (fc * 0x24)), *(ba + (fc * 0x25)), *(ba + (fc * 0x26)), *(ba + (fc * 0x27)));
        if (intrlv > 0xA) rv.m[0xA] = _mm_set_ps(*(ba + (fc * 0x28)), *(ba + (fc * 0x29)), *(ba + (fc * 0x2A)), *(ba + (fc * 0x2B)));
        if (intrlv > 0xB) rv.m[0xB] = _mm_set_ps(*(ba + (fc * 0x2C)), *(ba + (fc * 0x2D)), *(ba + (fc * 0x2E)), *(ba + (fc * 0x2F)));

        if (intrlv > 0xC) rv.m[0xC] = _mm_set_ps(*(ba + (fc * 0x30)), *(ba + (fc * 0x31)), *(ba + (fc * 0x32)), *(ba + (fc * 0x33)));
        if (intrlv > 0xD) rv.m[0xD] = _mm_set_ps(*(ba + (fc * 0x34)), *(ba + (fc * 0x35)), *(ba + (fc * 0x36)), *(ba + (fc * 0x37)));
        if (intrlv > 0xE) rv.m[0xE] = _mm_set_ps(*(ba + (fc * 0x38)), *(ba + (fc * 0x39)), *(ba + (fc * 0x3A)), *(ba + (fc * 0x3B)));
        if (intrlv > 0xF) rv.m[0xF] = _mm_set_ps(*(ba + (fc * 0x3C)), *(ba + (fc * 0x3D)), *(ba + (fc * 0x3E)), *(ba + (fc * 0x3F)));
        
        return rv;
    }
    
    struct alff
    {
        float data[4];
    } __attribute__((aligned(16)));
    
    vforceinline void mystore_ps(const __m128& data, float& a, float& b, float& c, float& d)
    {
        alff x;
        _mm_store_ps(&x.data[0], data);
        a = x.data[0];
        b = x.data[1];
        c = x.data[2];
        d = x.data[3];
    }
    
    template <size_t increment> vforceinline vec_float scatter(const vec_float& rv, float* base_address)
    {
        //        printf("%d\n", (const int32)increment);
        int32 fc = increment / sizeof(float);
        float* ba = base_address;
        
        if (intrlv > 0x0) mystore_ps(rv.m[0x0], *(ba + (fc * 0x00)), *(ba + (fc * 0x01)), *(ba + (fc * 0x02)), *(ba + (fc * 0x03)));
        if (intrlv > 0x1) mystore_ps(rv.m[0x1], *(ba + (fc * 0x04)), *(ba + (fc * 0x05)), *(ba + (fc * 0x06)), *(ba + (fc * 0x07)));
        if (intrlv > 0x2) mystore_ps(rv.m[0x2], *(ba + (fc * 0x08)), *(ba + (fc * 0x09)), *(ba + (fc * 0x0A)), *(ba + (fc * 0x0B)));
        if (intrlv > 0x3) mystore_ps(rv.m[0x3], *(ba + (fc * 0x0C)), *(ba + (fc * 0x0D)), *(ba + (fc * 0x0E)), *(ba + (fc * 0x0F)));
        
        if (intrlv > 0x4) mystore_ps(rv.m[0x4], *(ba + (fc * 0x10)), *(ba + (fc * 0x11)), *(ba + (fc * 0x12)), *(ba + (fc * 0x13)));
        if (intrlv > 0x5) mystore_ps(rv.m[0x5], *(ba + (fc * 0x14)), *(ba + (fc * 0x15)), *(ba + (fc * 0x16)), *(ba + (fc * 0x17)));
        if (intrlv > 0x6) mystore_ps(rv.m[0x6], *(ba + (fc * 0x18)), *(ba + (fc * 0x19)), *(ba + (fc * 0x1A)), *(ba + (fc * 0x1B)));
        if (intrlv > 0x7) mystore_ps(rv.m[0x7], *(ba + (fc * 0x1C)), *(ba + (fc * 0x1D)), *(ba + (fc * 0x1E)), *(ba + (fc * 0x1F)));
        
        if (intrlv > 0x8) mystore_ps(rv.m[0x8], *(ba + (fc * 0x20)), *(ba + (fc * 0x21)), *(ba + (fc * 0x22)), *(ba + (fc * 0x23)));
        if (intrlv > 0x9) mystore_ps(rv.m[0x9], *(ba + (fc * 0x24)), *(ba + (fc * 0x25)), *(ba + (fc * 0x26)), *(ba + (fc * 0x27)));
        if (intrlv > 0xA) mystore_ps(rv.m[0xA], *(ba + (fc * 0x28)), *(ba + (fc * 0x29)), *(ba + (fc * 0x2A)), *(ba + (fc * 0x2B)));
        if (intrlv > 0xB) mystore_ps(rv.m[0xB], *(ba + (fc * 0x2C)), *(ba + (fc * 0x2D)), *(ba + (fc * 0x2E)), *(ba + (fc * 0x2F)));
        
        if (intrlv > 0xC) mystore_ps(rv.m[0xC], *(ba + (fc * 0x30)), *(ba + (fc * 0x31)), *(ba + (fc * 0x32)), *(ba + (fc * 0x33)));
        if (intrlv > 0xD) mystore_ps(rv.m[0xD], *(ba + (fc * 0x34)), *(ba + (fc * 0x35)), *(ba + (fc * 0x36)), *(ba + (fc * 0x37)));
        if (intrlv > 0xE) mystore_ps(rv.m[0xE], *(ba + (fc * 0x38)), *(ba + (fc * 0x39)), *(ba + (fc * 0x3A)), *(ba + (fc * 0x3B)));
        if (intrlv > 0xF) mystore_ps(rv.m[0xF], *(ba + (fc * 0x3C)), *(ba + (fc * 0x3D)), *(ba + (fc * 0x3E)), *(ba + (fc * 0x3F)));
        
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
        int32 mask = 0x7FFFFFFF;
        vec_float tmp = *(reinterpret_cast<float*>(&mask));
        return andps(q1, tmp);
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
