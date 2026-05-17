#ifndef EDITOR_H
#define EDITOR_H

#include "display.h"
#include "fs.h"
#include "io.h"

// FIX 1: Type match kar diya (const char)
extern const char keyboard_map[128];
extern const char keyboard_map_shifted[128];

// FIX 2: Cursor variables ko top par declare kiya
extern int cursor_x;
extern int cursor_y;
extern unsigned char current_color; 
void update_cursor(int x, int y);

// FIX 3: 'const' word hata diya
void run_editor(char* filename) {
    clear_screen();
    
    // Editor ka UI Draw karna
    draw_window(0, 1, 79, 22, filename, COLOR_BLUE);
    set_color(COLOR_WHITE, COLOR_BLUE);
    
    cursor_x = 2; 
    cursor_y = 3; 
    update_cursor(cursor_x, cursor_y);

    char buffer[1024] = {0};
    int idx = 0;
    int shift = 0;

    // Agar file pehle se hai, toh usko load karo
    int f = find_file(filename);
    if (f != -1) {
        while(file_system[f].content[idx] != '\0' && idx < 1023) {
            buffer[idx] = file_system[f].content[idx];
            print_char(buffer[idx]);
            idx++;
        }
    }

    // Top instruction bar
    int old_x = cursor_x, old_y = cursor_y;
    set_color(COLOR_BLACK, COLOR_CYAN);
    cursor_x = 0; cursor_y = 0; update_cursor(cursor_x, cursor_y);
    print_string(" Micro-Edit v1.0 | Press [ESC] to Save and Exit ");
    set_color(COLOR_WHITE, COLOR_BLUE);
    cursor_x = old_x; cursor_y = old_y; update_cursor(cursor_x, cursor_y);

    // Editor ka apna Keyboard Loop
    while(1) {
        unsigned char status = inb(0x64);
        if ((status & 1) && !(status & 0x20)) { // Data ready AND Not Mouse
            unsigned char scancode = inb(0x60);
            
            if (scancode == 0x2A || scancode == 0x36) { shift = 1; continue; }
            if (scancode == 0xAA || scancode == 0xB6) { shift = 0; continue; }
            
            // 0x01 is the scancode for 'ESC' Key
            if (scancode == 0x01) { 
                if(f != -1) {
                    for(int k=0; k<=idx; k++) file_system[f].content[k] = buffer[k];
                    file_system[f].size = idx;
                } else {
                    buffer[idx] = '\0';
                    create_file(filename, buffer);
                }
                break; // Exit editor
            }
            
            if (!(scancode & 0x80)) { // Key press down
                char c = shift ? keyboard_map_shifted[scancode] : keyboard_map[scancode];
                
                if (c == '\b' && idx > 0) {
                    idx--; buffer[idx] = 0; print_char('\b');
                } else if (c == '\n') {
                    buffer[idx++] = '\n'; print_char('\n');
                    cursor_x = 2; update_cursor(cursor_x, cursor_y); 
                } else if (c != 0 && idx < 1023) {
                    buffer[idx++] = c; print_char(c);
                }
            }
        } else if (status & 0x20) {
            inb(0x60); // Mouse data ignore karo
        }
    }

    set_color(COLOR_WHITE, COLOR_BLACK);
    clear_screen();
    draw_top_bar(" Micro OS v0.1 | .ind Application Runtime");
    print_string("File saved successfully!\nMicroOS> ");
}

#endif