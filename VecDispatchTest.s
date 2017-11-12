	.text
	.file	"VecDispatchTest.cpp"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:
	pushq	%rax
.Lcfi0:
	.cfi_def_cfa_offset 16
	movl	$2, %edi
	callq	sleep
	vstmxcsr	4(%rsp)
	movl	4(%rsp), %eax
	orl	$64, %eax
	movl	%eax, (%rsp)
	vldmxcsr	(%rsp)
	movl	$.L.str, %edi
	callq	_Z8run_testI7YSawOsc14MathOps_AVX512ILi4EEEvPKc
	movl	$2, %edi
	callq	sleep
	xorl	%eax, %eax
	popq	%rcx
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3               # -- Begin function _Z8run_testI7YSawOsc14MathOps_AVX512ILi4EEEvPKc
.LCPI1_0:
	.quad	4741671816366391296     # double 1.0E+9
	.section	.rodata.cst4,"aM",@progbits,4
	.p2align	2
.LCPI1_1:
	.long	3204448256              # float -0.5
.LCPI1_2:
	.long	805306368               # float 4.65661287E-10
.LCPI1_3:
	.long	1082130432              # float 4
.LCPI1_4:
	.long	1065353216              # float 1
.LCPI1_5:
	.long	3212836864              # float -1
.LCPI1_7:
	.long	1073741824              # 0x40000000
.LCPI1_8:
	.long	2147483648              # float -0
.LCPI1_9:
	.long	1056964608              # float 0.5
.LCPI1_10:
	.long	1040187392              # float 0.125
.LCPI1_11:
	.long	1232348160              # float 1.0E+6
.LCPI1_12:
	.long	1015021568              # float 0.015625
.LCPI1_13:
	.long	1194083328              # float 44100
.LCPI1_14:
	.long	1031798784              # float 0.0625
	.section	.rodata,"a",@progbits
	.p2align	6
.LCPI1_6:
	.long	10560                   # 0x2940
	.long	9856                    # 0x2680
	.long	9152                    # 0x23c0
	.long	8448                    # 0x2100
	.long	7744                    # 0x1e40
	.long	7040                    # 0x1b80
	.long	6336                    # 0x18c0
	.long	5632                    # 0x1600
	.long	4928                    # 0x1340
	.long	4224                    # 0x1080
	.long	3520                    # 0xdc0
	.long	2816                    # 0xb00
	.long	2112                    # 0x840
	.long	1408                    # 0x580
	.long	704                     # 0x2c0
	.long	0                       # 0x0
	.section	.text._Z8run_testI7YSawOsc14MathOps_AVX512ILi4EEEvPKc,"axG",@progbits,_Z8run_testI7YSawOsc14MathOps_AVX512ILi4EEEvPKc,comdat
	.weak	_Z8run_testI7YSawOsc14MathOps_AVX512ILi4EEEvPKc
	.p2align	4, 0x90
	.type	_Z8run_testI7YSawOsc14MathOps_AVX512ILi4EEEvPKc,@function
_Z8run_testI7YSawOsc14MathOps_AVX512ILi4EEEvPKc: # @_Z8run_testI7YSawOsc14MathOps_AVX512ILi4EEEvPKc
.Lfunc_begin0:
	.cfi_startproc
	.cfi_personality 3, __gxx_personality_v0
	.cfi_lsda 3, .Lexception0
# BB#0:
	pushq	%rbp
.Lcfi1:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Lcfi2:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Lcfi3:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Lcfi4:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Lcfi5:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Lcfi6:
	.cfi_def_cfa_offset 56
	subq	$1032, %rsp             # imm = 0x408
.Lcfi7:
	.cfi_def_cfa_offset 1088
.Lcfi8:
	.cfi_offset %rbx, -56
.Lcfi9:
	.cfi_offset %r12, -48
.Lcfi10:
	.cfi_offset %r13, -40
.Lcfi11:
	.cfi_offset %r14, -32
.Lcfi12:
	.cfi_offset %r15, -24
.Lcfi13:
	.cfi_offset %rbp, -16
	movq	%rdi, %rbx
	movabsq	$4359484440359993344, %rax # imm = 0x3C8000003F800000
	movq	%rax, 152(%rsp)
	movl	$869711765, 160(%rsp)   # imm = 0x33D6BF95
	movabsq	$5168865736020214784, %rax # imm = 0x47BB8000472C4400
	movq	%rax, 168(%rsp)
	movl	$925811518, 176(%rsp)   # imm = 0x372EC33E
	movabsq	$274877907008, %rax     # imm = 0x4000000040
	movq	%rax, 136(%rsp)
	movl	$48, %edi
	callq	_Znwm
	movq	%rax, %r15
	vxorps	%ymm0, %ymm0, %ymm0
	vmovups	%ymm0, (%r15)
	vmovups	%ymm0, 16(%r15)
	movq	$_ZTVN4XDSP8NodeTmplI9YBasicAmpEE+16, (%r15)
	movq	$0, 192(%rsp)
	leaq	192(%rsp), %rdi
	movl	$64, %esi
	movl	$45056, %edx            # imm = 0xB000
	vzeroupper
	callq	posix_memalign
	movq	192(%rsp), %rax
	movq	%rax, 40(%r15)
	leaq	16(%r15), %rbp
.Ltmp0:
	movl	$64, %esi
	movq	%rbp, %rdi
	callq	_ZNSt6vectorIPN4XDSP4Node5VoiceESaIS3_EE17_M_default_appendEm
.Ltmp1:
# BB#1:
	movq	%rbp, 48(%rsp)          # 8-byte Spill
	movq	%rbx, 112(%rsp)         # 8-byte Spill
	xorl	%ecx, %ecx
	xorl	%esi, %esi
	.p2align	4, 0x90
.LBB1_2:                                # =>This Inner Loop Header: Depth=1
	movq	40(%r15), %rax
	movq	$_ZTVN9YBasicAmp5VoiceE+16, (%rax,%rcx)
	addq	%rcx, %rax
	movq	16(%r15), %rdx
	movq	%rax, (%rdx,%rsi,8)
	addq	$1, %rsi
	addq	$704, %rcx              # imm = 0x2C0
	cmpq	$64, %rsi
	jne	.LBB1_2
# BB#3:
	movq	$_ZTVN7YSawOsc4NodeE+16, (%r15)
	movq	$0, 192(%rsp)
	leaq	192(%rsp), %rdi
	movl	$64, %esi
	movl	$16384, %edx            # imm = 0x4000
	callq	posix_memalign
	movq	192(%rsp), %r13
	movq	$0, 192(%rsp)
	leaq	192(%rsp), %rdi
	movl	$64, %esi
	movl	$16384, %edx            # imm = 0x4000
	callq	posix_memalign
	movq	192(%rsp), %r14
	movl	$5, %edi
	callq	srand
	xorl	%r12d, %r12d
	movq	%r14, 56(%rsp)          # 8-byte Spill
	.p2align	4, 0x90
.LBB1_4:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_6 Depth 2
                                        #     Child Loop BB1_9 Depth 2
	movq	(%r15), %rax
	movq	%r15, %rdi
	callq	*24(%rax)
	testl	%eax, %eax
	jle	.LBB1_7
# BB#5:                                 #   in Loop: Header=BB1_4 Depth=1
	leaq	(,%r12,4), %rbx
	addq	%r13, %rbx
	xorl	%ebp, %ebp
	.p2align	4, 0x90
.LBB1_6:                                #   Parent Loop BB1_4 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	16(%r15), %rax
	movq	(%rax,%r12,8), %rax
	movq	%rbx, 520(%rax,%rbp,8)
	addq	$1, %rbp
	movq	(%r15), %rax
	movq	%r15, %rdi
	callq	*24(%rax)
	cltq
	cmpq	%rax, %rbp
	jl	.LBB1_6
.LBB1_7:                                #   in Loop: Header=BB1_4 Depth=1
	movq	(%r15), %rax
	movq	%r15, %rdi
	callq	*32(%rax)
	movq	16(%r15), %rcx
	movq	(%rcx,%r12,8), %rdi
	testl	%eax, %eax
	jle	.LBB1_10
# BB#8:                                 #   in Loop: Header=BB1_4 Depth=1
	leaq	(%r14,%r12,4), %r14
	xorl	%ebx, %ebx
	.p2align	4, 0x90
.LBB1_9:                                #   Parent Loop BB1_4 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%r14, 584(%rdi,%rbx,8)
	addq	$1, %rbx
	movq	(%r15), %rax
	movq	%r15, %rdi
	callq	*32(%rax)
	cltq
	movq	16(%r15), %rcx
	movq	(%rcx,%r12,8), %rdi
	cmpq	%rax, %rbx
	jl	.LBB1_9
.LBB1_10:                               #   in Loop: Header=BB1_4 Depth=1
	movq	(%rdi), %rax
	callq	*24(%rax)
	addq	$1, %r12
	cmpq	$64, %r12
	movq	56(%rsp), %r14          # 8-byte Reload
	jne	.LBB1_4
# BB#11:
	movq	$0, 192(%rsp)
	leaq	192(%rsp), %rdi
	movl	$64, %esi
	movl	$16384, %edx            # imm = 0x4000
	callq	posix_memalign
	movq	192(%rsp), %rax
	xorl	%ecx, %ecx
	movq	48(%rsp), %rbx          # 8-byte Reload
	.p2align	4, 0x90
.LBB1_12:                               # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_13 Depth 2
	movl	.L_ZZ8run_testI7YSawOsc14MathOps_AVX512ILi4EEEvPKcE14control_params(,%rcx,4), %edx
	xorl	%esi, %esi
	.p2align	4, 0x90
.LBB1_13:                               #   Parent Loop BB1_12 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	leaq	(%rax,%rsi), %rdi
	movl	%edx, (%rax,%rsi)
	movq	(%rbx), %rbp
	movq	(%rbp,%rsi,2), %rbp
	movq	%rdi, 8(%rbp,%rcx,8)
	addq	$4, %rsi
	cmpq	$256, %rsi              # imm = 0x100
	jne	.LBB1_13
# BB#14:                                #   in Loop: Header=BB1_12 Depth=1
	addq	$1, %rcx
	addq	$256, %rax              # imm = 0x100
	cmpq	$8, %rcx
	jne	.LBB1_12
# BB#15:
	movq	(%r15), %rax
	leaq	136(%rsp), %rsi
	movq	%r15, %rdi
	callq	*(%rax)
	movq	$_ZTV11Benchmarker+16, 64(%rsp)
	cmpb	$0, _ZN9StopWatch10s_bDidInitE(%rip)
	jne	.LBB1_17
# BB#16:
	movb	$1, _ZN9StopWatch10s_bDidInitE(%rip)
.LBB1_17:
	xorl	%ebx, %ebx
	leaq	192(%rsp), %rsi
	xorl	%edi, %edi
	callq	clock_gettime
	movq	192(%rsp), %rcx
	movabsq	$2361183241434822607, %rbp # imm = 0x20C49BA5E353F7CF
	movq	%rcx, %rax
	imulq	%rbp
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$7, %rdx
	addq	%rax, %rdx
	imulq	$1000, %rdx, %rax       # imm = 0x3E8
	subq	%rax, %rcx
	vcvtsi2sdq	%rcx, %xmm1, %xmm0
	vcvtsi2sdq	200(%rsp), %xmm1, %xmm1
	vfmadd231sd	.LCPI1_0(%rip), %xmm0, %xmm1
	vcvttsd2usi	%xmm1, %rax
	movq	%rax, 72(%rsp)
	cmpb	$0, _ZN9StopWatch10s_bDidInitE(%rip)
	jne	.LBB1_19
