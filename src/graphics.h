#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "vga.h"

void clear_graphics(unsigned char color) {
    for(int i = 0; i < 320 * 200; i++) vga_mem[i] = color;
}

void draw_rect(int x, int y, int w, int h, unsigned char color) {
    for(int i = y; i < y + h; i++) {
        for(int j = x; j < x + w; j++) {
            put_pixel(j, i, color);
        }
    }
}

// NAYA (DAY 47): Screen se pixel color read karna
unsigned char get_pixel(int x, int y) {
    if(x >= 0 && x < 320 && y >= 0 && y < 200) {
        return vga_mem[(y * 320) + x];
    }
    return 0;
}

// NAYA: Mouse ke peeche ka background save/restore karne ka system
unsigned char mouse_buffer[36]; // 6x6 max cursor size buffer

void save_mouse_bg(int x, int y) {
    int idx = 0;
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j <= i; j++) {
            mouse_buffer[idx++] = get_pixel(x + j, y + i);
        }
    }
}

void restore_mouse_bg(int x, int y) {
    int idx = 0;
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j <= i; j++) {
            put_pixel(x + j, y + i, mouse_buffer[idx++]);
        }
    }
}

void draw_mouse_pointer(int x, int y) {
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j <= i; j++) {
            put_pixel(x + j, y + i, 15); // 15 = White
        }
    }
}

// Micro-Paint Desktop UI (Canvas ke sath)
void draw_desktop_test() {
    clear_graphics(1); // Blue Background
    
    // Taskbar & Start Button
    draw_rect(0, 180, 320, 20, 7); 
    draw_rect(2, 182, 30, 16, 2);  
    
    // Micro-Paint App Window (White)
    draw_rect(50, 40, 200, 120, 15); 
    // Title Bar (Dark Blue) & Close Button (Red)
    draw_rect(50, 40, 200, 15, 9);
    draw_rect(235, 42, 12, 11, 4); 
    
    // NAYA (DAY 48): Paint Canvas Area (Light Gray Area)
    draw_rect(52, 57, 196, 100, 7); 
}

#endif