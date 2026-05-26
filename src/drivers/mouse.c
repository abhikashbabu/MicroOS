#include "../drivers/mouse.h"
#include "../kernel/io.h"

// Variables yahan actually declare honge
int mouse_x = 40;
int mouse_y = 12;

// Mouse ka wait function
void mouse_wait(unsigned char type) {
    int timeout = 100000;
    if (type == 0) {
        while (timeout--) { if ((inb(0x64) & 1) == 1) return; } 
    } else {
        while (timeout--) { if ((inb(0x64) & 2) == 0) return; } 
    }
}

// Mouse hardware ko command bhejna
void mouse_write(unsigned char command) {
    mouse_wait(1);
    outb(0x64, 0xD4); 
    mouse_wait(1);
    outb(0x60, command); 
}

// Mouse hardware se data padhna
unsigned char mouse_read() {
    mouse_wait(0);
    return inb(0x60);
}

// OS boot par mouse ko ON karna
void init_mouse() {
    unsigned char status;

    mouse_wait(1);
    outb(0x64, 0xA8); 
    
    mouse_wait(1);
    outb(0x64, 0x20);
    mouse_wait(0);
    status = (inb(0x60) | 2);
    mouse_wait(1);
    outb(0x64, 0x60);
    mouse_wait(1);
    outb(0x60, status);
    
    mouse_write(0xF6);
    mouse_read();  
    
    mouse_write(0xF4);
    mouse_read();  
}