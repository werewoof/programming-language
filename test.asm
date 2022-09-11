default rel
bits 64

segment .data
    LC0:
        db "%d", 0xd, 0xa, 0 ;format for printing int
    first equ 12
    second equ 14

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
    
    mov     r9, first
    mov     r8, 3
    idiv    r9
    
    call    printf

    mov rsp, rbp
    pop rbp ;or we can just use the leave instruction
    
    ret

main:
    push    rbp ;push old base pointer in stack
    mov     rbp, rsp ;stack pointer is base pointer now
    sub     rsp, 32 ; allocates 32 bytes on stack

    call    _CRT_INIT

    call    printint

    mov rsp, rbp
    pop rbp

    xor     rcx, rcx ; returns status code 0 i think

    call    ExitProcess
    
