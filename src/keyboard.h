#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "io.h"
#include "display.h"
#include "shell.h"

// Yeh hai wo actual array jo missing thi!
const char keyboard_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' ', 0
};

char command_buffer[256];
int buffer_index = 0;

void keyboard_read_loop() {
    unsigned char scancode;
    
    print_string("MicroOS> ");

    while(1) {
        if (inb(0x64) & 1) {
            scancode = inb(0x60);

            if (!(scancode & 0x80)) {
                char c = keyboard_map[scancode];
                
                if (c == '\n') {
                    // Enter dabaya -> Command execute karo
                    print_char('\n');
                    command_buffer[buffer_index] = '\0'; // String ko close karo
                    execute_command(command_buffer);     // Shell ko command do
                    
                    // Buffer reset karke naya prompt dikhao
                    buffer_index = 0;
                    print_string("MicroOS> ");
                } 
                else if (c == '\b') {
                    // Backspace dabaya -> Buffer se last char hatao aur screen se clear karo
                    if (buffer_index > 0) {
                        buffer_index--;
                        print_char('\b');
                    }
                } 
                else if (c != 0) {
                    // Normal character -> Buffer mein daalo aur print karo
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