#ifndef MATHOPS_SSE_X4_H
#define MATHOPS_SSE_X4_H

///////////////////////////////////
// Math ops for 4-way SSE code
// Author: Angus F. Hewlett
// Copyright FXpansion Audio UK Ltd. 2012
///////////////////////////////////

////////////////////////////////
// This file provides:-
// * Typedefs for n-way SSE (4x32) containers
// ** interleave amount configured by template parameter - can be any power of 2
// ** vec_float & vec_int - float32 and int32 respectively
// * copy constructors, assignment and basic math operators for those containers
// * General intrinsic-function-style math operations for 4-way SSE data ("addps()" etc.) operating on vec_float & vec_int types
// ** (as static functions in Mathops_SSExN class - inherit to win)
// * typedefs / conversion routines for packing/unpacking to plain vectors of floats/ints
////////////////////////////////

#ifndef MATHOPS_SSE_SSE41
#error Need to select SSE2 or SSE4 by defining MATHOPS_SSE_SSE41 to 0 or 1
#endif

#include <emmintrin.h>
#if MATHOPS_SSE_SSE41
#include <smmintrin.h>
#endif

#ifndef CEXCOMPILE
#include "MathOps_Common.h"
#endif

#if (_MSC_VER || __ICC) // MS compiler allows direct access to union members
#define VECPRE16 __declspec(align(16))
#define VECPOST16
#else
#define VECPRE16
#define VECPOST16 __attribute__ ((aligned(16)))
#endif
#undef VECPRE_NATIVE
#undef VECPOST_NATIVE
#define VECPRE_NATIVE VECPRE16
#define VECPOST_NATIVE VECPOST16

#define generic_addps _mm_add_ps
#define generic_mulps _mm_mul_ps
#define generic_subps _mm_sub_ps


