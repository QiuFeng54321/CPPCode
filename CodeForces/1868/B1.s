	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0	sdk_version 13, 0
	.globl	__Z8floorDivxx                  ## -- Begin function _Z8floorDivxx
	.p2align	4, 0x90
__Z8floorDivxx:                         ## @_Z8floorDivxx
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, %rax
	orq	%rsi, %rax
	shrq	$32, %rax
	je	LBB0_1
## %bb.2:
	movq	%rdi, %rax
	cqto
	idivq	%rsi
	jmp	LBB0_3
LBB0_1:
	movl	%edi, %eax
	xorl	%edx, %edx
	divl	%esi
                                        ## kill: def $eax killed $eax def $rax
LBB0_3:
	addq	$1, %rax
	movq	%rsi, %rcx
	imulq	%rax, %rcx
	.p2align	4, 0x90
LBB0_4:                                 ## =>This Inner Loop Header: Depth=1
	addq	$-1, %rax
	subq	%rsi, %rcx
	cmpq	%rdi, %rcx
	jg	LBB0_4
## %bb.5:
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__Z5sieveRNSt3__16vectorIxNS_9allocatorIxEEEERNS0_IcNS1_IcEEEEx ## -- Begin function _Z5sieveRNSt3__16vectorIxNS_9allocatorIxEEEERNS0_IcNS1_IcEEEEx
	.p2align	4, 0x90
__Z5sieveRNSt3__16vectorIxNS_9allocatorIxEEEERNS0_IcNS1_IcEEEEx: ## @_Z5sieveRNSt3__16vectorIxNS_9allocatorIxEEEERNS0_IcNS1_IcEEEEx
Lfunc_begin0:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception0
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	cvtsi2sd	%rdx, %xmm0
	movq	%rsi, %r12
	sqrtsd	%xmm0, %xmm0
	cvttsd2si	%xmm0, %r14
	movq	%r14, %r15
	xorpd	%xmm0, %xmm0
	movapd	%xmm0, -96(%rbp)
	movq	$0, -80(%rbp)
	addq	$2, %r15
	movq	%rdi, -48(%rbp)                 ## 8-byte Spill
	je	LBB1_1
## %bb.2:
	cmpq	$-3, %r14
	jle	LBB1_3
## %bb.5:
Ltmp0:
	movq	%r15, %rdi
	callq	__Znwm
Ltmp1:
## %bb.6:
	movq	%rax, %rbx
	movq	%rax, %r13
	addq	%r15, %r13
	movq	%rax, %rdi
	movl	$1, %esi
	movq	%r15, %rdx
	callq	_memset
	movq	(%r12), %rdi
	testq	%rdi, %rdi
	je	LBB1_9
LBB1_8:
	movq	%rdi, 8(%r12)
	callq	__ZdlPv
	xorpd	%xmm0, %xmm0
	movupd	%xmm0, (%r12)
	movq	$0, 16(%r12)
LBB1_9:
	movq	%rbx, (%r12)
	movq	%r13, 8(%r12)
	movq	%r13, 16(%r12)
	cmpq	$2, %r14
	movq	-48(%rbp), %r13                 ## 8-byte Reload
	jge	LBB1_10
LBB1_17:
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
LBB1_10:
	movl	$2, %r15d
	cmpb	$0, (%rbx,%r15)
	je	LBB1_30
	.p2align	4, 0x90
LBB1_12:
	movq	8(%r13), %rbx
	cmpq	16(%r13), %rbx
	je	LBB1_18
## %bb.13:
	movq	%r15, (%rbx)
	addq	$8, %rbx
	movq	%rbx, 8(%r13)
	movq	%r15, %rax
	imulq	%r15, %rax
	cmpq	%r14, %rax
	jle	LBB1_28
	jmp	LBB1_30
	.p2align	4, 0x90
LBB1_18:
	movq	(%r13), %rdx
	subq	%rdx, %rbx
	movq	%rbx, %r13
	sarq	$3, %r13
	leaq	1(%r13), %rax
	movabsq	$2305843009213693951, %rcx      ## imm = 0x1FFFFFFFFFFFFFFF
	cmpq	%rcx, %rax
	ja	LBB1_32
## %bb.19:
	movq	%rbx, %rsi
	sarq	$2, %rsi
	cmpq	%rax, %rsi
	cmovbq	%rax, %rsi
	movabsq	$1152921504606846975, %rax      ## imm = 0xFFFFFFFFFFFFFFF
	cmpq	%rax, %r13
	cmovaeq	%rcx, %rsi
	testq	%rsi, %rsi
	movq	%rdx, -56(%rbp)                 ## 8-byte Spill
	movq	%rsi, -72(%rbp)                 ## 8-byte Spill
	je	LBB1_20
## %bb.21:
	cmpq	%rcx, %rsi
	ja	LBB1_33
## %bb.22:
	leaq	(,%rsi,8), %rdi
	callq	__Znwm
	movq	%rax, %rsi
	movq	-56(%rbp), %rdx                 ## 8-byte Reload
	movq	%r15, (%rsi,%r13,8)
	testq	%rbx, %rbx
	jle	LBB1_25
LBB1_24:
	movq	%rsi, -64(%rbp)                 ## 8-byte Spill
	movq	-64(%rbp), %rdi                 ## 8-byte Reload
	movq	-56(%rbp), %rsi                 ## 8-byte Reload
	movq	%rbx, %rdx
	callq	_memcpy
	movq	-64(%rbp), %rsi                 ## 8-byte Reload
	movq	-56(%rbp), %rdx                 ## 8-byte Reload
LBB1_25:
	movq	-72(%rbp), %rax                 ## 8-byte Reload
	leaq	(%rsi,%rax,8), %rax
	leaq	(%rsi,%r13,8), %rcx
	addq	$8, %rcx
	movq	-48(%rbp), %r13                 ## 8-byte Reload
	movq	%rsi, (%r13)
	movq	%rcx, 8(%r13)
	movq	%rax, 16(%r13)
	testq	%rdx, %rdx
	je	LBB1_27
## %bb.26:
	movq	%rdx, %rdi
	callq	__ZdlPv
LBB1_27:
	movq	%r15, %rax
	imulq	%r15, %rax
	cmpq	%r14, %rax
	jg	LBB1_30
	.p2align	4, 0x90
LBB1_28:                                ## =>This Inner Loop Header: Depth=1
	movq	(%r12), %rcx
	movb	$0, (%rcx,%rax)
	addq	%r15, %rax
	cmpq	%r14, %rax
	jle	LBB1_28
LBB1_30:                                ## =>This Inner Loop Header: Depth=1
	cmpq	%r14, %r15
	je	LBB1_17
## %bb.31:                              ##   in Loop: Header=BB1_30 Depth=1
	addq	$1, %r15
	movq	(%r12), %rbx
	cmpb	$0, (%rbx,%r15)
	jne	LBB1_12
	jmp	LBB1_30
LBB1_20:
	xorl	%esi, %esi
	movq	%r15, (%rsi,%r13,8)
	testq	%rbx, %rbx
	jg	LBB1_24
	jmp	LBB1_25
LBB1_1:
	xorl	%r13d, %r13d
	xorl	%ebx, %ebx
	movq	(%r12), %rdi
	testq	%rdi, %rdi
	jne	LBB1_8
	jmp	LBB1_9
LBB1_32:
	movq	-48(%rbp), %rdi                 ## 8-byte Reload
	callq	__ZNKSt3__113__vector_baseIxNS_9allocatorIxEEE20__throw_length_errorEv
LBB1_33:
	callq	__ZNSt3__1L20__throw_length_errorEPKc
LBB1_3:
Ltmp2:
	leaq	-96(%rbp), %rdi
	callq	__ZNKSt3__113__vector_baseIcNS_9allocatorIcEEE20__throw_length_errorEv
Ltmp3:
## %bb.4:
	ud2
LBB1_14:
Ltmp4:
	movq	%rax, %rbx
	movq	-96(%rbp), %rdi
	testq	%rdi, %rdi
	je	LBB1_16
## %bb.15:
	movq	%rdi, -88(%rbp)
	callq	__ZdlPv
