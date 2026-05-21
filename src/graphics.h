#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "vga.h"

void clear_graphics(unsigned char color) {
    for(int i = 0; i < 320 * 200; i++) vga_mem[i] = color;
}
void draw_rect(int x, int y, int w, int h, unsigned char color) {
    for(int i = y; i < y + h; i++) {
        for(int j = x; j < x + w; j++) put_pixel(j, i, color);
    }
}
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

unsigned char font3x5[11][5] = {
    {7,5,5,5,7}, {2,2,2,2,2}, {7,1,7,4,7}, {7,1,7,1,7}, {5,5,7,1,1}, 
    {7,4,7,1,7}, {7,4,7,5,7}, {7,1,1,1,1}, {7,5,7,5,7}, {7,5,7,1,7}, {0,2,0,2,0}  
};

unsigned char font_alpha[26][5] = {
    {2,5,7,5,5}, {3,5,3,5,3}, {7,4,4,4,7}, {3,5,5,5,3}, {7,4,7,4,7}, {7,4,6,4,4}, {7,4,5,5,7}, {5,5,7,5,5}, 
    {7,2,2,2,7}, {1,1,1,5,2}, {5,5,6,5,5}, {4,4,4,4,7}, {5,7,7,5,5}, {5,7,7,5,5}, {7,5,5,5,7}, {7,5,7,4,4}, 
    {7,5,5,7,1}, {7,5,7,5,5}, {7,4,7,1,7}, {7,2,2,2,2}, {5,5,5,5,7}, {5,5,5,2,2}, {5,5,7,7,5}, {5,5,2,5,5}, 
    {5,5,2,2,2}, {7,1,2,4,7}                            
};

void draw_char(char c, int x, int y, unsigned char color) {
    if (c == ' ') return; 
    int pattern;
    for(int row = 0; row < 5; row++) {
        if (c >= '0' && c <= '9') pattern = font3x5[c - '0'][row];
        else if (c >= 'A' && c <= 'Z') pattern = font_alpha[c - 'A'][row];
        else if (c >= 'a' && c <= 'z') pattern = font_alpha[c - 'a'][row]; 
        else if (c == ':') pattern = font3x5[10][row];
        else if (c == '_') pattern = (row == 4) ? 7 : 0; // Typing cursor
        else return;

        if(pattern & 4) put_pixel(x,   y + row, color);
        if(pattern & 2) put_pixel(x + 1, y + row, color);
        if(pattern & 1) put_pixel(x + 2, y + row, color);
    }
}

void draw_gui_string(char* str, int x, int y, unsigned char color) {
    int i = 0;
    while(str[i] != '\0') {
        draw_char(str[i], x, y, color);
        x += 4; 
        i++;
    }
}

// ----------------------------------------------------
// NAYA (DAY 60): MULTI-APP DESKTOP
// app_mode: 0 = None, 1 = Paint, 2 = Notes
// ----------------------------------------------------
void draw_desktop_dynamic(int win_x, int win_y, int app_mode, int start_menu_open, char* note_text) {
    clear_graphics(1); // Blue Background
    
    // Icon 1: Paint
    draw_rect(10, 10, 32, 32, 14); draw_rect(14, 14, 24, 24, 15); 
    draw_gui_string("PNT", 15, 45, 15); 
    
    // Icon 2: Notes
    draw_rect(60, 10, 32, 32, 15); draw_rect(64, 14, 24, 24, 11); // Cyan Icon
    draw_gui_string("NOT", 65, 45, 15); 
    
    // Taskbar 
    draw_rect(0, 180, 320, 20, 7); 
    draw_rect(2, 182, 30, 16, 2);  
    draw_gui_string("OS", 10, 187, 15); 
    
    // Application Window Renderer
    if (app_mode > 0) {
        draw_rect(win_x, win_y, 200, 135, 15); // Main Window
        draw_rect(win_x, win_y, 200, 15, 9);   // Title Bar
        draw_rect(win_x + 185, win_y + 2, 12, 11, 4); // Close Button
        draw_char('X', win_x + 189, win_y + 5, 15);
        
        if (app_mode == 1) {
            // PAINT APP UI
            draw_gui_string("MICRO PAINT", win_x + 5, win_y + 5, 15);
            draw_rect(win_x + 2, win_y + 17, 196, 95, 7); 
            draw_rect(win_x + 5, win_y + 116, 15, 15, 0);  
            draw_rect(win_x + 25, win_y + 116, 15, 15, 4);  
            draw_rect(win_x + 45, win_y + 116, 15, 15, 2);  
            draw_rect(win_x + 65, win_y + 116, 15, 15, 1);  
            draw_rect(win_x + 85, win_y + 116, 15, 15, 14); 
            draw_rect(win_x + 105, win_y + 116, 15, 15, 7); 
        } 
        else if (app_mode == 2) {
            // NAYA (DAY 60): NOTES APP UI
            draw_gui_string("MINI NOTES", win_x + 5, win_y + 5, 15);
            draw_rect(win_x + 2, win_y + 17, 196, 115, 15); // Clean White Canvas
            
            // Draw Typed Text
            int tx = win_x + 5;
            int ty = win_y + 22;
            for(int i = 0; note_text[i] != '\0'; i++) {
                draw_char(note_text[i], tx, ty, 0); // Black text
                tx += 4;
                if (tx > win_x + 190) { tx = win_x + 5; ty += 7; } // Auto Line Break!
            }
            draw_char('_', tx, ty, 0); // Typing Blinker
        }
    }

    // START MENU RENDERER
    if (start_menu_open) {
        draw_rect(2, 80, 120, 100, 7); 
        draw_gui_string("MENU", 10, 83, 0);
        
        draw_rect(10, 95, 15, 15, 14); draw_gui_string("PAINT", 35, 100, 0); 
        draw_rect(10, 115, 15, 15, 11); draw_gui_string("NOTES", 35, 120, 0); 
        draw_rect(10, 135, 15, 15, 1); draw_gui_string("CLOSE", 35, 140, 0); 
        draw_rect(10, 155, 15, 15, 4); draw_gui_string("REBOOT", 35, 160, 0); 
    }
}

void draw_gui_time(int h, int m) {
    draw_rect(275, 185, 40, 10, 7); 
    draw_char((h / 10) + '0', 275, 187, 0); 
    draw_char((h % 10) + '0', 279, 187, 0); 
    draw_char(':', 284, 187, 0);
    draw_char((m / 10) + '0', 289, 187, 0); 
    draw_char((m % 10) + '0', 293, 187, 0); 
}

#endif