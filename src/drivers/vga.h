#ifndef VGA_H
#define VGA_H

#include "../kernel/io.h"

// VGA Hardware Register Ports
#define MISC_PORT 0x3C2
#define CRTC_INDEX 0x3D4
#define CRTC_DATA 0x3D5
#define SEQ_INDEX 0x3C4
#define SEQ_DATA 0x3C5
#define GC_INDEX 0x3CE
#define GC_DATA 0x3CF
#define AC_INDEX 0x3C0
#define AC_WRITE 0x3C0
#define AC_READ 0x3C1

// The Magical 61-byte array to unlock 320x200 Graphical Mode (Mode 13h)
unsigned char mode_13h_regs[] = {
    /* MISC */ 0x63,
    /* SEQ */ 0x03, 0x01, 0x0F, 0x00, 0x0E,
    /* CRTC */ 0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F, 0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9C, 0x0E, 0x8F, 0x28, 0x40, 0x96, 0xB9, 0xA3, 0xFF,
    /* GC */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F, 0xFF,
    /* AC */ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x41, 0x00, 0x0F, 0x00, 0x00
};

// Function to inject array into GPU Registers
void init_vga_graphics() {
    int i;
    outb(MISC_PORT, mode_13h_regs[0]);
    for(i = 0; i < 5; i++) { outb(SEQ_INDEX, i); outb(SEQ_DATA, mode_13h_regs[1 + i]); }
    
    // Unlock CRTC registers
    outb(CRTC_INDEX, 0x03); outb(CRTC_DATA, inb(CRTC_DATA) | 0x80);
    outb(CRTC_INDEX, 0x11); outb(CRTC_DATA, inb(CRTC_DATA) & ~0x80);
    mode_13h_regs[0x03] |= 0x80;
    mode_13h_regs[0x11] &= ~0x80;
    
    for(i = 0; i < 25; i++) { outb(CRTC_INDEX, i); outb(CRTC_DATA, mode_13h_regs[6 + i]); }
    for(i = 0; i < 9; i++) { outb(GC_INDEX, i); outb(GC_DATA, mode_13h_regs[31 + i]); }
    for(i = 0; i < 21; i++) { inb(0x3DA); outb(AC_INDEX, i); outb(AC_WRITE, mode_13h_regs[40 + i]); }
    
    inb(0x3DA); outb(AC_INDEX, 0x20); // Enable screen output
}

// 0xA0000 is the physical RAM address where VGA pixels are stored
unsigned char* vga_mem = (unsigned char*) 0xA0000;

// The Ultimate Function: Draw a single dot on the screen
void put_pixel(int x, int y, unsigned char color) {
    if(x >= 0 && x < 320 && y >= 0 && y < 200) {
        vga_mem[(y * 320) + x] = color;
    }
}

#endif