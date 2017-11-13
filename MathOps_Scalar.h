#ifndef MATHOPS_SCALAR_H
#define MATHOPS_SCALAR_H

////////////////////////////////
// File: MathOps_Scalar.h
// Defines math operations for scalar floating point.
// Author: Angus F. Hewlett
// Copyright FXpansion Audio UK Ltd. 2012-2017
////////////////////////////////

#ifndef CEXCOMPILE
#include "MathOps_Common.h"
#endif

template <const int interleave_i> class MathOps_FPU : public MathBase<MathOps_FPU<interleave_i>, float, interleave_i>
{
public:
    static constexpr int raw_num_elem = 1;
    static constexpr int raw_vec_2pow = 0;
    static constexpr int num_elem = interleave_i * raw_num_elem;
    static constexpr int alignment = 4;   
	static constexpr int interleave = interleave_i;
    
    typedef float vec_elem_f;
    typedef int vec_elem_i;
	typedef vf_t<MathOps_FPU, interleave> vf;
    
    ////////////////////////////////
    // Operation classes: set, add, sub, mul, div, min, max, rcp, abs, and, or, andn, xor, not, cmp(ge,gt,le,lt,eq,ne).
	class op_set_f
	{
	public: static vforceinline vec_elem_f op(float a) { return a; };
	};

	class op_add_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b)	{ return a + b;	};
	};

	class op_sub_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b)	{ return a - b; };
	};

	class op_mul_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b)	{ return a * b; };
	};

	class op_div_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return a / b; };
	};

	class op_min_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return std::min<float>(a, b); };
	};

	class op_max_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { return std::max<float>(a, b); };
	};

	class op_rcp_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a) { return 1.f / a; };
	};

	class op_abs_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a) { int32 tmp = (*reinterpret_cast<const int32*>(&a) & 0x7FFFFFFF); return *reinterpret_cast<float*>(&tmp); };
	};

	class op_and_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { int32 tmp = (*reinterpret_cast<const int32*>(&a) & *reinterpret_cast<const int32*>(&b)); return *reinterpret_cast<float*>(&tmp); };
	};

	class op_or_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { int32 tmp = (*reinterpret_cast<const int32*>(&a) | *reinterpret_cast<const int32*>(&b)); return *reinterpret_cast<float*>(&tmp); };
	};

	class op_andn_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { int32 tmp = (*reinterpret_cast<const int32*>(&a) &~*reinterpret_cast<const int32*>(&b)); return *reinterpret_cast<float*>(&tmp); };
	};

	class op_xor_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { int32 tmp = (*reinterpret_cast<const int32*>(&a) ^ *reinterpret_cast<const int32*>(&b)); return *reinterpret_cast<float*>(&tmp); };
	};

	class op_not_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a) { int32 tmp = (*reinterpret_cast<const int32*>(&a) ^ 0xFFFFFFFF); return *reinterpret_cast<float*>(&tmp); };
	};

	class op_cmpge_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { int32 tmp = (a >= b) ? 0xFFFFFFFF : 0; return *reinterpret_cast<float*>(&tmp); };
	};

	class op_cmpgt_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { int32 tmp = (a > b) ? 0xFFFFFFFF : 0; return *reinterpret_cast<float*>(&tmp); };
	};

	class op_cmple_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { int32 tmp = (a <= b) ? 0xFFFFFFFF : 0; return *reinterpret_cast<float*>(&tmp); };
	};

	class op_cmplt_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { int32 tmp = (a < b) ? 0xFFFFFFFF : 0; return *reinterpret_cast<float*>(&tmp); };
	};

	class op_cmpeq_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { int32 tmp = (a == b) ? 0xFFFFFFFF : 0; return *reinterpret_cast<float*>(&tmp); };
	};

	class op_cmpne_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b) { int32 tmp = (a != b) ? 0xFFFFFFFF : 0; return *reinterpret_cast<float*>(&tmp); };
	};

	class op_sub_if_greater_f
	{
	public: static vforceinline vec_elem_f op(const vec_elem_f& a, const vec_elem_f& b, const vec_elem_f& c) 
	{ 
		int32 tmp = (a >= b) ? 0xFFFFFFFF : 0; return a - op_and_f::op(*reinterpret_cast<float*>(&tmp), c); 
	};
	};
             
    ////////////////////////////////
    // Load, gather, scatter

	////////////////////////////////
	// Load
    static vforceinline vf  loadps(const float* q1)
    {
        vf rv;
        if (interleave > 0x0) rv.m[0x0] = q1[0];
        if (interleave > 0x1) rv.m[0x1] = q1[1];
        if (interleave > 0x2) rv.m[0x2] = q1[2];
        if (interleave > 0x3) rv.m[0x3] = q1[3];
        if (interleave > 0x4) rv.m[0x4] = q1[4];
        if (interleave > 0x5) rv.m[0x5] = q1[5];
        if (interleave > 0x6) rv.m[0x6] = q1[6];
        if (interleave > 0x7) rv.m[0x7] = q1[7];
        if (interleave > 0x8) rv.m[0x8] = q1[8];
        if (interleave > 0x9) rv.m[0x9] = q1[9];
        if (interleave > 0xA) rv.m[0xA] = q1[10];
        if (interleave > 0xB) rv.m[0xB] = q1[11];
        if (interleave > 0xC) rv.m[0xC] = q1[12];
        if (interleave > 0xD) rv.m[0xD] = q1[13];
        if (interleave > 0xE) rv.m[0xE] = q1[14];
        if (interleave > 0xF) rv.m[0xF] = q1[15];
        return rv;
    };
    
	////////////////////////////////
	// Gather with known stride
    template <size_t increment> vforceinline vf gather(const float* base_address)
    {
        vf rv;
        if (interleave > 0x0) rv.m[0x0] = *(base_address + ((increment * 0x00)/ sizeof(float)));
        if (interleave > 0x1) rv.m[0x1] = *(base_address + ((increment * 0x01)/ sizeof(float)));
        if (interleave > 0x2) rv.m[0x2] = *(base_address + ((increment * 0x02)/ sizeof(float)));
        if (interleave > 0x3) rv.m[0x3] = *(base_address + ((increment * 0x03)/ sizeof(float)));
        if (interleave > 0x4) rv.m[0x4] = *(base_address + ((increment * 0x04)/ sizeof(float)));
        if (interleave > 0x5) rv.m[0x5] = *(base_address + ((increment * 0x05)/ sizeof(float)));
        if (interleave > 0x6) rv.m[0x6] = *(base_address + ((increment * 0x06)/ sizeof(float)));
        if (interleave > 0x7) rv.m[0x7] = *(base_address + ((increment * 0x07)/ sizeof(float)));
        if (interleave > 0x8) rv.m[0x8] = *(base_address + ((increment * 0x08)/ sizeof(float)));
        if (interleave > 0x9) rv.m[0x9] = *(base_address + ((increment * 0x09)/ sizeof(float)));
        if (interleave > 0xA) rv.m[0xA] = *(base_address + ((increment * 0x0A)/ sizeof(float)));
        if (interleave > 0xB) rv.m[0xB] = *(base_address + ((increment * 0x0B)/ sizeof(float)));
        if (interleave > 0xC) rv.m[0xC] = *(base_address + ((increment * 0x0C)/ sizeof(float)));
        if (interleave > 0xD) rv.m[0xD] = *(base_address + ((increment * 0x0D)/ sizeof(float)));
        if (interleave > 0xE) rv.m[0xE] = *(base_address + ((increment * 0x0E)/ sizeof(float)));
        if (interleave > 0xF) rv.m[0xF] = *(base_address + ((increment * 0x0F)/ sizeof(float)));
        return rv;
    }
    
	////////////////////////////////
	// Scatter with known stride
    template <size_t increment> vforceinline void scatter(const vf& rv, float* base_address)
    {
        if (interleave > 0x0) *(base_address + ((increment * 0x00)/ sizeof(float))) = rv.m[0x0];
        if (interleave > 0x1) *(base_address + ((increment * 0x01)/ sizeof(float))) = rv.m[0x1];
        if (interleave > 0x2) *(base_address + ((increment * 0x02)/ sizeof(float))) = rv.m[0x2];
        if (interleave > 0x3) *(base_address + ((increment * 0x03)/ sizeof(float))) = rv.m[0x3];
        if (interleave > 0x4) *(base_address + ((increment * 0x04)/ sizeof(float))) = rv.m[0x4];
        if (interleave > 0x5) *(base_address + ((increment * 0x05)/ sizeof(float))) = rv.m[0x5];
        if (interleave > 0x6) *(base_address + ((increment * 0x06)/ sizeof(float))) = rv.m[0x6];
        if (interleave > 0x7) *(base_address + ((increment * 0x07)/ sizeof(float))) = rv.m[0x7];
        if (interleave > 0x8) *(base_address + ((increment * 0x08)/ sizeof(float))) = rv.m[0x8];
        if (interleave > 0x9) *(base_address + ((increment * 0x09)/ sizeof(float))) = rv.m[0x9];
        if (interleave > 0xA) *(base_address + ((increment * 0x0A)/ sizeof(float))) = rv.m[0xA];
        if (interleave > 0xB) *(base_address + ((increment * 0x0B)/ sizeof(float))) = rv.m[0xB];
        if (interleave > 0xC) *(base_address + ((increment * 0x0C)/ sizeof(float))) = rv.m[0xC];
        if (interleave > 0xD) *(base_address + ((increment * 0x0D)/ sizeof(float))) = rv.m[0xD];
        if (interleave > 0xE) *(base_address + ((increment * 0x0E)/ sizeof(float))) = rv.m[0xE];
        if (interleave > 0xF) *(base_address + ((increment * 0x0F)/ sizeof(float))) = rv.m[0xF];
    }        
};

#endif
