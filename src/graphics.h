#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "vga.h"

// Poori screen ko ek color se paint karna
void clear_graphics(unsigned char color) {
    for(int i = 0; i < 320 * 200; i++) {
        vga_mem[i] = color;
    }
}

// X, Y coordinates par ek W (width) aur H (height) ka box draw karna
void draw_rect(int x, int y, int w, int h, unsigned char color) {
    for(int i = y; i < y + h; i++) {
        for(int j = x; j < x + w; j++) {
            put_pixel(j, i, color);
        }
    }
}

// OS ka Graphical Boot Logo / Desktop Background test
void draw_desktop_test() {
    clear_graphics(1); // 1 = Blue Background
    
    // Draw a fake Taskbar (Gray)
    draw_rect(0, 180, 320, 20, 7); // 7 = Light Gray
    
    // Draw a fake Start Button (Green)
    draw_rect(2, 182, 30, 16, 2); // 2 = Green
    
    // Draw an App Window (White)
    draw_rect(50, 40, 200, 100, 15); // 15 = White
    // Window Title Bar (Dark Blue)
    draw_rect(50, 40, 200, 15, 1);
}

#endif