LBB1_16:
	movq	%rbx, %rdi
	callq	__Unwind_Resume
Lfunc_end0:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2
GCC_except_table1:
Lexception0:
	.byte	255                             ## @LPStart Encoding = omit
	.byte	255                             ## @TType Encoding = omit
	.byte	1                               ## Call site Encoding = uleb128
	.uleb128 Lcst_end0-Lcst_begin0
Lcst_begin0:
	.uleb128 Ltmp0-Lfunc_begin0             ## >> Call Site 1 <<
	.uleb128 Ltmp1-Ltmp0                    ##   Call between Ltmp0 and Ltmp1
	.uleb128 Ltmp4-Lfunc_begin0             ##     jumps to Ltmp4
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp1-Lfunc_begin0             ## >> Call Site 2 <<
	.uleb128 Ltmp2-Ltmp1                    ##   Call between Ltmp1 and Ltmp2
	.byte	0                               ##     has no landing pad
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp2-Lfunc_begin0             ## >> Call Site 3 <<
	.uleb128 Ltmp3-Ltmp2                    ##   Call between Ltmp2 and Ltmp3
	.uleb128 Ltmp4-Lfunc_begin0             ##     jumps to Ltmp4
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp3-Lfunc_begin0             ## >> Call Site 4 <<
	.uleb128 Lfunc_end0-Ltmp3               ##   Call between Ltmp3 and Lfunc_end0
	.byte	0                               ##     has no landing pad
	.byte	0                               ##   On action: cleanup
Lcst_end0:
	.p2align	2
                                        ## -- End function
	.section	__TEXT,__literal16,16byte_literals
	.p2align	4                               ## -- Begin function _Z14unique_factorsxRNSt3__16vectorIxNS_9allocatorIxEEEE
LCPI2_0:
	.space	16
	.section	__TEXT,__text,regular,pure_instructions
	.globl	__Z14unique_factorsxRNSt3__16vectorIxNS_9allocatorIxEEEE
	.p2align	4, 0x90
__Z14unique_factorsxRNSt3__16vectorIxNS_9allocatorIxEEEE: ## @_Z14unique_factorsxRNSt3__16vectorIxNS_9allocatorIxEEEE
Lfunc_begin1:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception1
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	movq	%rsi, %r15
	leaq	8(%rdi), %rax
	xorps	%xmm0, %xmm0
	movups	%xmm0, 8(%rdi)
	movq	%rdi, -56(%rbp)                 ## 8-byte Spill
	movq	%rax, -48(%rbp)                 ## 8-byte Spill
	movq	%rax, (%rdi)
	movq	(%rdx), %rax
	movq	8(%rdx), %rcx
	movq	%rcx, -64(%rbp)                 ## 8-byte Spill
	cmpq	%rcx, %rax
	jne	LBB2_8
LBB2_1:
	cmpq	$2, %r15
	jl	LBB2_38
## %bb.2:
	movq	-48(%rbp), %r13                 ## 8-byte Reload
	movq	(%r13), %rbx
	testq	%rbx, %rbx
	je	LBB2_33
## %bb.3:
	movq	%rbx, %rax
	jmp	LBB2_4
	.p2align	4, 0x90
LBB2_7:                                 ##   in Loop: Header=BB2_8 Depth=1
	movq	-72(%rbp), %rax                 ## 8-byte Reload
	addq	$8, %rax
	cmpq	-64(%rbp), %rax                 ## 8-byte Folded Reload
	je	LBB2_1
LBB2_8:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB2_9 Depth 2
                                        ##       Child Loop BB2_16 Depth 3
	movq	%rax, -72(%rbp)                 ## 8-byte Spill
	movq	(%rax), %r13
	movq	%r13, %rax
	imulq	%r13, %rax
	cmpq	%r15, %rax
	jle	LBB2_9
	jmp	LBB2_1
	.p2align	4, 0x90
LBB2_29:                                ##   in Loop: Header=BB2_9 Depth=2
	movq	%r15, %rax
	cqto
	idivq	%r13
	movq	%rax, %r15
LBB2_9:                                 ##   Parent Loop BB2_8 Depth=1
                                        ## =>  This Loop Header: Depth=2
                                        ##       Child Loop BB2_16 Depth 3
	movq	%r15, %rax
	orq	%r13, %rax
	shrq	$32, %rax
	je	LBB2_10
LBB2_11:                                ##   in Loop: Header=BB2_9 Depth=2
	movq	%r15, %rax
	cqto
	idivq	%r13
	testq	%rdx, %rdx
	je	LBB2_13
	jmp	LBB2_7
	.p2align	4, 0x90
LBB2_10:                                ##   in Loop: Header=BB2_9 Depth=2
	movl	%r15d, %eax
	xorl	%edx, %edx
	divl	%r13d
                                        ## kill: def $edx killed $edx def $rdx
	testq	%rdx, %rdx
	jne	LBB2_7
LBB2_13:                                ##   in Loop: Header=BB2_9 Depth=2
	movq	-48(%rbp), %r14                 ## 8-byte Reload
	movq	(%r14), %rbx
	testq	%rbx, %rbx
	je	LBB2_14
## %bb.15:                              ##   in Loop: Header=BB2_9 Depth=2
	movq	%rbx, %r12
	jmp	LBB2_16
	.p2align	4, 0x90
LBB2_17:                                ##   in Loop: Header=BB2_16 Depth=3
	movq	(%r12), %rax
	movq	%r12, %r14
	testq	%rax, %rax
	je	LBB2_18
LBB2_28:                                ##   in Loop: Header=BB2_16 Depth=3
	movq	%rax, %r12
LBB2_16:                                ##   Parent Loop BB2_8 Depth=1
                                        ##     Parent Loop BB2_9 Depth=2
                                        ## =>    This Inner Loop Header: Depth=3
	cmpq	%r13, 32(%r12)
	jg	LBB2_17
## %bb.26:                              ##   in Loop: Header=BB2_16 Depth=3
	jge	LBB2_19
## %bb.27:                              ##   in Loop: Header=BB2_16 Depth=3
	leaq	8(%r12), %r14
	movq	8(%r12), %rax
	testq	%rax, %rax
	jne	LBB2_28
	jmp	LBB2_19
	.p2align	4, 0x90
LBB2_14:                                ##   in Loop: Header=BB2_9 Depth=2
	movq	%r14, %r12
LBB2_19:                                ##   in Loop: Header=BB2_9 Depth=2
	cmpq	$0, (%r14)
	je	LBB2_20
LBB2_24:                                ##   in Loop: Header=BB2_9 Depth=2
	movq	%r15, %rax
	orq	%r13, %rax
	shrq	$32, %rax
	jne	LBB2_29
	jmp	LBB2_25
LBB2_18:                                ##   in Loop: Header=BB2_9 Depth=2
	movq	%r12, %r14
	cmpq	$0, (%r14)
	jne	LBB2_24
LBB2_20:                                ##   in Loop: Header=BB2_9 Depth=2
Ltmp5:
	movl	$40, %edi
	callq	__Znwm
Ltmp6:
## %bb.21:                              ##   in Loop: Header=BB2_9 Depth=2
	movq	%r13, 32(%rax)
	xorps	%xmm0, %xmm0
	movups	%xmm0, (%rax)
	movq	%r12, 16(%rax)
	movq	%rax, (%r14)
	movq	-56(%rbp), %rbx                 ## 8-byte Reload
	movq	(%rbx), %rcx
	movq	(%rcx), %rcx
	testq	%rcx, %rcx
	je	LBB2_23
## %bb.22:                              ##   in Loop: Header=BB2_9 Depth=2
	movq	%rcx, (%rbx)
	movq	(%r14), %rax
LBB2_23:                                ##   in Loop: Header=BB2_9 Depth=2
	movq	8(%rbx), %rdi
	movq	%rax, %rsi
	callq	__ZNSt3__127__tree_balance_after_insertIPNS_16__tree_node_baseIPvEEEEvT_S5_
	addq	$1, 16(%rbx)
	movq	%r15, %rax
	orq	%r13, %rax
	shrq	$32, %rax
	jne	LBB2_29
