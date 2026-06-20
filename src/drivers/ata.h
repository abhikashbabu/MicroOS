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

// ==============================================================
// NAYA MAGIC: TIMEOUT EMERGENCY EXIT (OS Hang hone se bachayega)
// ==============================================================
int ata_wait() {
    int timeout = 100000; // Maximum itni baar wait karega, phir chhod dega
    
    // Wait for BSY (Busy) bit to clear
    while((inb(0x1F7) & 0x80) == 0x80) { 
        if (--timeout == 0) return 0; // Fail (Disk ne dhoka de diya)
    } 
    
    timeout = 100000;
    // Wait for DRQ (Data Request) bit to set
    while((inb(0x1F7) & 0x08) == 0) {    
        if (inb(0x1F7) & 0x01) return 0; // Error bit check
        if (--timeout == 0) return 0; // Fail
    }
    
    return 1; // Success (Disk is ready)
}

// 512 Bytes (1 Sector) Hard Disk se Padhna
void ata_read_sector(unsigned int lba, unsigned char* buffer) {
    outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F));
    outb(0x1F2, 1); // 1 sector
    outb(0x1F3, (unsigned char) lba);
    outb(0x1F4, (unsigned char)(lba >> 8));
    outb(0x1F5, (unsigned char)(lba >> 16));
    outb(0x1F7, 0x20); // COMMAND: READ SECTOR

    // NAYA: Agar disk fassi, toh OS aage badh jayega, hang nahi hoga!
    if (!ata_wait()) return; 

    for (int i = 0; i < 256; i++) {
        unsigned short word = inw(0x1F0);
        buffer[i * 2] = (unsigned char)(word & 0xFF);
        buffer[i * 2 + 1] = (unsigned char)(word >> 8);
    }
}

// 512 Bytes (1 Sector) Hard Disk par Likhna
void ata_write_sector(unsigned int lba, unsigned char* buffer) {
    outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F));
    outb(0x1F2, 1);
    outb(0x1F3, (unsigned char) lba);
    outb(0x1F4, (unsigned char)(lba >> 8));
    outb(0x1F5, (unsigned char)(lba >> 16));
    outb(0x1F7, 0x30); // COMMAND: WRITE SECTOR

    if (!ata_wait()) return; // Hang hone se bacho

    for (int i = 0; i < 256; i++) {
        unsigned short word = (buffer[i * 2 + 1] << 8) | buffer[i * 2];
        outw(0x1F0, word);
    }
    
    outb(0x1F7, 0xE7); // Cache Flush
}

#endif