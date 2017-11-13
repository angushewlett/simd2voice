#ifndef MATHOPS_SSE_H
#define MATHOPS_SSE_H

////////////////////////////////
// File: MathOps_SSE.h
// Defines math operations for SSE SIMD floating point.
// Author: Angus F. Hewlett
// Copyright FXpansion Audio UK Ltd. 2012-2017
////////////////////////////////

#ifndef CEXCOMPILE
#include "MathOps_Common.h"
#endif
#include <xmmintrin.h>
#include <emmintrin.h>

template <const int interleave_i> class MathOps_SSE_v : public MathBase<MathOps_SSE_v<interleave_i>, __m128, interleave_i>
{
public:
    static constexpr int raw_num_elem = 4;
    static constexpr int raw_vec_2pow = 2;
    static constexpr int num_elem = interleave_i * raw_num_elem;
    static constexpr int alignment = 16;
	static constexpr int interleave = interleave_i;

    typedef ALIGN_PRE(16) __m128 vec_elem_f ALIGN_POST(16);
    typedef ALIGN_PRE(16) __m128i vec_elem_i ALIGN_POST(16);
	typedef ALIGN_PRE(16) vf_t<MathOps_SSE_v, interleave> vf ALIGN_POST(16);
    
    ////////////////////////////////
    // Operation classes: set, add, sub, mul, div, min, max, rcp, abs, and, or, andn, xor, not, cmp(ge,gt,le,lt,eq,ne).
	class op_set_f
	{
	public: static vforceinline vec_elem_f op(float a) { return _mm_set1_ps(a); };
	};

	class op_add_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm_add_ps(a , b); };
	};

	class op_sub_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm_sub_ps(a , b); };
	};

	class op_mul_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm_mul_ps(a, b); };
	};

	class op_div_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm_div_ps(a, b); };
	};

	class op_min_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm_min_ps(a , b); };
	};

	class op_max_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm_max_ps(a, b); };
	};

	class op_rcp_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a) { return _mm_rcp_ps(a); };
	};

	class op_abs_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a) { const int32 mask = 0x7FFFFFFF; return  _mm_and_ps(a, _mm_set1_ps(mask)); };
	};

	class op_and_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm_and_ps(a, b); };
	};

	class op_or_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm_or_ps(a, b); };
	};

	class op_andn_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm_andnot_ps(a, b); };
	};

	class op_xor_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm_xor_ps(a, b); };
	};

	class op_not_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a) { return _mm_xor_ps(a, _mm_set1_epi32(0xFFFFFFFF)); };
	};

	class op_cmpge_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm_cmpge_ps(a,b); };
	};

	class op_cmpgt_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm_cmpgt_ps(a,b); };
	};

	class op_cmple_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm_cmple_ps(a,b); };
	};

	class op_cmplt_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm_cmplt_ps(a,b); };
	};

	class op_cmpeq_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm_cmpeq_ps(a,b); };
	};

	class op_cmpne_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return _mm_cmpneq_ps(a,b); };
	};
        class op_sub_if_greater_f
        {
        public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b, const vec_elem_f& c) 
                {
                        vec_elem_f k = _mm_cmpge_ps(a, b); 
                        return _mm_sub_ps(a,_mm_and_ps(k, c)); 
                };
        };             
    ////////////////////////////////
    // Load, gather, scatter

    // Load
    static vforceinline vf  loadps(const float* q1)
    {
        vf rv;
        if (interleave > 0x0) rv.m[0x0] = _mm_loadu_ps(&(q1[0]));
        if (interleave > 0x1) rv.m[0x1] = _mm_loadu_ps(&(q1[4]));
        if (interleave > 0x2) rv.m[0x2] = _mm_loadu_ps(&(q1[8]));
        if (interleave > 0x3) rv.m[0x3] = _mm_loadu_ps(&(q1[12]));
        if (interleave > 0x4) rv.m[0x4] = _mm_loadu_ps(&(q1[16]));
        if (interleave > 0x5) rv.m[0x5] = _mm_loadu_ps(&(q1[20]));
        if (interleave > 0x6) rv.m[0x6] = _mm_loadu_ps(&(q1[24]));
        if (interleave > 0x7) rv.m[0x7] = _mm_loadu_ps(&(q1[28]));
        if (interleave > 0x8) rv.m[0x8] = _mm_loadu_ps(&(q1[32]));
        if (interleave > 0x9) rv.m[0x9] = _mm_loadu_ps(&(q1[36]));
        if (interleave > 0xA) rv.m[0xA] = _mm_loadu_ps(&(q1[40]));
        if (interleave > 0xB) rv.m[0xB] = _mm_loadu_ps(&(q1[44]));
        if (interleave > 0xC) rv.m[0xC] = _mm_loadu_ps(&(q1[48]));
        if (interleave > 0xD) rv.m[0xD] = _mm_loadu_ps(&(q1[52]));
        if (interleave > 0xE) rv.m[0xE] = _mm_loadu_ps(&(q1[56]));
        if (interleave > 0xF) rv.m[0xF] = _mm_loadu_ps(&(q1[60]));
        return rv;
    };
    
    // Gather
    template <size_t increment> vforceinline vf gather(const float* base_address)
    {
        vf rv;
        int32 fc = increment / sizeof(float);
        const float* ba = base_address;
        
        if (interleave > 0x0) rv.m[0x0] = _mm_set_ps(*(ba + (fc * 0x00)), *(ba + (fc * 0x01)), *(ba + (fc * 0x02)), *(ba + (fc * 0x03)));
        if (interleave > 0x1) rv.m[0x1] = _mm_set_ps(*(ba + (fc * 0x04)), *(ba + (fc * 0x05)), *(ba + (fc * 0x06)), *(ba + (fc * 0x07)));
        if (interleave > 0x2) rv.m[0x2] = _mm_set_ps(*(ba + (fc * 0x08)), *(ba + (fc * 0x09)), *(ba + (fc * 0x0A)), *(ba + (fc * 0x0B)));
        if (interleave > 0x3) rv.m[0x3] = _mm_set_ps(*(ba + (fc * 0x0C)), *(ba + (fc * 0x0D)), *(ba + (fc * 0x0E)), *(ba + (fc * 0x0F)));

        if (interleave > 0x4) rv.m[0x4] = _mm_set_ps(*(ba + (fc * 0x10)), *(ba + (fc * 0x11)), *(ba + (fc * 0x12)), *(ba + (fc * 0x13)));
        if (interleave > 0x5) rv.m[0x5] = _mm_set_ps(*(ba + (fc * 0x14)), *(ba + (fc * 0x15)), *(ba + (fc * 0x16)), *(ba + (fc * 0x17)));
        if (interleave > 0x6) rv.m[0x6] = _mm_set_ps(*(ba + (fc * 0x18)), *(ba + (fc * 0x19)), *(ba + (fc * 0x1A)), *(ba + (fc * 0x1B)));
        if (interleave > 0x7) rv.m[0x7] = _mm_set_ps(*(ba + (fc * 0x1C)), *(ba + (fc * 0x1D)), *(ba + (fc * 0x1E)), *(ba + (fc * 0x1F)));

        if (interleave > 0x8) rv.m[0x8] = _mm_set_ps(*(ba + (fc * 0x20)), *(ba + (fc * 0x21)), *(ba + (fc * 0x22)), *(ba + (fc * 0x23)));
        if (interleave > 0x9) rv.m[0x9] = _mm_set_ps(*(ba + (fc * 0x24)), *(ba + (fc * 0x25)), *(ba + (fc * 0x26)), *(ba + (fc * 0x27)));
        if (interleave > 0xA) rv.m[0xA] = _mm_set_ps(*(ba + (fc * 0x28)), *(ba + (fc * 0x29)), *(ba + (fc * 0x2A)), *(ba + (fc * 0x2B)));
        if (interleave > 0xB) rv.m[0xB] = _mm_set_ps(*(ba + (fc * 0x2C)), *(ba + (fc * 0x2D)), *(ba + (fc * 0x2E)), *(ba + (fc * 0x2F)));

        if (interleave > 0xC) rv.m[0xC] = _mm_set_ps(*(ba + (fc * 0x30)), *(ba + (fc * 0x31)), *(ba + (fc * 0x32)), *(ba + (fc * 0x33)));
        if (interleave > 0xD) rv.m[0xD] = _mm_set_ps(*(ba + (fc * 0x34)), *(ba + (fc * 0x35)), *(ba + (fc * 0x36)), *(ba + (fc * 0x37)));
        if (interleave > 0xE) rv.m[0xE] = _mm_set_ps(*(ba + (fc * 0x38)), *(ba + (fc * 0x39)), *(ba + (fc * 0x3A)), *(ba + (fc * 0x3B)));
        if (interleave > 0xF) rv.m[0xF] = _mm_set_ps(*(ba + (fc * 0x3C)), *(ba + (fc * 0x3D)), *(ba + (fc * 0x3E)), *(ba + (fc * 0x3F)));
        
        return rv;
    }
    
    // Scatter helpers
    struct aligned_f
    {
        float data[4];
	} ALIGN_POST(16);
    
    vforceinline void mystore_ps(const __m128& data, float& a, float& b, float& c, float& d)
    {
        aligned_f x;
        _mm_store_ps(&x.data[0], data);
        a = x.data[0];
        b = x.data[1];
        c = x.data[2];
        d = x.data[3];
    }
    
    // Scatter
    template <size_t increment> vforceinline void scatter(const vf& rv, float* base_address)
    {
        //        printf("%d\n", (const int32)increment);
        int32 fc = increment / sizeof(float);
        float* ba = base_address;
        
        if (interleave > 0x0) mystore_ps(rv.m[0x0], *(ba + (fc * 0x00)), *(ba + (fc * 0x01)), *(ba + (fc * 0x02)), *(ba + (fc * 0x03)));
        if (interleave > 0x1) mystore_ps(rv.m[0x1], *(ba + (fc * 0x04)), *(ba + (fc * 0x05)), *(ba + (fc * 0x06)), *(ba + (fc * 0x07)));
        if (interleave > 0x2) mystore_ps(rv.m[0x2], *(ba + (fc * 0x08)), *(ba + (fc * 0x09)), *(ba + (fc * 0x0A)), *(ba + (fc * 0x0B)));
        if (interleave > 0x3) mystore_ps(rv.m[0x3], *(ba + (fc * 0x0C)), *(ba + (fc * 0x0D)), *(ba + (fc * 0x0E)), *(ba + (fc * 0x0F)));
        
        if (interleave > 0x4) mystore_ps(rv.m[0x4], *(ba + (fc * 0x10)), *(ba + (fc * 0x11)), *(ba + (fc * 0x12)), *(ba + (fc * 0x13)));
        if (interleave > 0x5) mystore_ps(rv.m[0x5], *(ba + (fc * 0x14)), *(ba + (fc * 0x15)), *(ba + (fc * 0x16)), *(ba + (fc * 0x17)));
        if (interleave > 0x6) mystore_ps(rv.m[0x6], *(ba + (fc * 0x18)), *(ba + (fc * 0x19)), *(ba + (fc * 0x1A)), *(ba + (fc * 0x1B)));
        if (interleave > 0x7) mystore_ps(rv.m[0x7], *(ba + (fc * 0x1C)), *(ba + (fc * 0x1D)), *(ba + (fc * 0x1E)), *(ba + (fc * 0x1F)));
        
        if (interleave > 0x8) mystore_ps(rv.m[0x8], *(ba + (fc * 0x20)), *(ba + (fc * 0x21)), *(ba + (fc * 0x22)), *(ba + (fc * 0x23)));
        if (interleave > 0x9) mystore_ps(rv.m[0x9], *(ba + (fc * 0x24)), *(ba + (fc * 0x25)), *(ba + (fc * 0x26)), *(ba + (fc * 0x27)));
        if (interleave > 0xA) mystore_ps(rv.m[0xA], *(ba + (fc * 0x28)), *(ba + (fc * 0x29)), *(ba + (fc * 0x2A)), *(ba + (fc * 0x2B)));
        if (interleave > 0xB) mystore_ps(rv.m[0xB], *(ba + (fc * 0x2C)), *(ba + (fc * 0x2D)), *(ba + (fc * 0x2E)), *(ba + (fc * 0x2F)));
        
        if (interleave > 0xC) mystore_ps(rv.m[0xC], *(ba + (fc * 0x30)), *(ba + (fc * 0x31)), *(ba + (fc * 0x32)), *(ba + (fc * 0x33)));
        if (interleave > 0xD) mystore_ps(rv.m[0xD], *(ba + (fc * 0x34)), *(ba + (fc * 0x35)), *(ba + (fc * 0x36)), *(ba + (fc * 0x37)));
        if (interleave > 0xE) mystore_ps(rv.m[0xE], *(ba + (fc * 0x38)), *(ba + (fc * 0x39)), *(ba + (fc * 0x3A)), *(ba + (fc * 0x3B)));
        if (interleave > 0xF) mystore_ps(rv.m[0xF], *(ba + (fc * 0x3C)), *(ba + (fc * 0x3D)), *(ba + (fc * 0x3E)), *(ba + (fc * 0x3F)));
    };	
};

#endif