LBB2_25:                                ##   in Loop: Header=BB2_9 Depth=2
	movl	%r15d, %eax
	xorl	%edx, %edx
	divl	%r13d
	movl	%eax, %r15d
	movq	%r15, %rax
	orq	%r13, %rax
	shrq	$32, %rax
	jne	LBB2_11
	jmp	LBB2_10
	.p2align	4, 0x90
LBB2_5:                                 ##   in Loop: Header=BB2_4 Depth=1
	movq	(%rax), %rcx
	movq	%rax, %r13
	testq	%rcx, %rcx
	je	LBB2_6
LBB2_41:                                ##   in Loop: Header=BB2_4 Depth=1
	movq	%rcx, %rax
LBB2_4:                                 ## =>This Inner Loop Header: Depth=1
	cmpq	%r15, 32(%rax)
	jg	LBB2_5
## %bb.30:                              ##   in Loop: Header=BB2_4 Depth=1
	jge	LBB2_32
## %bb.31:                              ##   in Loop: Header=BB2_4 Depth=1
	leaq	8(%rax), %r13
	movq	8(%rax), %rcx
	testq	%rcx, %rcx
	jne	LBB2_41
LBB2_32:
	movq	%rax, -48(%rbp)                 ## 8-byte Spill
LBB2_33:
	cmpq	$0, (%r13)
	jne	LBB2_38
LBB2_34:
Ltmp8:
	movl	$40, %edi
	callq	__Znwm
Ltmp9:
## %bb.35:
	movq	%r15, 32(%rax)
	xorps	%xmm0, %xmm0
	movups	%xmm0, (%rax)
	movq	-48(%rbp), %rcx                 ## 8-byte Reload
	movq	%rcx, 16(%rax)
	movq	%rax, (%r13)
	movq	-56(%rbp), %rbx                 ## 8-byte Reload
	movq	(%rbx), %rcx
	movq	(%rcx), %rcx
	testq	%rcx, %rcx
	je	LBB2_37
## %bb.36:
	movq	%rcx, (%rbx)
	movq	(%r13), %rax
LBB2_37:
	movq	8(%rbx), %rdi
	movq	%rax, %rsi
	callq	__ZNSt3__127__tree_balance_after_insertIPNS_16__tree_node_baseIPvEEEEvT_S5_
	addq	$1, 16(%rbx)
	jmp	LBB2_38
LBB2_6:
	movq	%rax, -48(%rbp)                 ## 8-byte Spill
	movq	%rax, %r13
	cmpq	$0, (%r13)
	je	LBB2_34
LBB2_38:
	movq	-56(%rbp), %rax                 ## 8-byte Reload
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
LBB2_42:
Ltmp10:
	jmp	LBB2_40
LBB2_39:
Ltmp7:
LBB2_40:
	movq	%rax, %r14
	movq	-56(%rbp), %rdi                 ## 8-byte Reload
	movq	%rbx, %rsi
	callq	__ZNSt3__16__treeIxNS_4lessIxEENS_9allocatorIxEEE7destroyEPNS_11__tree_nodeIxPvEE
	movq	%r14, %rdi
	callq	__Unwind_Resume
Lfunc_end1:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2
GCC_except_table2:
Lexception1:
	.byte	255                             ## @LPStart Encoding = omit
	.byte	255                             ## @TType Encoding = omit
	.byte	1                               ## Call site Encoding = uleb128
	.uleb128 Lcst_end1-Lcst_begin1
Lcst_begin1:
	.uleb128 Ltmp5-Lfunc_begin1             ## >> Call Site 1 <<
	.uleb128 Ltmp6-Ltmp5                    ##   Call between Ltmp5 and Ltmp6
	.uleb128 Ltmp7-Lfunc_begin1             ##     jumps to Ltmp7
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp8-Lfunc_begin1             ## >> Call Site 2 <<
	.uleb128 Ltmp9-Ltmp8                    ##   Call between Ltmp8 and Ltmp9
	.uleb128 Ltmp10-Lfunc_begin1            ##     jumps to Ltmp10
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp9-Lfunc_begin1             ## >> Call Site 3 <<
	.uleb128 Lfunc_end1-Ltmp9               ##   Call between Ltmp9 and Lfunc_end1
	.byte	0                               ##     has no landing pad
	.byte	0                               ##   On action: cleanup
Lcst_end1:
	.p2align	2
                                        ## -- End function
	.section	__TEXT,__text,regular,pure_instructions
	.globl	__Z9factorizexRNSt3__16vectorIxNS_9allocatorIxEEEE ## -- Begin function _Z9factorizexRNSt3__16vectorIxNS_9allocatorIxEEEE
	.p2align	4, 0x90
__Z9factorizexRNSt3__16vectorIxNS_9allocatorIxEEEE: ## @_Z9factorizexRNSt3__16vectorIxNS_9allocatorIxEEEE
Lfunc_begin2:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception2
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	movq	%rdi, %r13
	xorps	%xmm0, %xmm0
	movups	%xmm0, (%rdi)
	movq	$0, 16(%rdi)
	movq	(%rdx), %rax
	movq	8(%rdx), %rcx
	movq	%rcx, -72(%rbp)                 ## 8-byte Spill
	cmpq	%rcx, %rax
	movq	%rdi, -48(%rbp)                 ## 8-byte Spill
	je	LBB3_28
## %bb.1:
	movabsq	$2305843009213693951, %rcx      ## imm = 0x1FFFFFFFFFFFFFFF
	xorl	%r9d, %r9d
	xorl	%r8d, %r8d
	xorl	%r15d, %r15d
	jmp	LBB3_3
	.p2align	4, 0x90
LBB3_2:                                 ##   in Loop: Header=BB3_3 Depth=1
	movq	-80(%rbp), %rax                 ## 8-byte Reload
	addq	$8, %rax
	cmpq	-72(%rbp), %rax                 ## 8-byte Folded Reload
	je	LBB3_45
LBB3_3:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB3_4 Depth 2
	movq	%rax, -80(%rbp)                 ## 8-byte Spill
	movq	(%rax), %r14
	movq	%r14, %rax
	imulq	%r14, %rax
	cmpq	%rsi, %rax
	jle	LBB3_4
	jmp	LBB3_45
	.p2align	4, 0x90
LBB3_26:                                ##   in Loop: Header=BB3_4 Depth=2
	movq	%rsi, %rax
	cqto
	idivq	%r14
	movq	%rax, %rsi
LBB3_4:                                 ##   Parent Loop BB3_3 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movq	%rsi, %rax
	orq	%r14, %rax
	shrq	$32, %rax
	je	LBB3_5
LBB3_6:                                 ##   in Loop: Header=BB3_4 Depth=2
	movq	%rsi, %rax
	cqto
	idivq	%r14
	testq	%rdx, %rdx
	je	LBB3_8
	jmp	LBB3_2
	.p2align	4, 0x90
LBB3_5:                                 ##   in Loop: Header=BB3_4 Depth=2
	movl	%esi, %eax
	xorl	%edx, %edx
	divl	%r14d
                                        ## kill: def $edx killed $edx def $rdx
	testq	%rdx, %rdx
	jne	LBB3_2
LBB3_8:                                 ##   in Loop: Header=BB3_4 Depth=2
	cmpq	%r8, %r15
	je	LBB3_10
## %bb.9:                               ##   in Loop: Header=BB3_4 Depth=2
	movq	%r14, (%r15)
	addq	$8, %r15
	movq	%r15, 8(%r13)
	movq	%rsi, %rax
	orq	%r14, %rax
	shrq	$32, %rax
	jne	LBB3_26
	jmp	LBB3_25
	.p2align	4, 0x90
LBB3_10:                                ##   in Loop: Header=BB3_4 Depth=2
	subq	%r9, %r8
	movq	%r8, %rbx
	sarq	$3, %rbx
	leaq	1(%rbx), %rax
	cmpq	%rcx, %rax
	ja	LBB3_11
