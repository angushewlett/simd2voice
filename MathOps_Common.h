#ifndef MATHOPS_COMMON_H
#define MATHOPS_COMMON_H

#if ARCH_X86 || ARCH_X64
#include <immintrin.h>
#endif

///////////////////////////////////
// Defines common macros for MathOps headers (AVX, SSE, scalar).
// Author: Angus F. Hewlett
// Copyright FXpansion Audio UK Ltd. 2014
///////////////////////////////////

////////////////////////////////
// This file provides:-
//
// * Interleaving macros (for compile time pseudo-"loop unrolling"). M$ compiler is dumb about loop unrolling, compile-time IFs work better. Really.
// NB: "intrlv" is a compile-time constant, the if-statements will not generate any branches in the code!
//
// * "typedef" and "using" aliases to import defs from the MATHOPS base class (which are required by gcc and llvm-clang)
//
////////////////////////////////

/*#ifdef __VELLOCET_VSIMD_H__
#error Sorry, this code can't be mixed in the same cpp as VSIMD.
#endif
*/


#define INTERLEAVED_SINGLE_ASSIGN(result, value_token)\
	if (intrlv > 0) result.m[0] = value_token;\
	if (intrlv > 1) result.m[1] = value_token; \
	if (intrlv > 2) result.m[2] = value_token; \
	if (intrlv > 3) result.m[3] = value_token; /*\
	if (intrlv > 4) result.m[4] = value_token; \
	if (intrlv > 5) result.m[5] = value_token; \
	if (intrlv > 6) result.m[6] = value_token; \
	if (intrlv > 7) result.m[7] = value_token; */

#define INTERLEAVED_INDEX_ASSIGN(result, value_token)\
	if (intrlv > 0) result.m[0] = value_token[0];\
	if (intrlv > 1) result.m[1] = value_token[1]; \
	if (intrlv > 2) result.m[2] = value_token[2]; \
	if (intrlv > 3) result.m[3] = value_token[3]; /*\
	if (intrlv > 4) result.m[4] = value_token[4]; \
	if (intrlv > 5) result.m[5] = value_token[5]; \
	if (intrlv > 6) result.m[6] = value_token[6]; \
	if (intrlv > 7) result.m[7] = value_token[7]; */

#define INTERLEAVED_INDEX_ASSIGN_T(result_token, value_token)\
	if (intrlv > 0) result_token[0] = value_token[0];\
	if (intrlv > 1) result_token[1] = value_token[1]; \
	if (intrlv > 2) result_token[2] = value_token[2]; \
	if (intrlv > 3) result_token[3] = value_token[3]; /*\
	if (intrlv > 4) result_token[4] = value_token[4]; \
	if (intrlv > 5) result_token[5] = value_token[5]; \
	if (intrlv > 6) result_token[6] = value_token[6]; \
	if (intrlv > 7) result_token[7] = value_token[7]; */

#define INTERLEAVED_SINGLE_ASSIGN_P(result, value_token, intp)\
	if (intp > 0) result.m[0] = value_token;\
	if (intp > 1) result.m[1] = value_token; \
	if (intp > 2) result.m[2] = value_token; \
	if (intp > 3) result.m[3] = value_token; /*\
	if (intrlv > 4) result.m[4] = value_token; \
	if (intrlv > 5) result.m[5] = value_token; \
	if (intrlv > 6) result.m[6] = value_token; \
	if (intrlv > 7) result.m[7] = value_token; */

#define INTERLEAVED_INDEX_ASSIGN_P(result, value_token, intp)\
	if (intp > 0) result.m[0] = value_token[0];\
	if (intp > 1) result.m[1] = value_token[1]; \
	if (intp > 2) result.m[2] = value_token[2]; \
	if (intp > 3) result.m[3] = value_token[3]; /*\
	if (intp > 4) result.m[4] = value_token[4]; \
	if (intp > 5) result.m[5] = value_token[5]; \
	if (intp > 6) result.m[6] = value_token[6]; \
	if (intp > 7) result.m[7] = value_token[7]; */

#define INTERLEAVED_INDEX_ASSIGN_TP(result_token, value_token, intp)\
	if (intp > 0) result_token[0] = value_token[0];\
	if (intp > 1) result_token[1] = value_token[1]; \
	if (intp > 2) result_token[2] = value_token[2]; \
	if (intp > 3) result_token[3] = value_token[3]; /*\
	if (intrlv > 4) result_token[4] = value_token[4]; \
	if (intrlv > 5) result_token[5] = value_token[5]; \
	if (intrlv > 6) result_token[6] = value_token[6]; \
	if (intrlv > 7) result_token[7] = value_token[7]; */


