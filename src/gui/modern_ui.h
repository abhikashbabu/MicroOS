#ifndef MODERN_UI_H
#define MODERN_UI_H

#include "vesa.h"

// Font Data (Same arrays from old graphics.h)
unsigned char font3x5_hd[11][5] = {
    {7,5,5,5,7}, {2,2,2,2,2}, {7,1,7,4,7}, {7,1,7,1,7}, {5,5,7,1,1}, 
    {7,4,7,1,7}, {7,4,7,5,7}, {7,1,1,1,1}, {7,5,7,5,7}, {7,5,7,1,7}, {0,2,0,2,0}  
};
unsigned char font_alpha_hd[26][5] = {
    {2,5,7,5,5}, {3,5,3,5,3}, {7,4,4,4,7}, {3,5,5,5,3}, {7,4,7,4,7}, {7,4,6,4,4}, {7,4,5,5,7}, {5,5,7,5,5}, 
    {7,2,2,2,7}, {1,1,1,5,2}, {5,5,6,5,5}, {4,4,4,4,7}, {5,7,7,5,5}, {5,7,7,5,5}, {7,5,5,5,7}, {7,5,7,4,4}, 
    {7,5,5,7,1}, {7,5,7,5,5}, {7,4,7,1,7}, {7,2,2,2,2}, {5,5,5,5,7}, {5,5,5,2,2}, {5,5,7,7,5}, {5,5,2,5,5}, 
    {5,5,2,2,2}, {7,1,2,4,7}                            
};

// ----------------------------------------------------
// NAYA (DAY 104): SCALED FONT RENDERER (HD TEXT)
// scale = 3 matlab text 3x bada draw hoga
// ----------------------------------------------------
void draw_scaled_char(char c, int x, int y, unsigned int hex_color, int scale) {
    if (c == ' ') return; 
    int pattern;
    for(int row = 0; row < 5; row++) {
        if (c >= '0' && c <= '9') pattern = font3x5_hd[c - '0'][row];
        else if (c >= 'A' && c <= 'Z') pattern = font_alpha_hd[c - 'A'][row];
        else if (c >= 'a' && c <= 'z') pattern = font_alpha_hd[c - 'a'][row]; 
        else if (c == ':') pattern = font3x5_hd[10][row];
        else if (c == '.') pattern = (row==4)?2:0; 
        else return;

        // Draw scaled blocks instead of single pixels
        if(pattern & 4) draw_rounded_rect(x, y + (row * scale), scale, scale, 0, hex_color);
        if(pattern & 2) draw_rounded_rect(x + scale, y + (row * scale), scale, scale, 0, hex_color);
        if(pattern & 1) draw_rounded_rect(x + (scale * 2), y + (row * scale), scale, scale, 0, hex_color);
    }
}

void draw_hd_string(char* str, int start_x, int start_y, unsigned int hex_color, int scale) {
    int x = start_x; 
    for(int i = 0; str[i] != '\0'; i++) {
        draw_scaled_char(str[i], x, start_y, hex_color, scale);
        x += (4 * scale); // Space between chars
    }
}

// ----------------------------------------------------
// NAYA (DAY 104): THE NEXT-GEN TASKBAR (Like Windows 11 / Mac)
// ----------------------------------------------------
void draw_modern_taskbar() {
    // Main Taskbar Background (Centered at bottom)
    int tb_width = 800;
    int tb_height = 50;
    int tb_x = (1024 - tb_width) / 2; // Center horizontally
    int tb_y = 768 - tb_height - 10;  // 10px margin from bottom

    // Draw the rounded dock (Drop shadow effect by drawing a darker box slightly lower)
    draw_rounded_rect(tb_x + 2, tb_y + 4, tb_width, tb_height, 10, 0x00111111); // Shadow
    draw_rounded_rect(tb_x, tb_y, tb_width, tb_height, 10, COLOR_TASKBAR);      // Main Dock

    // Start Button (Micro OS Logo)
    draw_rounded_rect(tb_x + 20, tb_y + 10, 30, 30, 8, COLOR_ACCENT);
    draw_hd_string("M", tb_x + 28, tb_y + 15, COLOR_TEXT, 2);

    // App Icons (Placeholders for now)
    draw_rounded_rect(tb_x + 70, tb_y + 10, 30, 30, 8, 0x00FFB300); // Yellow Folder
    draw_rounded_rect(tb_x + 120, tb_y + 10, 30, 30, 8, 0x004CAF50); // Browser App
    draw_rounded_rect(tb_x + 170, tb_y + 10, 30, 30, 8, 0x009C27B0); // Terminal App

    // Time Widget on Right Side
    draw_hd_string("10:30 AM", tb_x + tb_width - 120, tb_y + 18, COLOR_TEXT, 2);
}

// Clear the HD screen
void render_desktop_bg() {
    // Fill background with Dark Mode Color
    for (int i = 0; i < (1024 * 768); i++) {
        high_res_buffer[i] = COLOR_DARK_BG;
    }
    
    // Draw the new taskbar
    draw_modern_taskbar();
    
    // Swap buffer to screen
    swap_buffers_32();
}

#endif