## %bb.13:                              ##   in Loop: Header=BB3_4 Depth=2
	movq	%r8, %r15
	sarq	$2, %r15
	cmpq	%rax, %r15
	cmovbq	%rax, %r15
	movabsq	$1152921504606846975, %rax      ## imm = 0xFFFFFFFFFFFFFFF
	cmpq	%rax, %rbx
	cmovaeq	%rcx, %r15
	testq	%r15, %r15
	movq	%rsi, -56(%rbp)                 ## 8-byte Spill
	je	LBB3_14
## %bb.15:                              ##   in Loop: Header=BB3_4 Depth=2
	movq	%r8, -64(%rbp)                  ## 8-byte Spill
	cmpq	%rcx, %r15
	ja	LBB3_16
## %bb.17:                              ##   in Loop: Header=BB3_4 Depth=2
	movq	%r9, %r13
	leaq	(,%r15,8), %rdi
Ltmp11:
	callq	__Znwm
Ltmp12:
## %bb.18:                              ##   in Loop: Header=BB3_4 Depth=2
	movq	%rax, %r12
	movq	%r13, %r9
	movq	-64(%rbp), %r8                  ## 8-byte Reload
	movq	%r14, (%r12,%rbx,8)
	testq	%r8, %r8
	jle	LBB3_21
LBB3_20:                                ##   in Loop: Header=BB3_4 Depth=2
	movq	%r12, %rdi
	movq	%r9, %r13
	movq	%r9, %rsi
	movq	%r8, %rdx
	callq	_memcpy
	movq	%r13, %r9
LBB3_21:                                ##   in Loop: Header=BB3_4 Depth=2
	leaq	(%r12,%r15,8), %r8
	leaq	(%r12,%rbx,8), %r15
	addq	$8, %r15
	movq	-48(%rbp), %r13                 ## 8-byte Reload
	movq	%r12, (%r13)
	movq	%r15, 8(%r13)
	movq	%r8, 16(%r13)
	testq	%r9, %r9
	je	LBB3_23
## %bb.22:                              ##   in Loop: Header=BB3_4 Depth=2
	movq	%r9, %rdi
	movq	%r8, %rbx
	callq	__ZdlPv
	movq	%rbx, %r8
LBB3_23:                                ##   in Loop: Header=BB3_4 Depth=2
	movq	%r12, %r9
	movq	-56(%rbp), %rsi                 ## 8-byte Reload
	movabsq	$2305843009213693951, %rcx      ## imm = 0x1FFFFFFFFFFFFFFF
	movq	%rsi, %rax
	orq	%r14, %rax
	shrq	$32, %rax
	jne	LBB3_26
LBB3_25:                                ##   in Loop: Header=BB3_4 Depth=2
	movl	%esi, %eax
	xorl	%edx, %edx
	divl	%r14d
	movl	%eax, %esi
	movq	%rsi, %rax
	orq	%r14, %rax
	shrq	$32, %rax
	jne	LBB3_6
	jmp	LBB3_5
LBB3_14:                                ##   in Loop: Header=BB3_4 Depth=2
	xorl	%r12d, %r12d
	movq	%r14, (%r12,%rbx,8)
	testq	%r8, %r8
	jg	LBB3_20
	jmp	LBB3_21
LBB3_45:
	cmpq	$1, %rsi
	jle	LBB3_46
## %bb.32:
	cmpq	%r8, %r15
	je	LBB3_30
## %bb.33:
	movq	%rsi, (%r15)
	addq	$8, %r15
	movq	%r15, 8(%r13)
	jmp	LBB3_46
LBB3_28:
	cmpq	$1, %rsi
	jle	LBB3_46
## %bb.29:
	xorl	%r9d, %r9d
	xorl	%r8d, %r8d
LBB3_30:
	subq	%r9, %r8
	movq	%r8, %r14
	sarq	$3, %r14
	leaq	1(%r14), %rcx
	movq	%rcx, %rax
	shrq	$61, %rax
	jne	LBB3_31
## %bb.34:
	movq	%rsi, -56(%rbp)                 ## 8-byte Spill
	movabsq	$2305843009213693951, %rax      ## imm = 0x1FFFFFFFFFFFFFFF
	movq	%r8, %rbx
	sarq	$2, %rbx
	cmpq	%rcx, %rbx
	cmovbq	%rcx, %rbx
	movabsq	$1152921504606846975, %rcx      ## imm = 0xFFFFFFFFFFFFFFF
	cmpq	%rcx, %r14
	cmovaeq	%rax, %rbx
	testq	%rbx, %rbx
	je	LBB3_35
## %bb.36:
	movq	%r8, -64(%rbp)                  ## 8-byte Spill
	cmpq	%rax, %rbx
	ja	LBB3_37
## %bb.38:
	movq	%r9, %r12
	leaq	(,%rbx,8), %rdi
Ltmp19:
	callq	__Znwm
Ltmp20:
## %bb.39:
	movq	%rax, %r15
	movq	%r12, %r9
	movq	-64(%rbp), %r8                  ## 8-byte Reload
	jmp	LBB3_40
LBB3_35:
	xorl	%r15d, %r15d
LBB3_40:
	leaq	(%r15,%rbx,8), %r12
	movq	-56(%rbp), %rax                 ## 8-byte Reload
	movq	%rax, (%r15,%r14,8)
	leaq	(%r15,%r14,8), %r14
	addq	$8, %r14
	testq	%r8, %r8
	jle	LBB3_42
## %bb.41:
	movq	%r15, %rdi
	movq	%r9, %rbx
	movq	%r9, %rsi
	movq	%r8, %rdx
	callq	_memcpy
	movq	%rbx, %r9
LBB3_42:
	movq	-48(%rbp), %r13                 ## 8-byte Reload
	movq	%r15, (%r13)
	movq	%r14, 8(%r13)
	movq	%r12, 16(%r13)
	testq	%r9, %r9
	je	LBB3_46
## %bb.43:
	movq	%r9, %rdi
	callq	__ZdlPv
LBB3_46:
	movq	%r13, %rax
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
LBB3_11:
Ltmp16:
	movq	-48(%rbp), %rdi                 ## 8-byte Reload
	callq	__ZNKSt3__113__vector_baseIxNS_9allocatorIxEEE20__throw_length_errorEv
Ltmp17:
	jmp	LBB3_12
LBB3_16:
Ltmp14:
	callq	__ZNSt3__1L20__throw_length_errorEPKc
Ltmp15:
	jmp	LBB3_12
LBB3_31:
Ltmp23:
	movq	-48(%rbp), %rdi                 ## 8-byte Reload
	callq	__ZNKSt3__113__vector_baseIxNS_9allocatorIxEEE20__throw_length_errorEv
Ltmp24:
	jmp	LBB3_12
LBB3_37:
Ltmp21:
	callq	__ZNSt3__1L20__throw_length_errorEPKc
Ltmp22:
LBB3_12:
	ud2
LBB3_44:
Ltmp25:
	jmp	LBB3_48
LBB3_47:
Ltmp13:
	jmp	LBB3_48
LBB3_27:
Ltmp18:
LBB3_48:
	movq	%rax, %rbx
	movq	-48(%rbp), %rax                 ## 8-byte Reload
	movq	(%rax), %rdi
	testq	%rdi, %rdi
	je	LBB3_50
## %bb.49:
	movq	%rdi, 8(%rax)
	callq	__ZdlPv
LBB3_50:
	movq	%rbx, %rdi
	callq	__Unwind_Resume
Lfunc_end2:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2
GCC_except_table3:
Lexception2:
	.byte	255                             ## @LPStart Encoding = omit
	.byte	255                             ## @TType Encoding = omit
	.byte	1                               ## Call site Encoding = uleb128
	.uleb128 Lcst_end2-Lcst_begin2
