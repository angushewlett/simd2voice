#ifndef MATHOPS_NEON_H
#define MATHOPS_NEON_H

////////////////////////////////
// File: MathOps_NEON.h
// Defines math operations for ARM NEON SIMD floating point.
// Author: Angus F. Hewlett
// Copyright FXpansion Audio UK Ltd. 2012-2017
////////////////////////////////

#ifndef CEXCOMPILE
#include "MathOps_Common.h"
#endif
#include <arm_neon.h>

#if TARGET_OS_IPHONE || ANDROID
#define vrndqm_f32 vrndmq_f32
#define vrndqn_f32 vrndnq_f32
#endif

template <const int interleave_i> class MathOps_NEON : public MathBase<MathOps_NEON<interleave_i>, float32x4_t, interleave_i>
{
public:
    static constexpr int raw_vec_elem = 4;
    static constexpr int raw_vec_2pow = 2;
    static constexpr int vec_elem = interleave_i * raw_vec_elem;
    static constexpr int alignment = 16;
	static constexpr int interleave = interleave_i;

    typedef float32x4_t vec_elem_t;
	typedef int32x4_t vec_int_t;
	typedef vf_t<MathOps_NEON, interleave> vec_float;
    
    ////////////////////////////////
    // Operation classes: set, add, sub, mul, div, min, max, rcp, abs, and, or, andn, xor, not, cmp(ge,gt,le,lt,eq,ne).
	class op_set_f
	{
	public: static vforceinline vec_elem_t op(float a) { return vld1q_dup_f32(&a); };
	};

	class op_add_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return vaddq_f32(a , b); };
	};

	class op_sub_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return vsubq_f32(a , b); };
	};

	class op_mul_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return vmulq_f32(a, b); };
	};

	class op_div_f
	{
	public:
		static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) 
		{
        	// ARM doesn't have divide - we calculate the reciprocal and then multiply.
	        float32x4_t reciprocal = vrecpeq_f32(b);
	        float32x4_t inverse = vmulq_f32(vrecpsq_f32(b, reciprocal), reciprocal);
	        return vmulq_f32(inverse, a);        
		};
	};

	class op_min_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return vminq_f32(a , b); };
	};

	class op_max_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return vmaxq_f32(a, b); };
	};

	class op_rcp_f
	{
	public:
		static vforceinline vec_elem_t op(const vec_elem_t& a) 
		{
            float32x4_t recp = vrecpeq_f32(a);
            recp = vmulq_f32(vrecpsq_f32(a, recp), recp);
			return recp;	
		};
	};

	class op_abs_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a) { return  vabsq_f32(a); };
	};

	class op_and_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return vreinterpretq_f32_u32(vandq_u32(vreinterpretq_u32_f32(a), vreinterpretq_u32_f32(b))); };
	};

	class op_or_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return vreinterpretq_f32_u32(vorrq_u32(vreinterpretq_u32_f32(a), vreinterpretq_u32_f32(b))); };
	};

	class op_andn_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return op_and_f::op(op_not_f::op(a), b); };
	};

	class op_xor_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return vreinterpretq_f32_u32(veorq_u32(vreinterpretq_u32_f32(a), vreinterpretq_u32_f32(b))); };
	};

	class op_not_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a) { return vreinterpretq_f32_u32(vmvnq_u32(vreinterpretq_u32_f32(a))); };
	};

	class op_cmpge_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return vreinterpretq_f32_u32(vcgeq_f32(a,b)); };
	};

	class op_cmpgt_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return vreinterpretq_f32_u32(vcgtq_f32(a,b)); };
	};

	class op_cmple_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return vreinterpretq_f32_u32(vcleq_f32(a,b)); };
	};

	class op_cmplt_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return vreinterpretq_f32_u32(vcltq_f32(a,b)); };
	};

	class op_cmpeq_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return vreinterpretq_f32_u32(vceqq_f32(a,b)); };
	};

	class op_cmpne_f
	{
	public: static vforceinline vec_elem_t op(const vec_elem_t& a, const vec_elem_t& b) { return op_not_f::op(op_cmpeq_f::op(a,b)); };
	};
             
    ////////////////////////////////
    // Load, gather, scatter

    // Load    
    static vforceinline vec_float loadps(const float* q1)
    {
        vec_float rv;
        if (interleave > 0x0) rv.m[0x0] = *(float32x4_t*)(&(q1[0]));
        if (interleave > 0x1) rv.m[0x1] = *(float32x4_t*)(&(q1[4]));
        if (interleave > 0x2) rv.m[0x2] = *(float32x4_t*)(&(q1[8]));
        if (interleave > 0x3) rv.m[0x3] = *(float32x4_t*)(&(q1[12]));
        if (interleave > 0x4) rv.m[0x4] = *(float32x4_t*)(&(q1[16]));
        if (interleave > 0x5) rv.m[0x5] = *(float32x4_t*)(&(q1[20]));
        if (interleave > 0x6) rv.m[0x6] = *(float32x4_t*)(&(q1[24]));
        if (interleave > 0x7) rv.m[0x7] = *(float32x4_t*)(&(q1[28]));
        if (interleave > 0x8) rv.m[0x8] = *(float32x4_t*)(&(q1[32]));
        if (interleave > 0x9) rv.m[0x9] = *(float32x4_t*)(&(q1[36]));
        if (interleave > 0xA) rv.m[0xA] = *(float32x4_t*)(&(q1[40]));
        if (interleave > 0xB) rv.m[0xB] = *(float32x4_t*)(&(q1[44]));
        if (interleave > 0xC) rv.m[0xC] = *(float32x4_t*)(&(q1[48]));
        if (interleave > 0xD) rv.m[0xD] = *(float32x4_t*)(&(q1[52]));
        if (interleave > 0xE) rv.m[0xE] = *(float32x4_t*)(&(q1[56]));
        if (interleave > 0xF) rv.m[0xF] = *(float32x4_t*)(&(q1[60]));
        return rv;
    };       
    // Scatter / Gather helpers
    struct aligned_f
    {
        float data[4];
	} ALIGN_POST(16);
	
    vforceinline void myload_ps(float32x4_t& data, const float& a, const float& b, const float& c, const float& d)
    {
        aligned_f x;
        x.data[0] = a;
        x.data[1] = b;
        x.data[2] = c;
        x.data[3] = d;		
        data = vld1q_f32(&x.data[0]);
    };
	
    vforceinline void mystore_ps(const float32x4_t& data, float& a, float& b, float& c, float& d)
    {
        aligned_f x;
        vst1q_f32(&x.data[0], data);
        a = x.data[0];
        b = x.data[1];
        c = x.data[2];
        d = x.data[3];
    };

    // Gather
    template <size_t increment> vforceinline vec_float gather(const float* base_address)
    {
        vec_float rv;
        int32 fc = increment / sizeof(float);
        const float* ba = base_address;
        
        if (interleave > 0x0) rv.m[0x0] = myload_ps(*(ba + (fc * 0x00)), *(ba + (fc * 0x01)), *(ba + (fc * 0x02)), *(ba + (fc * 0x03)));
        if (interleave > 0x1) rv.m[0x1] = myload_ps(*(ba + (fc * 0x04)), *(ba + (fc * 0x05)), *(ba + (fc * 0x06)), *(ba + (fc * 0x07)));
        if (interleave > 0x2) rv.m[0x2] = myload_ps(*(ba + (fc * 0x08)), *(ba + (fc * 0x09)), *(ba + (fc * 0x0A)), *(ba + (fc * 0x0B)));
        if (interleave > 0x3) rv.m[0x3] = myload_ps(*(ba + (fc * 0x0C)), *(ba + (fc * 0x0D)), *(ba + (fc * 0x0E)), *(ba + (fc * 0x0F)));

        if (interleave > 0x4) rv.m[0x4] = myload_ps(*(ba + (fc * 0x10)), *(ba + (fc * 0x11)), *(ba + (fc * 0x12)), *(ba + (fc * 0x13)));
        if (interleave > 0x5) rv.m[0x5] = myload_ps(*(ba + (fc * 0x14)), *(ba + (fc * 0x15)), *(ba + (fc * 0x16)), *(ba + (fc * 0x17)));
        if (interleave > 0x6) rv.m[0x6] = myload_ps(*(ba + (fc * 0x18)), *(ba + (fc * 0x19)), *(ba + (fc * 0x1A)), *(ba + (fc * 0x1B)));
        if (interleave > 0x7) rv.m[0x7] = myload_ps(*(ba + (fc * 0x1C)), *(ba + (fc * 0x1D)), *(ba + (fc * 0x1E)), *(ba + (fc * 0x1F)));

        if (interleave > 0x8) rv.m[0x8] = myload_ps(*(ba + (fc * 0x20)), *(ba + (fc * 0x21)), *(ba + (fc * 0x22)), *(ba + (fc * 0x23)));
        if (interleave > 0x9) rv.m[0x9] = myload_ps(*(ba + (fc * 0x24)), *(ba + (fc * 0x25)), *(ba + (fc * 0x26)), *(ba + (fc * 0x27)));
        if (interleave > 0xA) rv.m[0xA] = myload_ps(*(ba + (fc * 0x28)), *(ba + (fc * 0x29)), *(ba + (fc * 0x2A)), *(ba + (fc * 0x2B)));
        if (interleave > 0xB) rv.m[0xB] = myload_ps(*(ba + (fc * 0x2C)), *(ba + (fc * 0x2D)), *(ba + (fc * 0x2E)), *(ba + (fc * 0x2F)));

        if (interleave > 0xC) rv.m[0xC] = myload_ps(*(ba + (fc * 0x30)), *(ba + (fc * 0x31)), *(ba + (fc * 0x32)), *(ba + (fc * 0x33)));
        if (interleave > 0xD) rv.m[0xD] = myload_ps(*(ba + (fc * 0x34)), *(ba + (fc * 0x35)), *(ba + (fc * 0x36)), *(ba + (fc * 0x37)));
        if (interleave > 0xE) rv.m[0xE] = myload_ps(*(ba + (fc * 0x38)), *(ba + (fc * 0x39)), *(ba + (fc * 0x3A)), *(ba + (fc * 0x3B)));
        if (interleave > 0xF) rv.m[0xF] = myload_ps(*(ba + (fc * 0x3C)), *(ba + (fc * 0x3D)), *(ba + (fc * 0x3E)), *(ba + (fc * 0x3F)));
        
        return rv;
    }
	
    
    // Scatter
    template <size_t increment> vforceinline vec_float scatter(const vec_float& rv, float* base_address)
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
        
        return rv;
    };	
    // These need reinterpret-casts on their input and output operands on ARM
	// GENERATE_INTERLEAVED_FUNCTION_2ARG_III(orps,  vorrq_u32);   
	// GENERATE_INTERLEAVED_FUNCTION_2ARG_IFF(cmpgeps, vcgeq_f32);
};

#endif
