; ----------------------------------------------------
; NAYA (DAY 103): MULTIBOOT HEADER FOR VESA HIGH-RES
; ----------------------------------------------------
MBALIGN     equ  1<<0                   ; Align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; Provide memory map
VIDINFO     equ  1<<2                   ; NAYA: Tell GRUB we want a Video Framebuffer!
FLAGS       equ  MBALIGN | MEMINFO | VIDINFO
MAGIC       equ  0x1BADB002             ; Multiboot Magic Number
CHECKSUM    equ -(MAGIC + FLAGS)

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
    
    ; Address fields (not used here, so 5 zeros)
    dd 0, 0, 0, 0, 0
    
    ; Graphics requests (Because VIDINFO flag is set)
    dd 0        ; Mode type: 0 = Linear Graphics (VESA)
    dd 1024     ; Width
    dd 768      ; Height
    dd 32       ; Depth (32-bit color ARGB)

section .bss
align 16
stack_bottom:
resb 16384 ; 16 KB Stack
stack_top:

section .text
global _start
extern kernel_main

_start:
    mov esp, stack_top
    
    ; Push Multiboot info structure pointer (ebx) and magic number (eax) to kernel
    push ebx
    push eax
    
    call kernel_main

    cli
.hang:
    hlt
    jmp .hang