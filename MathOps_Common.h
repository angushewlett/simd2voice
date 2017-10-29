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

#define SIMDFUNC static vforceinline vec_float


#define GENERATE_INTERLEAVED_FUNCTION_2ARG(func_alias, sseop) SIMDFUNC func_alias(const vec_float& q1, const vec_float& q2)   { return simd_funcgen_2op<vec_float, vec_elem_t, sseop, interleave>(q1, q2); };
#define GENERATE_INTERLEAVED_FUNCTION_2ARG_K(func_alias, sseop, K) SIMDFUNC func_alias(const vec_float& q1, const vec_float& q2)   { return simd_funcgen_2op_k<vec_float, vec_elem_t, sseop, interleave, K>(q1, q2); };
#define GENERATE_INTERLEAVED_FUNCTION_1ARG(func_alias, sseop) SIMDFUNC func_alias(const vec_float& q1)   { return simd_funcgen_1op<vec_float, vec_elem_t, sseop, interleave>(q1); };


// Macros to generate wrapper functions around the compiler SIMD intrinsics
#define ARG2WRAPPER(t, x) inline static t wrap_##x (const t& a, const t& b) { return x(a,b); };
#define ARG2WRAPPERK(t, x) template<int k> inline static t wrap_##x (const t& a, const t& b) { return x(a,b,k); };
#define ARG1WRAPPER(t, x) inline static t wrap_##x (const t& a) { return x(a); };



template <typename container_t, typename elem_t, elem_t(&lambda)(const elem_t&), int loop_max> static inline container_t simd_funcgen_1op(const container_t& a)
{
    container_t result;
    if (loop_max > 0x0) result.m[0x0] = lambda(a.m[0x0]);
    if (loop_max > 0x1) result.m[0x1] = lambda(a.m[0x1]);
    if (loop_max > 0x2) result.m[0x2] = lambda(a.m[0x2]);
    if (loop_max > 0x3) result.m[0x3] = lambda(a.m[0x3]);
    if (loop_max > 0x4) result.m[0x4] = lambda(a.m[0x4]);
    if (loop_max > 0x5) result.m[0x5] = lambda(a.m[0x5]);
    if (loop_max > 0x6) result.m[0x6] = lambda(a.m[0x6]);
    if (loop_max > 0x7) result.m[0x7] = lambda(a.m[0x7]);
    if (loop_max > 0x8) result.m[0x8] = lambda(a.m[0x8]);
    if (loop_max > 0x9) result.m[0x9] = lambda(a.m[0x9]);
    if (loop_max > 0xA) result.m[0xA] = lambda(a.m[0xA]);
    if (loop_max > 0xB) result.m[0xB] = lambda(a.m[0xB]);
    if (loop_max > 0xC) result.m[0xC] = lambda(a.m[0xC]);
    if (loop_max > 0xD) result.m[0xD] = lambda(a.m[0xD]);
    if (loop_max > 0xE) result.m[0xE] = lambda(a.m[0xE]);
    if (loop_max > 0xF) result.m[0xF] = lambda(a.m[0xF]);
    return result;
};

template <typename container_t, int interleave> class InterleaverNew
{
public:
    typedef typename container_t::elem_t elem_t;
    typedef elem_t(&TwoArgFunCall)(const elem_t&, const elem_t&);
    template <TwoArgFunCall twoArg> static inline container_t simd_funcgen_2arg(const container_t& a, const container_t& b)
    {
        container_t result;
        for (int i = 0; i < interleave; i++)
        {
            result.m[i] = twoArg(a.m[i], b.m[i]);
        }
        return result;
    };
};