# BB#18:
	movb	$1, _ZN9StopWatch10s_bDidInitE(%rip)
.LBB1_19:
	leaq	192(%rsp), %rsi
	xorl	%edi, %edi
	callq	clock_gettime
	movq	192(%rsp), %rcx
	movq	%rcx, %rax
	imulq	%rbp
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$7, %rdx
	addq	%rax, %rdx
	imulq	$1000, %rdx, %rax       # imm = 0x3E8
	subq	%rax, %rcx
	vcvtsi2sdq	%rcx, %xmm2, %xmm0
	vcvtsi2sdq	200(%rsp), %xmm2, %xmm1
	vfmadd231sd	.LCPI1_0(%rip), %xmm0, %xmm1
	vcvttsd2usi	%xmm1, %rax
	movq	%rax, 80(%rsp)
	leaq	88(%rsp), %rbp
	movq	%rbp, 88(%rsp)
	movq	%rbp, 96(%rsp)
	movq	$0, 104(%rsp)
	vbroadcastss	.LCPI1_3(%rip), %zmm0 # zmm0 = [4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4]
	vmovups	%zmm0, 768(%rsp)        # 64-byte Spill
	vbroadcastss	.LCPI1_4(%rip), %zmm0 # zmm0 = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
	vmovups	%zmm0, 960(%rsp)        # 64-byte Spill
	vbroadcastss	.LCPI1_5(%rip), %zmm0 # zmm0 = [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1]
	vmovups	%zmm0, 704(%rsp)        # 64-byte Spill
	movl	$-1, %r12d
	vbroadcastss	.LCPI1_7(%rip), %zmm0 # zmm0 = [1073741824,1073741824,1073741824,1073741824,1073741824,1073741824,1073741824,1073741824,1073741824,1073741824,1073741824,1073741824,1073741824,1073741824,1073741824,1073741824]
	vmovups	%zmm0, 896(%rsp)        # 64-byte Spill
	vbroadcastss	.LCPI1_8(%rip), %zmm0 # zmm0 = [-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0]
	vmovups	%zmm0, 832(%rsp)        # 64-byte Spill
	movq	%r13, 120(%rsp)         # 8-byte Spill
	.p2align	4, 0x90
.LBB1_20:                               # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_21 Depth 2
                                        #     Child Loop BB1_23 Depth 2
                                        #       Child Loop BB1_25 Depth 3
	movq	%rbx, 128(%rsp)         # 8-byte Spill
	xorl	%ebx, %ebx
	.p2align	4, 0x90
.LBB1_21:                               #   Parent Loop BB1_20 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vzeroupper
	callq	rand
	vcvtsi2ssl	%eax, %xmm3, %xmm0
	vmovss	.LCPI1_1(%rip), %xmm1   # xmm1 = mem[0],zero,zero,zero
	vmovaps	%xmm1, %xmm2
	vmovss	.LCPI1_2(%rip), %xmm1   # xmm1 = mem[0],zero,zero,zero
	vfmadd213ss	%xmm2, %xmm1, %xmm0
	vaddss	%xmm0, %xmm0, %xmm0
	vmovss	%xmm0, (%r13,%rbx,4)
	callq	rand
	vcvtsi2ssl	%eax, %xmm3, %xmm0
	vmovss	.LCPI1_2(%rip), %xmm1   # xmm1 = mem[0],zero,zero,zero
	vfmadd213ss	.LCPI1_1(%rip), %xmm1, %xmm0
	vaddss	%xmm0, %xmm0, %xmm0
	vmovss	%xmm0, (%r14,%rbx,4)
	addq	$1, %rbx
	cmpq	$4096, %rbx             # imm = 0x1000
	jne	.LBB1_21
