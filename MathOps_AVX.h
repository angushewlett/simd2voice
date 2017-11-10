#ifndef MATHOPS_AVX_H
#define MATHOPS_AVX_H

////////////////////////////////
// File: MathOps_AVX.h
// Defines math operations for AVX SIMD floating point.
// Author: Angus F. Hewlett
// Copyright FXpansion Audio UK Ltd. 2012-2017
////////////////////////////////

#ifndef CEXCOMPILE
#include "MathOps_Common.h"
#endif
#include <immintrin.h>

template <const int interleave_i> class ALIGN_PRE(32) MathOps_AVX_v : public MathBase<MathOps_AVX_v<interleave_i>, __m256, interleave_i>
{
public:
	static constexpr int raw_num_elem = 8;
	static constexpr int raw_vec_2pow = 3;
    static constexpr int num_elem = interleave_i * raw_num_elem;
    static constexpr int alignment = 32;
	static constexpr int interleave = interleave_i;

	typedef ALIGN_PRE(32) __m256 vec_elem_f ALIGN_POST(32);
	typedef ALIGN_PRE(32) __m256i vec_elem_i ALIGN_POST(32);
	typedef ALIGN_PRE(32) vf_t<MathOps_AVX_v, interleave> vec_float ALIGN_POST(32);
    
    ////////////////////////////////
    // Operation classes: set, add, sub, mul, div, min, max, rcp, abs, and, or, andn, xor, not, cmp(ge,gt,le,lt,eq,ne).
	class op_set_f
	{
	public: static vforceinline vec_elem_f op(float a) { return _mm256_set1_ps(a); };
	};

	class op_add_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm256_add_ps(a , b); };
	};

	class op_sub_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm256_sub_ps(a , b); };
	};

	class op_mul_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm256_mul_ps(a, b); };
	};

	class op_div_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm256_div_ps(a, b); };
	};

	class op_min_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm256_min_ps(a , b); };
	};

	class op_max_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm256_max_ps(a, b); };
	};

	class op_rcp_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a) { return _mm256_rcp_ps(a); };
	};

	class op_abs_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a) { const int32 mask = 0x7FFFFFFF; return  _mm256_and_ps(a, _mm256_set1_ps(mask)); };
	};

	class op_and_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm256_and_ps(a, b); };
	};

	class op_or_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm256_or_ps(a, b); };
	};

	class op_andn_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm256_andnot_ps(a, b); };
	};

	class op_xor_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm256_xor_ps(a, b); };
	};

	class op_not_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a) { return _mm256_xor_ps(a, _mm256_set1_epi32(0xFFFFFFFF)); };
	};

	class op_cmpge_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm256_cmp_ps(a,b, _CMP_GE_OS); };
	};

	class op_cmpgt_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm256_cmp_ps(a,b, _CMP_GT_OS); };
	};

	class op_cmple_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm256_cmp_ps(a,b, _CMP_LE_OS); };
	};

	class op_cmplt_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm256_cmp_ps(a,b, _CMP_LT_OS); };
	};

	class op_cmpeq_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm256_cmp_ps(a,b, _CMP_EQ_OS); };
	};

	class op_cmpne_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm256_cmp_ps(a,b, _CMP_NEQ_OS); };
	};
             
    ////////////////////////////////
    // Load, gather, scatter

    // Load
    static vforceinline vec_float  loadps(const float* q1)
    {
        vec_float rv;
        if (interleave > 0x0) rv.m[0x0] = _mm256_loadu_ps(&(q1[0]));
        if (interleave > 0x1) rv.m[0x1] = _mm256_loadu_ps(&(q1[8]));
        if (interleave > 0x2) rv.m[0x2] = _mm256_loadu_ps(&(q1[16]));
        if (interleave > 0x3) rv.m[0x3] = _mm256_loadu_ps(&(q1[24]));
        if (interleave > 0x4) rv.m[0x4] = _mm256_loadu_ps(&(q1[32]));
        if (interleave > 0x5) rv.m[0x5] = _mm256_loadu_ps(&(q1[40]));
        if (interleave > 0x6) rv.m[0x6] = _mm256_loadu_ps(&(q1[48]));
        if (interleave > 0x7) rv.m[0x7] = _mm256_loadu_ps(&(q1[56]));
        if (interleave > 0x8) rv.m[0x8] = _mm256_loadu_ps(&(q1[64]));
        if (interleave > 0x9) rv.m[0x9] = _mm256_loadu_ps(&(q1[72]));
        if (interleave > 0xA) rv.m[0xA] = _mm256_loadu_ps(&(q1[80]));
        if (interleave > 0xB) rv.m[0xB] = _mm256_loadu_ps(&(q1[88]));
        if (interleave > 0xC) rv.m[0xC] = _mm256_loadu_ps(&(q1[96]));
        if (interleave > 0xD) rv.m[0xD] = _mm256_loadu_ps(&(q1[104]));
        if (interleave > 0xE) rv.m[0xE] = _mm256_loadu_ps(&(q1[112]));
        if (interleave > 0xF) rv.m[0xF] = _mm256_loadu_ps(&(q1[120]));
        return rv;
    };
    
    // Gather
    template <size_t increment> vforceinline vec_float gather(const float* base_address)
    {
        const __m256i scale_base = _mm256_set_epi32(0x00 * increment,0x01 * increment, 0x02 * increment, 0x03 * increment, 0x04 * increment, 0x05 * increment, 0x06 * increment, 0x07 * increment);
        vec_float rv;
        constexpr int32 inc_f = increment / sizeof(float);
        if (interleave > 0x0) rv.m[0x0] = _mm256_i32gather_ps(base_address + (inc_f * 0x00), scale_base, 1);
        if (interleave > 0x1) rv.m[0x1] = _mm256_i32gather_ps(base_address + (inc_f * 0x08), scale_base, 1);
        if (interleave > 0x2) rv.m[0x2] = _mm256_i32gather_ps(base_address + (inc_f * 0x10), scale_base, 1);
        if (interleave > 0x3) rv.m[0x3] = _mm256_i32gather_ps(base_address + (inc_f * 0x18), scale_base, 1);
        if (interleave > 0x4) rv.m[0x4] = _mm256_i32gather_ps(base_address + (inc_f * 0x20), scale_base, 1);
        if (interleave > 0x5) rv.m[0x5] = _mm256_i32gather_ps(base_address + (inc_f * 0x28), scale_base, 1);
        if (interleave > 0x6) rv.m[0x6] = _mm256_i32gather_ps(base_address + (inc_f * 0x30), scale_base, 1);
        if (interleave > 0x7) rv.m[0x7] = _mm256_i32gather_ps(base_address + (inc_f * 0x38), scale_base, 1);
        if (interleave > 0x8) rv.m[0x8] = _mm256_i32gather_ps(base_address + (inc_f * 0x40), scale_base, 1);
        if (interleave > 0x9) rv.m[0x9] = _mm256_i32gather_ps(base_address + (inc_f * 0x48), scale_base, 1);
        if (interleave > 0xA) rv.m[0xA] = _mm256_i32gather_ps(base_address + (inc_f * 0x50), scale_base, 1);
        if (interleave > 0xB) rv.m[0xB] = _mm256_i32gather_ps(base_address + (inc_f * 0x58), scale_base, 1);
        if (interleave > 0xC) rv.m[0xC] = _mm256_i32gather_ps(base_address + (inc_f * 0x60), scale_base, 1);
        if (interleave > 0xD) rv.m[0xD] = _mm256_i32gather_ps(base_address + (inc_f * 0x68), scale_base, 1);
        if (interleave > 0xE) rv.m[0xE] = _mm256_i32gather_ps(base_address + (inc_f * 0x70), scale_base, 1);
        if (interleave > 0xF) rv.m[0xF] = _mm256_i32gather_ps(base_address + (inc_f * 0x78), scale_base, 1);
        return rv;
    }
    
    
    template <int __N> vforceinline float _mm256_extract_ps (const __m256& __X)
    {
          __m128 __Y = _mm256_extractf128_ps (__X, __N >> 2);
          return _mm_extract_ps (__Y, __N % 4);
    }
    
    template <size_t increment> vforceinline void storeps(const __m256& data, float* e0)
    {
        *(e0 + (increment * 0x00)) = _mm256_extract_ps<0x0>(data);
        *(e0 + (increment * 0x01)) = _mm256_extract_ps<0x1>(data);
        *(e0 + (increment * 0x02)) = _mm256_extract_ps<0x2>(data);
        *(e0 + (increment * 0x03)) = _mm256_extract_ps<0x3>(data);
        *(e0 + (increment * 0x04)) = _mm256_extract_ps<0x4>(data);
        *(e0 + (increment * 0x05)) = _mm256_extract_ps<0x5>(data);
        *(e0 + (increment * 0x06)) = _mm256_extract_ps<0x6>(data);
        *(e0 + (increment * 0x07)) = _mm256_extract_ps<0x7>(data);
    };
    
    // Scatter
    template <size_t increment> vforceinline void scatter(const vec_float& rv, float* base_address)
    {
        constexpr int32 inc_f = increment / sizeof(float);
        if (interleave > 0x0) storeps<inc_f>(rv.m[0x0],  base_address + (inc_f * 0x00));
        if (interleave > 0x1) storeps<inc_f>(rv.m[0x1],  base_address + (inc_f * 0x08));
        if (interleave > 0x2) storeps<inc_f>(rv.m[0x2],  base_address + (inc_f * 0x10));
        if (interleave > 0x3) storeps<inc_f>(rv.m[0x3],  base_address + (inc_f * 0x18));
        if (interleave > 0x4) storeps<inc_f>(rv.m[0x4],  base_address + (inc_f * 0x20));
        if (interleave > 0x5) storeps<inc_f>(rv.m[0x5],  base_address + (inc_f * 0x28));
        if (interleave > 0x6) storeps<inc_f>(rv.m[0x6],  base_address + (inc_f * 0x30));
        if (interleave > 0x7) storeps<inc_f>(rv.m[0x7],  base_address + (inc_f * 0x38));
        if (interleave > 0x8) storeps<inc_f>(rv.m[0x8],  base_address + (inc_f * 0x40));
        if (interleave > 0x9) storeps<inc_f>(rv.m[0x9],  base_address + (inc_f * 0x48));
        if (interleave > 0xA) storeps<inc_f>(rv.m[0xA],  base_address + (inc_f * 0x50));
        if (interleave > 0xB) storeps<inc_f>(rv.m[0xB],  base_address + (inc_f * 0x58));
        if (interleave > 0xC) storeps<inc_f>(rv.m[0xC],  base_address + (inc_f * 0x60));
        if (interleave > 0xD) storeps<inc_f>(rv.m[0xD],  base_address + (inc_f * 0x68));
        if (interleave > 0xE) storeps<inc_f>(rv.m[0xE],  base_address + (inc_f * 0x70));
        if (interleave > 0xF) storeps<inc_f>(rv.m[0xF],  base_address + (inc_f * 0x78));
    };
    
} ALIGN_POST(32);
#endif
