#if 1 //ndef MATHOPS_AVX_H
#define MATHOPS_AVX_H

///////////////////////////////////
// Math ops for 8-way AVX code
// Author: Angus F. Hewlett
// Copyright FXpansion Audio UK Ltd. 2012
///////////////////////////////////

////////////////////////////////
// This file provides:-
// * Typedefs for n-way AVX (8x32) containers
// ** interleave amount configured by template parameter - can be any power of 2
// ** vec_float & vec_int - float32 and int32 respectively
// * copy constructors, assignment and basic math operators for those containers
// * General intrinsic-function-style math operations for 8-way AVX data ("addps()" etc.) operating on vec_float & vec_int types
// ** (as static functions in Mathops_AVXxN class - inherit to win)
// * typedefs / conversion routines for packing/unpacking to plain vectors of floats/ints
////////////////////////////////

#ifndef CEXCOMPILE
#include "MathOps_Common.h"
#endif

#if (_MSC_VER || __ICC) // MS compiler allows direct access to union members
#define VECPRE32 __declspec(align(32))
#define VECPOST32
#else
#define VECPRE32 
#define VECPOST32 __attribute__ ((aligned (32)))
#endif
#undef VECPRE_NATIVE
#undef VECPOST_NATIVE
#define VECPRE_NATIVE VECPRE32
#define VECPOST_NATIVE VECPOST32

#define generic_addps _mm256_add_ps
#define generic_mulps _mm256_mul_ps
#define generic_subps _mm256_sub_ps

///////////////////////////////////////////////////////////////////////////////////////////////////
// class Mathops_AVX
// Math operations for interleaved N-way SSE data
///////////////////////////////////////////////////////////////////////////////////////////////////