# BB#22:                                #   in Loop: Header=BB1_20 Depth=1
	xorl	%r14d, %r14d
	xorl	%edi, %edi
	leaq	192(%rsp), %rsi
	callq	clock_gettime
	movq	192(%rsp), %rcx
	movq	%rcx, %rax
	movabsq	$2361183241434822607, %rdx # imm = 0x20C49BA5E353F7CF
	imulq	%rdx
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$7, %rdx
	addq	%rax, %rdx
	imulq	$1000, %rdx, %rax       # imm = 0x3E8
	subq	%rax, %rcx
	vcvtsi2sdq	%rcx, %xmm3, %xmm0
	vcvtsi2sdq	200(%rsp), %xmm3, %xmm1
	vfmadd231sd	.LCPI1_0(%rip), %xmm0, %xmm1
	vcvttsd2usi	%xmm1, %rax
	movq	%rax, 80(%rsp)
	movl	136(%rsp), %r13d
	movq	48(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rbx
	.p2align	4, 0x90
.LBB1_23:                               #   Parent Loop BB1_20 Depth=1
                                        # =>  This Loop Header: Depth=2
                                        #       Child Loop BB1_25 Depth 3
	movl	$512, %edx              # imm = 0x200
	leaq	192(%rsp), %rdi
	movq	%rbx, %rsi
	vzeroupper
	callq	memcpy
	testl	%r13d, %r13d
	vmovups	960(%rsp), %zmm24       # 64-byte Reload
	vxorps	%zmm25, %zmm25, %zmm25
	vmovdqu64	896(%rsp), %zmm26 # 64-byte Reload
	vmovups	832(%rsp), %zmm27       # 64-byte Reload
	jle	.LBB1_26
# BB#24:                                #   in Loop: Header=BB1_23 Depth=2
	movq	192(%rsp), %rcx
	movq	8(%rcx), %rax
	vmovaps	(%rax), %zmm0
	vmovaps	64(%rax), %zmm1
	vmovaps	128(%rax), %zmm2
	vmovaps	192(%rax), %zmm3
	vmovups	768(%rsp), %zmm7        # 64-byte Reload
	vmulps	%zmm7, %zmm0, %zmm4
	vmulps	%zmm7, %zmm1, %zmm5
	vmulps	%zmm7, %zmm2, %zmm6
	vmulps	%zmm7, %zmm3, %zmm7
	vdivps	%zmm4, %zmm24, %zmm4
	vdivps	%zmm5, %zmm24, %zmm5
	vdivps	%zmm6, %zmm24, %zmm6
	vdivps	%zmm7, %zmm24, %zmm7
	vmovups	704(%rsp), %zmm11       # 64-byte Reload
	vaddps	%zmm11, %zmm4, %zmm8
	vaddps	%zmm11, %zmm5, %zmm9
	vaddps	%zmm11, %zmm6, %zmm10
	vaddps	%zmm11, %zmm7, %zmm11
	movq	584(%rcx), %rax
	leaq	34440(%rcx), %rdx
	kxnorw	%k0, %k0, %k1
	vxorps	%zmm12, %zmm12, %zmm12
	vmovaps	.LCPI1_6(%rip), %zmm13  # zmm13 = [10560,9856,9152,8448,7744,7040,6336,5632,4928,4224,3520,2816,2112,1408,704,0]
	vmovaps	%zmm13, %zmm16
	vgatherdps	(%rdx,%zmm16), %zmm12 {%k1}
	leaq	23176(%rcx), %rdx
	kxnorw	%k0, %k0, %k1
	vxorps	%zmm13, %zmm13, %zmm13
	vgatherdps	(%rdx,%zmm16), %zmm13 {%k1}
	leaq	11912(%rcx), %rdx
	kxnorw	%k0, %k0, %k1
	vxorps	%zmm14, %zmm14, %zmm14
	vgatherdps	(%rdx,%zmm16), %zmm14 {%k1}
	addq	$648, %rcx              # imm = 0x288
	kxnorw	%k0, %k0, %k1
	vxorps	%zmm15, %zmm15, %zmm15
	vgatherdps	(%rcx,%zmm16), %zmm15 {%k1}
	movl	%r13d, %ecx
	.p2align	4, 0x90
.LBB1_25:                               #   Parent Loop BB1_20 Depth=1
                                        #     Parent Loop BB1_23 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
	vaddps	%zmm15, %zmm0, %zmm15
	vaddps	%zmm14, %zmm1, %zmm14
	vaddps	%zmm13, %zmm2, %zmm13
	vaddps	%zmm12, %zmm3, %zmm12
	vcmpgtps	%zmm24, %zmm15, %k1
	vcmpgtps	%zmm24, %zmm14, %k2
	vcmpgtps	%zmm24, %zmm13, %k3
	vcmpgtps	%zmm24, %zmm12, %k4
	vpbroadcastd	%r12d, %zmm16 {%k4} {z}
	vpbroadcastd	%r12d, %zmm17 {%k3} {z}
	vpbroadcastd	%r12d, %zmm18 {%k2} {z}
	vpbroadcastd	%r12d, %zmm19 {%k1} {z}
	vpandd	%zmm26, %zmm19, %zmm19
	vpandd	%zmm26, %zmm18, %zmm18
	vpandd	%zmm26, %zmm17, %zmm17
	vpandd	%zmm26, %zmm16, %zmm16
	vsubps	%zmm19, %zmm15, %zmm15
	vsubps	%zmm18, %zmm14, %zmm14
	vsubps	%zmm17, %zmm13, %zmm13
	vsubps	%zmm16, %zmm12, %zmm12
	vmulps	%zmm15, %zmm4, %zmm16
	vmulps	%zmm14, %zmm5, %zmm17
	vmulps	%zmm13, %zmm6, %zmm18
	vmulps	%zmm12, %zmm7, %zmm19
	vsubps	%zmm8, %zmm16, %zmm20
	vsubps	%zmm9, %zmm17, %zmm21
	vsubps	%zmm10, %zmm18, %zmm22
	vsubps	%zmm11, %zmm19, %zmm23
	vmaxps	%zmm20, %zmm25, %zmm20
	vmaxps	%zmm21, %zmm25, %zmm21
	vmaxps	%zmm22, %zmm25, %zmm22
	vmaxps	%zmm23, %zmm25, %zmm23
	vxorps	%zmm27, %zmm16, %zmm16
	vxorps	%zmm27, %zmm17, %zmm17
	vxorps	%zmm27, %zmm18, %zmm18
	vxorps	%zmm27, %zmm19, %zmm19
	vsubps	%zmm8, %zmm16, %zmm16
	vsubps	%zmm9, %zmm17, %zmm17
	vsubps	%zmm10, %zmm18, %zmm18
	vsubps	%zmm11, %zmm19, %zmm19
	vmaxps	%zmm16, %zmm25, %zmm16
	vmaxps	%zmm17, %zmm25, %zmm17
	vmaxps	%zmm18, %zmm25, %zmm18
	vmaxps	%zmm19, %zmm25, %zmm19
	vfnmadd213ps	%zmm15, %zmm20, %zmm20
	vfnmadd213ps	%zmm14, %zmm21, %zmm21
	vfnmadd213ps	%zmm13, %zmm22, %zmm22
	vfnmadd213ps	%zmm12, %zmm23, %zmm23
	vfmadd231ps	%zmm16, %zmm16, %zmm20
	vfmadd231ps	%zmm17, %zmm17, %zmm21
	vfmadd231ps	%zmm18, %zmm18, %zmm22
	vfmadd231ps	%zmm19, %zmm19, %zmm23
	vmovaps	%zmm20, (%rax)
	vmovaps	%zmm21, 64(%rax)
	vmovaps	%zmm22, 128(%rax)
	vmovaps	%zmm23, 192(%rax)
	addq	$256, %rax              # imm = 0x100
	addl	$-1, %ecx
	jne	.LBB1_25
.LBB1_26:                               #   in Loop: Header=BB1_23 Depth=2
	addl	$1, %r14d
	cmpl	$8, %r14d
	jne	.LBB1_23
# BB#27:                                #   in Loop: Header=BB1_20 Depth=1
	xorl	%edi, %edi
	leaq	192(%rsp), %rsi
	vzeroupper
	callq	clock_gettime
	movq	192(%rsp), %rbx
	movq	200(%rsp), %r13
	movq	80(%rsp), %r14
.Ltmp3:
	movl	$24, %edi
	callq	_Znwm
	movq	%rax, %rcx
.Ltmp4:
# BB#28:                                #   in Loop: Header=BB1_20 Depth=1
	movq	%rbx, %rax
	movabsq	$2361183241434822607, %rdx # imm = 0x20C49BA5E353F7CF
	imulq	%rdx
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$7, %rdx
	addq	%rax, %rdx
	imulq	$1000, %rdx, %rax       # imm = 0x3E8
	subq	%rax, %rbx
	vcvtsi2sdq	%rbx, %xmm28, %xmm0
	vcvtsi2sdq	%r13, %xmm28, %xmm1
	vmovsd	.LCPI1_0(%rip), %xmm2   # xmm2 = mem[0],zero
	vfmadd213sd	%xmm1, %xmm2, %xmm0
	vcvttsd2usi	%xmm0, %rax
	subq	%r14, %rax
	vcvtusi2sdq	%rax, %xmm28, %xmm0
	vdivsd	%xmm2, %xmm0, %xmm0
	vcvtsd2ss	%xmm0, %xmm0, %xmm0
	vmovss	%xmm0, 16(%rcx)
	movq	%rcx, %rdi
	movq	%rbp, %rsi
	callq	_ZNSt8__detail15_List_node_base7_M_hookEPS0_
	incq	104(%rsp)
	movq	128(%rsp), %rcx         # 8-byte Reload
	leal	1(%rcx), %eax
	cmpl	$2047, %ecx             # imm = 0x7FF
	movl	%eax, %ebx
	movq	120(%rsp), %r13         # 8-byte Reload
	movq	56(%rsp), %r14          # 8-byte Reload
	jb	.LBB1_20
# BB#29:
.Ltmp6:
	movq	%rbp, %rdi
	callq	_ZNSt7__cxx114listIfSaIfEE4sortEv
.Ltmp7:
# BB#30:
	movq	88(%rsp), %rcx
	movq	104(%rsp), %rax
	cmpq	$4, %rax
	movq	112(%rsp), %rdx         # 8-byte Reload
	jb	.LBB1_33
# BB#31:
	movq	%rax, %rdi
	shrq	$2, %rdi
	xorl	%esi, %esi
	.p2align	4, 0x90
.LBB1_32:                               # =>This Inner Loop Header: Depth=1
	addq	$1, %rsi
	movq	(%rcx), %rcx
	cmpq	%rsi, %rdi
	ja	.LBB1_32
.LBB1_33:
	movq	%rax, %rsi
	vxorps	%xmm0, %xmm0, %xmm0
	shrq	%rsi
	je	.LBB1_35
	.p2align	4, 0x90
.LBB1_34:                               # =>This Inner Loop Header: Depth=1
	vaddss	16(%rcx), %xmm0, %xmm0
	movq	(%rcx), %rcx
	addq	$-1, %rsi
	jne	.LBB1_34
.LBB1_35:
	vcvtusi2ssq	%rax, %xmm3, %xmm1
	vmulss	.LCPI1_9(%rip), %xmm1, %xmm1
	vdivss	%xmm1, %xmm0, %xmm0
	vmulss	.LCPI1_10(%rip), %xmm0, %xmm0
	movl	136(%rsp), %r8d
	movl	%r8d, %eax
	shll	$6, %eax
	vcvtsi2ssl	%eax, %xmm3, %xmm1
	vmovss	.LCPI1_4(%rip), %xmm2   # xmm2 = mem[0],zero,zero,zero
	vdivss	%xmm0, %xmm2, %xmm2
	vmulss	%xmm1, %xmm2, %xmm1
	vmovss	.LCPI1_11(%rip), %xmm2  # xmm2 = mem[0],zero,zero,zero
	vdivss	%xmm2, %xmm1, %xmm3
	vmulss	%xmm2, %xmm3, %xmm1
	vmovss	.LCPI1_12(%rip), %xmm4  # xmm4 = mem[0],zero,zero,zero
	vmulss	%xmm4, %xmm1, %xmm1
	vdivss	.LCPI1_13(%rip), %xmm1, %xmm5
	vmulss	%xmm2, %xmm0, %xmm0
	vcvtss2sd	%xmm0, %xmm0, %xmm0
	vcvtss2sd	%xmm3, %xmm3, %xmm1
	vmulss	.LCPI1_14(%rip), %xmm3, %xmm2
	vcvtss2sd	%xmm2, %xmm2, %xmm2
	vmulss	%xmm4, %xmm3, %xmm3
	vcvtss2sd	%xmm3, %xmm3, %xmm3
	vcvtss2sd	%xmm5, %xmm5, %xmm4
	movl	$.L.str.1, %edi
	movl	$.L.str.3, %esi
	movl	$64, %ecx
	movb	$5, %al
	callq	printf
	movq	(%r15), %rax
	movq	%r15, %rdi
	callq	*48(%rax)
	movq	%r13, %rdi
	callq	free
	movq	%r14, %rdi
	callq	free
	movq	$_ZTV11Benchmarker+16, 64(%rsp)
	movq	88(%rsp), %rdi
	cmpq	%rbp, %rdi
	je	.LBB1_37
	.p2align	4, 0x90
.LBB1_36:                               # =>This Inner Loop Header: Depth=1
	movq	(%rdi), %rbx
	callq	_ZdlPv
	movq	%rbx, %rdi
	cmpq	%rbp, %rbx
	jne	.LBB1_36
.LBB1_37:
	addq	$1032, %rsp             # imm = 0x408
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB1_42:
.Ltmp8:
	jmp	.LBB1_43
.LBB1_38:
.Ltmp2:
	movq	%rax, %r14
	movq	$_ZTVN4XDSP4NodeE+16, (%r15)
	movq	16(%r15), %rdi
	testq	%rdi, %rdi
	je	.LBB1_40
# BB#39:
	callq	_ZdlPv
.LBB1_40:
	movq	%r15, %rdi
	callq	_ZdlPv
	movq	%r14, %rdi
	callq	_Unwind_Resume
.LBB1_41:
.Ltmp5:
.LBB1_43:
	movq	%rax, %r14
	movq	$_ZTV11Benchmarker+16, 64(%rsp)
	movq	88(%rsp), %rdi
	cmpq	%rbp, %rdi
	je	.LBB1_45
	.p2align	4, 0x90
.LBB1_44:                               # =>This Inner Loop Header: Depth=1
	movq	(%rdi), %rbx
	callq	_ZdlPv
	movq	%rbx, %rdi
	cmpq	%rbp, %rbx
	jne	.LBB1_44
.LBB1_45:
	movq	%r14, %rdi
	callq	_Unwind_Resume
.Lfunc_end1:
	.size	_Z8run_testI7YSawOsc14MathOps_AVX512ILi4EEEvPKc, .Lfunc_end1-_Z8run_testI7YSawOsc14MathOps_AVX512ILi4EEEvPKc
	.cfi_endproc
	.section	.gcc_except_table,"a",@progbits
	.p2align	2
GCC_except_table1:
.Lexception0:
	.byte	255                     # @LPStart Encoding = omit
	.byte	3                       # @TType Encoding = udata4
	.asciz	"\320"                  # @TType base offset
	.byte	3                       # Call site Encoding = udata4
	.byte	78                      # Call site table length
	.long	.Lfunc_begin0-.Lfunc_begin0 # >> Call Site 1 <<
	.long	.Ltmp0-.Lfunc_begin0    #   Call between .Lfunc_begin0 and .Ltmp0
	.long	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.long	.Ltmp0-.Lfunc_begin0    # >> Call Site 2 <<
	.long	.Ltmp1-.Ltmp0           #   Call between .Ltmp0 and .Ltmp1
	.long	.Ltmp2-.Lfunc_begin0    #     jumps to .Ltmp2
	.byte	0                       #   On action: cleanup
	.long	.Ltmp1-.Lfunc_begin0    # >> Call Site 3 <<
	.long	.Ltmp3-.Ltmp1           #   Call between .Ltmp1 and .Ltmp3
	.long	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.long	.Ltmp3-.Lfunc_begin0    # >> Call Site 4 <<
	.long	.Ltmp4-.Ltmp3           #   Call between .Ltmp3 and .Ltmp4
	.long	.Ltmp5-.Lfunc_begin0    #     jumps to .Ltmp5
	.byte	0                       #   On action: cleanup
	.long	.Ltmp6-.Lfunc_begin0    # >> Call Site 5 <<
	.long	.Ltmp7-.Ltmp6           #   Call between .Ltmp6 and .Ltmp7
	.long	.Ltmp8-.Lfunc_begin0    #     jumps to .Ltmp8
	.byte	0                       #   On action: cleanup
	.long	.Ltmp7-.Lfunc_begin0    # >> Call Site 6 <<
	.long	.Lfunc_end1-.Ltmp7      #   Call between .Ltmp7 and .Lfunc_end1
	.long	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.p2align	2
                                        # -- End function
	.section	.text._ZN11BenchmarkerD2Ev,"axG",@progbits,_ZN11BenchmarkerD2Ev,comdat
	.weak	_ZN11BenchmarkerD2Ev    # -- Begin function _ZN11BenchmarkerD2Ev
	.p2align	4, 0x90
	.type	_ZN11BenchmarkerD2Ev,@function
_ZN11BenchmarkerD2Ev:                   # @_ZN11BenchmarkerD2Ev
	.cfi_startproc
# BB#0:
	pushq	%r14
.Lcfi14:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Lcfi15:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Lcfi16:
	.cfi_def_cfa_offset 32
.Lcfi17:
	.cfi_offset %rbx, -24
.Lcfi18:
	.cfi_offset %r14, -16
	movq	%rdi, %r14
	movq	$_ZTV11Benchmarker+16, (%r14)
	movq	24(%r14), %rdi
	addq	$24, %r14
	cmpq	%r14, %rdi
	je	.LBB2_2
	.p2align	4, 0x90
.LBB2_1:                                # =>This Inner Loop Header: Depth=1
	movq	(%rdi), %rbx
	callq	_ZdlPv
	movq	%rbx, %rdi
	cmpq	%r14, %rbx
	jne	.LBB2_1
.LBB2_2:
	addq	$8, %rsp
	popq	%rbx
	popq	%r14
	retq
.Lfunc_end2:
	.size	_ZN11BenchmarkerD2Ev, .Lfunc_end2-_ZN11BenchmarkerD2Ev
	.cfi_endproc
                                        # -- End function
	.section	.text._ZN4XDSP4Node13PrepareStreamERKNS_14ProcessGlobalsE,"axG",@progbits,_ZN4XDSP4Node13PrepareStreamERKNS_14ProcessGlobalsE,comdat
	.weak	_ZN4XDSP4Node13PrepareStreamERKNS_14ProcessGlobalsE # -- Begin function _ZN4XDSP4Node13PrepareStreamERKNS_14ProcessGlobalsE
	.p2align	4, 0x90
	.type	_ZN4XDSP4Node13PrepareStreamERKNS_14ProcessGlobalsE,@function
_ZN4XDSP4Node13PrepareStreamERKNS_14ProcessGlobalsE: # @_ZN4XDSP4Node13PrepareStreamERKNS_14ProcessGlobalsE
	.cfi_startproc
# BB#0:
	pushq	%r15
.Lcfi19:
	.cfi_def_cfa_offset 16
	pushq	%r14
.Lcfi20:
	.cfi_def_cfa_offset 24
	pushq	%rbx
.Lcfi21:
	.cfi_def_cfa_offset 32
.Lcfi22:
	.cfi_offset %rbx, -32
.Lcfi23:
	.cfi_offset %r14, -24
.Lcfi24:
	.cfi_offset %r15, -16
	movq	%rsi, %r14
	movq	%rdi, %r15
	xorl	%ebx, %ebx
	.p2align	4, 0x90
.LBB3_1:                                # =>This Inner Loop Header: Depth=1
	movq	16(%r15), %rax
	movq	(%rax,%rbx,8), %rdi
	movq	(%rdi), %rax
	movq	%r14, %rsi
	callq	*16(%rax)
	addq	$1, %rbx
	cmpq	$64, %rbx
	jne	.LBB3_1
# BB#2:
	popq	%rbx
	popq	%r14
	popq	%r15
	retq
.Lfunc_end3:
	.size	_ZN4XDSP4Node13PrepareStreamERKNS_14ProcessGlobalsE, .Lfunc_end3-_ZN4XDSP4Node13PrepareStreamERKNS_14ProcessGlobalsE
	.cfi_endproc
                                        # -- End function
	.section	.text._ZN4XDSP8NodeTmplI9YBasicAmpE22ProcessBuffer_DispatchERKNS_14ProcessGlobalsE,"axG",@progbits,_ZN4XDSP8NodeTmplI9YBasicAmpE22ProcessBuffer_DispatchERKNS_14ProcessGlobalsE,comdat
	.weak	_ZN4XDSP8NodeTmplI9YBasicAmpE22ProcessBuffer_DispatchERKNS_14ProcessGlobalsE # -- Begin function _ZN4XDSP8NodeTmplI9YBasicAmpE22ProcessBuffer_DispatchERKNS_14ProcessGlobalsE
	.p2align	4, 0x90
	.type	_ZN4XDSP8NodeTmplI9YBasicAmpE22ProcessBuffer_DispatchERKNS_14ProcessGlobalsE,@function
_ZN4XDSP8NodeTmplI9YBasicAmpE22ProcessBuffer_DispatchERKNS_14ProcessGlobalsE: # @_ZN4XDSP8NodeTmplI9YBasicAmpE22ProcessBuffer_DispatchERKNS_14ProcessGlobalsE
	.cfi_startproc
# BB#0:
	xorl	%eax, %eax
	retq
.Lfunc_end4:
	.size	_ZN4XDSP8NodeTmplI9YBasicAmpE22ProcessBuffer_DispatchERKNS_14ProcessGlobalsE, .Lfunc_end4-_ZN4XDSP8NodeTmplI9YBasicAmpE22ProcessBuffer_DispatchERKNS_14ProcessGlobalsE
	.cfi_endproc
                                        # -- End function
	.section	.text._ZN4XDSP8NodeTmplI9YBasicAmpE14AllocateVoicesEv,"axG",@progbits,_ZN4XDSP8NodeTmplI9YBasicAmpE14AllocateVoicesEv,comdat
	.weak	_ZN4XDSP8NodeTmplI9YBasicAmpE14AllocateVoicesEv # -- Begin function _ZN4XDSP8NodeTmplI9YBasicAmpE14AllocateVoicesEv
	.p2align	4, 0x90
	.type	_ZN4XDSP8NodeTmplI9YBasicAmpE14AllocateVoicesEv,@function
_ZN4XDSP8NodeTmplI9YBasicAmpE14AllocateVoicesEv: # @_ZN4XDSP8NodeTmplI9YBasicAmpE14AllocateVoicesEv
	.cfi_startproc
# BB#0:
	pushq	%rbx
.Lcfi25:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
.Lcfi26:
	.cfi_def_cfa_offset 32
.Lcfi27:
	.cfi_offset %rbx, -16
	movq	%rdi, %rbx
	movq	$0, 8(%rsp)
	leaq	8(%rsp), %rdi
	movl	$64, %esi
	movl	$45056, %edx            # imm = 0xB000
	callq	posix_memalign
	movq	8(%rsp), %rax
	movq	%rax, 40(%rbx)
	movq	16(%rbx), %rax
	movq	24(%rbx), %rcx
	subq	%rax, %rcx
	sarq	$3, %rcx
	cmpq	$63, %rcx
	ja	.LBB5_2
# BB#1:
	leaq	16(%rbx), %rdi
	movl	$64, %esi
	subq	%rcx, %rsi
	callq	_ZNSt6vectorIPN4XDSP4Node5VoiceESaIS3_EE17_M_default_appendEm
	jmp	.LBB5_4
.LBB5_2:
	cmpq	$64, %rcx
	je	.LBB5_4
# BB#3:
	addq	$512, %rax              # imm = 0x200
	movq	%rax, 24(%rbx)
.LBB5_4:
	xorl	%eax, %eax
	xorl	%ecx, %ecx
	.p2align	4, 0x90
.LBB5_5:                                # =>This Inner Loop Header: Depth=1
	movq	40(%rbx), %rdx
	movq	$_ZTVN9YBasicAmp5VoiceE+16, (%rdx,%rax)
	addq	%rax, %rdx
	movq	16(%rbx), %rsi
	movq	%rdx, (%rsi,%rcx,8)
	addq	$1, %rcx
	addq	$704, %rax              # imm = 0x2C0
	cmpq	$64, %rcx
	jne	.LBB5_5
# BB#6:
	addq	$16, %rsp
	popq	%rbx
	retq
.Lfunc_end5:
	.size	_ZN4XDSP8NodeTmplI9YBasicAmpE14AllocateVoicesEv, .Lfunc_end5-_ZN4XDSP8NodeTmplI9YBasicAmpE14AllocateVoicesEv
	.cfi_endproc
                                        # -- End function
	.section	.text._ZN4XDSP8NodeTmplI9YBasicAmpE12AudioInCountEv,"axG",@progbits,_ZN4XDSP8NodeTmplI9YBasicAmpE12AudioInCountEv,comdat
	.weak	_ZN4XDSP8NodeTmplI9YBasicAmpE12AudioInCountEv # -- Begin function _ZN4XDSP8NodeTmplI9YBasicAmpE12AudioInCountEv
	.p2align	4, 0x90
	.type	_ZN4XDSP8NodeTmplI9YBasicAmpE12AudioInCountEv,@function
_ZN4XDSP8NodeTmplI9YBasicAmpE12AudioInCountEv: # @_ZN4XDSP8NodeTmplI9YBasicAmpE12AudioInCountEv
	.cfi_startproc
# BB#0:
	movl	$1, %eax
	retq
.Lfunc_end6:
	.size	_ZN4XDSP8NodeTmplI9YBasicAmpE12AudioInCountEv, .Lfunc_end6-_ZN4XDSP8NodeTmplI9YBasicAmpE12AudioInCountEv
	.cfi_endproc
                                        # -- End function
	.section	.text._ZN4XDSP8NodeTmplI9YBasicAmpE13AudioOutCountEv,"axG",@progbits,_ZN4XDSP8NodeTmplI9YBasicAmpE13AudioOutCountEv,comdat
	.weak	_ZN4XDSP8NodeTmplI9YBasicAmpE13AudioOutCountEv # -- Begin function _ZN4XDSP8NodeTmplI9YBasicAmpE13AudioOutCountEv
	.p2align	4, 0x90
	.type	_ZN4XDSP8NodeTmplI9YBasicAmpE13AudioOutCountEv,@function
_ZN4XDSP8NodeTmplI9YBasicAmpE13AudioOutCountEv: # @_ZN4XDSP8NodeTmplI9YBasicAmpE13AudioOutCountEv
	.cfi_startproc
# BB#0:
	movl	$1, %eax
	retq
.Lfunc_end7:
	.size	_ZN4XDSP8NodeTmplI9YBasicAmpE13AudioOutCountEv, .Lfunc_end7-_ZN4XDSP8NodeTmplI9YBasicAmpE13AudioOutCountEv
	.cfi_endproc
                                        # -- End function
	.section	.text._ZN7YSawOsc4NodeD0Ev,"axG",@progbits,_ZN7YSawOsc4NodeD0Ev,comdat
	.weak	_ZN7YSawOsc4NodeD0Ev    # -- Begin function _ZN7YSawOsc4NodeD0Ev
	.p2align	4, 0x90
	.type	_ZN7YSawOsc4NodeD0Ev,@function
_ZN7YSawOsc4NodeD0Ev:                   # @_ZN7YSawOsc4NodeD0Ev
	.cfi_startproc
# BB#0:
	pushq	%r14
.Lcfi28:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Lcfi29:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Lcfi30:
	.cfi_def_cfa_offset 32
.Lcfi31:
	.cfi_offset %rbx, -24
.Lcfi32:
	.cfi_offset %r14, -16
	movq	%rdi, %r14
	movq	$_ZTVN4XDSP8NodeTmplI9YBasicAmpEE+16, (%r14)
	xorl	%ebx, %ebx
	.p2align	4, 0x90
.LBB8_1:                                # =>This Inner Loop Header: Depth=1
	movq	16(%r14), %rax
	movq	(%rax,%rbx,8), %rdi
	movq	(%rdi), %rax
	callq	*(%rax)
	addq	$1, %rbx
	cmpq	$64, %rbx
	jne	.LBB8_1
# BB#2:
	movq	40(%r14), %rdi
	callq	free
	movq	$_ZTVN4XDSP4NodeE+16, (%r14)
	movq	16(%r14), %rdi
	testq	%rdi, %rdi
	je	.LBB8_4
# BB#3:
	callq	_ZdlPv
.LBB8_4:
	movq	%r14, %rdi
	addq	$8, %rsp
	popq	%rbx
	popq	%r14
	jmp	_ZdlPv                  # TAILCALL
.Lfunc_end8:
	.size	_ZN7YSawOsc4NodeD0Ev, .Lfunc_end8-_ZN7YSawOsc4NodeD0Ev
	.cfi_endproc
                                        # -- End function
	.section	.text._ZN4XDSP8NodeTmplI9YBasicAmpE10FreeVoicesEv,"axG",@progbits,_ZN4XDSP8NodeTmplI9YBasicAmpE10FreeVoicesEv,comdat
	.weak	_ZN4XDSP8NodeTmplI9YBasicAmpE10FreeVoicesEv # -- Begin function _ZN4XDSP8NodeTmplI9YBasicAmpE10FreeVoicesEv
	.p2align	4, 0x90
	.type	_ZN4XDSP8NodeTmplI9YBasicAmpE10FreeVoicesEv,@function
_ZN4XDSP8NodeTmplI9YBasicAmpE10FreeVoicesEv: # @_ZN4XDSP8NodeTmplI9YBasicAmpE10FreeVoicesEv
	.cfi_startproc
# BB#0:
	pushq	%r14
.Lcfi33:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Lcfi34:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Lcfi35:
	.cfi_def_cfa_offset 32
.Lcfi36:
	.cfi_offset %rbx, -24
.Lcfi37:
	.cfi_offset %r14, -16
	movq	%rdi, %r14
	xorl	%ebx, %ebx
	.p2align	4, 0x90
.LBB9_1:                                # =>This Inner Loop Header: Depth=1
	movq	16(%r14), %rax
	movq	(%rax,%rbx,8), %rdi
	movq	(%rdi), %rax
	callq	*(%rax)
	addq	$1, %rbx
	cmpq	$64, %rbx
	jne	.LBB9_1
# BB#2:
	movq	40(%r14), %rdi
	addq	$8, %rsp
	popq	%rbx
	popq	%r14
	jmp	free                    # TAILCALL
.Lfunc_end9:
	.size	_ZN4XDSP8NodeTmplI9YBasicAmpE10FreeVoicesEv, .Lfunc_end9-_ZN4XDSP8NodeTmplI9YBasicAmpE10FreeVoicesEv
	.cfi_endproc
                                        # -- End function
	.section	.text._ZN4XDSP8NodeTmplI9YBasicAmpE13GetVoiceTypedEi,"axG",@progbits,_ZN4XDSP8NodeTmplI9YBasicAmpE13GetVoiceTypedEi,comdat
	.weak	_ZN4XDSP8NodeTmplI9YBasicAmpE13GetVoiceTypedEi # -- Begin function _ZN4XDSP8NodeTmplI9YBasicAmpE13GetVoiceTypedEi
	.p2align	4, 0x90
	.type	_ZN4XDSP8NodeTmplI9YBasicAmpE13GetVoiceTypedEi,@function
_ZN4XDSP8NodeTmplI9YBasicAmpE13GetVoiceTypedEi: # @_ZN4XDSP8NodeTmplI9YBasicAmpE13GetVoiceTypedEi
	.cfi_startproc
# BB#0:
	movslq	%esi, %rax
	movq	16(%rdi), %rcx
	movq	(%rcx,%rax,8), %rax
	retq
.Lfunc_end10:
	.size	_ZN4XDSP8NodeTmplI9YBasicAmpE13GetVoiceTypedEi, .Lfunc_end10-_ZN4XDSP8NodeTmplI9YBasicAmpE13GetVoiceTypedEi
	.cfi_endproc
                                        # -- End function
	.section	.text._ZN4XDSP8NodeTmplI9YBasicAmpE13ProcessBufferERKNS_14ProcessGlobalsE,"axG",@progbits,_ZN4XDSP8NodeTmplI9YBasicAmpE13ProcessBufferERKNS_14ProcessGlobalsE,comdat
	.weak	_ZN4XDSP8NodeTmplI9YBasicAmpE13ProcessBufferERKNS_14ProcessGlobalsE # -- Begin function _ZN4XDSP8NodeTmplI9YBasicAmpE13ProcessBufferERKNS_14ProcessGlobalsE
	.p2align	4, 0x90
	.type	_ZN4XDSP8NodeTmplI9YBasicAmpE13ProcessBufferERKNS_14ProcessGlobalsE,@function
_ZN4XDSP8NodeTmplI9YBasicAmpE13ProcessBufferERKNS_14ProcessGlobalsE: # @_ZN4XDSP8NodeTmplI9YBasicAmpE13ProcessBufferERKNS_14ProcessGlobalsE
	.cfi_startproc
# BB#0:
	movq	(%rdi), %rax
	movq	8(%rax), %rax
	jmpq	*%rax                   # TAILCALL
.Lfunc_end11:
	.size	_ZN4XDSP8NodeTmplI9YBasicAmpE13ProcessBufferERKNS_14ProcessGlobalsE, .Lfunc_end11-_ZN4XDSP8NodeTmplI9YBasicAmpE13ProcessBufferERKNS_14ProcessGlobalsE
	.cfi_endproc
                                        # -- End function
	.section	.text._ZN4XDSP8NodeTmplI9YBasicAmpED2Ev,"axG",@progbits,_ZN4XDSP8NodeTmplI9YBasicAmpED2Ev,comdat
	.weak	_ZN4XDSP8NodeTmplI9YBasicAmpED2Ev # -- Begin function _ZN4XDSP8NodeTmplI9YBasicAmpED2Ev
	.p2align	4, 0x90
	.type	_ZN4XDSP8NodeTmplI9YBasicAmpED2Ev,@function
_ZN4XDSP8NodeTmplI9YBasicAmpED2Ev:      # @_ZN4XDSP8NodeTmplI9YBasicAmpED2Ev
	.cfi_startproc
# BB#0:
	pushq	%r14
.Lcfi38:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Lcfi39:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Lcfi40:
	.cfi_def_cfa_offset 32
.Lcfi41:
	.cfi_offset %rbx, -24
.Lcfi42:
	.cfi_offset %r14, -16
	movq	%rdi, %r14
	movq	$_ZTVN4XDSP8NodeTmplI9YBasicAmpEE+16, (%r14)
	xorl	%ebx, %ebx
	.p2align	4, 0x90
.LBB12_1:                               # =>This Inner Loop Header: Depth=1
	movq	16(%r14), %rax
	movq	(%rax,%rbx,8), %rdi
	movq	(%rdi), %rax
	callq	*(%rax)
	addq	$1, %rbx
	cmpq	$64, %rbx
	jne	.LBB12_1
# BB#2:
	movq	40(%r14), %rdi
	callq	free
	movq	$_ZTVN4XDSP4NodeE+16, (%r14)
	movq	16(%r14), %rdi
	addq	$8, %rsp
	testq	%rdi, %rdi
	je	.LBB12_3
# BB#4:
	popq	%rbx
	popq	%r14
	jmp	_ZdlPv                  # TAILCALL
.LBB12_3:
	popq	%rbx
	popq	%r14
	retq
.Lfunc_end12:
	.size	_ZN4XDSP8NodeTmplI9YBasicAmpED2Ev, .Lfunc_end12-_ZN4XDSP8NodeTmplI9YBasicAmpED2Ev
	.cfi_endproc
                                        # -- End function
	.section	.text._ZN4XDSP8NodeTmplI9YBasicAmpED0Ev,"axG",@progbits,_ZN4XDSP8NodeTmplI9YBasicAmpED0Ev,comdat
	.weak	_ZN4XDSP8NodeTmplI9YBasicAmpED0Ev # -- Begin function _ZN4XDSP8NodeTmplI9YBasicAmpED0Ev
	.p2align	4, 0x90
	.type	_ZN4XDSP8NodeTmplI9YBasicAmpED0Ev,@function
_ZN4XDSP8NodeTmplI9YBasicAmpED0Ev:      # @_ZN4XDSP8NodeTmplI9YBasicAmpED0Ev
	.cfi_startproc
# BB#0:
	pushq	%r14
.Lcfi43:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Lcfi44:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Lcfi45:
	.cfi_def_cfa_offset 32
.Lcfi46:
	.cfi_offset %rbx, -24
.Lcfi47:
	.cfi_offset %r14, -16
	movq	%rdi, %r14
	movq	$_ZTVN4XDSP8NodeTmplI9YBasicAmpEE+16, (%r14)
	xorl	%ebx, %ebx
	.p2align	4, 0x90
.LBB13_1:                               # =>This Inner Loop Header: Depth=1
	movq	16(%r14), %rax
	movq	(%rax,%rbx,8), %rdi
	movq	(%rdi), %rax
	callq	*(%rax)
	addq	$1, %rbx
	cmpq	$64, %rbx
	jne	.LBB13_1
# BB#2:
	movq	40(%r14), %rdi
	callq	free
	movq	$_ZTVN4XDSP4NodeE+16, (%r14)
	movq	16(%r14), %rdi
	testq	%rdi, %rdi
	je	.LBB13_4
# BB#3:
	callq	_ZdlPv
.LBB13_4:
	movq	%r14, %rdi
	addq	$8, %rsp
	popq	%rbx
	popq	%r14
	jmp	_ZdlPv                  # TAILCALL
.Lfunc_end13:
	.size	_ZN4XDSP8NodeTmplI9YBasicAmpED0Ev, .Lfunc_end13-_ZN4XDSP8NodeTmplI9YBasicAmpED0Ev
	.cfi_endproc
                                        # -- End function
	.section	.text._ZNSt6vectorIPN4XDSP4Node5VoiceESaIS3_EE17_M_default_appendEm,"axG",@progbits,_ZNSt6vectorIPN4XDSP4Node5VoiceESaIS3_EE17_M_default_appendEm,comdat
	.weak	_ZNSt6vectorIPN4XDSP4Node5VoiceESaIS3_EE17_M_default_appendEm # -- Begin function _ZNSt6vectorIPN4XDSP4Node5VoiceESaIS3_EE17_M_default_appendEm
	.p2align	4, 0x90
	.type	_ZNSt6vectorIPN4XDSP4Node5VoiceESaIS3_EE17_M_default_appendEm,@function
_ZNSt6vectorIPN4XDSP4Node5VoiceESaIS3_EE17_M_default_appendEm: # @_ZNSt6vectorIPN4XDSP4Node5VoiceESaIS3_EE17_M_default_appendEm
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Lcfi48:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Lcfi49:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Lcfi50:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Lcfi51:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Lcfi52:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Lcfi53:
	.cfi_def_cfa_offset 56
	pushq	%rax
.Lcfi54:
	.cfi_def_cfa_offset 64
.Lcfi55:
	.cfi_offset %rbx, -56
.Lcfi56:
	.cfi_offset %r12, -48
.Lcfi57:
	.cfi_offset %r13, -40
.Lcfi58:
	.cfi_offset %r14, -32
.Lcfi59:
	.cfi_offset %r15, -24
.Lcfi60:
	.cfi_offset %rbp, -16
	movq	%rsi, %rbx
	movq	%rdi, %r14
	testq	%rbx, %rbx
	je	.LBB14_14
# BB#1:
	movq	8(%r14), %r15
	movq	16(%r14), %rax
	subq	%r15, %rax
	sarq	$3, %rax
	cmpq	%rbx, %rax
	jae	.LBB14_2
# BB#3:
	movabsq	$2305843009213693951, %rax # imm = 0x1FFFFFFFFFFFFFFF
	movq	(%r14), %rsi
	movq	%r15, %rcx
	subq	%rsi, %rcx
	sarq	$3, %rcx
	movq	%rax, %rdx
	subq	%rcx, %rdx
	cmpq	%rbx, %rdx
	jb	.LBB14_15
# BB#4:
	cmpq	%rbx, %rcx
	movq	%rcx, %rdx
	cmovbq	%rbx, %rdx
	leaq	(%rdx,%rcx), %rbp
	cmpq	%rax, %rbp
	cmovaq	%rax, %rbp
	addq	%rcx, %rdx
	cmovbq	%rax, %rbp
	testq	%rbp, %rbp
	je	.LBB14_5
# BB#6:
	cmpq	%rax, %rbp
	ja	.LBB14_16
# BB#7:
	leaq	(,%rbp,8), %rdi
	callq	_Znwm
	movq	%rax, %r12
	movq	(%r14), %rsi
	movq	8(%r14), %r15
	jmp	.LBB14_8
.LBB14_2:
	addq	$8, %r14
	leaq	(,%rbx,8), %rdx
	xorl	%esi, %esi
	movq	%r15, %rdi
	callq	memset
	leaq	(%r15,%rbx,8), %rax
	jmp	.LBB14_13
.LBB14_5:
	xorl	%r12d, %r12d
.LBB14_8:
	movq	%rsi, (%rsp)            # 8-byte Spill
	subq	%rsi, %r15
	movq	%r15, %r13
	sarq	$3, %r13
	je	.LBB14_10
# BB#9:
	movq	%r12, %rdi
	movq	(%rsp), %rsi            # 8-byte Reload
	movq	%r15, %rdx
	callq	memmove
.LBB14_10:
	leaq	(%r12,%r13,8), %r15
	leaq	(,%rbx,8), %rdx
	xorl	%esi, %esi
	movq	%r15, %rdi
	callq	memset
	leaq	(%r15,%rbx,8), %rbx
	movq	(%rsp), %rax            # 8-byte Reload
	testq	%rax, %rax
	movq	%rax, %rdi
	je	.LBB14_12
# BB#11:
	callq	_ZdlPv
.LBB14_12:
	movq	%r12, (%r14)
	movq	%rbx, 8(%r14)
	leaq	16(%r14), %r14
	leaq	(%r12,%rbp,8), %rax
.LBB14_13:
	movq	%rax, (%r14)
.LBB14_14:
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB14_15:
	movl	$.L.str.2, %edi
	callq	_ZSt20__throw_length_errorPKc
.LBB14_16:
	callq	_ZSt17__throw_bad_allocv
.Lfunc_end14:
	.size	_ZNSt6vectorIPN4XDSP4Node5VoiceESaIS3_EE17_M_default_appendEm, .Lfunc_end14-_ZNSt6vectorIPN4XDSP4Node5VoiceESaIS3_EE17_M_default_appendEm
	.cfi_endproc
                                        # -- End function
	.section	.text._ZN9YBasicAmp5VoiceD0Ev,"axG",@progbits,_ZN9YBasicAmp5VoiceD0Ev,comdat
	.weak	_ZN9YBasicAmp5VoiceD0Ev # -- Begin function _ZN9YBasicAmp5VoiceD0Ev
	.p2align	4, 0x90
	.type	_ZN9YBasicAmp5VoiceD0Ev,@function
_ZN9YBasicAmp5VoiceD0Ev:                # @_ZN9YBasicAmp5VoiceD0Ev
	.cfi_startproc
# BB#0:
	jmp	_ZdlPv                  # TAILCALL
.Lfunc_end15:
	.size	_ZN9YBasicAmp5VoiceD0Ev, .Lfunc_end15-_ZN9YBasicAmp5VoiceD0Ev
	.cfi_endproc
                                        # -- End function
	.section	.text._ZN4XDSP4Node5Voice13PrepareStreamERKNS_14ProcessGlobalsE,"axG",@progbits,_ZN4XDSP4Node5Voice13PrepareStreamERKNS_14ProcessGlobalsE,comdat
	.weak	_ZN4XDSP4Node5Voice13PrepareStreamERKNS_14ProcessGlobalsE # -- Begin function _ZN4XDSP4Node5Voice13PrepareStreamERKNS_14ProcessGlobalsE
	.p2align	4, 0x90
	.type	_ZN4XDSP4Node5Voice13PrepareStreamERKNS_14ProcessGlobalsE,@function
_ZN4XDSP4Node5Voice13PrepareStreamERKNS_14ProcessGlobalsE: # @_ZN4XDSP4Node5Voice13PrepareStreamERKNS_14ProcessGlobalsE
	.cfi_startproc
# BB#0:
	retq
.Lfunc_end16:
	.size	_ZN4XDSP4Node5Voice13PrepareStreamERKNS_14ProcessGlobalsE, .Lfunc_end16-_ZN4XDSP4Node5Voice13PrepareStreamERKNS_14ProcessGlobalsE
	.cfi_endproc
                                        # -- End function
	.section	.text._ZN9YBasicAmp5Voice5ResetEv,"axG",@progbits,_ZN9YBasicAmp5Voice5ResetEv,comdat
	.weak	_ZN9YBasicAmp5Voice5ResetEv # -- Begin function _ZN9YBasicAmp5Voice5ResetEv
	.p2align	4, 0x90
	.type	_ZN9YBasicAmp5Voice5ResetEv,@function
_ZN9YBasicAmp5Voice5ResetEv:            # @_ZN9YBasicAmp5Voice5ResetEv
	.cfi_startproc
# BB#0:
	retq
.Lfunc_end17:
	.size	_ZN9YBasicAmp5Voice5ResetEv, .Lfunc_end17-_ZN9YBasicAmp5Voice5ResetEv
	.cfi_endproc
                                        # -- End function
	.section	.text._ZN4XDSP4Node5VoiceD2Ev,"axG",@progbits,_ZN4XDSP4Node5VoiceD2Ev,comdat
	.weak	_ZN4XDSP4Node5VoiceD2Ev # -- Begin function _ZN4XDSP4Node5VoiceD2Ev
	.p2align	4, 0x90
	.type	_ZN4XDSP4Node5VoiceD2Ev,@function
_ZN4XDSP4Node5VoiceD2Ev:                # @_ZN4XDSP4Node5VoiceD2Ev
	.cfi_startproc
# BB#0:
	retq
.Lfunc_end18:
	.size	_ZN4XDSP4Node5VoiceD2Ev, .Lfunc_end18-_ZN4XDSP4Node5VoiceD2Ev
	.cfi_endproc
                                        # -- End function
	.section	.text._ZN11BenchmarkerD0Ev,"axG",@progbits,_ZN11BenchmarkerD0Ev,comdat
	.weak	_ZN11BenchmarkerD0Ev    # -- Begin function _ZN11BenchmarkerD0Ev
	.p2align	4, 0x90
	.type	_ZN11BenchmarkerD0Ev,@function
_ZN11BenchmarkerD0Ev:                   # @_ZN11BenchmarkerD0Ev
	.cfi_startproc
# BB#0:
	pushq	%r15
.Lcfi61:
	.cfi_def_cfa_offset 16
	pushq	%r14
.Lcfi62:
	.cfi_def_cfa_offset 24
	pushq	%rbx
.Lcfi63:
	.cfi_def_cfa_offset 32
.Lcfi64:
	.cfi_offset %rbx, -32
.Lcfi65:
	.cfi_offset %r14, -24
.Lcfi66:
	.cfi_offset %r15, -16
	movq	%rdi, %r14
	movq	$_ZTV11Benchmarker+16, (%r14)
	leaq	24(%r14), %r15
	movq	24(%r14), %rdi
	cmpq	%r15, %rdi
	je	.LBB19_2
	.p2align	4, 0x90
.LBB19_1:                               # =>This Inner Loop Header: Depth=1
	movq	(%rdi), %rbx
	callq	_ZdlPv
	movq	%rbx, %rdi
	cmpq	%r15, %rbx
	jne	.LBB19_1
.LBB19_2:
	movq	%r14, %rdi
	popq	%rbx
	popq	%r14
	popq	%r15
	jmp	_ZdlPv                  # TAILCALL
.Lfunc_end19:
	.size	_ZN11BenchmarkerD0Ev, .Lfunc_end19-_ZN11BenchmarkerD0Ev
	.cfi_endproc
                                        # -- End function
	.section	.text._ZNSt7__cxx114listIfSaIfEE4sortEv,"axG",@progbits,_ZNSt7__cxx114listIfSaIfEE4sortEv,comdat
	.weak	_ZNSt7__cxx114listIfSaIfEE4sortEv # -- Begin function _ZNSt7__cxx114listIfSaIfEE4sortEv
	.p2align	4, 0x90
	.type	_ZNSt7__cxx114listIfSaIfEE4sortEv,@function
_ZNSt7__cxx114listIfSaIfEE4sortEv:      # @_ZNSt7__cxx114listIfSaIfEE4sortEv
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Lcfi67:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Lcfi68:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Lcfi69:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Lcfi70:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Lcfi71:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Lcfi72:
	.cfi_def_cfa_offset 56
	subq	$1576, %rsp             # imm = 0x628
.Lcfi73:
	.cfi_def_cfa_offset 1632
.Lcfi74:
	.cfi_offset %rbx, -56
.Lcfi75:
	.cfi_offset %r12, -48
.Lcfi76:
	.cfi_offset %r13, -40
.Lcfi77:
	.cfi_offset %r14, -32
.Lcfi78:
	.cfi_offset %r15, -24
.Lcfi79:
	.cfi_offset %rbp, -16
	movq	%rdi, %r13
	movq	(%r13), %rax
	cmpq	%r13, %rax
	je	.LBB20_43
# BB#1:
	cmpq	%r13, (%rax)
	je	.LBB20_43
# BB#2:
	movq	%rsp, %r15
	movq	%r15, (%rsp)
	movq	%r15, 8(%rsp)
	movq	$0, 16(%rsp)
	leaq	32(%rsp), %rax
	leaq	1568(%rsp), %rbp
	.p2align	4, 0x90
.LBB20_3:                               # =>This Inner Loop Header: Depth=1
	movq	%rax, (%rax)
	movq	%rax, 8(%rax)
	movq	$0, 16(%rax)
	addq	$24, %rax
	cmpq	%rbp, %rax
	jne	.LBB20_3
# BB#4:
	leaq	32(%rsp), %rbx
	movq	(%r13), %rsi
	movq	%r15, %rdi
	movq	%rbx, %r14
	movq	%r13, 24(%rsp)          # 8-byte Spill
	cmpq	%rsi, %rdi
	jne	.LBB20_6
	jmp	.LBB20_8
	.p2align	4, 0x90
.LBB20_22:                              #   in Loop: Header=BB20_8 Depth=1
	movq	%r14, %r12
	movq	24(%rsp), %r13          # 8-byte Reload
.LBB20_23:                              #   in Loop: Header=BB20_8 Depth=1
	movb	$1, %bl
	jmp	.LBB20_24
	.p2align	4, 0x90
.LBB20_10:                              #   in Loop: Header=BB20_8 Depth=1
	xorl	%ebx, %ebx
	movq	24(%rsp), %r13          # 8-byte Reload
.LBB20_24:                              #   in Loop: Header=BB20_8 Depth=1
	movq	%r15, %rdi
	movq	%r12, %rsi
	callq	_ZNSt8__detail15_List_node_base4swapERS0_S1_
	movq	16(%r12), %rax
	movq	16(%rsp), %rcx
	movq	%rcx, 16(%r12)
	movq	%rax, 16(%rsp)
	leaq	24(%r14), %rax
	testb	%bl, %bl
	cmovneq	%rax, %r14
	movq	(%r13), %rsi
	cmpq	%r13, %rsi
	je	.LBB20_26
# BB#25:                                #   in Loop: Header=BB20_8 Depth=1
	movq	(%rsp), %rdi
	leaq	32(%rsp), %rbx
	cmpq	%rsi, %rdi
	je	.LBB20_8
.LBB20_6:
	movq	(%rsi), %rdx
	cmpq	%rdi, %rdx
	je	.LBB20_8
# BB#7:
	callq	_ZNSt8__detail15_List_node_base11_M_transferEPS0_S1_
	incq	16(%rsp)
	decq	16(%r13)
.LBB20_8:                               # =>This Loop Header: Depth=1
                                        #     Child Loop BB20_9 Depth 2
                                        #       Child Loop BB20_13 Depth 3
	movq	%rbx, %r12
	cmpq	%r14, %rbx
	je	.LBB20_23
	.p2align	4, 0x90
.LBB20_9:                               #   Parent Loop BB20_8 Depth=1
                                        # =>  This Loop Header: Depth=2
                                        #       Child Loop BB20_13 Depth 3
	movq	(%r12), %rbx
	cmpq	%r12, %rbx
	je	.LBB20_10
# BB#11:                                #   in Loop: Header=BB20_9 Depth=2
	cmpq	%r12, %r15
	je	.LBB20_21
# BB#12:                                #   in Loop: Header=BB20_9 Depth=2
	movq	(%rsp), %rsi
	.p2align	4, 0x90
.LBB20_13:                              #   Parent Loop BB20_8 Depth=1
                                        #     Parent Loop BB20_9 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
	cmpq	%rsi, %r15
	je	.LBB20_18
# BB#14:                                #   in Loop: Header=BB20_13 Depth=3
	vmovss	16(%rbx), %xmm0         # xmm0 = mem[0],zero,zero,zero
	vucomiss	16(%rsi), %xmm0
	jbe	.LBB20_16
# BB#15:                                #   in Loop: Header=BB20_13 Depth=3
	movq	(%rsi), %r13
	movq	%rbx, %rdi
	movq	%r13, %rdx
	callq	_ZNSt8__detail15_List_node_base11_M_transferEPS0_S1_
	movq	%r13, %rsi
	cmpq	%rbx, %r12
	jne	.LBB20_13
	jmp	.LBB20_18
	.p2align	4, 0x90
.LBB20_16:                              #   in Loop: Header=BB20_13 Depth=3
	movq	(%rbx), %rbx
	cmpq	%rbx, %r12
	jne	.LBB20_13
.LBB20_18:                              #   in Loop: Header=BB20_9 Depth=2
	cmpq	%rsi, %r15
	je	.LBB20_20
# BB#19:                                #   in Loop: Header=BB20_9 Depth=2
	movq	%r12, %rdi
	movq	%r15, %rdx
	callq	_ZNSt8__detail15_List_node_base11_M_transferEPS0_S1_
.LBB20_20:                              #   in Loop: Header=BB20_9 Depth=2
	movq	16(%rsp), %rax
	addq	%rax, 16(%r12)
	movq	$0, 16(%rsp)
.LBB20_21:                              #   in Loop: Header=BB20_9 Depth=2
	movq	%r15, %rdi
	movq	%r12, %rsi
	callq	_ZNSt8__detail15_List_node_base4swapERS0_S1_
	movq	16(%r12), %rax
	movq	16(%rsp), %rcx
	movq	%rcx, 16(%r12)
	movq	%rax, 16(%rsp)
	addq	$24, %r12
	cmpq	%r14, %r12
	jne	.LBB20_9
	jmp	.LBB20_22
.LBB20_26:
	leaq	56(%rsp), %r12
	cmpq	%r14, %r12
	jne	.LBB20_28
	jmp	.LBB20_37
	.p2align	4, 0x90
.LBB20_36:                              #   in Loop: Header=BB20_28 Depth=1
	movq	-8(%r12), %rax
	addq	%rax, 16(%r12)
	movq	$0, -8(%r12)
	addq	$24, %r12
	cmpq	%r14, %r12
	je	.LBB20_37
.LBB20_28:                              # =>This Loop Header: Depth=1
                                        #     Child Loop BB20_30 Depth 2
	leaq	-24(%r12), %r15
	movq	-24(%r12), %rsi
	movq	(%r12), %rbx
	cmpq	%rbx, %r12
	jne	.LBB20_30
	jmp	.LBB20_34
	.p2align	4, 0x90
.LBB20_33:                              #   in Loop: Header=BB20_30 Depth=2
	movq	(%rbx), %rbx
	cmpq	%rbx, %r12
	je	.LBB20_34
.LBB20_30:                              #   Parent Loop BB20_28 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	cmpq	%rsi, %r15
	je	.LBB20_34
# BB#31:                                #   in Loop: Header=BB20_30 Depth=2
	vmovss	16(%rbx), %xmm0         # xmm0 = mem[0],zero,zero,zero
	vucomiss	16(%rsi), %xmm0
	jbe	.LBB20_33
# BB#32:                                #   in Loop: Header=BB20_30 Depth=2
	movq	(%rsi), %r13
	movq	%rbx, %rdi
	movq	%r13, %rdx
	callq	_ZNSt8__detail15_List_node_base11_M_transferEPS0_S1_
	movq	%r13, %rsi
	cmpq	%rbx, %r12
	jne	.LBB20_30
.LBB20_34:                              #   in Loop: Header=BB20_28 Depth=1
	cmpq	%rsi, %r15
	je	.LBB20_36
# BB#35:                                #   in Loop: Header=BB20_28 Depth=1
	movq	%r12, %rdi
	movq	%r15, %rdx
	callq	_ZNSt8__detail15_List_node_base11_M_transferEPS0_S1_
	jmp	.LBB20_36
.LBB20_37:
	leaq	-24(%r14), %rsi
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %rdi
	callq	_ZNSt8__detail15_List_node_base4swapERS0_S1_
	movq	-8(%r14), %rax
	movq	16(%rbx), %rcx
	movq	%rcx, -8(%r14)
	movq	%rax, 16(%rbx)
	leaq	32(%rsp), %r14
	.p2align	4, 0x90
.LBB20_38:                              # =>This Loop Header: Depth=1
                                        #     Child Loop BB20_39 Depth 2
	movq	-24(%rbp), %rdi
	addq	$-24, %rbp
	cmpq	%rbp, %rdi
	je	.LBB20_40
	.p2align	4, 0x90
.LBB20_39:                              #   Parent Loop BB20_38 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	(%rdi), %rbx
	callq	_ZdlPv
	movq	%rbx, %rdi
	cmpq	%rbp, %rbx
	jne	.LBB20_39
.LBB20_40:                              #   in Loop: Header=BB20_38 Depth=1
	cmpq	%r14, %rbp
	jne	.LBB20_38
# BB#41:
	movq	(%rsp), %rdi
	movq	%rsp, %rbx
	cmpq	%rbx, %rdi
	je	.LBB20_43
	.p2align	4, 0x90
.LBB20_42:                              # =>This Inner Loop Header: Depth=1
	movq	(%rdi), %rbp
	callq	_ZdlPv
	movq	%rbp, %rdi
	cmpq	%rbx, %rbp
	jne	.LBB20_42
.LBB20_43:
	addq	$1576, %rsp             # imm = 0x628
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end20:
	.size	_ZNSt7__cxx114listIfSaIfEE4sortEv, .Lfunc_end20-_ZNSt7__cxx114listIfSaIfEE4sortEv
	.cfi_endproc
                                        # -- End function
	.type	_ZN9StopWatch10s_bDidInitE,@object # @_ZN9StopWatch10s_bDidInitE
	.bss
	.globl	_ZN9StopWatch10s_bDidInitE
_ZN9StopWatch10s_bDidInitE:
	.byte	0                       # 0x0
	.size	_ZN9StopWatch10s_bDidInitE, 1

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"AVX512,  4"
	.size	.L.str, 11

	.type	.L_ZZ8run_testI7YSawOsc14MathOps_AVX512ILi4EEEvPKcE14control_params,@object # @_ZZ8run_testI7YSawOsc14MathOps_AVX512ILi4EEEvPKcE14control_params
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	4
.L_ZZ8run_testI7YSawOsc14MathOps_AVX512ILi4EEEvPKcE14control_params:
	.long	1045220557              # float 0.200000003
	.long	1061997773              # float 0.800000011
	.long	1058642330              # float 0.600000024
	.long	1050253722              # float 0.300000012
	.long	1061997773              # float 0.800000011
	.long	1063675494              # float 0.899999976
	.long	1045220557              # float 0.200000003
	.long	1056964608              # float 0.5
	.size	.L_ZZ8run_testI7YSawOsc14MathOps_AVX512ILi4EEEvPKcE14control_params, 32

	.type	.L.str.1,@object        # @.str.1
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str.1:
	.asciz	"Average time for [ %s %s ] [%dv, %ds] bl: %0.2f us \t\t%0.2f MIt/sec\t%0.2f MOp/sec\t%0.2f MCall/sec\t%0.2f x Realtime\n"
	.size	.L.str.1, 115

	.type	_ZTVN7YSawOsc4NodeE,@object # @_ZTVN7YSawOsc4NodeE
	.section	.rodata._ZTVN7YSawOsc4NodeE,"aG",@progbits,_ZTVN7YSawOsc4NodeE,comdat
	.weak	_ZTVN7YSawOsc4NodeE
	.p2align	3
_ZTVN7YSawOsc4NodeE:
	.quad	0
	.quad	_ZTIN7YSawOsc4NodeE
	.quad	_ZN4XDSP4Node13PrepareStreamERKNS_14ProcessGlobalsE
	.quad	_ZN4XDSP8NodeTmplI9YBasicAmpE22ProcessBuffer_DispatchERKNS_14ProcessGlobalsE
	.quad	_ZN4XDSP8NodeTmplI9YBasicAmpE14AllocateVoicesEv
	.quad	_ZN4XDSP8NodeTmplI9YBasicAmpE12AudioInCountEv
	.quad	_ZN4XDSP8NodeTmplI9YBasicAmpE13AudioOutCountEv
	.quad	_ZN4XDSP8NodeTmplI9YBasicAmpED2Ev
	.quad	_ZN7YSawOsc4NodeD0Ev
	.quad	_ZN4XDSP8NodeTmplI9YBasicAmpE10FreeVoicesEv
	.quad	_ZN4XDSP8NodeTmplI9YBasicAmpE13GetVoiceTypedEi
	.quad	_ZN4XDSP8NodeTmplI9YBasicAmpE13ProcessBufferERKNS_14ProcessGlobalsE
	.size	_ZTVN7YSawOsc4NodeE, 96

	.type	_ZTSN7YSawOsc4NodeE,@object # @_ZTSN7YSawOsc4NodeE
	.section	.rodata._ZTSN7YSawOsc4NodeE,"aG",@progbits,_ZTSN7YSawOsc4NodeE,comdat
	.weak	_ZTSN7YSawOsc4NodeE
_ZTSN7YSawOsc4NodeE:
	.asciz	"N7YSawOsc4NodeE"
	.size	_ZTSN7YSawOsc4NodeE, 16

	.type	_ZTSN4XDSP8NodeTmplI9YBasicAmpEE,@object # @_ZTSN4XDSP8NodeTmplI9YBasicAmpEE
	.section	.rodata._ZTSN4XDSP8NodeTmplI9YBasicAmpEE,"aG",@progbits,_ZTSN4XDSP8NodeTmplI9YBasicAmpEE,comdat
	.weak	_ZTSN4XDSP8NodeTmplI9YBasicAmpEE
	.p2align	4
_ZTSN4XDSP8NodeTmplI9YBasicAmpEE:
	.asciz	"N4XDSP8NodeTmplI9YBasicAmpEE"
	.size	_ZTSN4XDSP8NodeTmplI9YBasicAmpEE, 29

	.type	_ZTSN4XDSP4NodeE,@object # @_ZTSN4XDSP4NodeE
	.section	.rodata._ZTSN4XDSP4NodeE,"aG",@progbits,_ZTSN4XDSP4NodeE,comdat
	.weak	_ZTSN4XDSP4NodeE
_ZTSN4XDSP4NodeE:
	.asciz	"N4XDSP4NodeE"
	.size	_ZTSN4XDSP4NodeE, 13

	.type	_ZTIN4XDSP4NodeE,@object # @_ZTIN4XDSP4NodeE
	.section	.rodata._ZTIN4XDSP4NodeE,"aG",@progbits,_ZTIN4XDSP4NodeE,comdat
	.weak	_ZTIN4XDSP4NodeE
	.p2align	3
_ZTIN4XDSP4NodeE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSN4XDSP4NodeE
	.size	_ZTIN4XDSP4NodeE, 16

	.type	_ZTIN4XDSP8NodeTmplI9YBasicAmpEE,@object # @_ZTIN4XDSP8NodeTmplI9YBasicAmpEE
	.section	.rodata._ZTIN4XDSP8NodeTmplI9YBasicAmpEE,"aG",@progbits,_ZTIN4XDSP8NodeTmplI9YBasicAmpEE,comdat
	.weak	_ZTIN4XDSP8NodeTmplI9YBasicAmpEE
	.p2align	4
_ZTIN4XDSP8NodeTmplI9YBasicAmpEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN4XDSP8NodeTmplI9YBasicAmpEE
	.quad	_ZTIN4XDSP4NodeE
	.size	_ZTIN4XDSP8NodeTmplI9YBasicAmpEE, 24

	.type	_ZTIN7YSawOsc4NodeE,@object # @_ZTIN7YSawOsc4NodeE
	.section	.rodata._ZTIN7YSawOsc4NodeE,"aG",@progbits,_ZTIN7YSawOsc4NodeE,comdat
	.weak	_ZTIN7YSawOsc4NodeE
	.p2align	4
_ZTIN7YSawOsc4NodeE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN7YSawOsc4NodeE
	.quad	_ZTIN4XDSP8NodeTmplI9YBasicAmpEE
	.size	_ZTIN7YSawOsc4NodeE, 24

	.type	_ZTVN4XDSP8NodeTmplI9YBasicAmpEE,@object # @_ZTVN4XDSP8NodeTmplI9YBasicAmpEE
	.section	.rodata._ZTVN4XDSP8NodeTmplI9YBasicAmpEE,"aG",@progbits,_ZTVN4XDSP8NodeTmplI9YBasicAmpEE,comdat
	.weak	_ZTVN4XDSP8NodeTmplI9YBasicAmpEE
	.p2align	3
_ZTVN4XDSP8NodeTmplI9YBasicAmpEE:
	.quad	0
	.quad	_ZTIN4XDSP8NodeTmplI9YBasicAmpEE
	.quad	_ZN4XDSP4Node13PrepareStreamERKNS_14ProcessGlobalsE
	.quad	_ZN4XDSP8NodeTmplI9YBasicAmpE22ProcessBuffer_DispatchERKNS_14ProcessGlobalsE
	.quad	_ZN4XDSP8NodeTmplI9YBasicAmpE14AllocateVoicesEv
	.quad	_ZN4XDSP8NodeTmplI9YBasicAmpE12AudioInCountEv
	.quad	_ZN4XDSP8NodeTmplI9YBasicAmpE13AudioOutCountEv
	.quad	_ZN4XDSP8NodeTmplI9YBasicAmpED2Ev
	.quad	_ZN4XDSP8NodeTmplI9YBasicAmpED0Ev
	.quad	_ZN4XDSP8NodeTmplI9YBasicAmpE10FreeVoicesEv
	.quad	_ZN4XDSP8NodeTmplI9YBasicAmpE13GetVoiceTypedEi
	.quad	_ZN4XDSP8NodeTmplI9YBasicAmpE13ProcessBufferERKNS_14ProcessGlobalsE
	.size	_ZTVN4XDSP8NodeTmplI9YBasicAmpEE, 96

	.type	_ZTVN4XDSP4NodeE,@object # @_ZTVN4XDSP4NodeE
	.section	.rodata._ZTVN4XDSP4NodeE,"aG",@progbits,_ZTVN4XDSP4NodeE,comdat
	.weak	_ZTVN4XDSP4NodeE
	.p2align	3
_ZTVN4XDSP4NodeE:
	.quad	0
	.quad	_ZTIN4XDSP4NodeE
	.quad	_ZN4XDSP4Node13PrepareStreamERKNS_14ProcessGlobalsE
	.quad	__cxa_pure_virtual
	.quad	__cxa_pure_virtual
	.quad	__cxa_pure_virtual
	.quad	__cxa_pure_virtual
	.size	_ZTVN4XDSP4NodeE, 56

	.type	.L.str.2,@object        # @.str.2
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str.2:
	.asciz	"vector::_M_default_append"
	.size	.L.str.2, 26

	.type	_ZTVN9YBasicAmp5VoiceE,@object # @_ZTVN9YBasicAmp5VoiceE
	.section	.rodata._ZTVN9YBasicAmp5VoiceE,"aG",@progbits,_ZTVN9YBasicAmp5VoiceE,comdat
	.weak	_ZTVN9YBasicAmp5VoiceE
	.p2align	3
_ZTVN9YBasicAmp5VoiceE:
	.quad	0
	.quad	_ZTIN9YBasicAmp5VoiceE
	.quad	_ZN4XDSP4Node5VoiceD2Ev
	.quad	_ZN9YBasicAmp5VoiceD0Ev
	.quad	_ZN4XDSP4Node5Voice13PrepareStreamERKNS_14ProcessGlobalsE
	.quad	_ZN9YBasicAmp5Voice5ResetEv
	.size	_ZTVN9YBasicAmp5VoiceE, 48

	.type	_ZTSN9YBasicAmp5VoiceE,@object # @_ZTSN9YBasicAmp5VoiceE
	.section	.rodata._ZTSN9YBasicAmp5VoiceE,"aG",@progbits,_ZTSN9YBasicAmp5VoiceE,comdat
	.weak	_ZTSN9YBasicAmp5VoiceE
	.p2align	4
_ZTSN9YBasicAmp5VoiceE:
	.asciz	"N9YBasicAmp5VoiceE"
	.size	_ZTSN9YBasicAmp5VoiceE, 19

	.type	_ZTSN4XDSP9VoiceTmplI9YBasicAmpEE,@object # @_ZTSN4XDSP9VoiceTmplI9YBasicAmpEE
	.section	.rodata._ZTSN4XDSP9VoiceTmplI9YBasicAmpEE,"aG",@progbits,_ZTSN4XDSP9VoiceTmplI9YBasicAmpEE,comdat
	.weak	_ZTSN4XDSP9VoiceTmplI9YBasicAmpEE
	.p2align	4
_ZTSN4XDSP9VoiceTmplI9YBasicAmpEE:
	.asciz	"N4XDSP9VoiceTmplI9YBasicAmpEE"
	.size	_ZTSN4XDSP9VoiceTmplI9YBasicAmpEE, 30

	.type	_ZTSN4XDSP4Node5VoiceE,@object # @_ZTSN4XDSP4Node5VoiceE
	.section	.rodata._ZTSN4XDSP4Node5VoiceE,"aG",@progbits,_ZTSN4XDSP4Node5VoiceE,comdat
	.weak	_ZTSN4XDSP4Node5VoiceE
	.p2align	4
_ZTSN4XDSP4Node5VoiceE:
	.asciz	"N4XDSP4Node5VoiceE"
	.size	_ZTSN4XDSP4Node5VoiceE, 19

	.type	_ZTIN4XDSP4Node5VoiceE,@object # @_ZTIN4XDSP4Node5VoiceE
	.section	.rodata._ZTIN4XDSP4Node5VoiceE,"aG",@progbits,_ZTIN4XDSP4Node5VoiceE,comdat
	.weak	_ZTIN4XDSP4Node5VoiceE
	.p2align	3
_ZTIN4XDSP4Node5VoiceE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSN4XDSP4Node5VoiceE
	.size	_ZTIN4XDSP4Node5VoiceE, 16

	.type	_ZTIN4XDSP9VoiceTmplI9YBasicAmpEE,@object # @_ZTIN4XDSP9VoiceTmplI9YBasicAmpEE
	.section	.rodata._ZTIN4XDSP9VoiceTmplI9YBasicAmpEE,"aG",@progbits,_ZTIN4XDSP9VoiceTmplI9YBasicAmpEE,comdat
	.weak	_ZTIN4XDSP9VoiceTmplI9YBasicAmpEE
	.p2align	4
_ZTIN4XDSP9VoiceTmplI9YBasicAmpEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN4XDSP9VoiceTmplI9YBasicAmpEE
	.quad	_ZTIN4XDSP4Node5VoiceE
	.size	_ZTIN4XDSP9VoiceTmplI9YBasicAmpEE, 24

	.type	_ZTIN9YBasicAmp5VoiceE,@object # @_ZTIN9YBasicAmp5VoiceE
	.section	.rodata._ZTIN9YBasicAmp5VoiceE,"aG",@progbits,_ZTIN9YBasicAmp5VoiceE,comdat
	.weak	_ZTIN9YBasicAmp5VoiceE
	.p2align	4
_ZTIN9YBasicAmp5VoiceE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN9YBasicAmp5VoiceE
	.quad	_ZTIN4XDSP9VoiceTmplI9YBasicAmpEE
	.size	_ZTIN9YBasicAmp5VoiceE, 24

	.type	_ZTV11Benchmarker,@object # @_ZTV11Benchmarker
	.section	.rodata._ZTV11Benchmarker,"aG",@progbits,_ZTV11Benchmarker,comdat
	.weak	_ZTV11Benchmarker
	.p2align	3
_ZTV11Benchmarker:
	.quad	0
	.quad	_ZTI11Benchmarker
	.quad	_ZN11BenchmarkerD2Ev
	.quad	_ZN11BenchmarkerD0Ev
	.size	_ZTV11Benchmarker, 32

	.type	_ZTS11Benchmarker,@object # @_ZTS11Benchmarker
	.section	.rodata._ZTS11Benchmarker,"aG",@progbits,_ZTS11Benchmarker,comdat
	.weak	_ZTS11Benchmarker
_ZTS11Benchmarker:
	.asciz	"11Benchmarker"
	.size	_ZTS11Benchmarker, 14

	.type	_ZTI11Benchmarker,@object # @_ZTI11Benchmarker
	.section	.rodata._ZTI11Benchmarker,"aG",@progbits,_ZTI11Benchmarker,comdat
	.weak	_ZTI11Benchmarker
	.p2align	3
_ZTI11Benchmarker:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTS11Benchmarker
	.size	_ZTI11Benchmarker, 16

	.type	.L.str.3,@object        # @.str.3
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str.3:
	.asciz	"YSawOsc"
	.size	.L.str.3, 8


	.ident	"clang version 5.0.0-+rc2-1 (tags/RELEASE_500/rc2)"
	.section	".note.GNU-stack","",@progbits
