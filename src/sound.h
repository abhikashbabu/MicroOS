#ifndef SOUND_H
#define SOUND_H

#include "io.h"

// NAYA: ind_runner.h ke error ko fix karne ke liye ek shortcut (Macro)
#define stop_sound nosound

// 1. PIT (Timer) ko frequency set karne ko bolna
// 'static inline' lagaya taaki "Multiple Definition" ka error na aaye
static inline void play_sound(unsigned int nFrequence) {
    unsigned int Div = 1193180 / nFrequence; // Base hardware frequency divider
    outb(0x43, 0xb6);
    outb(0x42, (unsigned char)(Div));
    outb(0x42, (unsigned char)(Div >> 8));

    // Speaker ko ON karna (Port 0x61 ki bit 0 aur 1 ko set karke)
    unsigned char tmp = inb(0x61);
    if (tmp != (tmp | 3)) {
        outb(0x61, tmp | 3);
    }
}

// 2. Speaker ko OFF karna
static inline void nosound() {
    unsigned char tmp = inb(0x61) & 0xFC;
    outb(0x61, tmp);
}

// 3. Ek proper "Beep" generate karna (Frequency aur Duration ke sath)
static inline void os_beep(unsigned int freq, int duration) {
    play_sound(freq);
    // Custom delay loop taaki sound thodi der baje
    for(volatile int i = 0; i < duration * 1000000; i++) {} 
    nosound();
}

#endif