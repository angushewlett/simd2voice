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
#include <x86intrin.h>

template <const int interleave_i> class MathOps_AVX512 : public MathBase<MathOps_AVX512<interleave_i>, __m512, interleave_i>
{
public:
    static constexpr int raw_num_elem = 16;
    static constexpr int raw_vec_2pow = 4;
    static constexpr int num_elem = interleave_i * raw_num_elem;
    static constexpr int alignment = 64;
	static constexpr int interleave = interleave_i;
    
    typedef ALIGN_PRE(64) __m512 vec_elem_f ALIGN_POST(64);
    typedef ALIGN_PRE(64) __m512i vec_elem_i ALIGN_POST(64);
	typedef ALIGN_PRE(64) vf_t<MathOps_AVX512, interleave> vec_float ALIGN_POST(64);
    
    ////////////////////////////////
    // Operation classes: set, add, sub, mul, div, min, max, rcp, abs, and, or, andn, xor, not, cmp(ge,gt,le,lt,eq,ne).
	class op_set_f
	{
	public: static vforceinline vec_elem_f op(float a) { return _mm512_set1_ps(a); };
	};

	class op_add_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm512_add_ps(a , b); };
	};

	class op_sub_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm512_sub_ps(a , b); };
	};

	class op_mul_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm512_mul_ps(a, b); };
	};

	class op_div_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm512_div_ps(a, b); };
	};

	class op_min_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm512_min_ps(a , b); };
	};

	class op_max_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm512_max_ps(a, b); };
	};

	class op_rcp_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a) { return _mm512_rcp14_ps(a); };
	};

	class op_abs_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a) { const int32 mask = 0x7FFFFFFF; return  _mm512_and_ps(a, _mm512_set1_ps(mask)); };
	};

	class op_and_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm512_and_ps(a, b); };
	};

	class op_or_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm512_or_ps(a, b); };
	};

	class op_andn_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm512_andnot_ps(a, b); };
	};

	class op_xor_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm512_xor_ps(a, b); };
	};

	class op_not_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a) { return _mm512_xor_ps(a, _mm512_set1_epi32(0xFFFFFFFF)); };
	};

	template <int32 cmp_op> static vforceinline vec_elem_f _mm512_cmp_ps(const vec_elem_f& a, const vec_elem_f &b)
        {
            return _mm512_castsi512_ps(_mm512_maskz_set1_epi32(_mm512_cmp_ps_mask(a, b, cmp_op), 0xFFFFFFFF));
        };

	class op_cmpge_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm512_cmp_ps<_CMP_GE_OS>(a,b); };
	};

	class op_cmpgt_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm512_cmp_ps<_CMP_GT_OS>(a,b); };
	};

	class op_cmple_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm512_cmp_ps<_CMP_LE_OS>(a,b); };
	};

	class op_cmplt_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm512_cmp_ps<_CMP_LT_OS>(a,b); };
	};

	class op_cmpeq_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm512_cmp_ps<_CMP_EQ_OS>(a,b); };
	};

	class op_cmpne_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm512_cmp_ps<_CMP_NEQ_OS>(a,b); };
	};

	class op_sub_if_greater_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b, const vec_elem_f& c) 
		{
			__mmask16 k = _mm512_cmp_ps_mask(a, b, _CMP_GE_OS); 
			return _mm512_mask_sub_ps(a,k,a,c); 
		};
	};

             
    ////////////////////////////////
    // Load, gather, scatter

    // Load
    static vforceinline vec_float  loadps(const float* q1)
    {
        vec_float rv;
        if (interleave > 0x0) rv.m[0x0] = _mm512_loadu_ps(&(q1[0]));
        if (interleave > 0x1) rv.m[0x1] = _mm512_loadu_ps(&(q1[16]));
        if (interleave > 0x2) rv.m[0x2] = _mm512_loadu_ps(&(q1[32]));
        if (interleave > 0x3) rv.m[0x3] = _mm512_loadu_ps(&(q1[48]));
        if (interleave > 0x4) rv.m[0x4] = _mm512_loadu_ps(&(q1[64]));
        if (interleave > 0x5) rv.m[0x5] = _mm512_loadu_ps(&(q1[80]));
        if (interleave > 0x6) rv.m[0x6] = _mm512_loadu_ps(&(q1[96]));
        if (interleave > 0x7) rv.m[0x7] = _mm512_loadu_ps(&(q1[112]));
        if (interleave > 0x8) rv.m[0x8] = _mm512_loadu_ps(&(q1[128]));
        if (interleave > 0x9) rv.m[0x9] = _mm512_loadu_ps(&(q1[144]));
        if (interleave > 0xA) rv.m[0xA] = _mm512_loadu_ps(&(q1[160]));
        if (interleave > 0xB) rv.m[0xB] = _mm512_loadu_ps(&(q1[176]));
        if (interleave > 0xC) rv.m[0xC] = _mm512_loadu_ps(&(q1[192]));
        if (interleave > 0xD) rv.m[0xD] = _mm512_loadu_ps(&(q1[208]));
        if (interleave > 0xE) rv.m[0xE] = _mm512_loadu_ps(&(q1[224]));
        if (interleave > 0xF) rv.m[0xF] = _mm512_loadu_ps(&(q1[240]));
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

        if (interleave > 0x0) rv.m[0x0] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0x00), 1);
        if (interleave > 0x1) rv.m[0x1] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0x10), 1);
        if (interleave > 0x2) rv.m[0x2] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0x20), 1);
        if (interleave > 0x3) rv.m[0x3] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0x30), 1);
        if (interleave > 0x4) rv.m[0x4] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0x40), 1);
        if (interleave > 0x5) rv.m[0x5] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0x50), 1);
        if (interleave > 0x6) rv.m[0x6] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0x60), 1);
        if (interleave > 0x7) rv.m[0x7] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0x70), 1);
        if (interleave > 0x8) rv.m[0x8] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0x80), 1);
        if (interleave > 0x9) rv.m[0x9] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0x90), 1);
        if (interleave > 0xA) rv.m[0xA] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0xA0), 1);
        if (interleave > 0xB) rv.m[0xB] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0xB0), 1);
        if (interleave > 0xC) rv.m[0xC] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0xC0), 1);
        if (interleave > 0xD) rv.m[0xD] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0xD0), 1);
        if (interleave > 0xE) rv.m[0xE] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0xE0), 1);
        if (interleave > 0xF) rv.m[0xF] = _mm512_i32gather_ps(scale_base, base_address + (inc_f * 0xF0), 1);
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

        if (interleave > 0x0) _mm512_i32scatter_ps(base_address + (inc_f * 0x00), scale_base, data.m[0x0], 1);
        if (interleave > 0x1) _mm512_i32scatter_ps(base_address + (inc_f * 0x10), scale_base, data.m[0x1], 1);
        if (interleave > 0x2) _mm512_i32scatter_ps(base_address + (inc_f * 0x20), scale_base, data.m[0x2], 1);
        if (interleave > 0x3) _mm512_i32scatter_ps(base_address + (inc_f * 0x30), scale_base, data.m[0x3], 1);
        if (interleave > 0x4) _mm512_i32scatter_ps(base_address + (inc_f * 0x40), scale_base, data.m[0x4], 1);
        if (interleave > 0x5) _mm512_i32scatter_ps(base_address + (inc_f * 0x50), scale_base, data.m[0x5], 1);
        if (interleave > 0x6) _mm512_i32scatter_ps(base_address + (inc_f * 0x60), scale_base, data.m[0x6], 1);
        if (interleave > 0x7) _mm512_i32scatter_ps(base_address + (inc_f * 0x70), scale_base, data.m[0x7], 1);
        if (interleave > 0x8) _mm512_i32scatter_ps(base_address + (inc_f * 0x80), scale_base, data.m[0x8], 1);
        if (interleave > 0x9) _mm512_i32scatter_ps(base_address + (inc_f * 0x90), scale_base, data.m[0x9], 1);
        if (interleave > 0xA) _mm512_i32scatter_ps(base_address + (inc_f * 0xA0), scale_base, data.m[0xA], 1);
        if (interleave > 0xB) _mm512_i32scatter_ps(base_address + (inc_f * 0xB0), scale_base, data.m[0xB], 1);
        if (interleave > 0xC) _mm512_i32scatter_ps(base_address + (inc_f * 0xC0), scale_base, data.m[0xC], 1);
        if (interleave > 0xD) _mm512_i32scatter_ps(base_address + (inc_f * 0xD0), scale_base, data.m[0xD], 1);
        if (interleave > 0xE) _mm512_i32scatter_ps(base_address + (inc_f * 0xE0), scale_base, data.m[0xE], 1);
        if (interleave > 0xF) _mm512_i32scatter_ps(base_address + (inc_f * 0xF0), scale_base, data.m[0xF], 1);
    }
};


#endif
