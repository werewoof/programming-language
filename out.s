default rel
bits 64
global main
global printint
extern _CRT_INIT
extern ExitProcess
extern printf
segment . data
	LC0: db "%d", 0xd, 0xa, 0
segment .text
printint:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	lea	rcx, [LC0]
	mov	rdx, rdi
	call	printf
	mov	rsp, rbp
	pop	rbp
	ret
main:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	call _CRT_INIT
	mov	$r8, 2
	mov	$r9, 3
	mov	$r10, 5
	imul	r10, r9
	add	r10, r8
	mov	$r8, 8
	mov	$r9, 3
	mov	r8, r8
	mov	r9, r9
	idiv	r9
	mov	rax,r8
	sub	r8, r10
	mov	rdi, rax
	call	printint
	mov	rsp, rbp
	pop	rbp
	xor	rcx, rcx
	call	ExitProcess
