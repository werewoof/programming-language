default rel
bits 64

segment .data
    LC0:
        db "brah %d", 0xd, 0xa, 0 ;format for printing int
    LC1:
        dq 6

segment .text

global main
global printint

extern _CRT_INIT
extern ExitProcess
extern printf

printint:
    push    rbp ;push old base pointer in stack
    mov     rbp, rsp ;stack pointer is base pointer now
    sub     rsp, 32 ; allocates 32 bytes on stack
    
    lea     rcx, [LC0] ;load memory address of string format to rcx register
    
    mov rdx, rdi

    call    printf

    mov rsp, rbp
    pop rbp ;or we can just use the leave instruction
    
    ret

main:
    push    rbp ;push old base pointer in stack
    mov     rbp, rsp ;stack pointer is base pointer now
    sub     rsp, 32 ; allocates 32 bytes on stack

    call    _CRT_INIT

    ;mov     rax, 36
    ;mov     r9, 6
    ;cqo ; extends to 8 bytes
    ;crashes if u remove cqo
    ;idiv    r9 ;rax is affected by idiv
	mov		r8, 2
	mov		r9, 3
	mov		r10, 5
	imul		r10, r9
	add		r10, r8
	mov		r8, 8
	mov		r9, 3
	mov		rax, r8
	cqo
	idiv	r9
	mov		r8,rax
	sub		r10, r8
	mov		rdi, r10

    call    printint

    mov rsp, rbp
    pop rbp

    xor     rcx, rcx ; returns status code 0 i think

    call    ExitProcess
    
