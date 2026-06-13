#ifndef RTL8139_H
#define RTL8139_H

#include "../kernel/io.h"
#include "pci.h"

// NAYA MAGIC: 16-bit hardware writer (Loop ko rokne ke liye)
static inline void rtl_outw(unsigned short port, unsigned short data) {
    __asm__ volatile("outw %0, %1" : : "a"(data), "Nd"(port));
}

// Safe Buffers
unsigned char rx_buffer[8192 + 16 + 1500]; 
unsigned char tx_buffer[1500]; 

void rtl8139_init() {
    outb(rtl_io_base + 0x52, 0x0);
    outb(rtl_io_base + 0x37, 0x10);
    while((inb(rtl_io_base + 0x37) & 0x10) != 0) { }
    outl(rtl_io_base + 0x30, (unsigned int)rx_buffer);
    outl(rtl_io_base + 0x44, 0x8F); 
    outb(rtl_io_base + 0x37, 0x0C); 
}

void rtl8139_send_packet(unsigned char* packet_data, int length) {
    for(int i = 0; i < length; i++) {
        tx_buffer[i] = packet_data[i];
    }
    outl(rtl_io_base + 0x20, (unsigned int)tx_buffer);
    outl(rtl_io_base + 0x10, length);
}

// ==============================================================
// PACKET RECEIVER ENGINE (FIXED THE INFINITE LOOP)
// ==============================================================
unsigned int rx_read_ptr = 0; 

int rtl8139_receive_packet(unsigned char* out_buffer, int* out_length) {
    // Agar bit 0 zero hai, matlab buffer khali nahi hai, PACKET AAYA HAI!
    if ((inb(rtl_io_base + 0x37) & 0x01) == 0) {
        
        unsigned int rx_offset = rx_read_ptr % 8192;
        unsigned short status = *(unsigned short*)(rx_buffer + rx_offset);
        unsigned short length = *(unsigned short*)(rx_buffer + rx_offset + 2);
        
        if (status & 0x0001) { 
            for(int i = 0; i < length - 4; i++) { 
                out_buffer[i] = rx_buffer[rx_offset + 4 + i];
            }
            *out_length = length - 4;
        }
        
        rx_read_ptr = (rx_read_ptr + length + 4 + 3) & ~3;
        
        // YAHAN THA BUG! outl ki jagah outw hona chahiye! (16-bit register)
        rtl_outw(rtl_io_base + 0x38, rx_read_ptr - 16); 
        
        // Packet padhne ke baad Receive Status clear karna zaroori hai (Interrupt reset)
        rtl_outw(rtl_io_base + 0x3E, 0x01); 

        return 1; 
    }
    return 0; 
}

#endif