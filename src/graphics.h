#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "vga.h"

// Poori screen ko paint karna
void clear_graphics(unsigned char color) {
    for(int i = 0; i < 320 * 200; i++) {
        vga_mem[i] = color;
    }
}

// Box draw karna
void draw_rect(int x, int y, int w, int h, unsigned char color) {
    for(int i = y; i < y + h; i++) {
        for(int j = x; j < x + w; j++) {
            put_pixel(j, i, color);
        }
    }
}

// NAYA (DAY 45): Asli Mouse Arrow draw karna!
void draw_mouse_pointer(int x, int y) {
    // 5x5 pixel ka ek simple right-angled triangle (Teer) draw kar rahe hain
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j <= i; j++) {
            put_pixel(x + j, y + i, 15); // 15 = White Color
        }
    }
}

// Updated Desktop: Isme ab Red Close Button bhi hai
void draw_desktop_test() {
    clear_graphics(1); // 1 = Blue Background
    
    // Taskbar (Gray)
    draw_rect(0, 180, 320, 20, 7); 
    // Start Button (Green)
    draw_rect(2, 182, 30, 16, 2); 
    
    // App Window (White)
    draw_rect(50, 40, 200, 100, 15); 
    // Window Title Bar (Dark Blue)
    draw_rect(50, 40, 200, 15, 9);
    
    // NAYA: Window Close Button (Red box at top right of the window)
    draw_rect(235, 42, 12, 11, 4); // 4 = Red
}

#endif