#define INTERLEAVED_UNROLL_1(result, oper, ar1)\
	if (intrlv > 0) result.m[0] = oper(ar1.m[0]);\
	if (intrlv > 1) result.m[1] = oper(ar1.m[1]); \
	if (intrlv > 2) result.m[2] = oper(ar1.m[2]); \
	if (intrlv > 3) result.m[3] = oper(ar1.m[3]); /*\
	if (intrlv > 4) result.m[4] = oper(ar1.m[4]); \
	if (intrlv > 5) result.m[5] = oper(ar1.m[5]); \
	if (intrlv > 6) result.m[6] = oper(ar1.m[6]); \
	if (intrlv > 7) result.m[7] = oper(ar1.m[7]); */

#define INTERLEAVED_UNROLL_OP(result, oper, ar1, ar2)\
	if (intrlv > 0) result.m[0] = ar1.m[0] oper ar2.m[0];\
	if (intrlv > 1) result.m[1] = ar1.m[1] oper ar2.m[1];\
	if (intrlv > 2) result.m[2] = ar1.m[2] oper ar2.m[2];\
	if (intrlv > 3) result.m[3] = ar1.m[3] oper ar2.m[3];/*\
	if (intrlv > 4) result.m[4] = ar1.m[4] oper ar2.m[4];\
	if (intrlv > 5) result.m[5] = ar1.m[5] oper ar2.m[5];\
	if (intrlv > 6) result.m[6] = ar1.m[6] oper ar2.m[6];\
	if (intrlv > 7) result.m[7] = ar1.m[7] oper ar2.m[7];\*/

#if ARCH_ARM
#define INTERLEAVED_UNROLL_1K(result, oper, ar1, k)\
if (intrlv > 0) result.m[0] = vreinterpretq_s32_u32(oper(vreinterpretq_u32_s32(ar1.m[0]), k));\
if (intrlv > 1) result.m[1] = vreinterpretq_s32_u32(oper(vreinterpretq_u32_s32(ar1.m[1]), k));\
if (intrlv > 2) result.m[2] = vreinterpretq_s32_u32(oper(vreinterpretq_u32_s32(ar1.m[2]), k));\
if (intrlv > 3) result.m[3] = vreinterpretq_s32_u32(oper(vreinterpretq_u32_s32(ar1.m[3]), k));
#else
#define INTERLEAVED_UNROLL_1K(result, oper, ar1, k)\
	if (intrlv > 0) result.m[0] = oper(ar1.m[0], k);\
	if (intrlv > 1) result.m[1] = oper(ar1.m[1], k); \
	if (intrlv > 2) result.m[2] = oper(ar1.m[2], k); \
	if (intrlv > 3) result.m[3] = oper(ar1.m[3], k); 
#endif

/*\
	if (intrlv > 4) result.m[4] = oper(ar1.m[4], k); \
	if (intrlv > 5) result.m[5] = oper(ar1.m[5], k); \
	if (intrlv > 6) result.m[6] = oper(ar1.m[6], k); \
	if (intrlv > 7) result.m[7] = oper(ar1.m[7], k); */

#define INTERLEAVED_UNROLL_2(result, oper, ar1, ar2)\
	if (intrlv > 0) result.m[0] = oper(ar1.m[0], ar2.m[0]);\
	if (intrlv > 1) result.m[1] = oper(ar1.m[1], ar2.m[1]); \
	if (intrlv > 2) result.m[2] = oper(ar1.m[2], ar2.m[2]); \
	if (intrlv > 3) result.m[3] = oper(ar1.m[3], ar2.m[3]); /*\
	if (intrlv > 4) result.m[4] = oper(ar1.m[4], ar2.m[4]); \
	if (intrlv > 5) result.m[5] = oper(ar1.m[5], ar2.m[5]); \
	if (intrlv > 6) result.m[6] = oper(ar1.m[6], ar2.m[6]); \
	if (intrlv > 7) result.m[7] = oper(ar1.m[7], ar2.m[7]); */

#define INTERLEAVED_UNROLL_2D(result, oper, ar1, ar2)\
	if (2*intrlv > 0) result.m[0] = oper(ar1.m[0], ar2.m[0]);\
	if (2*intrlv > 1) result.m[1] = oper(ar1.m[1], ar2.m[1]); \
	if (2*intrlv > 2) result.m[2] = oper(ar1.m[2], ar2.m[2]); \
	if (2*intrlv > 3) result.m[3] = oper(ar1.m[3], ar2.m[3]); \
	if (2*intrlv > 4) result.m[4] = oper(ar1.m[4], ar2.m[4]); \
	if (2*intrlv > 5) result.m[5] = oper(ar1.m[5], ar2.m[5]); \
	if (2*intrlv > 6) result.m[6] = oper(ar1.m[6], ar2.m[6]); \
	if (2*intrlv > 7) result.m[7] = oper(ar1.m[7], ar2.m[7]);

