#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "io.h"
#include "display.h"

// Basic US Keyboard map (QWERTY)
// Sirf lowercase letters aur numbers (simplicity ke liye)
const char keyboard_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' ', 0
};

// Keyboard read karne ka function
void keyboard_read_loop() {
    unsigned char scancode;
    
    print_string("MicroOS> "); // Terminal jaisa prompt

    while(1) {
        // Port 0x64 ka status check karo (agar bit 0 high hai, toh data available hai)
        if (inb(0x64) & 1) {
            // Port 0x60 se scancode read karo
            scancode = inb(0x60);

            // Agar key release ka scancode hai (top bit set hoti hai), toh ignore karo
            if (!(scancode & 0x80)) {
                // Scancode ko char mein convert karo array se
                char c = keyboard_map[scancode];
                
                // Agar valid character hai toh print karo
                if (c != 0) {
                    print_char(c);
                }
            }
        }
    }
}

#endif