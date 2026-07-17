// ==============================================================
// BULLETPROOF ATA DRIVER (BSY SYNC PROTECTED)
// ==============================================================
#ifndef ATA_H
#define ATA_H

#include "../kernel/io.h"

static inline unsigned short inw(unsigned short port) {
    unsigned short rv;
    __asm__ __volatile__ ("inw %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}

static inline void outw(unsigned short port, unsigned short data) {
    __asm__ __volatile__ ("outw %1, %0" : : "dN" (port), "a" (data));
}

// FIX: Yahan static laga diya hai
static void ata_wait_ready() {
    int timeout = 99999999;
    while ((inb(0x1F7) & 0x80) == 0x80) { // Check BSY (Busy) bit
        if (--timeout == 0) break;
    }
    // Chhota sa safe delay 
    for(volatile int i = 0; i < 1000; i++); 
}

// FIX: Yahan static laga diya hai
static int ata_wait() {
    int timeout = 99999999; 
    while((inb(0x1F7) & 0x80) == 0x80) { 
        if (--timeout == 0) return 0; 
    } 
    timeout = 99999999;
    while((inb(0x1F7) & 0x08) == 0) {    
        if (inb(0x1F7) & 0x01) return 0; // ERR bit 
        if (--timeout == 0) return 0; 
    }
    return 1; 
}

// FIX: Yahan static laga diya hai
static void ata_read_sector(unsigned int lba, unsigned char* buffer) {
    ata_wait_ready(); 
    outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F));
    outb(0x1F2, 1); 
    outb(0x1F3, (unsigned char) lba);
    outb(0x1F4, (unsigned char)(lba >> 8));
    outb(0x1F5, (unsigned char)(lba >> 16));
    outb(0x1F7, 0x20); 

    if (!ata_wait()) return; 

    for (int i = 0; i < 256; i++) {
        unsigned short word = inw(0x1F0);
        buffer[i * 2] = (unsigned char)(word & 0xFF);
        buffer[i * 2 + 1] = (unsigned char)(word >> 8);
    }
}

// FIX: Yahan static laga diya hai
static void ata_write_sector(unsigned int lba, unsigned char* buffer) {
    ata_wait_ready(); 

    outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F));
    outb(0x1F2, 1);
    outb(0x1F3, (unsigned char) lba);
    outb(0x1F4, (unsigned char)(lba >> 8));
    outb(0x1F5, (unsigned char)(lba >> 16));
    outb(0x1F7, 0x30); 

    if (!ata_wait()) return; 

    for (int i = 0; i < 256; i++) {
        unsigned short word = (buffer[i * 2 + 1] << 8) | buffer[i * 2];
        outw(0x1F0, word);
    }
    
    ata_wait_ready(); 
}

#endif