#define INTERLEAVED_UNROLL_2K(result, oper, ar1, ar2, k)\
	if (intrlv > 0) result.m[0] = oper(ar1.m[0], ar2.m[0], k);\
	if (intrlv > 1) result.m[1] = oper(ar1.m[1], ar2.m[1], k); \
	if (intrlv > 2) result.m[2] = oper(ar1.m[2], ar2.m[2], k); \
	if (intrlv > 3) result.m[3] = oper(ar1.m[3], ar2.m[3], k);/* \
	if (intrlv > 4) result.m[4] = oper(ar1.m[4], ar2.m[4], k); \
	if (intrlv > 5) result.m[5] = oper(ar1.m[5], ar2.m[5], k); \
	if (intrlv > 6) result.m[6] = oper(ar1.m[6], ar2.m[6], k); \
	if (intrlv > 7) result.m[7] = oper(ar1.m[7], ar2.m[7], k); */


#if 1 // ARCH_X86 || ARCH_X64
// avx512 only - logical functions take INT
#define INTERLEAVED_UNROLL_2I(result, oper, ar1, ar2)\
if (intrlv > 0) result.m[0] = _mm512_castsi512_ps(oper(_mm512_castps_si512(ar1.m[0]),_mm512_castps_si512(ar2.m[0])));\
if (intrlv > 1) result.m[1] = _mm512_castsi512_ps(oper(_mm512_castps_si512(ar1.m[1]),_mm512_castps_si512(ar2.m[1])));\
if (intrlv > 2) result.m[2] = _mm512_castsi512_ps(oper(_mm512_castps_si512(ar1.m[2]),_mm512_castps_si512(ar2.m[2])));\
if (intrlv > 3) result.m[3] = _mm512_castsi512_ps(oper(_mm512_castps_si512(ar1.m[3]),_mm512_castps_si512(ar2.m[3])));
#else
// arm only - for logical functions which require reinterpret_casts to take float data
#define INTERLEAVED_UNROLL_1II(result, oper, ar1)\
if (intrlv > 0) result.m[0] = vreinterpretq_f32_u32(oper(vreinterpretq_u32_f32(ar1.m[0])));\
if (intrlv > 1) result.m[1] = vreinterpretq_f32_u32(oper(vreinterpretq_u32_f32(ar1.m[1]))); \
if (intrlv > 2) result.m[2] = vreinterpretq_f32_u32(oper(vreinterpretq_u32_f32(ar1.m[2]))); \
if (intrlv > 3) result.m[3] = vreinterpretq_f32_u32(oper(vreinterpretq_u32_f32(ar1.m[3])));


#define INTERLEAVED_UNROLL_2I(result, oper, ar1, ar2)\
if (intrlv > 0) result.m[0] = vreinterpretq_f32_u32(oper(ar1.m[0], ar2.m[0]));\
if (intrlv > 1) result.m[1] = vreinterpretq_f32_u32(oper(ar1.m[1], ar2.m[1])); \
if (intrlv > 2) result.m[2] = vreinterpretq_f32_u32(oper(ar1.m[2], ar2.m[2])); \
if (intrlv > 3) result.m[3] = vreinterpretq_f32_u32(oper(ar1.m[3], ar2.m[3])); /* \
if (intrlv > 4) result.m[4] = vreinterpretq_f32_s32(oper(ar1.m[4], ar2.m[4])); \
if (intrlv > 5) result.m[5] = vreinterpretq_f32_s32(oper(ar1.m[5], ar2.m[5])); \
if (intrlv > 6) result.m[6] = vreinterpretq_f32_s32(oper(ar1.m[6], ar2.m[6])); \
if (intrlv > 7) result.m[7] = vreinterpretq_f32_s32(oper(ar1.m[7], ar2.m[7]));*/
#endif