Lcst_begin2:
	.uleb128 Ltmp11-Lfunc_begin2            ## >> Call Site 1 <<
	.uleb128 Ltmp12-Ltmp11                  ##   Call between Ltmp11 and Ltmp12
	.uleb128 Ltmp13-Lfunc_begin2            ##     jumps to Ltmp13
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp12-Lfunc_begin2            ## >> Call Site 2 <<
	.uleb128 Ltmp19-Ltmp12                  ##   Call between Ltmp12 and Ltmp19
	.byte	0                               ##     has no landing pad
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp19-Lfunc_begin2            ## >> Call Site 3 <<
	.uleb128 Ltmp20-Ltmp19                  ##   Call between Ltmp19 and Ltmp20
	.uleb128 Ltmp25-Lfunc_begin2            ##     jumps to Ltmp25
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp20-Lfunc_begin2            ## >> Call Site 4 <<
	.uleb128 Ltmp16-Ltmp20                  ##   Call between Ltmp20 and Ltmp16
	.byte	0                               ##     has no landing pad
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp16-Lfunc_begin2            ## >> Call Site 5 <<
	.uleb128 Ltmp15-Ltmp16                  ##   Call between Ltmp16 and Ltmp15
	.uleb128 Ltmp18-Lfunc_begin2            ##     jumps to Ltmp18
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp23-Lfunc_begin2            ## >> Call Site 6 <<
	.uleb128 Ltmp22-Ltmp23                  ##   Call between Ltmp23 and Ltmp22
	.uleb128 Ltmp25-Lfunc_begin2            ##     jumps to Ltmp25
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp22-Lfunc_begin2            ## >> Call Site 7 <<
	.uleb128 Lfunc_end2-Ltmp22              ##   Call between Ltmp22 and Lfunc_end2
	.byte	0                               ##     has no landing pad
	.byte	0                               ##   On action: cleanup
Lcst_end2:
	.p2align	2
                                        ## -- End function
	.section	__TEXT,__text,regular,pure_instructions
	.globl	__Z9give_takex                  ## -- Begin function _Z9give_takex
	.p2align	4, 0x90
__Z9give_takex:                         ## @_Z9give_takex
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	xorl	%ecx, %ecx
	movq	%rdi, %rax
	negq	%rax
	cmovsq	%rdi, %rax
	jae	LBB4_5
## %bb.1:
	movl	%eax, %edx
	andl	$1, %edx
	testq	%rdx, %rdx
	jne	LBB4_5
## %bb.2:
	xorl	%ecx, %ecx
	.p2align	4, 0x90
LBB4_3:                                 ## =>This Inner Loop Header: Depth=1
	addq	$1, %rcx
	cmpq	$2, %rax
	jb	LBB4_5
## %bb.4:                               ##   in Loop: Header=BB4_3 Depth=1
	movq	%rax, %rdx
	shrq	$63, %rdx
	addq	%rax, %rdx
	sarq	%rdx
	movq	%rdx, %rax
                                        ## kill: def $edx killed $edx killed $rdx def $rdx
	andl	$1, %edx
	testq	%rdx, %rdx
	je	LBB4_3
LBB4_5:
	movq	%rcx, %rax
	shlq	$32, %rax
	orq	%rcx, %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZlsRNSt3__113basic_ostreamIcNS_11char_traitsIcEEEENS_4pairIiiEE ## -- Begin function _ZlsRNSt3__113basic_ostreamIcNS_11char_traitsIcEEEENS_4pairIiiEE
	.p2align	4, 0x90
__ZlsRNSt3__113basic_ostreamIcNS_11char_traitsIcEEEENS_4pairIiiEE: ## @_ZlsRNSt3__113basic_ostreamIcNS_11char_traitsIcEEEENS_4pairIiiEE
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r14
	pushq	%rbx
	.cfi_offset %rbx, -32
	.cfi_offset %r14, -24
	movq	%rsi, %r14
	movq	%rsi, %rbx
	shrq	$32, %rbx
	leaq	L_.str(%rip), %rsi
	movl	$1, %edx
	callq	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	movq	%rax, %rdi
	movl	%r14d, %esi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi
	leaq	L_.str.1(%rip), %rsi
	movl	$2, %edx
	movq	%rax, %rdi
	callq	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	movq	%rax, %rdi
	movl	%ebx, %esi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi
	leaq	L_.str.2(%rip), %rsi
	movl	$1, %edx
	movq	%rax, %rdi
	popq	%rbx
	popq	%r14
	popq	%rbp
	jmp	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m ## TAILCALL
	.cfi_endproc
                                        ## -- End function
	.globl	__Z5solvev                      ## -- Begin function _Z5solvev
	.p2align	4, 0x90
__Z5solvev:                             ## @_Z5solvev
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                           ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
Lfunc_begin3:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception3
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r14
	pushq	%rbx
	subq	$16, %rsp
	.cfi_offset %rbx, -32
	.cfi_offset %r14, -24
	xorl	%edi, %edi
	callq	__ZNSt3__18ios_base15sync_with_stdioEb
	movq	__ZNSt3__13cinE@GOTPCREL(%rip), %rax
	movq	(%rax), %rcx
	movq	-24(%rcx), %rcx
	movq	$0, 136(%rax,%rcx)
	movq	__ZNSt3__14coutE@GOTPCREL(%rip), %rdi
	leaq	L_.str(%rip), %rsi
	movl	$1, %edx
	callq	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	movq	%rax, %rdi
	xorl	%esi, %esi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi
	leaq	L_.str.1(%rip), %rsi
	movl	$2, %edx
	movq	%rax, %rdi
	callq	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	movq	%rax, %rdi
	xorl	%esi, %esi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi
	leaq	L_.str.2(%rip), %rsi
	movl	$1, %edx
	movq	%rax, %rdi
	callq	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	movq	%rax, %rbx
	movq	(%rax), %rax
	movq	-24(%rax), %rsi
	addq	%rbx, %rsi
	leaq	-24(%rbp), %r14
	movq	%r14, %rdi
	callq	__ZNKSt3__18ios_base6getlocEv
Ltmp26:
	movq	__ZNSt3__15ctypeIcE2idE@GOTPCREL(%rip), %rsi
	movq	%r14, %rdi
	callq	__ZNKSt3__16locale9use_facetERNS0_2idE
Ltmp27:
## %bb.1:
	movq	(%rax), %rcx
Ltmp28:
	movq	%rax, %rdi
	movl	$10, %esi
	callq	*56(%rcx)
Ltmp29:
## %bb.2:
	movl	%eax, %r14d
	leaq	-24(%rbp), %rdi
	callq	__ZNSt3__16localeD1Ev
	movsbl	%r14b, %esi
	movq	%rbx, %rdi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE3putEc
	movq	%rbx, %rdi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE5flushEv
	xorl	%eax, %eax
	addq	$16, %rsp
	popq	%rbx
	popq	%r14
	popq	%rbp
	retq
LBB7_3:
Ltmp30:
	movq	%rax, %rbx
	leaq	-24(%rbp), %rdi
	callq	__ZNSt3__16localeD1Ev
	movq	%rbx, %rdi
	callq	__Unwind_Resume
Lfunc_end3:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2
GCC_except_table7:
Lexception3:
	.byte	255                             ## @LPStart Encoding = omit
	.byte	255                             ## @TType Encoding = omit
	.byte	1                               ## Call site Encoding = uleb128
	.uleb128 Lcst_end3-Lcst_begin3
Lcst_begin3:
	.uleb128 Lfunc_begin3-Lfunc_begin3      ## >> Call Site 1 <<
	.uleb128 Ltmp26-Lfunc_begin3            ##   Call between Lfunc_begin3 and Ltmp26
	.byte	0                               ##     has no landing pad
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp26-Lfunc_begin3            ## >> Call Site 2 <<
	.uleb128 Ltmp29-Ltmp26                  ##   Call between Ltmp26 and Ltmp29
	.uleb128 Ltmp30-Lfunc_begin3            ##     jumps to Ltmp30
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp29-Lfunc_begin3            ## >> Call Site 3 <<
	.uleb128 Lfunc_end3-Ltmp29              ##   Call between Ltmp29 and Lfunc_end3
	.byte	0                               ##     has no landing pad
	.byte	0                               ##   On action: cleanup
Lcst_end3:
	.p2align	2
                                        ## -- End function
	.section	__TEXT,__text,regular,pure_instructions
	.private_extern	___clang_call_terminate ## -- Begin function __clang_call_terminate
	.globl	___clang_call_terminate
	.weak_def_can_be_hidden	___clang_call_terminate
	.p2align	4, 0x90