template <typename container_t,
        typename container_t::elem_t(&lambda)(const typename container_t::elem_t&,  const typename container_t::elem_t&), int loop_max> static inline container_t simd_funcgen_2op(const container_t& a, const container_t& b)
{
    container_t result;
    if (loop_max > 0x0) result.m[0x0] = lambda(a.m[0x0], b.m[0x0]);
    if (loop_max > 0x1) result.m[0x1] = lambda(a.m[0x1], b.m[0x1]);
    if (loop_max > 0x2) result.m[0x2] = lambda(a.m[0x2], b.m[0x2]);
    if (loop_max > 0x3) result.m[0x3] = lambda(a.m[0x3], b.m[0x3]);
    if (loop_max > 0x4) result.m[0x4] = lambda(a.m[0x4], b.m[0x4]);
    if (loop_max > 0x5) result.m[0x5] = lambda(a.m[0x5], b.m[0x5]);
    if (loop_max > 0x6) result.m[0x6] = lambda(a.m[0x6], b.m[0x6]);
    if (loop_max > 0x7) result.m[0x7] = lambda(a.m[0x7], b.m[0x7]);
    if (loop_max > 0x8) result.m[0x8] = lambda(a.m[0x8], b.m[0x8]);
    if (loop_max > 0x9) result.m[0x9] = lambda(a.m[0x9], b.m[0x9]);
    if (loop_max > 0xA) result.m[0xA] = lambda(a.m[0xA], b.m[0xA]);
    if (loop_max > 0xB) result.m[0xB] = lambda(a.m[0xB], b.m[0xB]);
    if (loop_max > 0xC) result.m[0xC] = lambda(a.m[0xC], b.m[0xC]);
    if (loop_max > 0xD) result.m[0xD] = lambda(a.m[0xD], b.m[0xD]);
    if (loop_max > 0xE) result.m[0xE] = lambda(a.m[0xE], b.m[0xE]);
    if (loop_max > 0xF) result.m[0xF] = lambda(a.m[0xF], b.m[0xF]);
    return result;
};



template <typename container_t, typename elem_t, elem_t(&lambda)(const elem_t&,  const elem_t&), int loop_max> static inline container_t simd_funcgen_2op(const container_t& a, const container_t& b)
{
    container_t result;
    if (loop_max > 0x0) result.m[0x0] = lambda(a.m[0x0], b.m[0x0]);
    if (loop_max > 0x1) result.m[0x1] = lambda(a.m[0x1], b.m[0x1]);
    if (loop_max > 0x2) result.m[0x2] = lambda(a.m[0x2], b.m[0x2]);
    if (loop_max > 0x3) result.m[0x3] = lambda(a.m[0x3], b.m[0x3]);
    if (loop_max > 0x4) result.m[0x4] = lambda(a.m[0x4], b.m[0x4]);
    if (loop_max > 0x5) result.m[0x5] = lambda(a.m[0x5], b.m[0x5]);
    if (loop_max > 0x6) result.m[0x6] = lambda(a.m[0x6], b.m[0x6]);
    if (loop_max > 0x7) result.m[0x7] = lambda(a.m[0x7], b.m[0x7]);
    if (loop_max > 0x8) result.m[0x8] = lambda(a.m[0x8], b.m[0x8]);
    if (loop_max > 0x9) result.m[0x9] = lambda(a.m[0x9], b.m[0x9]);
    if (loop_max > 0xA) result.m[0xA] = lambda(a.m[0xA], b.m[0xA]);
    if (loop_max > 0xB) result.m[0xB] = lambda(a.m[0xB], b.m[0xB]);
    if (loop_max > 0xC) result.m[0xC] = lambda(a.m[0xC], b.m[0xC]);
    if (loop_max > 0xD) result.m[0xD] = lambda(a.m[0xD], b.m[0xD]);
    if (loop_max > 0xE) result.m[0xE] = lambda(a.m[0xE], b.m[0xE]);
    if (loop_max > 0xF) result.m[0xF] = lambda(a.m[0xF], b.m[0xF]);
    return result;    
};

