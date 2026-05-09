#include "display.h"

volatile unsigned short* vga_buffer = (unsigned short*)0xB8000;
int cursor_x = 0;
int cursor_y = 0;

// Default color: White text on Black background
unsigned char current_color = (COLOR_BLACK << 4) | COLOR_WHITE; 

void set_color(unsigned char fg, unsigned char bg) {
    // Background ko shift karke foreground ke saath merge karna
    current_color = (bg << 4) | fg;
}

void clear_screen() {
    for (int i = 0; i < 80 * 25; i++) {
        // Space character print karo current background color ke saath
        vga_buffer[i] = (unsigned short)' ' | (current_color << 8);
    }
    cursor_x = 0;
    cursor_y = 0;
}

void print_char(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c == '\b') {
        if (cursor_x > 0) cursor_x--;
        else if (cursor_y > 0) { cursor_y--; cursor_x = 79; }
        
        int index = (cursor_y * 80) + cursor_x;
        vga_buffer[index] = (unsigned short)' ' | (current_color << 8);
    } else {
        int index = (cursor_y * 80) + cursor_x;
        // Text draw karte waqt current color use karo
        vga_buffer[index] = (unsigned short)c | (current_color << 8);
        cursor_x++;
        if (cursor_x >= 80) {
            cursor_x = 0;
            cursor_y++;
        }
    }
}

void print_string(const char* str) {
    int i = 0;
    while (str[i] != '\0') {
        print_char(str[i]);
        i++;
    }
}

// NAYA: Top Taskbar banane ka function
void draw_top_bar(const char* title) {
    int old_x = cursor_x;
    int old_y = cursor_y;

    // Taskbar ka color: White text on Blue background
    set_color(COLOR_WHITE, COLOR_BLUE);
    cursor_x = 0;
    cursor_y = 0;

    // Pura 1st row (80 columns) space se fill kar do background color ke liye
    for (int i = 0; i < 80; i++) {
        print_char(' ');
    }

    // Title ko row ke starting me likho
    cursor_x = 2;
    cursor_y = 0;
    print_string(title);

    // Color wapas default (Black/White) kar do OS area ke liye
    set_color(COLOR_WHITE, COLOR_BLACK);
    
    // Cursor ko line 1 (Taskbar ke niche) set kar do
    cursor_x = 0;
    cursor_y = 2; 
}