///////////////////////////////////////////////////////////////////////////////////////////////////
// class Mathops_SSExN
// Math operations for interleaved N-way SSE data
///////////////////////////////////////////////////////////////////////////////////////////////////
template <int intrlv> class MathOps
{
public:
	static const int raw_vec_elem = 4;		// elements in an SSE vector
	static const int raw_vec_2pow = 2;		// power of 2 for an SSE vector
	static const int interleave = intrlv;	// number of vectors to interleave
	static const int32 vec_elem = interleave * raw_vec_elem;	// total number of elements
	typedef __m128 vec_unaligned_float;
	typedef __m128i vec_unaligned_int;
	typedef __m128d vec_unaligned_double;

	typedef VECPRE16 vec_unaligned_float vec_float_t VECPOST16;
	typedef VECPRE16 vec_unaligned_int vec_int_t VECPOST16;
	typedef VECPRE16 vec_unaligned_double vec_double_t VECPOST16;

	union vec { vec_float_t sse; float f[4]; };

	template<int32 index> static float accessmember(vec_float_t v)
	{
		vec ve;
		ve.sse = v;
		return ve.f[index];
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Vector float type - class vec_float
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////
	class VECPRE16 vec_float
	{
	public:
		vec_float_t m[interleave];
		// Default ctor doesn't initialize. standard c++.
		vforceinline vec_float() {};

		////////////////////////////////
		// Copy constructors and assignment operators
		// Can take:- another vec_float, a single vec_float_t element which is copied to all, a single float copied to all.
		vforceinline vec_float(const vec_float& f) { *this = f; };
		vforceinline vec_float(const vec_float_t(&f)[interleave]) { *this = f; };
		vforceinline vec_float(const float& f) { *this = f; };

		vforceinline vec_float& operator=(const vec_float& f)
		{
//			INTERLEAVED_INDEX_ASSIGN_T(m, f.m);
#pragma unroll(intrlv)
            for (int32 i = 0; i < intrlv; i++) m[i] = f.m[i];
			return *this;
		};
		vforceinline vec_float& operator=(const vec_float_t(&f)[interleave])
		{
			INTERLEAVED_INDEX_ASSIGN_T(m, f);
			return *this;
		};

		vforceinline vec_float& operator=(const float f)
		{
			INTERLEAVED_SINGLE_ASSIGN((*this), _mm_set1_ps(f));
			return *this;
		};

		////////////////////////////////
		// Basic maths: +,-,* (no divide, it's slow. if you want divide, figure out a faster way).
		vforceinline vec_float  operator+(const vec_float& m2) const
		{
			return addps(*this, m2);
		};
		vforceinline vec_float  operator-(const vec_float& m2) const
		{
			return subps(*this, m2);
		};
		vforceinline vec_float  operator*(const vec_float& m2) const
		{
			return 	mulps(*this, m2);
		};

		vforceinline vec_float  operator>(const vec_float& m2) const
		{
			return 	cmpgtps(*this, m2);
		};

		vforceinline vec_float  operator>=(const vec_float& m2) const
		{
			return 	cmpgeps(*this, m2);
		};

		vforceinline vec_float  operator<(const vec_float& m2) const
		{
			return 	cmpltps(*this, m2);
		};

		vforceinline vec_float  operator<=(const vec_float& m2) const
		{
			return 	cmpleps(*this, m2);
		};

		vforceinline vec_float  operator==(const vec_float& m2) const
		{
			return 	cmpeqps(*this, m2);
		};

		vforceinline vec_float  operator!=(const vec_float& m2) const
		{
			return 	cmpneps(*this, m2);
		};

		vforceinline vec_float  operator&(const vec_float& m2) const
		{
			return 	andps(*this, m2);
		};

		vforceinline vec_float& operator!() const
		{
			return notps(*this);
		};

		////////////////////////////////
		// In-place maths: +,-,* with assignment, vector versions.
		vforceinline vec_float& operator+=(const vec_float& f)
		{
			*this = addps(*this, f);
			return *this;
		};
		vforceinline vec_float& operator-=(const vec_float& f)
		{
			*this = subps(*this, f);
			return *this;
		};
		vforceinline vec_float& operator*=(const vec_float& f)
		{
			*this = mulps(*this, f);
			return *this;
		};

		////////////////////////////////
		// In-place maths: +,-,* with assignment, scalar constant versions
		vforceinline vec_float& operator+=(const float f)
		{
			vec_float tmp_f;
			INTERLEAVED_SINGLE_ASSIGN(tmp_f, _mm_set1_ps(f));
			*this = addps(*this, tmp_f);
			return *this;
		};
		vforceinline vec_float& operator-=(const float f)
		{
			vec_float tmp_f;
			INTERLEAVED_SINGLE_ASSIGN(tmp_f, _mm_set1_ps(f));
			*this = subps(*this, tmp_f);
			return *this;
		};
		vforceinline vec_float& operator*=(const float f)
		{
			vec_float tmp_f;
			INTERLEAVED_SINGLE_ASSIGN(tmp_f, _mm_set1_ps(f));
			*this = mulps(*this, tmp_f);
			return *this;
		};


		////////////////////////////////
		// In-place clip functions: with vector bounds, with scalar const bounds, with input & vector bounds, with input & scalar const bounds
		vforceinline void clip(const vec_float& lo_lim, const vec_float& hi_lim)
		{
			vec_float tmp_f;
			INTERLEAVED_UNROLL_2(tmp_f, _mm_min_ps, (*this), hi_lim);
			INTERLEAVED_UNROLL_2((*this), _mm_max_ps, tmp_f, lo_lim);
		};

		vforceinline void clip(const float lo_lim, const float hi_lim)
		{
			vec_float hi_lim_v = hi_lim;
			vec_float lo_lim_v = lo_lim;
			vec_float tmp_f;
			INTERLEAVED_UNROLL_2(tmp_f, _mm_min_ps, (*this), hi_lim_v);
			INTERLEAVED_UNROLL_2((*this), _mm_max_ps, tmp_f, lo_lim_v);
		};
		vforceinline void clip_v(const vec_float& val, const vec_float& lo_lim, const vec_float& hi_lim)
		{
			vec_float tmp_f;
			INTERLEAVED_UNROLL_2(tmp_f, _mm_min_ps, val, hi_lim);
			INTERLEAVED_UNROLL_2((*this), _mm_max_ps, tmp_f, lo_lim);
		};
		vforceinline void clip_v(const vec_float& val, const float lo_lim, const float hi_lim)
		{
			vec_float hi_lim_v = hi_lim;
			vec_float lo_lim_v = lo_lim;
			vec_float tmp_f;
			INTERLEAVED_UNROLL_2(tmp_f, _mm_min_ps, val, hi_lim_v);
			INTERLEAVED_UNROLL_2((*this), _mm_max_ps, tmp_f, lo_lim_v);
		};

		////////////////////////////////
		// Apply a function, func ptr or lambda to each element, returning a result. Slow, but convenient
		template<typename Func> vec_float forEachElement(Func func)
		{
			vec_float result;
			for (int i = 0; i < interleave; i++) {
				vec_union_f tmp;
				// unpack to temp
				get_union_f(*this, tmp);
				for (int j = 0; j < raw_vec_elem; j++) {
					tmp.f[(i * raw_vec_elem) + j] = func(tmp.f[(i * raw_vec_elem) + j]);
				}
				m[i] = tmp.m[i];
			}
			return result;
		};

#if MATHOPS_SSE_SSE41
		vforceinline float horizontal_add()
		{
			vec_float_t result = m[0];
			if (intrlv > 1) result = _mm_add_ps(result, m[1]);
			if (intrlv > 2) result = _mm_add_ps(result, m[2]);
			if (intrlv > 3) result = _mm_add_ps(result, m[3]);
			if (intrlv > 4) result = _mm_add_ps(result, m[4]);
			if (intrlv > 5) result = _mm_add_ps(result, m[5]);
			if (intrlv > 6) result = _mm_add_ps(result, m[6]);
			if (intrlv > 7) result = _mm_add_ps(result, m[7]);
			result = _mm_hadd_ps(result, result); // first horizontal summing
			result = _mm_hadd_ps(result, result); // second horizontal summing
			float ret;
			_MM_EXTRACT_FLOAT(ret, result, 0);
			return ret;
		}
#else
		vforceinline float horizontal_add()
		{
			vec_float_t result = m[0];
			if (intrlv > 1) result = _mm_add_ps(result, m[1]);
			if (intrlv > 2) result = _mm_add_ps(result, m[2]);
			if (intrlv > 3) result = _mm_add_ps(result, m[3]);
			if (intrlv > 4) result = _mm_add_ps(result, m[4]);
			if (intrlv > 5) result = _mm_add_ps(result, m[5]);
			if (intrlv > 6) result = _mm_add_ps(result, m[6]);
			if (intrlv > 7) result = _mm_add_ps(result, m[7]);

			float ret[4] = {
				accessmember<0>(result),
				accessmember<1>(result),
				accessmember<2>(result),
				accessmember<3>(result)
			};
			return ret[0] + ret[1] + ret[2] + ret[3];
		}
#endif
		// Warning, SLOW. Use sparingly!
		float elem(int32 a) const
		{
			vec_union_f r_out = *this;
			return r_out.f[a];
		}

		// Warning, REALLY SLOW. Use sparingly!
		void set_elem(int32 a, float v)
		{
			vec_union_f *r_out = (vec_union_f*)this;
			r_out->f[a] = v;
		}

	} VECPOST16;	// End of class vec_float



	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Vector int type - class vec_int
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////
	class VECPRE16 vec_int
	{
	public:
		vec_int_t m[interleave];

		// Default ctor doesn't initialize. standard c++.
		vforceinline vec_int() {};

		////////////////////////////////
		// Copy constructors and assignment operators
		// Can take:- another vec_int, or a single integer copied to all.
		vforceinline vec_int(const vec_int& f) { *this = f; };
		vforceinline vec_int(const int32 f) { *this = f; };

		vforceinline vec_int& operator=(const vec_int& f)
		{
			INTERLEAVED_INDEX_ASSIGN_T(m, f.m);
			return *this;
		};

		vforceinline vec_int& operator=(const int32 f)
		{
			INTERLEAVED_SINGLE_ASSIGN((*this), _mm_set1_epi32(f));
			return *this;
		};

		////////////////////////////////
		// Math operations: +, -, *
		vforceinline vec_int operator+(const vec_int& m2) const
		{
			vec_int tmp = addepi32((*this), m2);
			return tmp;
		};
		vforceinline vec_int operator-(const vec_int& m2) const
		{
			vec_int tmp = subepi32((*this), m2);
			return tmp;
		};
		vforceinline vec_int operator*(const vec_int& m2) const
		{
			vec_int tmp = mulepi32((*this), m2);
			return tmp;
		};

		////////////////////////////////
		// In-place maths: +,-,* with assignment, vector versions.
		vforceinline vec_int& operator+=(const vec_int& f)
		{
			*this = addepi32((*this), f);
			return *this;
		};
		vforceinline vec_int& operator-=(const vec_int& f)
		{
			*this = subepi32((*this), f);
			return *this;
		};

		vforceinline vec_int& operator*=(const vec_int& f)
		{
			*this = mulepi32((*this), f);
			return *this;
		};

		vforceinline vec_int  operator&(const vec_int& m2) const
		{
			vec_int a = reinterpret_cast_ftoi(andps(reinterpret_cast_itof(*this), reinterpret_cast_itof(m2)));
			return a;

		};

		vforceinline vec_int  operator|(const vec_int& m2) const
		{
			vec_int a = reinterpret_cast_ftoi(orps(reinterpret_cast_itof(*this), reinterpret_cast_itof(m2)));
			return a;
		};

		vforceinline vec_int  operator&=(const vec_int& m2) const
		{
			*this = reinterpret_cast_ftoi(andps(reinterpret_cast_itof(*this), reinterpret_cast_itof(m2)));
			return *this;

		};

		vforceinline vec_int  operator|=(const vec_int& m2) const
		{
			*this = reinterpret_cast_ftoi(orps(reinterpret_cast_itof(*this), reinterpret_cast_itof(m2)));
			return *this;
		};


	} VECPOST16;	// End of class vec_int

	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Vector double type - class vec_double
	// Uses double interleaving - i.e. if vec_float is 4 float words, or __m128[1] , vec_double is 4 double words or __m128d[2]
	///////////////////////////////////////////////////////////////////////////////////////////////////
	class VECPRE16 vec_double
	{
	public:
		vec_double_t m[interleave * 2];
		// Default ctor doesn't initialize. standard c++.
		vforceinline vec_double() {};

		vforceinline vec_double(const double f)
		{
			*this = f;
		};

		vforceinline vec_double& operator=(const vec_double& f)
		{
			INTERLEAVED_INDEX_ASSIGN_TP(m, f.m, interleave * 2);
			return *this;
		};
		vforceinline vec_double& operator=(const vec_double_t(&f)[interleave])
		{
			INTERLEAVED_INDEX_ASSIGN_TP(m, f, interleave * 2);
			return *this;
		};

		vforceinline vec_double& operator=(const double f)
		{
			INTERLEAVED_SINGLE_ASSIGN_P((*this), _mm_set1_pd(f), interleave * 2);
			return *this;
		};

		////////////////////////////////
		// Basic maths: +,-,* (no divide, it's slow. if you want divide, figure out a faster way).
		vforceinline vec_double  operator+(const vec_double& m2) const
		{
			return addpd(*this, m2);
		};
		vforceinline vec_double  operator-(const vec_double& m2) const
		{
			return subpd(*this, m2);
		};

		// Warning, SLOW. Use sparingly!
		double elem(int32 a) const
		{
			vec_union_d r_out = *this;
			return r_out.d[a];
		}

		// Warning, REALLY SLOW. Use sparingly!
		void set_elem(int32 a, double v)
		{
			vec_union_d *r_out = (vec_union_d*)this;
			r_out->d[a] = v;
		}


	} VECPOST16;
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Intrinsic-style functions for f32 & i32 vector operations
	///////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////
	// Initialization - zeroes, set1float, set1int
	static vforceinline vec_float zerops()
	{
		vec_float rv;
		INTERLEAVED_SINGLE_ASSIGN(rv, _mm_setzero_ps());
		return rv;
	};
	
	static vforceinline vec_float set1ps(float q1)
	{
		vec_float rv;
		INTERLEAVED_SINGLE_ASSIGN(rv, _mm_set1_ps(q1));
		return rv;
	};

	static vforceinline vec_int set1epi32(const int32& q1)
	{
		vec_int rv;
		INTERLEAVED_SINGLE_ASSIGN(rv, _mm_set1_epi32(q1));
		return rv;
	};

	static vforceinline vec_float loadps(const float* q1)
	{
		vec_float rv;
		if (intrlv > 0) rv.m[0] = _mm_loadu_ps(&(q1[0]));
		if (intrlv > 1) rv.m[1] = _mm_loadu_ps(&(q1[4]));
		if (intrlv > 2) rv.m[2] = _mm_loadu_ps(&(q1[8]));
		if (intrlv > 3) rv.m[3] = _mm_loadu_ps(&(q1[12]));
		if (intrlv > 4) rv.m[4] = _mm_loadu_ps(&(q1[16]));
		if (intrlv > 5) rv.m[5] = _mm_loadu_ps(&(q1[20]));
		if (intrlv > 6) rv.m[6] = _mm_loadu_ps(&(q1[24]));
		if (intrlv > 7) rv.m[7] = _mm_loadu_ps(&(q1[28]));
		return rv;
	};

	//////////////////////////////////////
	// Float operations - add, sub, mul, min, max, bitwise or, bitwise and, abs
    static vforceinline vec_float  addps(const vec_float& q1, const vec_float& q2)
    {
        vec_float rv;
#pragma unroll intrlv
        for(int32 i = 0; i < intrlv; i++) rv.m[i] = _mm_add_ps(q1.m[i], q2.m[i]);
  //      INTERLEAVED_UNROLL_2(rv,_mm_add_ps, q1, q2);
        return rv;
    }
    
    static vforceinline vec_float  mulps(const vec_float& q1, const vec_float& q2)
    {
        vec_float rv;
#pragma unroll intrlv
        for(int32 i = 0; i < intrlv; i++) rv.m[i] = _mm_mul_ps(q1.m[i], q2.m[i]);
        //      INTERLEAVED_UNROLL_2(rv,_mm_add_ps, q1, q2);
        return rv;
    }
    
//    static vforceinline vec_float  func_alias(const vec_float& q1, const vec_float& q2)   { vec_float rv; INTERLEAVED_UNROLL_2(rv, sseop, q1, q2); return rv; }

//	GENERATE_INTERLEAVED_FUNCTION_2ARG(addps, _mm_add_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(subps, _mm_sub_ps);
//	GENERATE_INTERLEAVED_FUNCTION_2ARG(mulps, _mm_mul_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(divps, _mm_div_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(minps, _mm_min_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(maxps, _mm_max_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(orps, _mm_or_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(andps, _mm_and_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(andnps, _mm_andnot_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(xorps, _mm_xor_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(cmpgeps, _mm_cmpge_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(cmpgtps, _mm_cmpgt_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(cmpleps, _mm_cmple_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(cmpltps, _mm_cmplt_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(cmpeqps, _mm_cmpeq_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(cmpneps, _mm_cmpneq_ps);
	GENERATE_INTERLEAVED_FUNCTION_1ARG(rcpps, _mm_rcp_ps);
	GENERATE_INTERLEAVED_FUNCTION_1ARG(sqrtps, _mm_sqrt_ps);

	GENERATE_INTERLEAVED_FUNCTION_2ARG_D(addpd, _mm_add_pd);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_D(subpd, _mm_sub_pd);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_D(mulpd, _mm_mul_pd);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_D(divpd, _mm_div_pd);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_D(minpd, _mm_min_pd);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_D(maxpd, _mm_max_pd);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_D(orpd, _mm_or_pd);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_D(andpd, _mm_and_pd);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_D(andnpd, _mm_andnot_pd);

#if MATHOPS_SSE_SSE41
	GENERATE_INTERLEAVED_FUNCTION_1ARG(floorps, _mm_floor_ps);
#else 
	static vforceinline vec_float floorps(const vec_float& q1)
	{
		// this assumes ROUND_DOWN
		vec_int ipart = cvtps2epi32(q1);
		return cvtepi322ps(ipart);
	}
#endif
	static vforceinline vec_float roundps(const vec_float& q1)
	{
		// this assumes ROUND_DOWN
		vec_float rup = (q1 + 0.5f);
		return floorps(rup);
	}



	static vforceinline vec_float absps(const vec_float& q1)
	{
		return andps(reinterpret_cast_itof(set1epi32(0x7FFFFFFF)), q1);
	};

	static vforceinline vec_float notps(const vec_float& q1)
	{
		return xorps(q1, reinterpret_cast_itof(set1epi32(0xFFFFFFFF)));
	};

	static vforceinline vec_float clipps(const vec_float& val, const vec_float& lo_lim, const vec_float& hi_lim)
	{
		return maxps(lo_lim, minps(val, hi_lim));
	};

	static vforceinline vec_float cubeps(const vec_float& q1)
	{
		return mulps(q1, mulps(q1, q1));
	};

	static vforceinline vec_float clip01ps(const vec_float& q1)
	{
		return maxps(minps(q1, set1ps(1.f)), 0.f);
	};

	static vforceinline vec_float maskps(const vec_float& maskee, const vec_float& conditional_mask)
	{
		return andps(maskee, conditional_mask);
	};

	static vforceinline vec_float fma(const vec_float& a1, const vec_float& b1, const vec_float& c1) { return addps(a1, mulps(b1, c1)); }
	static vforceinline vec_float fms(const vec_float& a1, const vec_float& b1, const vec_float& c1) { return subps(a1, mulps(b1, c1)); }
	static vforceinline vec_float fms1(const vec_float& a1, const vec_float& b1, const vec_float& c1) { return subps(mulps(b1, c1), a1); }

	static vforceinline bool issmallfps(const vec_float& a1)
	{
		vec_float m1 = absps(a1);
		vec_float m2 = cmpgtps(m1, set1ps(1e-6f)); // set element to TRUE (0xFFFF) if m2 is NOT small
		int32 horizontal_sum = 0;
		if (intrlv > 0) horizontal_sum += _mm_movemask_ps(m2.m[0]);
		if (intrlv > 1) horizontal_sum += _mm_movemask_ps(m2.m[1]);
		if (intrlv > 2) horizontal_sum += _mm_movemask_ps(m2.m[2]);
		if (intrlv > 3) horizontal_sum += _mm_movemask_ps(m2.m[3]);
		return (horizontal_sum == 0);
	}


	//////////////////////////////////////
	// Integer ops - add, subtract, multiply
	//////////////////////////////////////

	static vforceinline vec_int addepi32(const vec_int& q1, const vec_int& q2)
	{
		vec_int rv;
		INTERLEAVED_UNROLL_2(rv, _mm_add_epi32, q1, q2);
		return rv;
	};
	static vforceinline vec_int subepi32(const vec_int& q1, const vec_int& q2)
	{
		vec_int rv;
		INTERLEAVED_UNROLL_2(rv, _mm_sub_epi32, q1, q2);
		return rv;
	};
	static vforceinline vec_int mulepi32(const vec_int& q1, const vec_int&  q2)
	{
		vec_int rv;
#if MATHOPS_SSE_SSE41
		// WARNING: This code won't work on pre SSE4.1 CPUs
		INTERLEAVED_UNROLL_2(rv, _mm_mullo_epi32, q1, q2);
#else
		vec_int tmp1, tmp2, q1h, q2h;
		INTERLEAVED_UNROLL_2(tmp1, _mm_mul_epu32, q1, q2); // Multiply elem 0 and 2
		INTERLEAVED_UNROLL_1K(q1h, _mm_srli_si128, q1, 4); // select elems 1 & 3 of q1 in to 0 and 2 of q1h
		INTERLEAVED_UNROLL_1K(q2h, _mm_srli_si128, q2, 4); // select elems 1 & 3 of q2 in to 0 and 2 of q2h
		INTERLEAVED_UNROLL_2(tmp2, _mm_mul_epu32, q1h, q2h); // Multiply elem 0 and 2 of "h"  (i.e. 1&3 of originals)
//		INTERLEAVED_UNROLL_2K(rv, _mm_shuffle_ps, tmp1, tmp2, _MM_SHUFFLE(2,0,2,0));	// shuffle down to the low bits and pack. This version is faster but requires reinterpret-casr
		INTERLEAVED_UNROLL_1K(tmp1, _mm_shuffle_epi32, tmp1, _MM_SHUFFLE(0, 0, 2, 0));	// shuffle down to the low bits
		INTERLEAVED_UNROLL_1K(tmp2, _mm_shuffle_epi32, tmp2, _MM_SHUFFLE(0, 0, 2, 0)); // shuffle down to the low bits 
		INTERLEAVED_UNROLL_2(rv, _mm_unpacklo_epi32, tmp1, tmp2); /* pack */
#endif
		return rv;
	};


	//////////////////////////////////////
	// Conversion and bit twiddling
	//////////////////////////////////////

	// cvtps2epi32 -- float --> int conversion
	static vforceinline vec_int cvtps2epi32(const vec_float& q1)
	{
		vec_int rv;
		INTERLEAVED_UNROLL_1(rv, _mm_cvtps_epi32, q1);
		return rv;
	};

	// cvtepi322ps -- int --> float conversion
	static vforceinline vec_float cvtepi322ps(const vec_int& q1)
	{
		vec_float rv;
		INTERLEAVED_UNROLL_1(rv, _mm_cvtepi32_ps, q1);
		return rv;
	};

	// slliepi32_23 -- integer shift left by 23	(useful for bit-twiddling SSE floats)
	static vforceinline vec_int slliepi32_23(const vec_int& q1)
	{
		vec_int rv;
		INTERLEAVED_UNROLL_1K(rv, _mm_slli_epi32, q1, 23);
		return rv;
	};

	// srliepi32_9 -- integer shift right by 9 (useful for bit-twiddling SSE floats)
	static vforceinline vec_int srliepi32_9(const vec_int& q1)
	{
		vec_int rv;
		INTERLEAVED_UNROLL_1K(rv, _mm_srli_epi32, q1, 9);
		return rv;
	};

	// srliepi32_23 -- integer shift right by 23 (useful for bit-twiddling SSE floats)
	static vforceinline vec_int srliepi32_23(const vec_int& q1)
	{
		vec_int rv;
		INTERLEAVED_UNROLL_1K(rv, _mm_srli_epi32, q1, 23);
		return rv;
	};


	// reinterpret cast a float vector as an int one
	static vforceinline vec_int reinterpret_cast_ftoi(const vec_float& q1)
	{
		vec_int rv;
		INTERLEAVED_UNROLL_1(rv, _mm_castps_si128, q1);
		return rv;
	};

	// reinterpret cast an int vector as a float one
	static vforceinline vec_float reinterpret_cast_itof(const vec_int& q1)
	{
		vec_float rv;
		INTERLEAVED_UNROLL_1(rv, _mm_castsi128_ps, q1);
		return rv;
	};

	// helper for random number generators
	static vforceinline vec_int set_random_seeds(const int32& seed0)
	{
		vec_int result;
		int32 seed1 = (seed0 * 176314165) + 903633515 + 1;
		int32 seed2 = (seed1 * 176314165) + 93633515 + 2;
		int32 seed3 = (seed2 * 17631165) + 903633515 + 6;
		if (intrlv > 0) result.m[0] = _mm_set_epi32(seed0, seed1, seed2, seed3);
		if (intrlv > 1) result.m[1] = _mm_set_epi32(seed0, seed1, seed2, seed3);
		if (intrlv > 2) result.m[2] = _mm_set_epi32(seed0, seed1, seed2, seed3);
		if (intrlv > 3) result.m[3] = _mm_set_epi32(seed0, seed1, seed2, seed3);
		return result;
	};

	// Transcendental math helpers, probably belong in the base class.
	static vforceinline vec_float axPOLY0(const vec_float& x, const vec_float& c0) { return c0; };
	static vforceinline vec_float axPOLY1(const vec_float& x, const vec_float& c0, const vec_float& c1) { return addps(mulps(axPOLY0(x, c1), x), c0); };
	static vforceinline vec_float axPOLY2(const vec_float& x, const vec_float& c0, const vec_float& c1, const vec_float& c2) { return addps(mulps(axPOLY1(x, c1, c2), x), c0); };
	static vforceinline vec_float axPOLY3(const vec_float& x, const vec_float& c0, const vec_float& c1, const vec_float& c2, const vec_float& c3) { return addps(mulps(axPOLY2(x, c1, c2, c3), x), c0); };
	static vforceinline vec_float axPOLY4(const vec_float& x, const vec_float& c0, const vec_float& c1, const vec_float& c2, const vec_float& c3, const vec_float& c4) { return addps(mulps(axPOLY3(x, c1, c2, c3, c4), x), c0); };

	// 2^X approximation, 4th order polynomial
	static vforceinline vec_float fpow2ps_poly4(const vec_float& x)
	{
		vec_float xx = maxps(minps(x, 126.f), -126.f);

		/* ipart = int32(x) */ // Don't subtract 0.5, assume we're in ROUND DOWN mode.
		vec_int ipart = cvtps2epi32(xx);
		/* fpart = x - ipart */
#if MATHOPS_SSE_SSE41
		vec_float fpart = subps(xx, floorps(xx));
#else
		vec_float fpart = subps(xx, cvtepi322ps(ipart));
#endif

		/* expipart = (float) (1 << ipart) */
		vec_int expipart = slliepi32_23(addepi32(ipart, 127));

		/* minimax polynomial fit of 2**x, in range [-0.5, 0.5[ */
		//expfpart = axPOLY4(fpart.m, 1.0f, 0.6960656421638072f, 0.224494337302845f, 0.07944023841053369f); // range [0,1] coeffs
		vec_float expfpart = axPOLY4(fpart, set1ps(1.0000026f), set1ps(6.9300383e-1f), set1ps(2.4144275e-1f), set1ps(5.2011464e-2f), set1ps(1.3534167e-2f));
		return mulps(reinterpret_cast_itof(expipart), expfpart);
	}

	// 2^X approximation, 2nd order polynomial
	static vforceinline vec_float fpow2ps_poly2(const vec_float& x)
	{
		// clip the input to between sensible bounds
		vec_float xx = maxps(minps(x, 126.f), -126.f);
		// get an int
		vec_int ipart = cvtps2epi32(xx);
		//m remainder
#if MATHOPS_SSE_SSE41
		vec_float fpart = subps(xx, floorps(xx));
#else
		vec_float fpart = subps(xx, cvtepi322ps(ipart));
#endif

		// add 127 & then shift left by 23
		vec_int expipart = slliepi32_23(addepi32(ipart, 127));

		// cubic apporoximation of 2^x in [0, 1]
		//x  = 1.0f + x*(0.6960656421638072f  + x*(0.224494337302845f   + x*(0.07944023841053369f)));
		vec_float expfpart = addps(set1ps(1.f),
			mulps(fpart, addps(set1ps(0.6960656421638072f),
				mulps(fpart, addps(set1ps(0.224494337302845f),
					mulps(fpart, set1ps(0.07944023841053369f))
					)))));
		return mulps(reinterpret_cast_itof(expipart), expfpart);
	}

	//////////////////////////////////////
	// Double to float
	static vforceinline vec_float vec_dtof(const vec_double& vd)
	{
		vec_float r;
		if (intrlv > 0) {
			r.m[0] = _mm_movelh_ps(_mm_cvtpd_ps(vd.m[0]), _mm_cvtpd_ps(vd.m[1]));
		}
		if (intrlv > 1) {
			r.m[1] = _mm_movelh_ps(_mm_cvtpd_ps(vd.m[2]), _mm_cvtpd_ps(vd.m[3]));
		}
		if (intrlv > 2) {
			r.m[2] = _mm_movelh_ps(_mm_cvtpd_ps(vd.m[4]), _mm_cvtpd_ps(vd.m[5]));
		}
		if (intrlv > 3) {
			r.m[3] = _mm_movelh_ps(_mm_cvtpd_ps(vd.m[6]), _mm_cvtpd_ps(vd.m[7]));
		}
		return r;
	}

	//////////////////////////////////////
	// Float to double
	static vforceinline vec_double vec_ftod(const vec_float& vd)
	{
		vec_double r;
		if (intrlv > 0) {
			r.m[0] = _mm_cvtps_pd(vd.m[0]);
			__m128 swapped = _mm_shuffle_ps(vd.m[0], vd.m[0], _MM_SHUFFLE(3, 2, 3, 2));
			r.m[1] = _mm_cvtps_pd(swapped);
		}
		if (intrlv > 1) {
			r.m[2] = _mm_cvtps_pd(vd.m[1]);
			__m128 swapped = _mm_shuffle_ps(vd.m[1], vd.m[1], _MM_SHUFFLE(3, 2, 3, 2));
			r.m[3] = _mm_cvtps_pd(swapped);
		}
		if (intrlv > 2) {
			r.m[4] = _mm_cvtps_pd(vd.m[2]);
			__m128 swapped = _mm_shuffle_ps(vd.m[2], vd.m[2], _MM_SHUFFLE(3, 2, 3, 2));
			r.m[5] = _mm_cvtps_pd(swapped);
		}
		if (intrlv > 3) {
			r.m[6] = _mm_cvtps_pd(vd.m[3]);
			__m128 swapped = _mm_shuffle_ps(vd.m[3], vd.m[3], _MM_SHUFFLE(3, 2, 3, 2));
			r.m[7] = _mm_cvtps_pd(swapped);
		}
		return r;
	}
	/////////////////////////////////////
	// Test if a vector is all zeros
	static vforceinline bool vec_iszero(const vec_float& v)
	{
#if MATHOPS_SSE_SSE41
		int32 res = _mm_testz_si128(_mm_castps_si128(v.m[0]), _mm_castps_si128(v.m[0]));
		if (intrlv > 1) {
			res += _mm_testz_si128(_mm_castps_si128(v.m[1]), _mm_castps_si128(v.m[1]));
		}
		if (intrlv > 2) {
			res += _mm_testz_si128(_mm_castps_si128(v.m[2]), _mm_castps_si128(v.m[2]));
		}
		if (intrlv > 3) {
			res += _mm_testz_si128(_mm_castps_si128(v.m[3]), _mm_castps_si128(v.m[3]));
		}
		return (res == intrlv);
#else
        __m128i mz = _mm_set1_epi32(0);
        __m128i result = _mm_cmpeq_epi32(_mm_castps_si128(v.m[0]), mz);
        if (intrlv > 1) result = _mm_add_epi32(result, _mm_cmpeq_epi32(_mm_castps_si128(v.m[1]), mz));
        if (intrlv > 2) result = _mm_add_epi32(result, _mm_cmpeq_epi32(_mm_castps_si128(v.m[2]), mz));
        if (intrlv > 3) result = _mm_add_epi32(result, _mm_cmpeq_epi32(_mm_castps_si128(v.m[3]), mz));
        __m128 resultf = _mm_cvtepi32_ps(result);
        
            float ret[4] = {
                accessmember<0>(resultf),
                accessmember<1>(resultf),
                accessmember<2>(resultf),
                accessmember<3>(resultf)
            };
            return (issmallf(ret[0] + ret[1] + ret[2] + ret[3] + (4.f * intrlv)));
       
#endif
	}

	//////////////////////////////////////
	// Types and conversions for extracting to raw data
	//////////////////////////////////////

	union VECPRE16 vec_union_i32
	{
		vec_int_t mi[interleave];
		int32 i[vec_elem];
		float f[vec_elem];
		uint32 u[vec_elem];
		vec_float_t m[interleave];
	} VECPOST16;

	union VECPRE16 vec_union_f
	{
		float f[vec_elem];
		uint32 u[vec_elem];
		int32 i[vec_elem];
		vec_float_t m[interleave];
		vec_int_t mi[interleave];
		vec_float mv;
		vec_union_f() {};
		vec_union_f(const vec_float& other) { mv = other; };
        vec_union_f(const vec_union_f& other) { mv = other.mv; };
		~vec_union_f() {};
	} VECPOST16;

	union VECPRE16 vec_union_d
	{
		double d[vec_elem];
		vec_double_t m[interleave * 2];
		vec_double mv;
		vec_union_d() {};
		vec_union_d(const vec_double& other) { mv = other; };
		~vec_union_d() {};
	} VECPOST16;

	static vforceinline void get_union_i32(const vec_int& obj, vec_union_i32& result)
	{
		INTERLEAVED_INDEX_ASSIGN_T(result.mi, obj.m);
	};
	static vforceinline void get_union_f(const vec_float& obj, vec_union_f& result)
	{
		INTERLEAVED_INDEX_ASSIGN_T(result.m, obj.m);
	};

	static vforceinline vec_float get_vector_f(const vec_union_f& obj)
	{
		vec_float result;
		INTERLEAVED_INDEX_ASSIGN_T(result.m, obj.m);
		return result;
	};

	static vforceinline void vec_stream_store(float* destination, const vec_float& data)
	{
		// NB: Not using streaming stores - if 2 processing lanes share a cache line, this degrades perf.
		if (interleave >= 1) _mm_store_ps(destination, data.m[0]);
		if (interleave >= 2) _mm_store_ps(destination + 4, data.m[1]);
		if (interleave >= 3) _mm_store_ps(destination + 8, data.m[2]);
		if (interleave >= 4) _mm_store_ps(destination + 12, data.m[3]);
	};

};

#endif
