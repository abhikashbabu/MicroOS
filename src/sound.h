#ifndef SOUND_H
#define SOUND_H

#include "io.h"

// Sound start karna (PIT timer ka use karke)
static inline void play_sound(unsigned int frequency) {
    if (frequency == 0) return;
    
    // PIT (Timer) ko frequency set karne ka formula
    unsigned int divisor = 1193180 / frequency;

    // Command bhejo ki hum frequency set kar rahe hain
    outb(0x43, 0xB6);
    outb(0x42, (unsigned char)(divisor & 0xFF));
    outb(0x42, (unsigned char)((divisor >> 8) & 0xFF));

    // PC speaker port (0x61) ko ON karo
    unsigned char tmp = inb(0x61);
    if (tmp != (tmp | 3)) {
        outb(0x61, tmp | 3);
    }
}

// Sound band karna (Speaker ko OFF karna)
static inline void stop_sound() {
    unsigned char tmp = inb(0x61) & 0xFC;
    outb(0x61, tmp);
}

#endif