___clang_call_terminate:                ## @__clang_call_terminate
## %bb.0:
	pushq	%rax
	callq	___cxa_begin_catch
	callq	__ZSt9terminatev
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function _ZNKSt3__113__vector_baseIcNS_9allocatorIcEEE20__throw_length_errorEv
__ZNKSt3__113__vector_baseIcNS_9allocatorIcEEE20__throw_length_errorEv: ## @_ZNKSt3__113__vector_baseIcNS_9allocatorIcEEE20__throw_length_errorEv
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	callq	__ZNKSt3__120__vector_base_commonILb1EE20__throw_length_errorEv
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function _ZNSt3__1L20__throw_length_errorEPKc
__ZNSt3__1L20__throw_length_errorEPKc:  ## @_ZNSt3__1L20__throw_length_errorEPKc
Lfunc_begin4:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception4
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r14
	pushq	%rbx
	.cfi_offset %rbx, -32
	.cfi_offset %r14, -24
	movl	$16, %edi
	callq	___cxa_allocate_exception
	movq	%rax, %rbx
Ltmp31:
	movq	%rax, %rdi
	callq	__ZNSt12length_errorC1EPKc
Ltmp32:
## %bb.1:
	movq	__ZTISt12length_error@GOTPCREL(%rip), %rsi
	movq	__ZNSt12length_errorD1Ev@GOTPCREL(%rip), %rdx
	movq	%rbx, %rdi
	callq	___cxa_throw
LBB10_2:
Ltmp33:
	movq	%rax, %r14
	movq	%rbx, %rdi
	callq	___cxa_free_exception
	movq	%r14, %rdi
	callq	__Unwind_Resume
Lfunc_end4:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2
GCC_except_table10:
Lexception4:
	.byte	255                             ## @LPStart Encoding = omit
	.byte	255                             ## @TType Encoding = omit
	.byte	1                               ## Call site Encoding = uleb128
	.uleb128 Lcst_end4-Lcst_begin4
Lcst_begin4:
	.uleb128 Lfunc_begin4-Lfunc_begin4      ## >> Call Site 1 <<
	.uleb128 Ltmp31-Lfunc_begin4            ##   Call between Lfunc_begin4 and Ltmp31
	.byte	0                               ##     has no landing pad
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp31-Lfunc_begin4            ## >> Call Site 2 <<
	.uleb128 Ltmp32-Ltmp31                  ##   Call between Ltmp31 and Ltmp32
	.uleb128 Ltmp33-Lfunc_begin4            ##     jumps to Ltmp33
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp32-Lfunc_begin4            ## >> Call Site 3 <<
	.uleb128 Lfunc_end4-Ltmp32              ##   Call between Ltmp32 and Lfunc_end4
	.byte	0                               ##     has no landing pad
	.byte	0                               ##   On action: cleanup
Lcst_end4:
	.p2align	2
                                        ## -- End function
	.section	__TEXT,__text,regular,pure_instructions
	.p2align	4, 0x90                         ## -- Begin function _ZNSt12length_errorC1EPKc
__ZNSt12length_errorC1EPKc:             ## @_ZNSt12length_errorC1EPKc
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	pushq	%rax
	.cfi_offset %rbx, -24
	movq	%rdi, %rbx
	leaq	L_.str.3(%rip), %rsi
	callq	__ZNSt11logic_errorC2EPKc
	movq	__ZTVSt12length_error@GOTPCREL(%rip), %rax
	addq	$16, %rax
	movq	%rax, (%rbx)
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function _ZNKSt3__113__vector_baseIxNS_9allocatorIxEEE20__throw_length_errorEv
__ZNKSt3__113__vector_baseIxNS_9allocatorIxEEE20__throw_length_errorEv: ## @_ZNKSt3__113__vector_baseIxNS_9allocatorIxEEE20__throw_length_errorEv
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	callq	__ZNKSt3__120__vector_base_commonILb1EE20__throw_length_errorEv
	.cfi_endproc
                                        ## -- End function
	.globl	__ZNSt3__16__treeIxNS_4lessIxEENS_9allocatorIxEEE7destroyEPNS_11__tree_nodeIxPvEE ## -- Begin function _ZNSt3__16__treeIxNS_4lessIxEENS_9allocatorIxEEE7destroyEPNS_11__tree_nodeIxPvEE
	.weak_def_can_be_hidden	__ZNSt3__16__treeIxNS_4lessIxEENS_9allocatorIxEEE7destroyEPNS_11__tree_nodeIxPvEE
	.p2align	4, 0x90
__ZNSt3__16__treeIxNS_4lessIxEENS_9allocatorIxEEE7destroyEPNS_11__tree_nodeIxPvEE: ## @_ZNSt3__16__treeIxNS_4lessIxEENS_9allocatorIxEEE7destroyEPNS_11__tree_nodeIxPvEE
	.cfi_startproc
## %bb.0:
	testq	%rsi, %rsi
	je	LBB13_1
## %bb.2:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r14
	pushq	%rbx
	.cfi_offset %rbx, -32
	.cfi_offset %r14, -24
	movq	%rsi, %rbx
	movq	%rdi, %r14
	movq	(%rsi), %rsi
	callq	__ZNSt3__16__treeIxNS_4lessIxEENS_9allocatorIxEEE7destroyEPNS_11__tree_nodeIxPvEE
	movq	8(%rbx), %rsi
	movq	%r14, %rdi
	callq	__ZNSt3__16__treeIxNS_4lessIxEENS_9allocatorIxEEE7destroyEPNS_11__tree_nodeIxPvEE
	movq	%rbx, %rdi
	popq	%rbx
	popq	%r14
	popq	%rbp
	jmp	__ZdlPv                         ## TAILCALL
LBB13_1:
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZNSt3__127__tree_balance_after_insertIPNS_16__tree_node_baseIPvEEEEvT_S5_ ## -- Begin function _ZNSt3__127__tree_balance_after_insertIPNS_16__tree_node_baseIPvEEEEvT_S5_
	.weak_def_can_be_hidden	__ZNSt3__127__tree_balance_after_insertIPNS_16__tree_node_baseIPvEEEEvT_S5_
	.p2align	4, 0x90
__ZNSt3__127__tree_balance_after_insertIPNS_16__tree_node_baseIPvEEEEvT_S5_: ## @_ZNSt3__127__tree_balance_after_insertIPNS_16__tree_node_baseIPvEEEEvT_S5_
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	cmpq	%rdi, %rsi
	sete	24(%rsi)
	jne	LBB14_1
LBB14_25:
	popq	%rbp
	retq
	.p2align	4, 0x90
LBB14_5:                                ##   in Loop: Header=BB14_1 Depth=1
	addq	$24, %rdx
	movb	$1, 24(%rcx)
	movq	%rax, %rsi
	cmpq	%rdi, %rax
	sete	24(%rax)
	movb	$1, (%rdx)
	je	LBB14_25
LBB14_1:                                ## =>This Inner Loop Header: Depth=1
	movq	16(%rsi), %rcx
	cmpb	$0, 24(%rcx)
	jne	LBB14_25
## %bb.2:                               ##   in Loop: Header=BB14_1 Depth=1
	movq	16(%rcx), %rax
	movq	(%rax), %rdx
	cmpq	%rcx, %rdx
	je	LBB14_3
## %bb.14:                              ##   in Loop: Header=BB14_1 Depth=1
	testq	%rdx, %rdx
	je	LBB14_16
## %bb.15:                              ##   in Loop: Header=BB14_1 Depth=1
	cmpb	$0, 24(%rdx)
	je	LBB14_5
	jmp	LBB14_16
	.p2align	4, 0x90
LBB14_3:                                ##   in Loop: Header=BB14_1 Depth=1
	movq	8(%rax), %rdx
	testq	%rdx, %rdx
	je	LBB14_6
## %bb.4:                               ##   in Loop: Header=BB14_1 Depth=1
	cmpb	$0, 24(%rdx)
	je	LBB14_5
LBB14_6:
	cmpq	%rsi, (%rcx)
	je	LBB14_7