template <typename container_t, typename elem_t, elem_t(&lambda)(const elem_t&,  const elem_t&, const int32), int loop_max, int32 k> static inline container_t simd_funcgen_2op_k(const container_t& a, const container_t& b)
{
    container_t result;
    if (loop_max > 0x0) result.m[0x0] = lambda(a.m[0x0], b.m[0x0], k);
    if (loop_max > 0x1) result.m[0x1] = lambda(a.m[0x1], b.m[0x1], k);
    if (loop_max > 0x2) result.m[0x2] = lambda(a.m[0x2], b.m[0x2], k);
    if (loop_max > 0x3) result.m[0x3] = lambda(a.m[0x3], b.m[0x3], k);
    if (loop_max > 0x4) result.m[0x4] = lambda(a.m[0x4], b.m[0x4], k);
    if (loop_max > 0x5) result.m[0x5] = lambda(a.m[0x5], b.m[0x5], k);
    if (loop_max > 0x6) result.m[0x6] = lambda(a.m[0x6], b.m[0x6], k);
    if (loop_max > 0x7) result.m[0x7] = lambda(a.m[0x7], b.m[0x7], k);
    if (loop_max > 0x8) result.m[0x8] = lambda(a.m[0x8], b.m[0x8], k);
    if (loop_max > 0x9) result.m[0x9] = lambda(a.m[0x9], b.m[0x9], k);
    if (loop_max > 0xA) result.m[0xA] = lambda(a.m[0xA], b.m[0xA], k);
    if (loop_max > 0xB) result.m[0xB] = lambda(a.m[0xB], b.m[0xB], k);
    if (loop_max > 0xC) result.m[0xC] = lambda(a.m[0xC], b.m[0xC], k);
    if (loop_max > 0xD) result.m[0xD] = lambda(a.m[0xD], b.m[0xD], k);
    if (loop_max > 0xE) result.m[0xE] = lambda(a.m[0xE], b.m[0xE], k);
    if (loop_max > 0xF) result.m[0xF] = lambda(a.m[0xF], b.m[0xF], k);
    return result;
};




