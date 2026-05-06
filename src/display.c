#include "display.h"

// VGA memory address
volatile unsigned short* vga_buffer = (unsigned short*)0xB8000;

// Cursor ki position track karne ke liye
int cursor_x = 0;
int cursor_y = 0;

void clear_screen() {
    for (int i = 0; i < 80 * 25; i++) {
        vga_buffer[i] = (unsigned short)' ' | (0x0F << 8);
    }
    cursor_x = 0;
    cursor_y = 0; // Cursor wapas top-left par
}

void print_char(char c) {
    // Agar 'Enter' (\n) aaye toh next line par jao
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        // Character ko memory mein daalo
        int index = (cursor_y * 80) + cursor_x;
        vga_buffer[index] = (unsigned short)c | (0x0F << 8);
        cursor_x++;
        
        // Agar line khatam ho jaye, toh next line par jao
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