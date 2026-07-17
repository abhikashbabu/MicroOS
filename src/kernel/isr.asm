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



    global gdt_flush
extern gp

gdt_flush:
    lgdt [gp]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2
flush2:
    ret

global tss_flush
tss_flush:
    mov ax, 0x2B ; GDT entry 5 (TSS) = 0x28 + Ring 3 (0x3) = 0x2B
    ltr ax       ; CPU ko TSS load karne ka command do
    ret
    global switch_to_user_mode

switch_to_user_mode:
    cli                     ; Interrupts band karo taaki switch ke beech mein OS crash na ho
    mov eax, [esp+4]        ; C code se aane wala pehla argument (User App ka address)
    
    ; Ring 3 Data Segment = 0x20 (GDT entry 4) | 0x3 (Ring 3) = 0x23
    mov cx, 0x23            
    mov ds, cx
    mov es, cx
    mov fs, cx
    mov gs, cx
    
    ; CPU ko bewakoof banane ke liye jhootha Stack (IRET Frame) banao:
    push 0x23               ; 1. SS3 (Ring 3 Stack Segment)
    mov ecx, esp            ; User Mode ke liye abhi current stack hi use kar lete hain
    push ecx                ; 2. ESP3 (Ring 3 Stack Pointer)
    
    pushf                   ; EFLAGS register ko stack par daalo
    pop ecx                 ; Usko ECX mein nikal lo
    or ecx, 0x3200          ; 3. EFLAGS mein Interrupts (0x200) aur IOPL=3 (0x3000) On karo! 
                            ; (IOPL=3 se humari app hardware direct use kar payegi bina Syscall ke)
    push ecx                ; Modify kiya hua EFLAGS wapas stack par daalo
    
    push 0x1B               ; 4. CS3 (Ring 3 Code Segment) = 0x18 | 0x3 = 0x1B
    push eax                ; 5. EIP (Asli App/Function ka address)
    
    iret                    ; BOOM! CPU ko lagega return kar raha hai, par wo Ring 3 mein girega!
    