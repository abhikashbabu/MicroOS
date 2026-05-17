#ifndef ATA_H
#define ATA_H

#include "io.h"

// 16-bit (word) in/out functions kyunki Hard Disk 2 bytes ek sath bhejti hai
static inline unsigned short inw(unsigned short port) {
    unsigned short rv;
    __asm__ __volatile__ ("inw %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}

static inline void outw(unsigned short port, unsigned short data) {
    __asm__ __volatile__ ("outw %1, %0" : : "dN" (port), "a" (data));
}

// Disk ready hone ka wait karna
void ata_wait() {
    while((inb(0x1F7) & 0x80) == 0x80); // Wait for BSY to clear
    while((inb(0x1F7) & 0x08) == 0);    // Wait for DRQ to set
}

// 512 Bytes (1 Sector) Hard Disk se Padhna
void ata_read_sector(unsigned int lba, unsigned char* buffer) {
    outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F));
    outb(0x1F2, 1); // 1 sector
    outb(0x1F3, (unsigned char) lba);
    outb(0x1F4, (unsigned char)(lba >> 8));
    outb(0x1F5, (unsigned char)(lba >> 16));
    outb(0x1F7, 0x20); // COMMAND: READ SECTOR

    ata_wait();

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

    ata_wait();

    for (int i = 0; i < 256; i++) {
        unsigned short word = (buffer[i * 2 + 1] << 8) | buffer[i * 2];
        outw(0x1F0, word);
    }
}

#endif