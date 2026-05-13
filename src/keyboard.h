#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "io.h"
#include "display.h"
#include "shell.h"

// Normal map (Bina shift ke)
const char keyboard_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' ', 0
};

// NAYA: Shift map (Jab shift daba ho tab konsa char aayega)
const char keyboard_map_shifted[128] = {
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', // Yahan ':' hai!
    0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
    '*', 0, ' ', 0
};

char command_buffer[256];
int buffer_index = 0;
int shift_pressed = 0; // NAYA: OS ko yaad rahega ki Shift daba hai ya nahi

void keyboard_read_loop() {
    unsigned char scancode;
    
    print_string("MicroOS> ");

    while(1) {
        if (inb(0x64) & 1) {
            scancode = inb(0x60);

            // Left Shift (0x2A) ya Right Shift (0x36) dabaya gaya
            if (scancode == 0x2A || scancode == 0x36) {
                shift_pressed = 1;
                continue; // Loop aage badhao, char print mat karo
            }
            // Left Shift (0xAA) ya Right Shift (0xB6) chhod diya gaya
            if (scancode == 0xAA || scancode == 0xB6) {
                shift_pressed = 0;
                continue;
            }

            if (!(scancode & 0x80)) { // Key press
                char c;
                // Agar shift pressed hai toh shifted array se lo, warna normal array se
                if (shift_pressed == 1) {
                    c = keyboard_map_shifted[scancode];
                } else {
                    c = keyboard_map[scancode];
                }
                
                if (c == '\n') {
                    print_char('\n');
                    command_buffer[buffer_index] = '\0';
                    execute_command(command_buffer);
                    
                    buffer_index = 0;
                    print_string("MicroOS> ");
                } 
                else if (c == '\b') {
                    if (buffer_index > 0) {
                        buffer_index--;
                        print_char('\b');
                    }
                } 
                else if (c != 0) {
                    if (buffer_index < 255) {
                        command_buffer[buffer_index] = c;
                        buffer_index++;
                        print_char(c);
                    }
                }
            }
        }
    }
}

#endif