template <int loop_max_i, class container_t, class elem_t, elem_t(assign_func)(float)> class Interleaver
{
public:
    static constexpr int loop_max = loop_max_i;
    static inline void assignT(container_t& result, const container_t& a)
    {
        if (loop_max > 0x0) result.m[0x0] = a.m[0x0];
        if (loop_max > 0x1) result.m[0x1] = a.m[0x1];
        if (loop_max > 0x2) result.m[0x2] = a.m[0x2];
        if (loop_max > 0x3) result.m[0x3] = a.m[0x3];
        if (loop_max > 0x4) result.m[0x4] = a.m[0x4];
        if (loop_max > 0x5) result.m[0x5] = a.m[0x5];
        if (loop_max > 0x6) result.m[0x6] = a.m[0x6];
        if (loop_max > 0x7) result.m[0x7] = a.m[0x7];
        if (loop_max > 0x8) result.m[0x8] = a.m[0x8];
        if (loop_max > 0x9) result.m[0x9] = a.m[0x9];
        if (loop_max > 0xA) result.m[0xA] = a.m[0xA];
        if (loop_max > 0xB) result.m[0xB] = a.m[0xB];
        if (loop_max > 0xC) result.m[0xC] = a.m[0xC];
        if (loop_max > 0xD) result.m[0xD] = a.m[0xD];
        if (loop_max > 0xE) result.m[0xE] = a.m[0xE];
        if (loop_max > 0xF) result.m[0xF] = a.m[0xF];
        
        
        //    The proper way (MS compiler doesn't know how to do this,
        //    #pragma unroll 4
        //    for (int i = 0; i < loop_max; i++) result.m[i] = lambda(a.m[i], b.m[i]);
    };
    
    static inline container_t assignE(const elem_t& a)
    {
        container_t result;
        if (loop_max > 0x0) result.m[0x0] = a;
        if (loop_max > 0x1) result.m[0x1] = a;
        if (loop_max > 0x2) result.m[0x2] = a;
        if (loop_max > 0x3) result.m[0x3] = a;
        if (loop_max > 0x4) result.m[0x4] = a;
        if (loop_max > 0x5) result.m[0x5] = a;
        if (loop_max > 0x6) result.m[0x6] = a;
        if (loop_max > 0x7) result.m[0x7] = a;
        if (loop_max > 0x8) result.m[0x8] = a;
        if (loop_max > 0x9) result.m[0x9] = a;
        if (loop_max > 0xA) result.m[0xA] = a;
        if (loop_max > 0xB) result.m[0xB] = a;
        if (loop_max > 0xC) result.m[0xC] = a;
        if (loop_max > 0xD) result.m[0xD] = a;
        if (loop_max > 0xE) result.m[0xE] = a;
        if (loop_max > 0xF) result.m[0xF] = a;
        return result;
    };
    
    static inline container_t assignS(float f)
    {
        elem_t a = assign_func(f);
        container_t result;
        if (loop_max > 0x0) result.m[0x0] = a;
        if (loop_max > 0x1) result.m[0x1] = a;
        if (loop_max > 0x2) result.m[0x2] = a;
        if (loop_max > 0x3) result.m[0x3] = a;
        if (loop_max > 0x4) result.m[0x4] = a;
        if (loop_max > 0x5) result.m[0x5] = a;
        if (loop_max > 0x6) result.m[0x6] = a;
        if (loop_max > 0x7) result.m[0x7] = a;
        if (loop_max > 0x8) result.m[0x8] = a;
        if (loop_max > 0x9) result.m[0x9] = a;
        if (loop_max > 0xA) result.m[0xA] = a;
        if (loop_max > 0xB) result.m[0xB] = a;
        if (loop_max > 0xC) result.m[0xC] = a;
        if (loop_max > 0xD) result.m[0xD] = a;
        if (loop_max > 0xE) result.m[0xE] = a;
        if (loop_max > 0xF) result.m[0xF] = a;
        return result;
    };
    
    static inline container_t assignA(const elem_t (&a)[loop_max])
    {
        container_t result;
        if (loop_max > 0x0) result.m[0x0] = a[0x0];
        if (loop_max > 0x1) result.m[0x1] = a[0x1];
        if (loop_max > 0x2) result.m[0x2] = a[0x2];
        if (loop_max > 0x3) result.m[0x3] = a[0x3];
        if (loop_max > 0x4) result.m[0x4] = a[0x4];
        if (loop_max > 0x5) result.m[0x5] = a[0x5];
        if (loop_max > 0x6) result.m[0x6] = a[0x6];
        if (loop_max > 0x7) result.m[0x7] = a[0x7];
        if (loop_max > 0x8) result.m[0x8] = a[0x8];
        if (loop_max > 0x9) result.m[0x9] = a[0x9];
        if (loop_max > 0xA) result.m[0xA] = a[0xA];
        if (loop_max > 0xB) result.m[0xB] = a[0xB];
        if (loop_max > 0xC) result.m[0xC] = a[0xC];
        if (loop_max > 0xD) result.m[0xD] = a[0xD];
        if (loop_max > 0xE) result.m[0xE] = a[0xE];
        if (loop_max > 0xF) result.m[0xF] = a[0xF];
        
        return result;
    };
};




// This provides typedef aliases from base class to make function definitions cleaner (required for gcc), and 'using' import definitions required by LLVM-Clang
#define DEFINE_MATHOPS_IMPORTS \
	typedef typename TIOAdapter::vec_float vec_float;\
    typedef typename TIOAdapter::SampleInputStream SampleInputStream;\
    typedef typename TIOAdapter::SampleOutputStream SampleOutputStream;\
    typedef TIOAdapter IOAdapterImpl;\
	using TIOAdapter::set1ps;\
	using TIOAdapter::zerops;\
	using TIOAdapter::mulps;\
	using TIOAdapter::divps;\
	using TIOAdapter::addps;\
	using TIOAdapter::minps;\
	using TIOAdapter::subps;\
	using TIOAdapter::maxps;\
    using TIOAdapter::maskps;\
    using TIOAdapter::notps;\
	using TIOAdapter::get_union_f;\
	using TIOAdapter::orps;\
	using TIOAdapter::absps;\
	using TIOAdapter::vec_elem;\
    using TIOAdapter::cubeps;\
    using TIOAdapter::floorps;\
    using TIOAdapter::xorps;\
    using TIOAdapter::andps;\
    using TIOAdapter::clip01ps;\
    using TIOAdapter::clipps;\
    using TIOAdapter::rcpps;\
    using TIOAdapter::get_vector_f;\
    using TIOAdapter::loadps;\
    using TIOAdapter::sqrtps;\
    using TIOAdapter::cmpgeps;\
    using TIOAdapter::cmpgtps;\
    using TIOAdapter::cmpleps;\
    using TIOAdapter::cmpltps;\
    using TIOAdapter::cmpeqps;\
    using TIOAdapter::cmpneps;\
    using TIOAdapter::roundps;\
    using TIOAdapter::andnps;\