## %bb.8:
	movq	8(%rcx), %rdx
	movq	(%rdx), %rsi
	movq	%rsi, 8(%rcx)
	testq	%rsi, %rsi
	je	LBB14_10
## %bb.9:
	movq	%rcx, 16(%rsi)
	movq	16(%rcx), %rax
LBB14_10:
	movq	%rax, 16(%rdx)
	movq	16(%rcx), %rax
	xorl	%esi, %esi
	cmpq	%rcx, (%rax)
	setne	%sil
	movq	%rdx, (%rax,%rsi,8)
	movq	%rcx, (%rdx)
	movq	%rdx, 16(%rcx)
	movq	16(%rdx), %rax
	jmp	LBB14_11
LBB14_16:
	cmpq	%rsi, (%rcx)
	je	LBB14_18
## %bb.17:
	movq	%rcx, %rsi
	jmp	LBB14_21
LBB14_18:
	movq	8(%rsi), %rdx
	movq	%rdx, (%rcx)
	testq	%rdx, %rdx
	je	LBB14_20
## %bb.19:
	movq	%rcx, 16(%rdx)
	movq	16(%rcx), %rax
LBB14_20:
	movq	%rax, 16(%rsi)
	movq	16(%rcx), %rax
	xorl	%edx, %edx
	cmpq	%rcx, (%rax)
	setne	%dl
	movq	%rsi, (%rax,%rdx,8)
	movq	%rcx, 8(%rsi)
	movq	%rsi, 16(%rcx)
	movq	16(%rsi), %rax
LBB14_21:
	movb	$1, 24(%rsi)
	movb	$0, 24(%rax)
	movq	8(%rax), %rcx
	movq	(%rcx), %rdx
	movq	%rdx, 8(%rax)
	testq	%rdx, %rdx
	je	LBB14_23
## %bb.22:
	movq	%rax, 16(%rdx)
LBB14_23:
	movq	16(%rax), %rdx
	movq	%rdx, 16(%rcx)
	movq	16(%rax), %rsi
	xorl	%edi, %edi
	cmpq	%rax, (%rsi)
	leaq	16(%rax), %rdx
	setne	%dil
	movq	%rcx, (%rsi,%rdi,8)
	movq	%rax, (%rcx)
	movq	%rcx, (%rdx)
	popq	%rbp
	retq
LBB14_7:
	movq	%rcx, %rdx
LBB14_11:
	movb	$1, 24(%rdx)
	movb	$0, 24(%rax)
	movq	(%rax), %rcx
	movq	8(%rcx), %rdx
	movq	%rdx, (%rax)
	testq	%rdx, %rdx
	je	LBB14_13
## %bb.12:
	movq	%rax, 16(%rdx)
LBB14_13:
	movq	16(%rax), %rdx
	movq	%rdx, 16(%rcx)
	movq	16(%rax), %rsi
	xorl	%edi, %edi
	cmpq	%rax, (%rsi)
	leaq	16(%rax), %rdx
	setne	%dil
	movq	%rcx, (%rsi,%rdi,8)
	movq	%rax, 8(%rcx)
	movq	%rcx, (%rdx)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m ## -- Begin function _ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	.weak_def_can_be_hidden	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	.p2align	4, 0x90
__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m: ## @_ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
Lfunc_begin5:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception5
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	movq	%rdx, %r14
	movq	%rsi, %r15
	movq	%rdi, %rbx
Ltmp34:
	leaq	-80(%rbp), %rdi
	movq	%rbx, %rsi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryC1ERS3_
Ltmp35:
## %bb.1:
	cmpb	$0, -80(%rbp)
	je	LBB15_10
## %bb.2:
	movq	(%rbx), %rax
	movq	-24(%rax), %rax
	leaq	(%rbx,%rax), %r12
	movq	40(%rbx,%rax), %rdi
	movl	8(%rbx,%rax), %r13d
	movl	144(%rbx,%rax), %eax
	cmpl	$-1, %eax
	jne	LBB15_7
## %bb.3:
Ltmp37:
	movq	%rdi, -64(%rbp)                 ## 8-byte Spill
	leaq	-56(%rbp), %rdi
	movq	%r12, %rsi
	callq	__ZNKSt3__18ios_base6getlocEv
Ltmp38:
## %bb.4:
Ltmp39:
	movq	__ZNSt3__15ctypeIcE2idE@GOTPCREL(%rip), %rsi
	leaq	-56(%rbp), %rdi
	callq	__ZNKSt3__16locale9use_facetERNS0_2idE
Ltmp40:
## %bb.5:
	movq	(%rax), %rcx
Ltmp41:
	movq	%rax, %rdi
	movl	$32, %esi
	callq	*56(%rcx)
	movb	%al, -41(%rbp)                  ## 1-byte Spill
Ltmp42:
## %bb.6:
	leaq	-56(%rbp), %rdi
	callq	__ZNSt3__16localeD1Ev
	movsbl	-41(%rbp), %eax                 ## 1-byte Folded Reload
	movl	%eax, 144(%r12)
	movq	-64(%rbp), %rdi                 ## 8-byte Reload
LBB15_7:
	addq	%r15, %r14
	andl	$176, %r13d
	cmpl	$32, %r13d
	movq	%r15, %rdx
	cmoveq	%r14, %rdx
Ltmp44:
	movsbl	%al, %r9d
	movq	%r15, %rsi
	movq	%r14, %rcx
	movq	%r12, %r8
	callq	__ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
Ltmp45:
## %bb.8:
	testq	%rax, %rax
	jne	LBB15_10
## %bb.9:
	movq	(%rbx), %rax
	movq	-24(%rax), %rax
	leaq	(%rbx,%rax), %rdi
	movl	32(%rbx,%rax), %esi
	orl	$5, %esi
Ltmp47:
	callq	__ZNSt3__18ios_base5clearEj
Ltmp48:
LBB15_10:
	leaq	-80(%rbp), %rdi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev
LBB15_11:
	movq	%rbx, %rax
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
LBB15_12:
Ltmp49:
	jmp	LBB15_15
LBB15_13:
Ltmp43:
	movq	%rax, %r14
	leaq	-56(%rbp), %rdi
	callq	__ZNSt3__16localeD1Ev
	jmp	LBB15_16
LBB15_14:
Ltmp46:
LBB15_15:
	movq	%rax, %r14
LBB15_16:
	leaq	-80(%rbp), %rdi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev
	jmp	LBB15_18
LBB15_17:
Ltmp36:
	movq	%rax, %r14
LBB15_18:
	movq	%r14, %rdi
	callq	___cxa_begin_catch
	movq	(%rbx), %rax
	movq	-24(%rax), %rdi
	addq	%rbx, %rdi
Ltmp50:
	callq	__ZNSt3__18ios_base33__set_badbit_and_consider_rethrowEv
Ltmp51:
## %bb.19:
	callq	___cxa_end_catch
	jmp	LBB15_11
LBB15_20:
Ltmp52:
	movq	%rax, %rbx
Ltmp53:
	callq	___cxa_end_catch
Ltmp54:
## %bb.21:
	movq	%rbx, %rdi
	callq	__Unwind_Resume
LBB15_22:
Ltmp55:
	movq	%rax, %rdi
	callq	___clang_call_terminate
Lfunc_end5:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2
GCC_except_table15:
Lexception5:
	.byte	255                             ## @LPStart Encoding = omit
	.byte	155                             ## @TType Encoding = indirect pcrel sdata4
	.uleb128 Lttbase0-Lttbaseref0
Lttbaseref0:
	.byte	1                               ## Call site Encoding = uleb128
	.uleb128 Lcst_end5-Lcst_begin5
