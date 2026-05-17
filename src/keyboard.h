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
    unsigned char status;
    
    print_string("MicroOS> ");

    while(1) {
        status = inb(0x64);
        
        // NAYA LOGIC: Bit 0 (Data ready hai) AND Bit 5 '0' hona chahiye (Mouse nahi hai)
        if ((status & 1) && !(status & 0x20)) { 
            scancode = inb(0x60);

            if (scancode == 0x2A || scancode == 0x36) {
                shift_pressed = 1;
                continue; 
            }
            if (scancode == 0xAA || scancode == 0xB6) {
                shift_pressed = 0;
                continue;
            }

            if (!(scancode & 0x80)) { 
                char c;
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
        // Agar data Mouse ka tha (Bit 5 is 1), toh bas read karke buffer khali kar do taaki hang na ho
        else if (status & 0x20) {
            inb(0x60); // Read and throw away mouse data for now
        }
    }
}

#endif