/*using TIOAdapter::set_random_seeds;\
using TIOAdapter::set1epi32;\
 using TIOAdapter::vec_ftod;\
 using TIOAdapter::vec_dtof;\
 using TIOAdapter::vec_iszero;\
	using TIOAdapter::slliepi32_23;\
	using TIOAdapter::srliepi32_9;\
 using TIOAdapter::srliepi32_23;\
	using TIOAdapter::cvtepi322ps;\
	using TIOAdapter::fpow2ps_poly2;\
	using TIOAdapter::fpow2ps_poly4;\
	using TIOAdapter::reinterpret_cast_ftoi;\
	using TIOAdapter::reinterpret_cast_itof;\
 using TIOAdapter::mulepi32;\
	using TIOAdapter::cvtps2epi32;\
	using TIOAdapter::addepi32;\
 using TIOAdapter::get_union_i32;\

 using TIOAdapter::fma;\
 using TIOAdapter::fms;\
 using TIOAdapter::fms1;\
 using TIOAdapter::issmallfps;\
 
 
 */

//    using MATHOPS_IO::vec_union_f;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Vector float type - class vec_float
//
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class MO, int32 interleave> class alignas(MO::alignment) vec_float_impl_t : public MO
{
public:
    
    typedef typename MO::vec_elem_t vec_elem_t;
    typedef typename MO::Inter Inter;
    typedef typename MO::vec_union_f vec_union_f;
    
    using MO::mulps;
    using MO::addps;
    using MO::subps;
    using MO::divps;
    using MO::minps;
    using MO::maxps;
    using MO::andps;
    using MO::orps;
    using MO::xorps;
    using MO::cmpltps;
    using MO::cmpgtps;
    using MO::cmpleps;
    using MO::cmpgeps;
    using MO::cmpeqps;
    using MO::cmpneps;
    
    vec_elem_t m[interleave];
    // Default ctor doesn't initialize. standard c++.
    vforceinline vec_float_impl_t() {};
    
    ////////////////////////////////
    // Copy constructors and assignment operators
    // Can take:- another vec_float_impl_t, a single vec_elem_t element which is copied to all, a single float copied to all.
    vforceinline vec_float_impl_t(const vec_float_impl_t& f) { *this = f; };
    vforceinline vec_float_impl_t(const vec_elem_t (&f)[interleave]) { *this = f; };
    vforceinline vec_float_impl_t(const float& f) { *this = f; };
    
    vforceinline vec_float_impl_t& operator=(const vec_float_impl_t& f)
    {
        Inter::assignT(*this, f);
        return *this;
    };
    
    vforceinline vec_float_impl_t& operator=(const vec_elem_t (&f)[interleave])
    {
        *this = Inter::assignA(f);
        return *this;
    };
    
    vforceinline vec_float_impl_t&  operator=(const float f)
    {
        *this = Inter::assignS(f);
        return *this;
    };
    
    friend vforceinline vec_float_impl_t operator* (float lhs, vec_float_impl_t rhs) { vec_float_impl_t tmp = vec_float_impl_t::set1ps(lhs) * rhs; return tmp; };
    friend vforceinline vec_float_impl_t operator+ (float lhs, vec_float_impl_t rhs) { vec_float_impl_t tmp = vec_float_impl_t::set1ps(lhs) + rhs; return tmp; };
    friend vforceinline vec_float_impl_t operator- (float lhs, vec_float_impl_t rhs) { vec_float_impl_t tmp = vec_float_impl_t::set1ps(lhs) - rhs; return tmp; };

    ////////////////////////////////
    // Basic maths: +,-,* (no divide, it's slow. if you want divide, figure out a faster way).
    vforceinline vec_float_impl_t   operator+(const vec_float_impl_t& m2) const
    {
        return addps(*this, m2);
    };
    vforceinline vec_float_impl_t   operator-(const vec_float_impl_t& m2) const
    {
        return subps(*this, m2);
    };
    vforceinline vec_float_impl_t   operator*(const vec_float_impl_t& m2) const
    {
        return 	mulps(*this, m2);
    };
    
    vforceinline vec_float_impl_t   operator>(const vec_float_impl_t& m2) const
    {
        return 	cmpgtps(*this, m2);
    };
    
    vforceinline vec_float_impl_t   operator>=(const vec_float_impl_t& m2) const
    {
        return 	cmpgeps(*this, m2);
    };
    
    vforceinline vec_float_impl_t   operator<(const vec_float_impl_t& m2) const
    {
        return 	cmpltps(*this, m2);
    };
    
    vforceinline vec_float_impl_t   operator<=(const vec_float_impl_t& m2) const
    {
        return 	cmpleps(*this, m2);
    };
    
    vforceinline vec_float_impl_t   operator==(const vec_float_impl_t& m2) const
    {
        return 	cmpeqps(*this, m2);
    };
    
    vforceinline vec_float_impl_t   operator!=(const vec_float_impl_t& m2) const
    {
        return 	cmpneps(*this, m2);
    };
    
    vforceinline vec_float_impl_t   operator&(const vec_float_impl_t& m2) const
    {
        return 	andps(*this, m2);
    };
    
    vforceinline vec_float_impl_t&  operator!() const
    {
        return notps(*this);
    };
    
    ////////////////////////////////
    // In-place maths: +,-,* with assignment, vector versions.
    vforceinline vec_float_impl_t&   operator+=(const vec_float_impl_t& f)
    {
        *this = addps(*this, f);
        return *this;
    };
    vforceinline vec_float_impl_t&   operator-=(const vec_float_impl_t& f)
    {
        *this = subps(*this, f);
        return *this;
    };
    vforceinline vec_float_impl_t&   operator*=(const vec_float_impl_t& f)
    {
        *this = mulps(*this, f);
        return *this;
    };
    
    ////////////////////////////////
    // In-place maths: +,-,* with assignment, scalar constant versions
    vforceinline vec_float_impl_t&  operator+=(const float f)
    {
        vec_float_impl_t tmp_f = f;
        *this = addps(*this, tmp_f);
        return *this;
    };
    
    vforceinline vec_float_impl_t&  operator-=(const float f)
    {
        vec_float_impl_t tmp_f = f;
        *this = subps(*this, tmp_f);
        return *this;
    };
    
    vforceinline vec_float_impl_t&  operator*=(const float f)
    {
        vec_float_impl_t tmp_f = f;
        *this = mulps(*this, tmp_f);
        return *this;
    };
    
    ////////////////////////////////
    // In-place clip functions: with vector bounds, with scalar const bounds, with input & vector bounds, with input & scalar const bounds
    vforceinline void  clip(const vec_float_impl_t& lo_lim, const vec_float_impl_t& hi_lim)
    {
        *this = minps( maxps(*this, lo_lim), hi_lim);
    };
    
    vforceinline void  clip(const float lo_lim, const float hi_lim)
    {
        vec_float_impl_t hi_lim_v = hi_lim;
        vec_float_impl_t lo_lim_v = lo_lim;
        *this = minps( maxps(*this, lo_lim_v), hi_lim_v);
    };
    
    vforceinline void clip_v(const vec_float_impl_t& val, const vec_float_impl_t& lo_lim, const vec_float_impl_t& hi_lim)
    {
        *this = minps( maxps(val, lo_lim), hi_lim);
    };
    
    vforceinline void  clip_v(const vec_float_impl_t& val, const float lo_lim, const float hi_lim)
    {
        vec_float_impl_t hi_lim_v = hi_lim;
        vec_float_impl_t lo_lim_v = lo_lim;
        *this = minps( maxps(val, lo_lim_v), hi_lim_v);
    };
    
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
} __attribute__ ((aligned (MO::alignment)));



#endif
