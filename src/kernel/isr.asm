; ==========================================
; MICRO OS: INTERRUPT SERVICE ROUTINES (ISR)
; ==========================================

section .text

; In functions ko hum C code (idt.h) se call karenge
global isr32
global isr33
global isr44

; Yeh functions humare C code (kernel.c ya timer.h) mein likhe hain
extern timer_handler
extern keyboard_irq_handler
extern mouse_irq_handler

; ------------------------------------------
; IRQ0: System Timer (Interrupt 32)
; ------------------------------------------
isr32:
    pusha           ; CPU ke saare registers ko safe rakho
    cld             ; C code call karne se pehle direction flag clear karo
    call timer_handler ; Tumhara C wala timer function call karo
    popa            ; Wapas aane par registers restore karo
    iretd           ; Interrupt se wapas return karo

; ------------------------------------------
; IRQ1: Keyboard (Interrupt 33)
; ------------------------------------------
isr33:
    pusha
    cld
    call keyboard_irq_handler
    popa
    iretd

; ------------------------------------------
; IRQ12: PS/2 Mouse (Interrupt 44)
; ------------------------------------------
isr44:
    pusha
    cld
    call mouse_irq_handler
    popa
    iretd