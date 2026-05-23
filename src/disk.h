#ifndef DISK_H
#define DISK_H

#include "io.h"

// ----------------------------------------------------
// NAYA (DAY 66): 16-BIT PORT I/O FOR HARD DRIVE
// Hard drive data 2-bytes (16 bits) ek sath bhejti hai
// ----------------------------------------------------
static inline void outw(unsigned short port, unsigned short data) {
    __asm__ volatile ("outw %0, %1" : : "a"(data), "Nd"(port));
}
static inline unsigned short inw(unsigned short port) {
    unsigned short result;
    __asm__ volatile ("inw %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

// Drive ready hone ka wait karna (BSY bit clear ho, DRQ bit set ho)
void ata_wait_ready() {
    while((inb(0x1F7) & 0x88) != 0x08);
}

// ----------------------------------------------------
// PHYSICAL WRITE ENGINE (Data -> Hard Drive)
// ----------------------------------------------------
void write_sector_lba28(unsigned int lba, unsigned char* buffer) {
    outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F)); // Select Master Drive & LBA top bits
    outb(0x1F2, 1);                           // Sector count = 1 (512 bytes)
    outb(0x1F3, (unsigned char)lba);          // LBA Low
    outb(0x1F4, (unsigned char)(lba >> 8));   // LBA Mid
    outb(0x1F5, (unsigned char)(lba >> 16));  // LBA High
    outb(0x1F7, 0x30);                        // Command: Write (0x30)

    ata_wait_ready();

    // 256 words = 512 bytes physical disk par bhejo
    unsigned short* ptr = (unsigned short*)buffer;
    for(int i = 0; i < 256; i++) {
        outw(0x1F0, ptr[i]);
    }
    outb(0x1F7, 0xE7); // Flush Cache (Force save)
}

// ----------------------------------------------------
// PHYSICAL READ ENGINE (Hard Drive -> RAM)
// ----------------------------------------------------
void read_sector_lba28(unsigned int lba, unsigned char* buffer) {
    outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F)); 
    outb(0x1F2, 1);                           
    outb(0x1F3, (unsigned char)lba);          
    outb(0x1F4, (unsigned char)(lba >> 8));   
    outb(0x1F5, (unsigned char)(lba >> 16));  
    outb(0x1F7, 0x20);                        // Command: Read (0x20)

    ata_wait_ready();

    // 512 bytes physical disk se padho
    unsigned short* ptr = (unsigned short*)buffer;
    for(int i = 0; i < 256; i++) {
        ptr[i] = inw(0x1F0);
    }
}

#endif