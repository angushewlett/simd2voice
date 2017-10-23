#ifndef MATHOPS_SCALAR_H
#define MATHOPS_SCALAR_H

///////////////////////////////////
// Math ops for 1-way scalar code
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
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// class Mathops_SSE
// Math operations for interleaved N-way SSE data
///////////////////////////////////////////////////////////////////////////////////////////////////


inline float setfloat (float a) {    return a;  };
inline float smm_mul_ss(float a, float b) { return a*b; };
inline float smm_div_ss(float a, float b) { return a/b; };
inline float smm_add_ss(float a, float b) { return a+b; };
inline float smm_sub_ss(float a, float b) { return a-b; };
inline float smm_min_ss(float a, float b) { return std::min(a,b); };
inline float smm_max_ss(float a, float b) { return std::max(a,b); };

inline float smm_and_ss(float a, float b) { int32 tmp = (*reinterpret_cast<int32*>(&a) & *reinterpret_cast<int32*>(&b)); return *reinterpret_cast<float*>(&tmp); };
inline float smm_or_ss(float a, float b) { int32 tmp = (*reinterpret_cast<int32*>(&a) | *reinterpret_cast<int32*>(&b)); return *reinterpret_cast<float*>(&tmp); };
inline float smm_andnot_ss(float a, float b) { int32 tmp = (*reinterpret_cast<int32*>(&a) &~ *reinterpret_cast<int32*>(&b)); return *reinterpret_cast<float*>(&tmp); };
inline float smm_xor_ss(float a, float b) { int32 tmp = (*reinterpret_cast<int32*>(&a) ^ *reinterpret_cast<int32*>(&b)); return *reinterpret_cast<float*>(&tmp); };


inline float smm_rcp_ss(float a) { return 1.f / a; };
inline float smm_sqrt_ss(float a) { return sqrt(a); };
inline float smm_floor_ss(float a) { return std::floor(a); };


inline float smm_cmp_ss(float a, float b, int32 cmpmode) { return a == b; };

template <const int intrlv> class MathOps
{
public:
    static constexpr int raw_vec_elem = 1;
    static constexpr int raw_vec_2pow = 0;
    static constexpr int interleave = intrlv;
    static constexpr int32 vec_elem = interleave * raw_vec_elem;
    static constexpr int alignment = 4;
    
    
    typedef float vec_elem_t;
    typedef int vec_int_t;
    
    
    ARG2WRAPPER(float, smm_min_ss);
    ARG2WRAPPER(float, smm_max_ss);
    ARG2WRAPPER(float, smm_add_ss);
    ARG2WRAPPER(float, smm_sub_ss);
    ARG2WRAPPER(float, smm_mul_ss);
    ARG2WRAPPER(float, smm_div_ss);
    ARG2WRAPPER(float, smm_or_ss);
    ARG2WRAPPER(float, smm_and_ss);
    ARG2WRAPPER(float, smm_andnot_ss);
    ARG2WRAPPER(float, smm_xor_ss);
    ARG2WRAPPERK(float, smm_cmp_ss);
    ARG1WRAPPER(float, smm_rcp_ss);
    ARG1WRAPPER(float, smm_sqrt_ss);
    ARG1WRAPPER(float, smm_floor_ss);
    
    
    
    typedef vec_float_impl_t<MathOps, interleave> vec_float;
    typedef Interleaver<interleave, vec_float, float, setfloat> Inter;
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // Intrinsic-style functions for f32 & i32 vector operations
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    
    //////////////////////////////////////
    // Initialization - zeroes, set1float, set1int
    static vforceinline vec_float  zerops()
    {
        return Inter::assignE(0.f);
    };
    
    static vforceinline vec_float  set1ps(float q1)
    {
        return Inter::assignS(q1);
    };
    
    static vforceinline vec_float  loadps(const float* q1)
    {
        vec_float rv;
        if (intrlv > 0x0) rv.m[0x0] = _mm_load_ss(&(q1[0]));
        if (intrlv > 0x1) rv.m[0x1] = _mm_load_ss(&(q1[1]));
        if (intrlv > 0x2) rv.m[0x2] = _mm_load_ss(&(q1[2]));
        if (intrlv > 0x3) rv.m[0x3] = _mm_load_ss(&(q1[3]));
        if (intrlv > 0x4) rv.m[0x4] = _mm_load_ss(&(q1[4]));
        if (intrlv > 0x5) rv.m[0x5] = _mm_load_ss(&(q1[5]));
        if (intrlv > 0x6) rv.m[0x6] = _mm_load_ss(&(q1[6]));
        if (intrlv > 0x7) rv.m[0x7] = _mm_load_ss(&(q1[7]));
        if (intrlv > 0x8) rv.m[0x8] = _mm_load_ss(&(q1[8]));
        if (intrlv > 0x9) rv.m[0x9] = _mm_load_ss(&(q1[9]));
        if (intrlv > 0xA) rv.m[0xA] = _mm_load_ss(&(q1[10]));
        if (intrlv > 0xB) rv.m[0xB] = _mm_load_ss(&(q1[11]));
        if (intrlv > 0xC) rv.m[0xC] = _mm_load_ss(&(q1[12]));
        if (intrlv > 0xD) rv.m[0xD] = _mm_load_ss(&(q1[13]));
        if (intrlv > 0xE) rv.m[0xE] = _mm_load_ss(&(q1[14]));
        if (intrlv > 0xF) rv.m[0xF] = _mm_load_ss(&(q1[15]));
        return rv;
    };
    
    //////////////////////////////////////
    // Float operations - add, sub, mul, min, max, bitwise or, bitwise and, abs
    GENERATE_INTERLEAVED_FUNCTION_2ARG(mulps, wrap_smm_mul_ss);
    GENERATE_INTERLEAVED_FUNCTION_2ARG(addps, wrap_smm_add_ss);
    GENERATE_INTERLEAVED_FUNCTION_2ARG(subps, wrap_smm_sub_ss);
    GENERATE_INTERLEAVED_FUNCTION_2ARG(divps, wrap_smm_div_ss);
    GENERATE_INTERLEAVED_FUNCTION_2ARG(minps, wrap_smm_min_ss);
    GENERATE_INTERLEAVED_FUNCTION_2ARG(maxps, wrap_smm_max_ss);
    GENERATE_INTERLEAVED_FUNCTION_2ARG(orps, wrap_smm_or_ss);
    GENERATE_INTERLEAVED_FUNCTION_2ARG(andps, wrap_smm_and_ss);
    GENERATE_INTERLEAVED_FUNCTION_2ARG(andnps, wrap_smm_andnot_ss);
    GENERATE_INTERLEAVED_FUNCTION_2ARG(xorps, wrap_smm_xor_ss);
    
    GENERATE_INTERLEAVED_FUNCTION_2ARG_K(cmpgeps, wrap_smm_cmp_ss<_CMP_GE_OS>, _CMP_GE_OS);
    GENERATE_INTERLEAVED_FUNCTION_2ARG_K(cmpgtps, wrap_smm_cmp_ss, _CMP_GT_OS);
    GENERATE_INTERLEAVED_FUNCTION_2ARG_K(cmpleps, wrap_smm_cmp_ss, _CMP_LE_OS);
    GENERATE_INTERLEAVED_FUNCTION_2ARG_K(cmpltps, wrap_smm_cmp_ss, _CMP_LT_OS);
    GENERATE_INTERLEAVED_FUNCTION_2ARG_K(cmpeqps, wrap_smm_cmp_ss, _CMP_EQ_OS);
    GENERATE_INTERLEAVED_FUNCTION_2ARG_K(cmpneps, wrap_smm_cmp_ss, _CMP_NEQ_OS);
    
    GENERATE_INTERLEAVED_FUNCTION_1ARG(rcpps, wrap_smm_rcp_ss);
    GENERATE_INTERLEAVED_FUNCTION_1ARG(sqrtps, wrap_smm_sqrt_ss);
    GENERATE_INTERLEAVED_FUNCTION_1ARG(floorps, wrap_smm_floor_ss);
    
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