Lcst_begin5:
	.uleb128 Ltmp34-Lfunc_begin5            ## >> Call Site 1 <<
	.uleb128 Ltmp35-Ltmp34                  ##   Call between Ltmp34 and Ltmp35
	.uleb128 Ltmp36-Lfunc_begin5            ##     jumps to Ltmp36
	.byte	1                               ##   On action: 1
	.uleb128 Ltmp37-Lfunc_begin5            ## >> Call Site 2 <<
	.uleb128 Ltmp38-Ltmp37                  ##   Call between Ltmp37 and Ltmp38
	.uleb128 Ltmp46-Lfunc_begin5            ##     jumps to Ltmp46
	.byte	1                               ##   On action: 1
	.uleb128 Ltmp39-Lfunc_begin5            ## >> Call Site 3 <<
	.uleb128 Ltmp42-Ltmp39                  ##   Call between Ltmp39 and Ltmp42
	.uleb128 Ltmp43-Lfunc_begin5            ##     jumps to Ltmp43
	.byte	1                               ##   On action: 1
	.uleb128 Ltmp44-Lfunc_begin5            ## >> Call Site 4 <<
	.uleb128 Ltmp45-Ltmp44                  ##   Call between Ltmp44 and Ltmp45
	.uleb128 Ltmp46-Lfunc_begin5            ##     jumps to Ltmp46
	.byte	1                               ##   On action: 1
	.uleb128 Ltmp47-Lfunc_begin5            ## >> Call Site 5 <<
	.uleb128 Ltmp48-Ltmp47                  ##   Call between Ltmp47 and Ltmp48
	.uleb128 Ltmp49-Lfunc_begin5            ##     jumps to Ltmp49
	.byte	1                               ##   On action: 1
	.uleb128 Ltmp48-Lfunc_begin5            ## >> Call Site 6 <<
	.uleb128 Ltmp50-Ltmp48                  ##   Call between Ltmp48 and Ltmp50
	.byte	0                               ##     has no landing pad
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp50-Lfunc_begin5            ## >> Call Site 7 <<
	.uleb128 Ltmp51-Ltmp50                  ##   Call between Ltmp50 and Ltmp51
	.uleb128 Ltmp52-Lfunc_begin5            ##     jumps to Ltmp52
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp51-Lfunc_begin5            ## >> Call Site 8 <<
	.uleb128 Ltmp53-Ltmp51                  ##   Call between Ltmp51 and Ltmp53
	.byte	0                               ##     has no landing pad
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp53-Lfunc_begin5            ## >> Call Site 9 <<
	.uleb128 Ltmp54-Ltmp53                  ##   Call between Ltmp53 and Ltmp54
	.uleb128 Ltmp55-Lfunc_begin5            ##     jumps to Ltmp55
	.byte	1                               ##   On action: 1
	.uleb128 Ltmp54-Lfunc_begin5            ## >> Call Site 10 <<
	.uleb128 Lfunc_end5-Ltmp54              ##   Call between Ltmp54 and Lfunc_end5
	.byte	0                               ##     has no landing pad
	.byte	0                               ##   On action: cleanup
Lcst_end5:
	.byte	1                               ## >> Action Record 1 <<
                                        ##   Catch TypeInfo 1
	.byte	0                               ##   No further actions
	.p2align	2
                                        ## >> Catch TypeInfos <<
	.long	0                               ## TypeInfo 1
Lttbase0:
	.p2align	2
                                        ## -- End function
	.section	__TEXT,__text,regular,pure_instructions
	.private_extern	__ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_ ## -- Begin function _ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
	.globl	__ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
	.weak_def_can_be_hidden	__ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
	.p2align	4, 0x90
__ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_: ## @_ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
Lfunc_begin6:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception6
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	testq	%rdi, %rdi
	je	LBB16_20
## %bb.1:
	movq	%r8, %r14
	movq	%rcx, %r15
	movq	%rdi, %r13
	movl	%r9d, -44(%rbp)                 ## 4-byte Spill
	movq	%rcx, %rax
	subq	%rsi, %rax
	movq	24(%r8), %rcx
	xorl	%r12d, %r12d
	subq	%rax, %rcx
	cmovgq	%rcx, %r12
	movq	%rdx, -88(%rbp)                 ## 8-byte Spill
	movq	%rdx, %rbx
	subq	%rsi, %rbx
	testq	%rbx, %rbx
	jle	LBB16_3
## %bb.2:
	movq	(%r13), %rax
	movq	%r13, %rdi
	movq	%rbx, %rdx
	callq	*96(%rax)
	cmpq	%rbx, %rax
	jne	LBB16_20
LBB16_3:
	testq	%r12, %r12
	jle	LBB16_16
## %bb.4:
	movq	%r14, -80(%rbp)                 ## 8-byte Spill
	cmpq	$23, %r12
	jae	LBB16_8
## %bb.5:
	leal	(%r12,%r12), %eax
	movb	%al, -72(%rbp)
	leaq	-71(%rbp), %r14
	jmp	LBB16_9
LBB16_8:
	leaq	16(%r12), %rbx
	andq	$-16, %rbx
	movq	%rbx, %rdi
	callq	__Znwm
	movq	%rax, %r14
	movq	%rax, -56(%rbp)
	orq	$1, %rbx
	movq	%rbx, -72(%rbp)
	movq	%r12, -64(%rbp)
LBB16_9:
	movl	-44(%rbp), %eax                 ## 4-byte Reload
	movzbl	%al, %esi
	movq	%r14, %rdi
	movq	%r12, %rdx
	callq	_memset
	movb	$0, (%r14,%r12)
	testb	$1, -72(%rbp)
	je	LBB16_11
## %bb.10:
	movq	-56(%rbp), %rsi
	jmp	LBB16_12
LBB16_11:
	leaq	-71(%rbp), %rsi
LBB16_12:
	movq	-80(%rbp), %r14                 ## 8-byte Reload
	movq	(%r13), %rax
Ltmp56:
	movq	%r13, %rdi
	movq	%r12, %rdx
	callq	*96(%rax)
Ltmp57:
## %bb.13:
	movq	%rax, %rbx
	testb	$1, -72(%rbp)
	je	LBB16_15
## %bb.14:
	movq	-56(%rbp), %rdi
	callq	__ZdlPv
LBB16_15:
	cmpq	%r12, %rbx
	jne	LBB16_20
LBB16_16:
	movq	-88(%rbp), %rsi                 ## 8-byte Reload
	subq	%rsi, %r15
	testq	%r15, %r15
	jle	LBB16_18
## %bb.17:
	movq	(%r13), %rax
	movq	%r13, %rdi
	movq	%r15, %rdx
	callq	*96(%rax)
	cmpq	%r15, %rax
	jne	LBB16_20
LBB16_18:
	movq	$0, 24(%r14)
	jmp	LBB16_21
LBB16_20:
	xorl	%r13d, %r13d
LBB16_21:
	movq	%r13, %rax
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
LBB16_22:
Ltmp58:
	movq	%rax, %rbx
	testb	$1, -72(%rbp)
	je	LBB16_24
## %bb.23:
	movq	-56(%rbp), %rdi
	callq	__ZdlPv
LBB16_24:
	movq	%rbx, %rdi
	callq	__Unwind_Resume
Lfunc_end6:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2
GCC_except_table16:
Lexception6:
	.byte	255                             ## @LPStart Encoding = omit
	.byte	255                             ## @TType Encoding = omit
	.byte	1                               ## Call site Encoding = uleb128
	.uleb128 Lcst_end6-Lcst_begin6
Lcst_begin6:
	.uleb128 Lfunc_begin6-Lfunc_begin6      ## >> Call Site 1 <<
	.uleb128 Ltmp56-Lfunc_begin6            ##   Call between Lfunc_begin6 and Ltmp56
	.byte	0                               ##     has no landing pad
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp56-Lfunc_begin6            ## >> Call Site 2 <<
	.uleb128 Ltmp57-Ltmp56                  ##   Call between Ltmp56 and Ltmp57
	.uleb128 Ltmp58-Lfunc_begin6            ##     jumps to Ltmp58
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp57-Lfunc_begin6            ## >> Call Site 3 <<
	.uleb128 Lfunc_end6-Ltmp57              ##   Call between Ltmp57 and Lfunc_end6
	.byte	0                               ##     has no landing pad
	.byte	0                               ##   On action: cleanup
Lcst_end6:
	.p2align	2
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"{"

L_.str.1:                               ## @.str.1
	.asciz	", "

L_.str.2:                               ## @.str.2
	.asciz	"}"

L_.str.3:                               ## @.str.3
	.asciz	"allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size"

.subsections_via_symbols
