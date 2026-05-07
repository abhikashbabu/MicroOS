#ifndef IO_H
#define IO_H

// Port se ek byte data read karne ka function
static inline unsigned char inb(unsigned short port) {
    unsigned char result;
    // Assembly command: 'in' se read karo
    __asm__ volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

#endif