template <const int intrlv> class MathOps
{
public:
	static constexpr int raw_vec_elem = 8;
	static constexpr int raw_vec_2pow = 3;
	static constexpr int interleave = intrlv;
	static constexpr int32 vec_elem = interleave * raw_vec_elem;

	typedef __m256 vec_unaligned_float;
	typedef __m256i vec_unaligned_int;
	typedef __m128 vec_unaligned_float__128;
	typedef __m128i vec_unaligned_int__128;
	typedef __m256d vec_unaligned_double;

	typedef VECPRE32 vec_unaligned_float vec_float_t VECPOST32;
	typedef VECPRE32 vec_unaligned_int vec_int_t VECPOST32;
	typedef VECPRE32 vec_unaligned_double vec_double_t VECPOST32;

	typedef VECPRE32 vec_unaligned_float__128 vec_float_t__128 VECPOST32;
	typedef VECPRE32 vec_unaligned_int__128 vec_int_t__128 VECPOST32;

	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Vector float type - class vec_float
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////
	class VECPRE32 vec_float 
	{
	public:
		vec_float_t m[interleave];
		// Default ctor doesn't initialize. standard c++.
		vforceinline vec_float() {};

		////////////////////////////////
		// Copy constructors and assignment operators
		// Can take:- another vec_float, a single vec_float_t element which is copied to all, a single float copied to all.
		vforceinline vec_float(const vec_float& f) { *this = f; };
		vforceinline vec_float(const vec_float_t (&f)[interleave]) { *this = f; };
		vforceinline vec_float(const float& f) { *this = f; };

		vforceinline vec_float& operator=(const vec_float& f) 
		{ 
			INTERLEAVED_INDEX_ASSIGN_T(m, f.m);
			return *this;
		};	
		
		vforceinline vec_float& operator=(const vec_float_t (&f)[interleave]) 
		{ 
			INTERLEAVED_INDEX_ASSIGN_T(m, f);
			return *this;
		};

		vforceinline vec_float&  operator=(const float f)
		{ 
			INTERLEAVED_SINGLE_ASSIGN((*this), _mm256_set1_ps(f));
			return *this;
		};

		////////////////////////////////
		// Basic maths: +,-,* (no divide, it's slow. if you want divide, figure out a faster way).
		vforceinline vec_float   operator+(const vec_float& m2) const
		{
			return addps(*this, m2);
		};
		vforceinline vec_float   operator-(const vec_float& m2) const
		{
			return subps(*this, m2);
		};
		vforceinline vec_float   operator*(const vec_float& m2) const
		{
			return 	mulps(*this, m2);
		};

		vforceinline vec_float   operator>(const vec_float& m2) const
		{
			return 	cmpgtps(*this, m2);
		};

		vforceinline vec_float   operator>=(const vec_float& m2) const
		{
			return 	cmpgeps(*this, m2);
		};

		vforceinline vec_float   operator<(const vec_float& m2) const
		{
			return 	cmpltps(*this, m2);
		};

		vforceinline vec_float   operator<=(const vec_float& m2) const
		{
			return 	cmpleps(*this, m2);
		};

		vforceinline vec_float   operator==(const vec_float& m2) const
		{
			return 	cmpeqps(*this, m2);
		};

		vforceinline vec_float   operator!=(const vec_float& m2) const
		{
			return 	cmpneps(*this, m2);
		};

		vforceinline vec_float   operator&(const vec_float& m2) const
		{
			return 	andps(*this, m2);
		};

		vforceinline vec_float&  operator!() const
		{
			return notps(*this);
		};
		/*
		vforceinline vec_float  operator^(const int32 pwr) const
		{
			if (pwr == 2) return (*this * *this);
			if (pwr == 3) return (*this * *this * *this);
			if (pwr == 4) return (*this * *this * *this * *this);
		};*/


		////////////////////////////////
		// In-place maths: +,-,* with assignment, vector versions.
		vforceinline vec_float&   operator+=(const vec_float& f)
		{ 
			*this = addps(*this, f);
			return *this;
		};
		vforceinline vec_float&   operator-=(const vec_float& f)
		{ 
			*this = subps(*this, f);
			return *this;
		};
		vforceinline vec_float&   operator*=(const vec_float& f)
		{ 
			*this = mulps(*this, f);
			return *this;
		};

		////////////////////////////////
		// In-place maths: +,-,* with assignment, scalar constant versions
		vforceinline vec_float&  operator+=(const float f)
		{
			vec_float tmp_f;
			INTERLEAVED_SINGLE_ASSIGN(tmp_f, _mm256_set1_ps(f));
			*this = addps(*this, tmp_f); 
			return *this;
		};
		vforceinline vec_float&  operator-=(const float f)
		{
			vec_float tmp_f;
			INTERLEAVED_SINGLE_ASSIGN(tmp_f, _mm256_set1_ps(f));
			*this = subps(*this, tmp_f);
			return *this;
		};
		vforceinline vec_float&  operator*=(const float f)
		{
			vec_float tmp_f;
			INTERLEAVED_SINGLE_ASSIGN(tmp_f, _mm256_set1_ps(f));
			*this = mulps(*this, tmp_f);
			return *this;
		};

		////////////////////////////////
		// In-place clip functions: with vector bounds, with scalar const bounds, with input & vector bounds, with input & scalar const bounds
		vforceinline void  clip(const vec_float& lo_lim, const vec_float& hi_lim)
		{
			vec_float tmp_f;
			INTERLEAVED_UNROLL_2(tmp_f, _mm256_min_ps, (*this), hi_lim);
			INTERLEAVED_UNROLL_2((*this), _mm256_max_ps, tmp_f, lo_lim);
		};

		vforceinline void  clip(const float lo_lim, const float hi_lim)
		{
			vec_float hi_lim_v = hi_lim;
			vec_float lo_lim_v = lo_lim;
			vec_float tmp_f;
			INTERLEAVED_UNROLL_2(tmp_f, _mm256_min_ps, (*this), hi_lim_v);
			INTERLEAVED_UNROLL_2((*this), _mm256_max_ps, tmp_f, lo_lim_v);
		};
		vforceinline void clip_v(const vec_float& val, const vec_float& lo_lim, const vec_float& hi_lim)
		{
			vec_float tmp_f;
			INTERLEAVED_UNROLL_2(tmp_f, _mm256_min_ps, val, hi_lim);
			INTERLEAVED_UNROLL_2((*this), _mm256_max_ps, tmp_f, lo_lim);
		};
		vforceinline void  clip_v(const vec_float& val, const float lo_lim, const float hi_lim)
		{
			vec_float hi_lim_v = hi_lim;
			vec_float lo_lim_v = lo_lim;
			vec_float tmp_f;
			INTERLEAVED_UNROLL_2(tmp_f, _mm256_min_ps, val, hi_lim_v);
			INTERLEAVED_UNROLL_2((*this), _mm256_max_ps, tmp_f, lo_lim_v);
		};


		float  avx_sum8(vec_float_t x) {
			// hiQuad = ( x7, x6, x5, x4 )
			const __m128 hiQuad = _mm256_extractf128_ps(x, 1);
			// loQuad = ( x3, x2, x1, x0 )
			const __m128 loQuad = _mm256_castps256_ps128(x);
			// sumQuad = ( x3 + x7, x2 + x6, x1 + x5, x0 + x4 )
			const __m128 sumQuad = _mm_add_ps(loQuad, hiQuad);
			// loDual = ( -, -, x1 + x5, x0 + x4 )
			const __m128 loDual = sumQuad;
			// hiDual = ( -, -, x3 + x7, x2 + x6 )
			const __m128 hiDual = _mm_movehl_ps(sumQuad, sumQuad);
			// sumDual = ( -, -, x1 + x3 + x5 + x7, x0 + x2 + x4 + x6 )
			const __m128 sumDual = _mm_add_ps(loDual, hiDual);
			// lo = ( -, -, -, x0 + x2 + x4 + x6 )
			const __m128 lo = sumDual;
			// hi = ( -, -, -, x1 + x3 + x5 + x7 )
			const __m128 hi = _mm_shuffle_ps(sumDual, sumDual, 0x1);
			// sum = ( -, -, -, x0 + x1 + x2 + x3 + x4 + x5 + x6 + x7 )
			const __m128 sum = _mm_add_ss(lo, hi);
			return _mm_cvtss_f32(sum);
		}


		vforceinline float  horizontal_add()
		{
			vec_float_t result = m[0];
			if (intrlv > 1) result = _mm256_add_ps(result, m[1]);
			if (intrlv > 2) result = _mm256_add_ps(result, m[2]);
			if (intrlv > 3) result = _mm256_add_ps(result, m[3]);
			if (intrlv > 4) result = _mm256_add_ps(result, m[4]);
			if (intrlv > 5) result = _mm256_add_ps(result, m[5]);
			if (intrlv > 6) result = _mm256_add_ps(result, m[6]);
			if (intrlv > 7) result = _mm256_add_ps(result, m[7]);

/*			result = _mm_hadd_ps(result, result); // first horizontal summing
			result = _mm_hadd_ps(result, result); // second horizontal summing
			float ret;
			_MM_EXTRACT_FLOAT(ret, result, 0);*/
			return avx_sum8(result);
		}

		// Warning, SLOW. Use sparingly!
		float  elem(int32 a) const
		{
			vec_union_f r_out = *this;
			return r_out.f[a];
		}

		// Warning, REALLY SLOW. Use sparingly!
		void  set_elem(int32 a, float v)
		{
			vec_union_f *r_out = (vec_union_f*)this;
			r_out->f[a] = v;
		}


	} VECPOST32;



	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Vector int type - class vec_int
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////
	class VECPRE32 vec_int
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

		vforceinline vec_int&  operator=(const int32 f)
		{ 
			INTERLEAVED_SINGLE_ASSIGN((*this), _mm256_set1_epi32(f));
			return *this;
		};

		////////////////////////////////
		// Math operations: +, -, *
		vforceinline vec_int  operator+(const vec_int& m2) const
		{
			vec_int tmp = addepi32((*this), m2);
			return tmp;
		};
		vforceinline vec_int  operator-(const vec_int& m2) const
		{
			vec_int tmp = subepi32((*this), m2);
			return tmp;
		};
		vforceinline vec_int  operator*(const vec_int& m2) const
		{
			vec_int tmp = mulepi32((*this), m2);
			return tmp;
		};

		////////////////////////////////
		// In-place maths: +,-,* with assignment, vector versions.
		vforceinline vec_int&  operator+=(const vec_int& f)
		{ 
			*this = addepi32((*this), f);
			return *this;
		};
		vforceinline vec_int&  operator-=(const vec_int& f)
		{ 
			*this = subepi32((*this), f);
			return *this;
		};

		vforceinline vec_int&  operator*=(const vec_int& f)
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


		vforceinline vec_int&  operator&=(const vec_int& m2) const
		{
			*this = reinterpret_cast_ftoi(andps(reinterpret_cast_itof(*this), reinterpret_cast_itof(m2)));
			return *this;
		};

		vforceinline vec_int&  operator|=(const vec_int& m2) const
		{
			*this = reinterpret_cast_ftoi(orps(reinterpret_cast_itof(*this), reinterpret_cast_itof(m2)));
			return *this;
		};



	} VECPOST32;

	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Vector double type - class vec_double
	// Uses double interleaving - i.e. if vec_float is 4 float words, or __m128[1] , vec_double is 4 double words or __m128d[2]
	///////////////////////////////////////////////////////////////////////////////////////////////////
	class VECPRE32 vec_double
	{
	public:
		vec_double_t m[interleave * 2];
		// Default ctor doesn't initialize. standard c++.
		vforceinline vec_double() {};

		vforceinline vec_double(const double f)
		{
		*this = f;
		};


		vforceinline vec_double&  operator=(const vec_double& f)
		{
			INTERLEAVED_INDEX_ASSIGN_TP(m, f.m, interleave * 2);
			return *this;
		};
		vforceinline vec_double&  operator=(const vec_double_t(&f)[interleave])
		{
			INTERLEAVED_INDEX_ASSIGN_TP(m, f, interleave * 2);
			return *this;
		};

		vforceinline vec_double&  operator=(const double f)
		{
			INTERLEAVED_SINGLE_ASSIGN_P((*this), _mm256_set1_pd(f), interleave * 2);
			return *this;
		};

		////////////////////////////////
		// Basic maths: +,-,* (no divide, it's slow. if you want divide, figure out a faster way).
		vforceinline vec_double   operator+(const vec_double& m2) const
		{
			return addpd(*this, m2);
		};
		vforceinline vec_double   operator-(const vec_double& m2) const
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
	} VECPOST32;


	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Vector int 128-bit type - class vec_int - for AVX int instructions where 2 128 bit words are needed
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////
	class VECPRE32 vec_int__128
	{
	public:
		vec_int_t__128 m[interleave];

		// Default ctor doesn't initialize. standard c++.
		vforceinline vec_int__128() {};

	} VECPOST32;

	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Intrinsic-style functions for f32 & i32 vector operations
	///////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////
	// Initialization - zeroes, set1float, set1int
	static vforceinline vec_float  zerops()
	{
		vec_float rv;
		INTERLEAVED_SINGLE_ASSIGN(rv, _mm256_setzero_ps());
		return rv;
	};

	static vforceinline vec_float  set1ps(float q1)
	{ 
		vec_float rv; 
		INTERLEAVED_SINGLE_ASSIGN(rv, _mm256_set1_ps(q1));
		return rv;
	};

	static vforceinline vec_int  set1epi32(const int32& q1)
	{
		vec_int rv;
		INTERLEAVED_SINGLE_ASSIGN(rv, _mm256_set1_epi32(q1));
		return rv; 
	};
    
    static vforceinline vec_float  loadps(const float* q1)
    {
        vec_float rv;
        if (intrlv > 0) rv.m[0] = _mm256_loadu_ps(&(q1[0]));
        if (intrlv > 1) rv.m[1] = _mm256_loadu_ps(&(q1[8]));
        if (intrlv > 2) rv.m[2] = _mm256_loadu_ps(&(q1[16]));
        if (intrlv > 3) rv.m[3] = _mm256_loadu_ps(&(q1[24]));
        if (intrlv > 4) rv.m[4] = _mm_loadu_ps(&(q1[32]));
        if (intrlv > 5) rv.m[5] = _mm_loadu_ps(&(q1[40]));
        if (intrlv > 6) rv.m[6] = _mm_loadu_ps(&(q1[48]));
        if (intrlv > 7) rv.m[7] = _mm_loadu_ps(&(q1[56]));
        return rv;
    };
	
	//////////////////////////////////////
	// Float operations - add, sub, mul, min, max, bitwise or, bitwise and, abs
	GENERATE_INTERLEAVED_FUNCTION_2ARG(addps, _mm256_add_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(subps, _mm256_sub_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(mulps, _mm256_mul_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(divps, _mm256_div_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(minps, _mm256_min_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(maxps, _mm256_max_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(orps, _mm256_or_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(andps, _mm256_and_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(andnps, _mm256_andnot_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG(xorps, _mm256_xor_ps);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_K(cmpgeps, _mm256_cmp_ps, _CMP_GE_OS);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_K(cmpgtps, _mm256_cmp_ps, _CMP_GT_OS);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_K(cmpleps, _mm256_cmp_ps, _CMP_LE_OS);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_K(cmpltps, _mm256_cmp_ps, _CMP_LT_OS);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_K(cmpeqps, _mm256_cmp_ps, _CMP_EQ_OS);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_K(cmpneps, _mm256_cmp_ps, _CMP_NEQ_OS);
	GENERATE_INTERLEAVED_FUNCTION_1ARG(rcpps, _mm256_rcp_ps);
    GENERATE_INTERLEAVED_FUNCTION_1ARG(sqrtps, _mm256_sqrt_ps);

	GENERATE_INTERLEAVED_FUNCTION_2ARG_D(addpd, _mm256_add_pd);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_D(subpd, _mm256_sub_pd);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_D(mulpd, _mm256_mul_pd);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_D(divpd, _mm256_div_pd);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_D(minpd, _mm256_min_pd);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_D(maxpd, _mm256_max_pd);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_D(orpd, _mm256_or_pd);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_D(andpd, _mm256_and_pd);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_D(andnpd, _mm256_andnot_pd);

	GENERATE_INTERLEAVED_FUNCTION_1ARG(floorps, _mm256_floor_ps);

	static vforceinline vec_float  roundps(const vec_float& q1)
	{
		// this assumes ROUND_DOWN. TODO: replace with proper controlword-based rounding
		vec_float rup = (q1 + 0.5f);
		return floorps(rup);
	}


	static vforceinline vec_float  absps(const vec_float& q1)
	{ 
		return andps(reinterpret_cast_itof(set1epi32(0x7FFFFFFF)), q1);
	};

	static vforceinline vec_float  notps(const vec_float& q1)
	{
		return xorps(q1, reinterpret_cast_itof(set1epi32(0xFFFFFFFF)));
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

#if	MATHOPS_AVX_FMA
	GENERATE_INTERLEAVED_FUNCTION_3ARG(fmaddps, _mm256_fmadd_ps);
	GENERATE_INTERLEAVED_FUNCTION_3ARG(fmsubps, _mm256_fmsub_ps);
	GENERATE_INTERLEAVED_FUNCTION_3ARG(fnmaddps, _mm256_fnmadd_ps);

	static vforceinline vec_float  fma(const vec_float& a1, const vec_float& b1, const vec_float& c1) { return fmaddps(b1, c1, a1); }
	static vforceinline vec_float  fms(const vec_float& a1, const vec_float& b1, const vec_float& c1) { return fnmaddps(b1, c1, a1); }
	static vforceinline vec_float  fms1(const vec_float& a1, const vec_float& b1, const vec_float& c1) { return fmsubps(b1, c1, a1); }

#else
	static vforceinline vec_float  fma(const vec_float& a1,  const vec_float& b1, const vec_float& c1)   { return addps(a1, mulps(b1, c1)); }
	static vforceinline vec_float  fms(const vec_float& a1, const vec_float& b1, const vec_float& c1) { return subps(a1, mulps(b1, c1)); }
	static vforceinline vec_float  fms1(const vec_float& a1, const vec_float& b1, const vec_float& c1) { return subps(mulps(b1, c1), a1); }
#endif


	static vforceinline bool  issmallfps(const vec_float& a1)
	{
		vec_float m1 = absps(a1);
		vec_float m2 = cmpgtps(m1, set1ps(1e-6f)); // set element to TRUE (0xFFFF) if m2 is NOT small
		int32 horizontal_sum = 0;
		if (intrlv > 0) horizontal_sum += _mm256_movemask_ps(m2.m[0]);
		if (intrlv > 1) horizontal_sum += _mm256_movemask_ps(m2.m[1]);
		if (intrlv > 2) horizontal_sum += _mm256_movemask_ps(m2.m[2]);
		if (intrlv > 3) horizontal_sum += _mm256_movemask_ps(m2.m[3]);
		return (horizontal_sum == 0);
	}

	//////////////////////////////////////
	// Integer ops - add, subtract, multiply
	// NB: These are unpacked to two 128-bit instructions as AVX(1) doesn't have integer ops.
	//////////////////////////////////////
#if MATHOPS_AVX_FMA
	GENERATE_INTERLEAVED_FUNCTION_2ARG_INT(addepi32, _mm256_add_epi32);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_INT(subepi32, _mm256_sub_epi32);
	GENERATE_INTERLEAVED_FUNCTION_2ARG_INT(mulepi32, _mm256_mullo_epi32);
#else


	static vforceinline vec_int  addepi32(const vec_int& q1, const vec_int& q2)
	{
		vec_int rv;
		vec_int__128 loword1, hiword1, loword2, hiword2;
		INTERLEAVED_UNROLL_1K(loword1, _mm256_extractf128_si256, q1, 0);
		INTERLEAVED_UNROLL_1K(hiword1, _mm256_extractf128_si256, q1, 1);
		INTERLEAVED_UNROLL_1K(loword2, _mm256_extractf128_si256, q2, 0);
		INTERLEAVED_UNROLL_1K(hiword2, _mm256_extractf128_si256, q2, 1);
		INTERLEAVED_UNROLL_2(loword1, _mm_add_epi32, loword1, loword2);
		INTERLEAVED_UNROLL_2(hiword1, _mm_add_epi32, hiword1, hiword2);
		INTERLEAVED_UNROLL_1(rv, _mm256_castsi128_si256, loword1);
		INTERLEAVED_UNROLL_2K(rv, _mm256_insertf128_si256, rv, hiword1, 1);
		return rv;

	};
	static vforceinline vec_int  subepi32(const vec_int& q1, const vec_int& q2)
	{
		vec_int rv;
		vec_int__128 loword1, hiword1, loword2, hiword2;
		INTERLEAVED_UNROLL_1K(loword1, _mm256_extractf128_si256, q1, 0);
		INTERLEAVED_UNROLL_1K(hiword1, _mm256_extractf128_si256, q1, 1);
		INTERLEAVED_UNROLL_1K(loword2, _mm256_extractf128_si256, q2, 0);
		INTERLEAVED_UNROLL_1K(hiword2, _mm256_extractf128_si256, q2, 1);
		INTERLEAVED_UNROLL_2(loword1, _mm_sub_epi32, loword1, loword2);
		INTERLEAVED_UNROLL_2(hiword1, _mm_sub_epi32, hiword1, hiword2);
		INTERLEAVED_UNROLL_1(rv, _mm256_castsi128_si256, loword1);
		INTERLEAVED_UNROLL_2K(rv, _mm256_insertf128_si256, rv, hiword1, 1);
		return rv;
	};
	static vforceinline vec_int  mulepi32(const vec_int& q1,const vec_int&  q2)
	{
		vec_int rv;
		vec_int__128 loword1, hiword1, loword2, hiword2;
		INTERLEAVED_UNROLL_1K(loword1, _mm256_extractf128_si256, q1, 0);
		INTERLEAVED_UNROLL_1K(hiword1, _mm256_extractf128_si256, q1, 1);
		INTERLEAVED_UNROLL_1K(loword2, _mm256_extractf128_si256, q2, 0);
		INTERLEAVED_UNROLL_1K(hiword2, _mm256_extractf128_si256, q2, 1);
		INTERLEAVED_UNROLL_2(loword1, _mm_mullo_epi32, loword1, loword2);
		INTERLEAVED_UNROLL_2(hiword1, _mm_mullo_epi32, hiword1, hiword2);
		INTERLEAVED_UNROLL_1(rv, _mm256_castsi128_si256, loword1);
		INTERLEAVED_UNROLL_2K(rv, _mm256_insertf128_si256, rv, hiword1, 1);
		return rv;
	};
	
#endif
	//////////////////////////////////////
	// Conversion and bit twiddling
	//////////////////////////////////////


	// cvtps2epi32 -- float --> int conversion
	static vforceinline vec_int  cvtps2epi32(const vec_float& q1)
	{ 
		vec_int rv;
		INTERLEAVED_UNROLL_1(rv, _mm256_cvtps_epi32, q1);
		return rv; 
	};

	// cvtepi322ps -- int --> float conversion
	static vforceinline vec_float  cvtepi322ps(const vec_int& q1)
	{ 
		vec_float rv;
		INTERLEAVED_UNROLL_1(rv, _mm256_cvtepi32_ps, q1);
		return rv; 
	};

#if MATHOPS_AVX_FMA
	// slliepi32_23 -- integer shift left by 23	(useful for bit-twiddling SSE floats)
	static vforceinline vec_int  slliepi32_23(const vec_int& q1)
	{
		vec_int rv;
		INTERLEAVED_UNROLL_1K(rv, _mm256_slli_epi32, q1, 23);
		return rv;
	};

	// srliepi32_9 -- integer shift right by 9 (useful for bit-twiddling SSE floats)
	static vforceinline vec_int  srliepi32_9(const vec_int& q1)
	{
		vec_int rv;
		INTERLEAVED_UNROLL_1K(rv, _mm256_srli_epi32, q1, 9);
		return rv;
	};

	// srliepi32_23 -- integer shift right by 23 (useful for bit-twiddling SSE floats)
	static vforceinline vec_int  srliepi32_23(const vec_int& q1)
	{
		vec_int rv;
		INTERLEAVED_UNROLL_1K(rv, _mm256_srli_epi32, q1, 23);
		return rv;
	};


#else

	// slliepi32_23 -- integer shift left by 23	(useful for bit-twiddling SSE floats)
	static vforceinline vec_int  slliepi32_23(const vec_int& q1)
	{
		vec_int rv;
		vec_int__128 loword1, hiword1;
		INTERLEAVED_UNROLL_1K(loword1, _mm256_extractf128_si256, q1, 0);
		INTERLEAVED_UNROLL_1K(hiword1, _mm256_extractf128_si256, q1, 1);
		INTERLEAVED_UNROLL_1K(loword1, _mm_slli_epi32, loword1, 23);
		INTERLEAVED_UNROLL_1K(hiword1, _mm_slli_epi32, hiword1, 23);
		INTERLEAVED_UNROLL_1(rv, _mm256_castsi128_si256, loword1);
		INTERLEAVED_UNROLL_2K(rv, _mm256_insertf128_si256, rv, hiword1, 1);
		return rv;
	};

	// slliepi32_23 -- integer shift right by 9 (useful for bit-twiddling SSE floats)
	static vforceinline vec_int  srliepi32_9(const vec_int& q1)
	{
		vec_int rv;
		vec_int__128 loword1, hiword1;
		INTERLEAVED_UNROLL_1K(loword1, _mm256_extractf128_si256, q1, 0);
		INTERLEAVED_UNROLL_1K(hiword1, _mm256_extractf128_si256, q1, 1);
		INTERLEAVED_UNROLL_1K(loword1, _mm_srli_epi32, loword1, 9);
		INTERLEAVED_UNROLL_1K(hiword1, _mm_srli_epi32, hiword1, 9);
		INTERLEAVED_UNROLL_1(rv, _mm256_castsi128_si256, loword1);
		INTERLEAVED_UNROLL_2K(rv, _mm256_insertf128_si256, rv, hiword1, 1);
		return rv;
	};

	// srliepi32_23 -- integer shift right by 23 (useful for bit-twiddling SSE floats)
	static vforceinline vec_int  srliepi32_23(const vec_int& q1)
	{
		vec_int rv;
		vec_int__128 loword1, hiword1;
		INTERLEAVED_UNROLL_1K(loword1, _mm256_extractf128_si256, q1, 0);
		INTERLEAVED_UNROLL_1K(hiword1, _mm256_extractf128_si256, q1, 1);
		INTERLEAVED_UNROLL_1K(loword1, _mm_srli_epi32, loword1, 23);
		INTERLEAVED_UNROLL_1K(hiword1, _mm_srli_epi32, hiword1, 23);
		INTERLEAVED_UNROLL_1(rv, _mm256_castsi128_si256, loword1);
		INTERLEAVED_UNROLL_2K(rv, _mm256_insertf128_si256, rv, hiword1, 1);
		return rv;
	};

#endif

	// reinterpret cast a float vector as an int one
	static vforceinline vec_int  reinterpret_cast_ftoi(const vec_float& q1)
	{ 
		vec_int rv;
		INTERLEAVED_UNROLL_1(rv, _mm256_castps_si256, q1);
		return rv; 
	};

	// reinterpret cast an int vector as a float one
	static vforceinline vec_float  reinterpret_cast_itof(const vec_int& q1)
	{ 
		vec_float rv;
		INTERLEAVED_UNROLL_1(rv, _mm256_castsi256_ps, q1);
		return rv; 
	};

	// helper for random number generators
	static vforceinline vec_int  set_random_seeds(const int32& seed0)
	{
		vec_int result;
		int32 seed1 = (seed0 * 176314165) + 903633515 + 1;
		int32 seed2 = (seed1 * 176314165) + 93633515 + 2;
		int32 seed3 = (seed2 * 17631165) + 903633515 + 6;
//#pragma unroll(intrlv)
		if (interleave > 0)result.m[0] = _mm256_set_epi32(seed0, seed1, seed2, seed3,seed0, seed1, seed2, seed3);
        if (interleave > 1)result.m[1] = _mm256_set_epi32(seed0, seed1, seed2, seed3,seed0, seed1, seed2, seed3);
        if (interleave > 2)result.m[2] = _mm256_set_epi32(seed0, seed1, seed2, seed3,seed0, seed1, seed2, seed3);
        if (interleave > 3)result.m[3] = _mm256_set_epi32(seed0, seed1, seed2, seed3,seed0, seed1, seed2, seed3);
		return result;
	};

	// Transcendental math helpers, probably belong in the base class.
	static vforceinline vec_float  axPOLY0(const vec_float& x, const vec_float& c0) { return c0; };
	static vforceinline vec_float  axPOLY1(const vec_float& x, const vec_float& c0, const vec_float& c1) { return addps(mulps(axPOLY0(x, c1), x), c0); };
	static vforceinline vec_float  axPOLY2(const vec_float& x, const vec_float& c0, const vec_float& c1, const vec_float& c2) { return addps(mulps(axPOLY1(x, c1, c2), x), c0); };
	static vforceinline vec_float  axPOLY3(const vec_float& x, const vec_float& c0, const vec_float& c1, const vec_float& c2, const vec_float& c3) { return addps(mulps(axPOLY2(x, c1, c2, c3), x), c0); };
	static vforceinline vec_float  axPOLY4(const vec_float& x, const vec_float& c0, const vec_float& c1, const vec_float& c2, const vec_float& c3, const vec_float& c4) { return addps(mulps(axPOLY3(x, c1, c2, c3, c4), x), c0); };

	// 2^X approximation, 4th order polynomial
	static vforceinline vec_float  fpow2ps_poly4(const vec_float& x)
	{
		vec_float xx = maxps(minps(x, 126.f), -126.f);

		/* ipart = int32(x) */ // Don't subtract 0.5, assume we're in ROUND DOWN mode.
		vec_int ipart = cvtps2epi32(xx);
		/* fpart = x - ipart */
		vec_float fpart = subps(xx, floorps(xx));

		/* expipart = (float) (1 << ipart) */
		// vec_int expipart = slliepi32_23(addepi32(ipart, 127));

#if MATHOPS_AVX_FMA
		const vec_int expipart = slliepi32_23(addepi32(ipart, 127));
#else
		__m128i k127 = _mm_set1_epi32(127);
		vec_int__128 loword1, hiword1; // low and hi words for shift operations
		vec_int expipart;	// 256bit container for reassembled result

		INTERLEAVED_UNROLL_1K(loword1, _mm256_extractf128_si256, ipart, 0);
		INTERLEAVED_UNROLL_1K(hiword1, _mm256_extractf128_si256, ipart, 1);
		INTERLEAVED_UNROLL_1K(loword1, _mm_add_epi32, loword1, k127); //-- IS THIS CORRECT? (Appears to be so, if we want to return the result with a multiply)
		INTERLEAVED_UNROLL_1K(hiword1, _mm_add_epi32, hiword1, k127); //-- IS THIS CORRECT?
		INTERLEAVED_UNROLL_1K(loword1, _mm_slli_epi32, loword1, 23);
		INTERLEAVED_UNROLL_1K(hiword1, _mm_slli_epi32, hiword1, 23);

		INTERLEAVED_UNROLL_1(expipart, _mm256_castsi128_si256, loword1);
		INTERLEAVED_UNROLL_2K(expipart, _mm256_insertf128_si256, expipart, hiword1, 1);
#endif

		/* minimax polynomial fit of 2**x, in range [-0.5, 0.5[ */
		//expfpart = axPOLY4(fpart.m, 1.0f, 0.6960656421638072f, 0.224494337302845f, 0.07944023841053369f); // range [0,1] coeffs
		vec_float expfpart = axPOLY4(fpart, set1ps(1.0000026f), set1ps(6.9300383e-1f), set1ps(2.4144275e-1f), set1ps(5.2011464e-2f), set1ps(1.3534167e-2f));
		return mulps(reinterpret_cast_itof(expipart), expfpart);
	}

	// 2^X approximation, 2nd order polynomial
	static vforceinline vec_float  fpow2ps_poly2(const vec_float& x)
	{
		// clip the input to between sensible bounds
		vec_float xx = maxps(minps(x, 126.f), -126.f);
		// get an int
		vec_int ipart = cvtps2epi32(xx);
		//m remainder
		vec_float fpart = subps(xx, floorps(xx));

#if MATHOPS_AVX_FMA
		const vec_int expipart = slliepi32_23(addepi32(ipart, 127));
#else
		// add 127 & then shift left by 23
		__m128i k127 = _mm_set1_epi32(127);
		vec_int__128 loword1, hiword1; // low and hi words for shift operations
		vec_int expipart;	// 256bit container for reassembled result

		INTERLEAVED_UNROLL_1K(loword1, _mm256_extractf128_si256, ipart, 0);
		INTERLEAVED_UNROLL_1K(hiword1, _mm256_extractf128_si256, ipart, 1);
		INTERLEAVED_UNROLL_1K(loword1, _mm_add_epi32, loword1, k127); //-- IS THIS CORRECT? (Appears to be so, if we want to return the result with a multiply)
		INTERLEAVED_UNROLL_1K(hiword1, _mm_add_epi32, hiword1, k127); //-- IS THIS CORRECT?
		INTERLEAVED_UNROLL_1K(loword1, _mm_slli_epi32, loword1, 23);
		INTERLEAVED_UNROLL_1K(hiword1, _mm_slli_epi32, hiword1, 23);

		INTERLEAVED_UNROLL_1(expipart, _mm256_castsi128_si256, loword1);
		INTERLEAVED_UNROLL_2K(expipart, _mm256_insertf128_si256, expipart, hiword1, 1);
#endif

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
	static vforceinline vec_float  vec_dtof(const vec_double& vd)
	{
		vec_float r;
		if (intrlv > 0)	{	
		r.m[0] = _mm256_castps128_ps256(_mm256_cvtpd_ps(vd.m[0]));
		r.m[0] = _mm256_insertf128_ps(r.m[0], _mm256_cvtpd_ps(vd.m[1]), 1);
		}
		if (intrlv > 1) {
			r.m[1] = _mm256_castps128_ps256(_mm256_cvtpd_ps(vd.m[2]));
			r.m[1] = _mm256_insertf128_ps(r.m[1], _mm256_cvtpd_ps(vd.m[3]), 1);
		}
		if (intrlv > 2) {
			r.m[2] = _mm256_castps128_ps256(_mm256_cvtpd_ps(vd.m[4]));
			r.m[2] = _mm256_insertf128_ps(r.m[2], _mm256_cvtpd_ps(vd.m[5]), 1);
		}
		if (intrlv > 3) {
			r.m[3] = _mm256_castps128_ps256(_mm256_cvtpd_ps(vd.m[6]));
			r.m[3] = _mm256_insertf128_ps(r.m[3], _mm256_cvtpd_ps(vd.m[7]), 1);
		}

		return r;
	}

	//////////////////////////////////////
	// Float to double
	static vforceinline vec_double  vec_ftod(const vec_float& vd)
	{
		vec_double r;
		if (intrlv > 0) {
			r.m[0] = _mm256_cvtps_pd(_mm256_castps256_ps128(vd.m[0]));
			__m256 swapped = _mm256_permute2f128_ps(vd.m[0], vd.m[0], 1);
			r.m[1] = _mm256_cvtps_pd(_mm256_castps256_ps128(swapped));
		}
		if (intrlv > 1) {
			r.m[2] = _mm256_cvtps_pd(_mm256_castps256_ps128(vd.m[1]));
			__m256 swapped = _mm256_permute2f128_ps(vd.m[1], vd.m[1], 1);
			r.m[3] = _mm256_cvtps_pd(_mm256_castps256_ps128(swapped));
		}
		if (intrlv > 2) {
			r.m[4] = _mm256_cvtps_pd(_mm256_castps256_ps128(vd.m[2]));
			__m256 swapped = _mm256_permute2f128_ps(vd.m[2], vd.m[2], 1);
			r.m[5] = _mm256_cvtps_pd(_mm256_castps256_ps128(swapped));
		}
		if (intrlv > 3) {
			r.m[6] = _mm256_cvtps_pd(_mm256_castps256_ps128(vd.m[3]));
			__m256 swapped = _mm256_permute2f128_ps(vd.m[3], vd.m[3], 1);
			r.m[7] = _mm256_cvtps_pd(_mm256_castps256_ps128(swapped));
		}
		return r;
	}
	/////////////////////////////////////
	// Test if a vector is all zeros
	static vforceinline bool  vec_iszero(const vec_float& v)
	{
		int32 res = _mm256_testz_si256(_mm256_castps_si256(v.m[0]), _mm256_castps_si256(v.m[0]));
		if (intrlv > 1) {
			res += _mm256_testz_si256(_mm256_castps_si256(v.m[1]), _mm256_castps_si256(v.m[1]));
		}
		if (intrlv > 2) {
			res += _mm256_testz_si256(_mm256_castps_si256(v.m[2]), _mm256_castps_si256(v.m[2]));
		}
		if (intrlv > 3) {
			res += _mm256_testz_si256(_mm256_castps_si256(v.m[3]), _mm256_castps_si256(v.m[3]));
		}
		return (res == intrlv);
	}

	//////////////////////////////////////
	// Types and conversions for extracting to raw data
	//////////////////////////////////////

	union VECPRE32 vec_union_i32
	{
		vec_int_t mi[interleave];
		int32 i[vec_elem];
		float f[vec_elem];
		uint32 u[vec_elem];
		vec_float_t m[interleave];
	} VECPOST32;

	union VECPRE32 vec_union_f
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
	} VECPOST32;


	union VECPRE32 vec_union_d
	{
		double d[vec_elem];
		vec_double_t m[interleave * 2];
		vec_double mv;
		vec_union_d() {};
		vec_union_d(const vec_double& other) { mv = other; };
		~vec_union_d() {};
	} VECPOST32;

	static vforceinline void  get_union_i32(const vec_int& obj, vec_union_i32& result)
	{ 
		INTERLEAVED_INDEX_ASSIGN_T(result.mi, obj.m);
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

	static vforceinline void  vec_stream_store(float* destination, const vec_float& data)
	{
		// NB: Not using streaming stores - if 2 processing lanes share a cache line, this degrades perf.
		if (interleave >= 1) _mm256_store_ps(destination, data.m[0]);
		if (interleave >= 2) _mm256_store_ps(destination + 8, data.m[1]);
		if (interleave >= 3) _mm256_store_ps(destination + 16, data.m[2]);
		if (interleave >= 4) _mm256_store_ps(destination + 24, data.m[3]);
	};

};

#endif