#define INTERLEAVED_UNROLL_2III(result, oper, ar1, ar2)\
if (intrlv > 0) result.m[0] = vreinterpretq_f32_u32(oper(vreinterpretq_u32_f32(ar1.m[0]), vreinterpretq_u32_f32(ar2.m[0])));\
if (intrlv > 1) result.m[1] = vreinterpretq_f32_u32(oper(vreinterpretq_u32_f32(ar1.m[1]), vreinterpretq_u32_f32(ar2.m[1]))); \
if (intrlv > 2) result.m[2] = vreinterpretq_f32_u32(oper(vreinterpretq_u32_f32(ar1.m[2]), vreinterpretq_u32_f32(ar2.m[2]))); \
if (intrlv > 3) result.m[3] = vreinterpretq_f32_u32(oper(vreinterpretq_u32_f32(ar1.m[3]), vreinterpretq_u32_f32(ar2.m[3]))); /*\
if (intrlv > 4) result.m[4] = vreinterpretq_f32_s32(oper(vreinterpretq_s32_f32(ar1.m[4]), vreinterpretq_s32_f32(ar2.m[4]))); \
if (intrlv > 5) result.m[5] = vreinterpretq_f32_s32(oper(vreinterpretq_s32_f32(ar1.m[5]), vreinterpretq_s32_f32(ar2.m[5]))); \
if (intrlv > 6) result.m[6] = vreinterpretq_f32_s32(oper(vreinterpretq_s32_f32(ar1.m[6]), vreinterpretq_s32_f32(ar2.m[6]))); \
if (intrlv > 7) result.m[7] = vreinterpretq_f32_s32(oper(vreinterpretq_s32_f32(ar1.m[7]), vreinterpretq_s32_f32(ar2.m[7])));*/

#define INTERLEAVED_UNROLL_3(result, oper, ar1, ar2, ar3)\
	if (intrlv > 0) result.m[0] = oper(ar1.m[0], ar2.m[0], ar3.m[0]);\
	if (intrlv > 1) result.m[1] = oper(ar1.m[1], ar2.m[1], ar3.m[1]); \
	if (intrlv > 2) result.m[2] = oper(ar1.m[2], ar2.m[2], ar3.m[2]); \
	if (intrlv > 3) result.m[3] = oper(ar1.m[3], ar2.m[3], ar3.m[3]); /*\
	if (intrlv > 4) result.m[4] = oper(ar1.m[4], ar2.m[4], ar3.m[4]); \
	if (intrlv > 5) result.m[5] = oper(ar1.m[5], ar2.m[5], ar3.m[5]); \
	if (intrlv > 6) result.m[6] = oper(ar1.m[6], ar2.m[6], ar3.m[6]); \
	if (intrlv > 7) result.m[7] = oper(ar1.m[7], ar2.m[7], ar3.m[7]); */


	/* These macros generate the equivalent of
	static vforceinline vec_float addps(const vec_float& q1, const vec_float& q2)
	{
		vec_float rv;
		INTERLEAVED_UNROLL_2(rv, _mm_add_ps, q1, q2);
		return rv;
	};*/

	// Three arguments (fmadd, fmsub)
#define GENERATE_INTERLEAVED_FUNCTION_3ARG(func_alias, sseop) \
	static vforceinline vec_float  func_alias(const vec_float& q1, const vec_float& q2, const vec_float& q3)   { vec_float rv; INTERLEAVED_UNROLL_3(rv, sseop, q1, q2, q3); return rv; }


// One argument (eg. fabs, sin, floor)
#define GENERATE_INTERLEAVED_FUNCTION_1ARG(func_alias, sseop) \
	static vforceinline vec_float  func_alias(const vec_float& q1)   { vec_float rv; INTERLEAVED_UNROLL_1(rv, sseop, q1); return rv; }

#define GENERATE_INTERLEAVED_FUNCTION_1ARG_II(func_alias, sseop) \
	static vforceinline vec_float  func_alias(const vec_float& q1)   { vec_float rv; INTERLEAVED_UNROLL_1II(rv, sseop, q1); return rv; }

// Two arguments (mul, add)
#define GENERATE_INTERLEAVED_FUNCTION_2ARG(func_alias, sseop) \
	static vforceinline vec_float  func_alias(const vec_float& q1, const vec_float& q2)   { vec_float rv; INTERLEAVED_UNROLL_2(rv, sseop, q1, q2); return rv; }

// Two arguments (mul, add) - integer args & result
#define GENERATE_INTERLEAVED_FUNCTION_2ARG_INT(func_alias, sseop) \
	static vforceinline vec_int  func_alias(const vec_int& q1, const vec_int& q2)   { vec_int rv; INTERLEAVED_UNROLL_2(rv, sseop, q1, q2); return rv; }

