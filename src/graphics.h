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
// NAYA (DAY 51): Updated Desktop with Color Palette Toolbar
void draw_desktop_dynamic(int win_x, int win_y, int win_open) {
    clear_graphics(1); // Blue Background
    
    // Desktop Icon for "Micro-Paint"
    draw_rect(10, 10, 32, 32, 14); // Yellow Icon Base
    draw_rect(14, 14, 24, 24, 15); // White inner paper
    
    // Taskbar & Start Button
    draw_rect(0, 180, 320, 20, 7); 
    draw_rect(2, 182, 30, 16, 2);  
    
    // Agar Window open hai, tabhi usko draw karo
    if (win_open) {
        // App Window (White) - HEIGHT BADA DI HAI (135 tak)
        draw_rect(win_x, win_y, 200, 135, 15); 
        // Title Bar (Dark Blue) - DRAG AREA
        draw_rect(win_x, win_y, 200, 15, 9);
        // Close Button (Red)
        draw_rect(win_x + 185, win_y + 2, 12, 11, 4); 
        
        // Paint Canvas Area (Light Gray Area) - Thoda chota kiya hai toolbar ke liye
        draw_rect(win_x + 2, win_y + 17, 196, 95, 7); 

        // ----------------------------------------------------
        // NAYA (DAY 51): COLOR PALETTE TOOLBAR
        // ----------------------------------------------------
        draw_rect(win_x + 5, win_y + 116, 15, 15, 0);   // Black Brush
        draw_rect(win_x + 25, win_y + 116, 15, 15, 4);  // Red Brush
        draw_rect(win_x + 45, win_y + 116, 15, 15, 2);  // Green Brush
        draw_rect(win_x + 65, win_y + 116, 15, 15, 1);  // Blue Brush
        draw_rect(win_x + 85, win_y + 116, 15, 15, 14); // Yellow Brush
        draw_rect(win_x + 105, win_y + 116, 15, 15, 7); // ERASER (Matches canvas gray color)
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

// ----------------------------------------------------
// NAYA (DAY 53): BITMAP FONT ENGINE (3x5 Pixels)
// ----------------------------------------------------

// 0 se 9 tak numbers aur 10th index par ':' (Colon) ka map
unsigned char font3x5[11][5] = {
    {7,5,5,5,7}, // 0 (111, 101, 101, 101, 111)
    {2,2,2,2,2}, // 1 (010, 010, 010, 010, 010)
    {7,1,7,4,7}, // 2
    {7,1,7,1,7}, // 3
    {5,5,7,1,1}, // 4
    {7,4,7,1,7}, // 5
    {7,4,7,5,7}, // 6
    {7,1,1,1,1}, // 7
    {7,5,7,5,7}, // 8
    {7,5,7,1,7}, // 9
    {0,2,0,2,0}  // 10 (:)
};

// Ek digit ko screen par pixels se paint karne ka function
void draw_digit(int digit, int x, int y, unsigned char color) {
    if (digit < 0 || digit > 10) return;
    for(int row = 0; row < 5; row++) {
        int pattern = font3x5[digit][row];
        // Binary bits check karke pixel draw kar rahe hain
        if(pattern & 4) put_pixel(x,   y + row, color);
        if(pattern & 2) put_pixel(x + 1, y + row, color);
        if(pattern & 1) put_pixel(x + 2, y + row, color);
    }
}

// ----------------------------------------------------
// NAYA (DAY 54): TASKBAR CLOCK RENDERER
// ----------------------------------------------------
void draw_gui_time(int h, int m) {
    // 1. Purana time mitane ke liye taskbar ke kone mein ek Grey box banao
    draw_rect(275, 185, 40, 10, 7); // 7 = Taskbar Gray

    // 2. Hours draw karo (Black color - 0)
    draw_digit(h / 10, 275, 187, 0); // Tens digit
    draw_digit(h % 10, 279, 187, 0); // Ones digit

    // 3. Colon (:) draw karo
    draw_digit(10, 284, 187, 0);

    // 4. Minutes draw karo
    draw_digit(m / 10, 289, 187, 0); 
    draw_digit(m % 10, 293, 187, 0); 
}

#endif