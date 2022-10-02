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
	common	x 8
	mov		r8, 7
	mov		r9, 9
	cmp		r8, r9
	setl	r9b
	and		r9, 255
	mov		qword [x], r9
	mov	r8, [x]
	mov		rdi, r8
	call	printint
	mov		r8, 7
	mov		r9, 9
	cmp		r8, r9
	setle	r9b
	and		r9, 255
	mov		qword [x], r9
	mov	r8, [x]
	mov		rdi, r8
	call	printint
	mov		r8, 7
	mov		r9, 9
	cmp		r8, r9
	setne	r9b
	and		r9, 255
	mov		qword [x], r9
	mov	r8, [x]
	mov		rdi, r8
	call	printint
	mov		r8, 7
	mov		r9, 7
	cmp		r8, r9
	sete	r9b
	and		r9, 255
	mov		qword [x], r9
	mov	r8, [x]
	mov		rdi, r8
	call	printint
	mov		r8, 7
	mov		r9, 7
	cmp		r8, r9
	setge	r9b
	and		r9, 255
	mov		qword [x], r9
	mov	r8, [x]
	mov		rdi, r8
	call	printint
	mov		r8, 7
	mov		r9, 7
	cmp		r8, r9
	setle	r9b
	and		r9, 255
	mov		qword [x], r9
	mov	r8, [x]
	mov		rdi, r8
	call	printint
	mov		r8, 6
	mov		r9, 7
	cmp		r8, r9
	setg	r9b
	and		r9, 255
	mov		qword [x], r9
	mov	r8, [x]
	mov		rdi, r8
	call	printint
	mov		r8, 9
	mov		r9, 7
	cmp		r8, r9
	setge	r9b
	and		r9, 255
	mov		qword [x], r9
	mov	r8, [x]
	mov		rdi, r8
	call	printint
	mov		r8, 9
	mov		r9, 7
	cmp		r8, r9
	setne	r9b
	and		r9, 255
	mov		qword [x], r9
	mov	r8, [x]
	mov		rdi, r8
	call	printint
	mov		rsp, rbp
	pop		rbp
	xor		rcx, rcx
	call	ExitProcess
