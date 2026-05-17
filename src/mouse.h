#ifndef MOUSE_H
#define MOUSE_H

#include "io.h"

// Hardware se wait karna taaki port free ho jaye
void mouse_wait(unsigned char type) {
    int time_out = 100000;
    if(type == 0) {
        while(time_out--) { if((inb(0x64) & 1) == 1) return; }
    } else {
        while(time_out--) { if((inb(0x64) & 2) == 0) return; }
    }
}

// Mouse ko setup commands bhejna
void init_mouse() {
    unsigned char status;

    // 1. Enable auxiliary mouse device
    mouse_wait(1);
    outb(0x64, 0xA8);

    // 2. Enable interrupts
    mouse_wait(1);
    outb(0x64, 0x20);
    mouse_wait(0);
    status = (inb(0x60) | 2);
    mouse_wait(1);
    outb(0x64, 0x60);
    mouse_wait(1);
    outb(0x60, status);

    // 3. Tell the mouse to use default settings
    mouse_wait(1);
    outb(0x64, 0xD4);
    mouse_wait(1);
    outb(0x60, 0xF6);
    mouse_wait(0);
    inb(0x60);  // Acknowledge

    // 4. Enable the mouse stream
    mouse_wait(1);
    outb(0x64, 0xD4);
    mouse_wait(1);
    outb(0x60, 0xF4);
    mouse_wait(0);
    inb(0x60);  // Acknowledge
}

#endif