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
	mov		rbp, rsp
	sub		rsp, 32
	lea		rcx, [LC0]
	mov		rdx, rdi
	call	printf
	mov		rsp, rbp
	pop		rbp
	ret
main:
	push	rbp
	mov		rbp, rsp
	sub		rsp, 32
	call	_CRT_INIT
	common	fred 8
	common	jim 8
	mov		r8, 5
	mov		r9, 12
	add		r9, r8
	mov	qword [fred], r9
	mov		r8, 12
	mov	r9, [fred]
	add		r9, r8
	mov	qword [jim], r9
	mov	r8, [fred]
	mov	r9, [jim]
	add		r9, r8
	mov		rdi, r9
	call	printint
	mov		rsp, rbp
	pop		rbp
	xor		rcx, rcx
	call	ExitProcess
