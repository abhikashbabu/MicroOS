#ifndef DISK_H
#define DISK_H

#include "../kernel/io.h"

static inline void outsw(unsigned short port, const void* addr, unsigned int word_count) {
    __asm__ volatile("rep outsw" : "+S"(addr), "+c"(word_count) : "d"(port) : "memory");
}
static inline void insw(unsigned short port, void* addr, unsigned int word_count) {
    __asm__ volatile("rep insw" : "+D"(addr), "+c"(word_count) : "d"(port) : "memory");
}

// ----------------------------------------------------
// NAYA (DAY 92.5): HARDWARE DEADLOCK PROTECTION!
// ----------------------------------------------------

// 1. Agar Drive apna pichla kaam kar rahi hai, toh wait karo
void ata_wait_busy() {
    while((inb(0x1F7) & 0x80) != 0); // Jab tak BSY (0x80) 1 hai, ruko
}

// 2. Data transfer ke liye drive ki permission ka wait karo
void ata_wait_ready() {
    while((inb(0x1F7) & 0x88) != 0x08); // Wait until BSY is 0 and DRQ is 1
}

// ----------------------------------------------------
// CRASH-FREE WRITE ENGINE
// ----------------------------------------------------
void write_sector_lba28(unsigned int lba, unsigned char* buffer) {
    ata_wait_busy(); // <--- CRITICAL FIX 1: Naya command bhejne se pehle pichla finish hone do!

    outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F)); 
    outb(0x1F2, 1);                           
    outb(0x1F3, (unsigned char)lba);          
    outb(0x1F4, (unsigned char)(lba >> 8));   
    outb(0x1F5, (unsigned char)(lba >> 16));  
    outb(0x1F7, 0x30);                        

    ata_wait_ready(); // Wait for data request from drive

    outsw(0x1F0, buffer, 256); // Turbo write

    ata_wait_busy(); // <--- CRITICAL FIX 2: Data bhejte hi drive flush karne mein time lagati hai, wahan wait karo
}

// ----------------------------------------------------
// CRASH-FREE READ ENGINE
// ----------------------------------------------------
void read_sector_lba28(unsigned int lba, unsigned char* buffer) {
    ata_wait_busy(); // Wait if busy with previous commands

    outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F)); 
    outb(0x1F2, 1);                           
    outb(0x1F3, (unsigned char)lba);          
    outb(0x1F4, (unsigned char)(lba >> 8));   
    outb(0x1F5, (unsigned char)(lba >> 16));  
    outb(0x1F7, 0x20);                        

    ata_wait_ready();

    insw(0x1F0, buffer, 256); // Turbo read
}

#endif