// Two arguments, return value reintepreted from int to float (NEON compare intrinsics)
#define GENERATE_INTERLEAVED_FUNCTION_2ARG_IFF(func_alias, sseop) \
static vforceinline vec_float  func_alias(const vec_float& q1, const vec_float& q2)   { vec_float rv; INTERLEAVED_UNROLL_2I(rv, sseop, q1, q2); return rv; }

// Two arguments, arguments and return value reintepreted from int to float (NEON compare intrinsics)
#define GENERATE_INTERLEAVED_FUNCTION_2ARG_III(func_alias, sseop) \
static vforceinline vec_float  func_alias(const vec_float& q1, const vec_float& q2)   { vec_float rv;INTERLEAVED_UNROLL_2III(rv, sseop, q1, q2); return rv; }


// One operator argument
#define GENERATE_INTERLEAVED_FUNCTION_OP(func_alias, op) \
	static vforceinline vec_float  func_alias(const vec_float& q1, const vec_float& q2)   { vec_float rv; INTERLEAVED_UNROLL_OP(rv, op, q1, q2); return rv; }

// Two arguments plus a constant (compare instructions with mode)
#define GENERATE_INTERLEAVED_FUNCTION_2ARG_K(func_alias, sseop, const_val) \
	static vforceinline vec_float  func_alias(const vec_float& q1, const vec_float& q2)   { vec_float rv; INTERLEAVED_UNROLL_2K(rv, sseop, q1, q2, const_val); return rv; }

// Double precision, two arguments (mul, add)
#define GENERATE_INTERLEAVED_FUNCTION_2ARG_D(func_alias, sseop) \
	static vforceinline vec_double  func_alias(const vec_double& q1, const vec_double& q2)   { vec_double rv; INTERLEAVED_UNROLL_2D(rv, sseop, q1, q2); return rv; }


// This provides typedef aliases from base class to make function definitions cleaner (required for gcc), and 'using' import definitions required by LLVM-Clang
#define DEFINE_MATHOPS_IMPORTS \
	typedef typename TIOAdapter::vec_float vec_float;\
    typedef typename TIOAdapter::SampleInputStream SampleInputStream;\
    typedef typename TIOAdapter::SampleOutputStream SampleOutputStream;\
    typedef TIOAdapter IOAdapterImpl;\
	using TIOAdapter::set1ps;\
	using TIOAdapter::set_random_seeds;\
	using TIOAdapter::set1epi32;\
	using TIOAdapter::zerops;\
	using TIOAdapter::mulps;\
	using TIOAdapter::divps;\
	using TIOAdapter::addps;\
	using TIOAdapter::minps;\
	using TIOAdapter::subps;\
	using TIOAdapter::maxps;\
    using TIOAdapter::maskps;\
    using TIOAdapter::notps;\
	using TIOAdapter::get_union_i32;\
	using TIOAdapter::get_union_f;\
	using TIOAdapter::mulepi32;\
	using TIOAdapter::cvtps2epi32;\
	using TIOAdapter::addepi32;\
	using TIOAdapter::orps;\
	using TIOAdapter::reinterpret_cast_ftoi;\
	using TIOAdapter::reinterpret_cast_itof;\
	using TIOAdapter::absps;\
	using TIOAdapter::slliepi32_23;\
	using TIOAdapter::srliepi32_9;\
    using TIOAdapter::srliepi32_23;\
	using TIOAdapter::cvtepi322ps;\
	using TIOAdapter::fpow2ps_poly2;\
	using TIOAdapter::fpow2ps_poly4;\
	using TIOAdapter::vec_elem;\
    using TIOAdapter::cubeps;\
    using TIOAdapter::floorps;\
    using TIOAdapter::xorps;\
    using TIOAdapter::andps;\
    using TIOAdapter::clip01ps;\
    using TIOAdapter::clipps;\
    using TIOAdapter::rcpps;\
    using TIOAdapter::get_vector_f;\
    using TIOAdapter::fma;\
    using TIOAdapter::fms;\
    using TIOAdapter::fms1;\
    using TIOAdapter::issmallfps;\
    using TIOAdapter::loadps;\
    using TIOAdapter::sqrtps;\
    using TIOAdapter::cmpgeps;\
    using TIOAdapter::cmpgtps;\
    using TIOAdapter::cmpleps;\
    using TIOAdapter::cmpltps;\
    using TIOAdapter::cmpeqps;\
    using TIOAdapter::cmpneps;\
    using TIOAdapter::vec_ftod;\
    using TIOAdapter::vec_dtof;\
    using TIOAdapter::vec_iszero;\
    using TIOAdapter::roundps;\
    using TIOAdapter::andnps;\


//    using MATHOPS_IO::vec_union_f;




#endif
