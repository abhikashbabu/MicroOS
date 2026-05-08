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
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c == '\b') { // BACKSPACE LOGIC
        if (cursor_x > 0) {
            cursor_x--;
        } else if (cursor_y > 0) {
            cursor_y--;
            cursor_x = 79;
        }
        // Character ko screen se hatane ke liye space print kar do
        int index = (cursor_y * 80) + cursor_x;
        vga_buffer[index] = (unsigned short)' ' | (0x0F << 8);
    } else {
        int index = (cursor_y * 80) + cursor_x;
        vga_buffer[index] = (unsigned short)c | (0x0F << 8);
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