MAGIC       equ  0x1BADB002
FLAGS       equ  3                   ; Sirf basic Memory aur Align flags
CHECKSUM    equ -(MAGIC + FLAGS)

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .text
global _start
extern kernel_main

_start:
    mov esp, stack_top
    push ebx
    push eax
    call kernel_main
    cli
.hang:
    hlt
    jmp .hang

section .bss
align 16
stack_bottom:
    resb 16384
stack_top: