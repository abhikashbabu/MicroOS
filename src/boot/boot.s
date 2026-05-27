MAGIC       equ  0x1BADB002
FLAGS       equ  7                   ; 1 (Align) + 2 (MemInfo) + 4 (Video Info/VESA)
CHECKSUM    equ -(MAGIC + FLAGS)

section .multiboot  ; Tumhara linker.ld isko top par rakhega
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
    dd 0, 0, 0, 0, 0
    dd 0        ; Mode type: 0 = Linear Graphics
    dd 1024     ; Width
    dd 768      ; Height
    dd 32       ; Depth (32-bit color)

section .text
global _start
extern kernel_main

_start:
    mov esp, stack_top
    push ebx  ; Parchi (Multiboot Info Address) Kernel ko bheji
    push eax  ; Magic Number Kernel ko bheja
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