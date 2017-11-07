#ifndef MATHOPS_AVX512_H
#define MATHOPS_AVX512_H

////////////////////////////////
// File: MathOps_AVX512.h
// Defines math operations for AVX512 SIMD floating point.
// Author: Angus F. Hewlett
// Copyright FXpansion Audio UK Ltd. 2012-2017
////////////////////////////////

#ifndef CEXCOMPILE
#include "MathOps_Common.h"
#endif
#include <zmmintrin.h>

template <const int interleave_i> class MathOps_AVX512 : public MathBase<MathOps_AVX512<interleave_i>, __m256, interleave_i>
{
public:
    static constexpr int raw_vec_elem = 16;
    static constexpr int raw_vec_2pow = 4;
    static constexpr int vec_elem = interleave_i * raw_vec_elem;
    static constexpr int alignment = 64;
	static constexpr int interleave = interleave_i;
    
    typedef __m512 vec_elem_t ALIGN_POST(64);
    typedef __m512i vec_int_t ALIGN_POST(64);    
	typedef vf_t<MathOps_AVX_v, interleave> vec_float;
    
    ////////////////////////////////
    // Operation classes: set, add, sub, mul, div, min, max, rcp, abs, and, or, andn, xor, not, cmp(ge,gt,le,lt,eq,ne).
	class op_set_f
	{
	public: static vforceinline vec_elem_t op(float a) { return _mm512_set1_ps(a); };
	};

	class op_add_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return _mm512_add_ps(a , b); };
	};

	class op_sub_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return _mm512_sub_ps(a , b); };
	};

	class op_mul_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return _mm512_mul_ps(a, b); };
	};

	class op_div_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return _mm512_div_ps(a, b); };
	};

	class op_min_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return _mm512_min_ps(a , b); };
	};

	class op_max_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return _mm512_max_ps(a, b); };
	};

	class op_rcp_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a) { return _mm512_rcp14_ps(a); };
	};

	class op_abs_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a) { const int32 mask = 0x7FFFFFFF; return  _mm512_and_ps(a, _mm512_set1_ps(mask)); };
	};

	class op_and_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return _mm512_and_ps(a, b); };
	};

	class op_or_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return _mm512_or_ps(a, b); };
	};

	class op_andn_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return _mm512_andnot_ps(a, b); };
	};

	class op_xor_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return _mm512_xor_ps(a, b); };
	};

	class op_not_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a) { return _mm512_xor_ps(a, _mm512_set1_epi32(0xFFFFFFFF)); };
	};

	class op_cmpge_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return _mm512_cmp_ps(a,b, _CMP_GE_OS); };
	};

	class op_cmpgt_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return _mm512_cmp_ps(a,b, _CMP_GT_OS); };
	};

	class op_cmple_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return _mm512_cmp_ps(a,b, _CMP_LE_OS); };
	};

	class op_cmplt_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return _mm512_cmp_ps(a,b, _CMP_LT_OS); };
	};

	class op_cmpeq_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return _mm512_cmp_ps(a,b, _CMP_EQ_OS); };
	};

	class op_cmpne_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return _mm512_cmp_ps(a,b, _CMP_NEQ_OS); };
	};
             
    ////////////////////////////////
    // Load, gather, scatter

    // Load
    static vforceinline vec_float  loadps(const float* q1)
    {
        vec_float rv;
        if (intrlv > 0x0) rv.m[0x0] = _mm512_loadu_ps(&(q1[0]));
        if (intrlv > 0x1) rv.m[0x1] = _mm512_loadu_ps(&(q1[16]));
        if (intrlv > 0x2) rv.m[0x2] = _mm512_loadu_ps(&(q1[32]));
        if (intrlv > 0x3) rv.m[0x3] = _mm512_loadu_ps(&(q1[48]));
        if (intrlv > 0x4) rv.m[0x4] = _mm512_loadu_ps(&(q1[64]));
        if (intrlv > 0x5) rv.m[0x5] = _mm512_loadu_ps(&(q1[80]));
        if (intrlv > 0x6) rv.m[0x6] = _mm512_loadu_ps(&(q1[96]));
        if (intrlv > 0x7) rv.m[0x7] = _mm512_loadu_ps(&(q1[112]));
        if (intrlv > 0x8) rv.m[0x8] = _mm512_loadu_ps(&(q1[128]));
        if (intrlv > 0x9) rv.m[0x9] = _mm512_loadu_ps(&(q1[144]));
        if (intrlv > 0xA) rv.m[0xA] = _mm512_loadu_ps(&(q1[160]));
        if (intrlv > 0xB) rv.m[0xB] = _mm512_loadu_ps(&(q1[176]));
        if (intrlv > 0xC) rv.m[0xC] = _mm512_loadu_ps(&(q1[192]));
        if (intrlv > 0xD) rv.m[0xD] = _mm512_loadu_ps(&(q1[208]));
        if (intrlv > 0xE) rv.m[0xE] = _mm512_loadu_ps(&(q1[224]));
        if (intrlv > 0xF) rv.m[0xF] = _mm512_loadu_ps(&(q1[240]));
        return rv;
    };
    
    // Gather
    template <size_t increment> vforceinline vec_float gather(const float* base_address)
    {
        //        printf("%d\n", (const int32)increment);
        vec_float rv;
		constexpr int32 inc_f = increment / sizeof(float);
        const __m512i scale_base = _mm512_set_epi32(0x00 * increment, 0x01 * increment, 0x02 * increment, 0x03 * increment, 0x04 * increment, 0x05 * increment, 0x06 * increment, 0x07 * increment,
						    0x08 * increment, 0x09 * increment, 0x0A * increment, 0x0B * increment, 0x0C * increment, 0x0D * increment, 0x0E * increment, 0x0F * increment);

        if (intrlv > 0x0) rv.m[0x0] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0x00), 1);
        if (intrlv > 0x1) rv.m[0x1] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0x10), 1);
        if (intrlv > 0x2) rv.m[0x2] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0x20), 1);
        if (intrlv > 0x3) rv.m[0x3] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0x30), 1);
        if (intrlv > 0x4) rv.m[0x4] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0x40), 1);
        if (intrlv > 0x5) rv.m[0x5] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0x50), 1);
        if (intrlv > 0x6) rv.m[0x6] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0x60), 1);
        if (intrlv > 0x7) rv.m[0x7] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0x70), 1);
        if (intrlv > 0x8) rv.m[0x8] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0x80), 1);
        if (intrlv > 0x9) rv.m[0x9] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0x90), 1);
        if (intrlv > 0xA) rv.m[0xA] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0xA0), 1);
        if (intrlv > 0xB) rv.m[0xB] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0xB0), 1);
        if (intrlv > 0xC) rv.m[0xC] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0xC0), 1);
        if (intrlv > 0xD) rv.m[0xD] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0xD0), 1);
        if (intrlv > 0xE) rv.m[0xE] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0xE0), 1);
        if (intrlv > 0xF) rv.m[0xF] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0xF0), 1);
        return rv;
    }
    
	// Scatter
    template <size_t increment> vforceinline void scatter(const vec_float& data, float* base_address)
    {
        //        printf("%d\n", (const int32)increment);
        constexpr int32 inc_f = increment / sizeof(float);
        const __m512i scale_base = _mm512_set_epi32(
                            0x00 * increment, 0x01 * increment, 0x02 * increment, 0x03 * increment, 0x04 * increment, 0x05 * increment, 0x06 * increment, 0x07 * increment,
						    0x08 * increment, 0x09 * increment, 0x0A * increment, 0x0B * increment, 0x0C * increment, 0x0D * increment, 0x0E * increment, 0x0F * increment
                                                    );

        if (intrlv > 0x0) _mm512_i32scatter_ps(base_address + (inc_f * 0x00), scale_base, data.m[0x0], 1);
        if (intrlv > 0x1) _mm512_i32scatter_ps(base_address + (inc_f * 0x10), scale_base, data.m[0x1], 1);
        if (intrlv > 0x2) _mm512_i32scatter_ps(base_address + (inc_f * 0x20), scale_base, data.m[0x2], 1);
        if (intrlv > 0x3) _mm512_i32scatter_ps(base_address + (inc_f * 0x30), scale_base, data.m[0x3], 1);
        if (intrlv > 0x4) _mm512_i32scatter_ps(base_address + (inc_f * 0x40), scale_base, data.m[0x4], 1);
        if (intrlv > 0x5) _mm512_i32scatter_ps(base_address + (inc_f * 0x50), scale_base, data.m[0x5], 1);
        if (intrlv > 0x6) _mm512_i32scatter_ps(base_address + (inc_f * 0x60), scale_base, data.m[0x6], 1);
        if (intrlv > 0x7) _mm512_i32scatter_ps(base_address + (inc_f * 0x70), scale_base, data.m[0x7], 1);
        if (intrlv > 0x8) _mm512_i32scatter_ps(base_address + (inc_f * 0x80), scale_base, data.m[0x8], 1);
        if (intrlv > 0x9) _mm512_i32scatter_ps(base_address + (inc_f * 0x90), scale_base, data.m[0x9], 1);
        if (intrlv > 0xA) _mm512_i32scatter_ps(base_address + (inc_f * 0xA0), scale_base, data.m[0xA], 1);
        if (intrlv > 0xB) _mm512_i32scatter_ps(base_address + (inc_f * 0xB0), scale_base, data.m[0xB], 1);
        if (intrlv > 0xC) _mm512_i32scatter_ps(base_address + (inc_f * 0xC0), scale_base, data.m[0xC], 1);
        if (intrlv > 0xD) _mm512_i32scatter_ps(base_address + (inc_f * 0xD0), scale_base, data.m[0xD], 1);
        if (intrlv > 0xE) _mm512_i32scatter_ps(base_address + (inc_f * 0xE0), scale_base, data.m[0xE], 1);
        if (intrlv > 0xF) _mm512_i32scatter_ps(base_address + (inc_f * 0xF0), scale_base, data.m[0xF], 1);
    }
};


#endif
