#ifndef PIC_H
#define PIC_H

#include "../kernel/io.h"

// PIC chips ke ports (Master aur Slave)
#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1
extern void context_switch_handler();
// ==========================================
// src/kernel/pic.h - UPDATE
// ==========================================

void pic_init() {
    // ICW1: Init
    outb(0x20, 0x11); outb(0xA0, 0x11);
    // ICW2: Vector Offset (Master starts at 32, Slave at 40)
    outb(0x21, 0x20); outb(0xA1, 0x28);
    // ICW3: Cascading
    outb(0x21, 0x04); outb(0xA1, 0x02);
    // ICW4: 8086 mode
    outb(0x21, 0x01); outb(0xA1, 0x01);
    
    // NAYA CODE YAHAN HAI:
    // Masking: 0xF8 = 11111000 (Allows IRQ0 Timer, IRQ1 Keyboard, IRQ2 Cascade)
    outb(0x21, 0xF8); 
    // Masking: 0xEF = 11101111 (Allows IRQ12 PS/2 Mouse)
    outb(0xA1, 0xEF); 
}

#endif