#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "vga.h"

// Screen paint karna aur Box draw karna
void clear_graphics(unsigned char color) {
    for(int i = 0; i < 320 * 200; i++) vga_mem[i] = color;
}
void draw_rect(int x, int y, int w, int h, unsigned char color) {
    for(int i = y; i < y + h; i++) {
        for(int j = x; j < x + w; j++) put_pixel(j, i, color);
    }
}

// Cursor Background Save/Restore logic
unsigned char get_pixel(int x, int y) {
    if(x >= 0 && x < 320 && y >= 0 && y < 200) return vga_mem[(y * 320) + x];
    return 0;
}
unsigned char mouse_buffer[36]; 
void save_mouse_bg(int x, int y) {
    int idx = 0;
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j <= i; j++) mouse_buffer[idx++] = get_pixel(x + j, y + i);
    }
}
void restore_mouse_bg(int x, int y) {
    int idx = 0;
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j <= i; j++) put_pixel(x + j, y + i, mouse_buffer[idx++]);
    }
}
void draw_mouse_pointer(int x, int y) {
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j <= i; j++) put_pixel(x + j, y + i, 15);
    }
}

// ----------------------------------------------------
// NAYA (DAY 57): FULL GUI TEXT ENGINE (A-Z & 0-9)
// ----------------------------------------------------
unsigned char font3x5[11][5] = {
    {7,5,5,5,7}, {2,2,2,2,2}, {7,1,7,4,7}, {7,1,7,1,7}, {5,5,7,1,1}, // 0-4
    {7,4,7,1,7}, {7,4,7,5,7}, {7,1,1,1,1}, {7,5,7,5,7}, {7,5,7,1,7}, // 5-9
    {0,2,0,2,0}  // 10 (:)
};

// A to Z (26 letters) compact binary font map
unsigned char font_alpha[26][5] = {
    {2,5,7,5,5}, {3,5,3,5,3}, {7,4,4,4,7}, {3,5,5,5,3}, // A,B,C,D
    {7,4,7,4,7}, {7,4,6,4,4}, {7,4,5,5,7}, {5,5,7,5,5}, // E,F,G,H
    {7,2,2,2,7}, {1,1,1,5,2}, {5,5,6,5,5}, {4,4,4,4,7}, // I,J,K,L
    {5,7,7,5,5}, {5,7,7,5,5}, {7,5,5,5,7}, {7,5,7,4,4}, // M,N,O,P
    {7,5,5,7,1}, {7,5,7,5,5}, {7,4,7,1,7}, {7,2,2,2,2}, // Q,R,S,T
    {5,5,5,5,7}, {5,5,5,2,2}, {5,5,7,7,5}, {5,5,2,5,5}, // U,V,W,X
    {5,5,2,2,2}, {7,1,2,4,7}                            // Y,Z
};

// Single Character draw karna
void draw_char(char c, int x, int y, unsigned char color) {
    if (c == ' ') return; // Space ko ignore karo
    
    int pattern;
    for(int row = 0; row < 5; row++) {
        if (c >= '0' && c <= '9') pattern = font3x5[c - '0'][row];
        else if (c >= 'A' && c <= 'Z') pattern = font_alpha[c - 'A'][row];
        else if (c >= 'a' && c <= 'z') pattern = font_alpha[c - 'a'][row]; // Lowercase ko uppercase ki tarah padho
        else if (c == ':') pattern = font3x5[10][row];
        else return;

        if(pattern & 4) put_pixel(x,   y + row, color);
        if(pattern & 2) put_pixel(x + 1, y + row, color);
        if(pattern & 1) put_pixel(x + 2, y + row, color);
    }
}

// Poori String draw karna
void draw_gui_string(char* str, int x, int y, unsigned char color) {
    int i = 0;
    while(str[i] != '\0') {
        draw_char(str[i], x, y, color);
        x += 4; // Agla letter 4 pixel aage shift hoga
        i++;
    }
}

// ----------------------------------------------------
// NAYA (DAY 58): DYNAMIC DESKTOP ENGINE WITH LABELS
// ----------------------------------------------------
void draw_desktop_dynamic(int win_x, int win_y, int win_open, int start_menu_open) {
    clear_graphics(1); // Blue Background
    
    // Desktop Icon for "Micro-Paint"
    draw_rect(10, 10, 32, 32, 14); 
    draw_rect(14, 14, 24, 24, 15); 
    draw_gui_string("APP", 15, 45, 15); // Icon Label
    
    // Taskbar & Start Button
    draw_rect(0, 180, 320, 20, 7); 
    draw_rect(2, 182, 30, 16, 2);  
    draw_gui_string("OS", 10, 187, 15); // Start button label
    
    if (win_open) {
        // App Window
        draw_rect(win_x, win_y, 200, 135, 15); 
        // Title Bar - DRAG AREA
        draw_rect(win_x, win_y, 200, 15, 9);
        
        // Window Title Text
        draw_gui_string("MICRO PAINT", win_x + 5, win_y + 5, 15);
        
        // Close Button
        draw_rect(win_x + 185, win_y + 2, 12, 11, 4); 
        draw_char('X', win_x + 189, win_y + 5, 15); // Close X mark
        
        // Paint Canvas Area 
        draw_rect(win_x + 2, win_y + 17, 196, 95, 7); 
        
        // Toolbar Boxes
        draw_rect(win_x + 5, win_y + 116, 15, 15, 0);  
        draw_rect(win_x + 25, win_y + 116, 15, 15, 4);  
        draw_rect(win_x + 45, win_y + 116, 15, 15, 2);  
        draw_rect(win_x + 65, win_y + 116, 15, 15, 1);  
        draw_rect(win_x + 85, win_y + 116, 15, 15, 14); 
        draw_rect(win_x + 105, win_y + 116, 15, 15, 7); 
    }

    // START MENU RENDERER
    if (start_menu_open) {
        draw_rect(2, 100, 120, 80, 7); 
        
        draw_gui_string("MENU", 10, 103, 0);
        
        // Item 1: Open Paint
        draw_rect(10, 115, 15, 15, 14);
        draw_gui_string("PAINT", 35, 120, 0); 
        
        // Item 2: Close All Windows
        draw_rect(10, 135, 15, 15, 1);
        draw_gui_string("CLOSE", 35, 140, 0); 
        
        // Item 3: Reboot OS
        draw_rect(10, 155, 15, 15, 4);
        draw_gui_string("REBOOT", 35, 160, 0); 
    }
}

// TASKBAR CLOCK RENDERER (Updated with string functions)
void draw_gui_time(int h, int m) {
    draw_rect(275, 185, 40, 10, 7); 
    draw_char((h / 10) + '0', 275, 187, 0); 
    draw_char((h % 10) + '0', 279, 187, 0); 
    draw_char(':', 284, 187, 0);
    draw_char((m / 10) + '0', 289, 187, 0); 
    draw_char((m % 10) + '0', 293, 187, 0); 
}

#endif