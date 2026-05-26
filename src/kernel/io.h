#ifndef IO_H
#define IO_H

// Port se read karna
static inline unsigned char inb(unsigned short port) {
    unsigned char result;
    __asm__ volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

// Port par write karna (NEW)
static inline void outb(unsigned short port, unsigned char data) {
    __asm__ volatile("outb %0, %1" : : "a"(data), "Nd"(port));
}

// NAYA: 32-bit I/O for PCI Hardware
    static inline void outl(unsigned short port, unsigned int data) {
        __asm__ __volatile__ ("outl %0, %1" : : "a"(data), "Nd"(port));
    }

    static inline unsigned int inl(unsigned short port) {
        unsigned int ret;
        __asm__ __volatile__ ("inl %1, %0" : "=a"(ret) : "Nd"(port));
        return ret;
    }
#endif