#ifndef MODERN_UI_H
#define MODERN_UI_H

#include "vesa.h"

   const unsigned char modern_font[91][8] = {
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, {0x18,0x3C,0x3C,0x18,0x18,0x00,0x18,0x00}, {0x6C,0x6C,0x6C,0x00,0x00,0x00,0x00,0x00}, {0x6C,0x6C,0xFE,0x6C,0xFE,0x6C,0x6C,0x00}, {0x18,0x7E,0xC0,0x7C,0x06,0xFC,0x18,0x00}, {0x00,0xC6,0xCC,0x18,0x30,0x66,0xC6,0x00}, {0x38,0x6C,0x38,0x76,0xDC,0xCC,0x76,0x00}, {0x30,0x30,0x60,0x00,0x00,0x00,0x00,0x00}, {0x18,0x30,0x60,0x60,0x60,0x30,0x18,0x00}, {0x60,0x30,0x18,0x18,0x18,0x30,0x60,0x00}, {0x00,0x66,0x3C,0xFF,0x3C,0x66,0x00,0x00}, {0x00,0x18,0x18,0x7E,0x18,0x18,0x00,0x00}, {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x30}, {0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00}, {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00}, {0x06,0x0C,0x18,0x30,0x60,0xC0,0x80,0x00}, {0x7C,0xC6,0xCE,0xDE,0xF6,0xE6,0x7C,0x00}, {0x30,0x70,0x30,0x30,0x30,0x30,0xFC,0x00}, {0x78,0xCC,0x0C,0x38,0x60,0xCC,0xFC,0x00}, {0x78,0xCC,0x0C,0x38,0x0C,0xCC,0x78,0x00}, {0x1C,0x3C,0x6C,0xCC,0xFE,0x0C,0x1E,0x00}, {0xFC,0xC0,0xF8,0x0C,0x0C,0xCC,0x78,0x00}, {0x38,0x60,0xC0,0xF8,0xCC,0xCC,0x78,0x00}, {0xFC,0xCC,0x0C,0x18,0x30,0x30,0x30,0x00}, {0x78,0xCC,0xCC,0x78,0xCC,0xCC,0x78,0x00}, {0x78,0xCC,0xCC,0x7C,0x0C,0x18,0x70,0x00}, {0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x00}, {0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x30}, {0x18,0x30,0x60,0xC0,0x60,0x30,0x18,0x00}, {0x00,0x00,0x7E,0x00,0x7E,0x00,0x00,0x00}, {0x60,0x30,0x18,0x0C,0x18,0x30,0x60,0x00}, {0x3C,0x66,0x0C,0x18,0x18,0x00,0x18,0x00}, {0x7C,0xC6,0xDE,0xDE,0xDC,0xC0,0x7C,0x00}, {0x38,0x6C,0xC6,0xFE,0xC6,0xC6,0xC6,0x00}, {0xFC,0x66,0x66,0x7C,0x66,0x66,0xFC,0x00}, {0x3C,0x66,0xC0,0xC0,0xC0,0x66,0x3C,0x00}, {0xF8,0x6C,0x66,0x66,0x66,0x6C,0xF8,0x00}, {0xFE,0x62,0x68,0x78,0x68,0x62,0xFE,0x00}, {0xFE,0x62,0x68,0x78,0x68,0x60,0xF0,0x00}, {0x3C,0x66,0xC0,0xCE,0xC6,0x66,0x3E,0x00}, {0xC6,0xC6,0xC6,0xFE,0xC6,0xC6,0xC6,0x00}, {0x3C,0x18,0x18,0x18,0x18,0x18,0x3C,0x00}, {0x1E,0x0C,0x0C,0x0C,0xCC,0xCC,0x78,0x00}, {0xE6,0x66,0x6C,0x78,0x6C,0x66,0xE6,0x00}, {0xF0,0x60,0x60,0x60,0x62,0x66,0xFE,0x00}, {0xC6,0xEE,0xFE,0xFE,0xD6,0xC6,0xC6,0x00}, {0xC6,0xE6,0xF6,0xDE,0xCE,0xC6,0xC6,0x00}, {0x38,0x6C,0xC6,0xC6,0xC6,0x6C,0x38,0x00}, {0xFC,0x66,0x66,0x7C,0x60,0x60,0xF0,0x00}, {0x7C,0xC6,0xC6,0xC6,0xD6,0x7C,0x0E,0x00}, {0xFC,0x66,0x66,0x7C,0x6C,0x66,0xE6,0x00}, {0x7C,0xC6,0xE0,0x78,0x0E,0xC6,0x3E,0x00}, {0xFC,0xB4,0x30,0x30,0x30,0x30,0x78,0x00}, {0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00}, {0xC6,0xC6,0xC6,0xC6,0xC6,0x6C,0x38,0x00}, {0xC6,0xC6,0xC6,0xD6,0xFE,0xEE,0xC6,0x00}, {0xC6,0xC6,0x6C,0x38,0x6C,0xC6,0xC6,0x00}, {0x66,0x66,0x66,0x3C,0x18,0x18,0x3C,0x00}, {0xFE,0x86,0x0C,0x18,0x30,0x61,0xFE,0x00}, {0x3C,0x30,0x30,0x30,0x30,0x30,0x3C,0x00}, {0x00,0x80,0xC0,0x60,0x30,0x18,0x0C,0x06}, {0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C,0x00}, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, {0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00}, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, {0x00,0x00,0x78,0x0C,0x7C,0xCC,0x76,0x00}, {0xE0,0x60,0x60,0x7C,0x66,0x66,0xDC,0x00}, {0x00,0x00,0x78,0xCC,0xC0,0xCC,0x78,0x00}, {0x1C,0x0C,0x0C,0x7C,0xCC,0xCC,0x76,0x00}, {0x00,0x00,0x78,0xCC,0xFC,0xC0,0x78,0x00}, {0x38,0x6C,0x60,0xF0,0x60,0x60,0xF0,0x00}, {0x00,0x00,0x76,0xCC,0xCC,0x7C,0x0C,0xF8}, {0xE0,0x60,0x6C,0x76,0x66,0x66,0xE6,0x00}, {0x18,0x00,0x38,0x18,0x18,0x18,0x3C,0x00}, {0x06,0x00,0x06,0x06,0x06,0x06,0x06,0x3C}, {0xE0,0x60,0x66,0x6C,0x78,0x6C,0xE6,0x00}, {0x38,0x18,0x18,0x18,0x18,0x18,0x3C,0x00}, {0x00,0x00,0xEC,0xFE,0xD6,0xD6,0xD6,0x00}, {0x00,0x00,0xDC,0x66,0x66,0x66,0x66,0x00}, {0x00,0x00,0x78,0xCC,0xCC,0xCC,0x78,0x00}, {0x00,0x00,0xDC,0x66,0x66,0x7C,0x60,0xF0}, {0x00,0x00,0x76,0xCC,0xCC,0x7C,0x0C,0x1E}, {0x00,0x00,0xDC,0x76,0x60,0x60,0xF0,0x00}, {0x00,0x00,0x7C,0xC0,0x78,0x0C,0xF8,0x00}, {0x10,0x30,0x7C,0x30,0x30,0x34,0x18,0x00}, {0x00,0x00,0xCC,0xCC,0xCC,0xCC,0x76,0x00}, {0x00,0x00,0xCC,0xCC,0xCC,0x78,0x30,0x00}, {0x00,0x00,0xC6,0xD6,0xFE,0xFE,0x6C,0x00}, {0x00,0x00,0xC6,0x6C,0x38,0x6C,0xC6,0x00}, {0x00,0x00,0xCC,0xCC,0xCC,0x7C,0x0C,0xF8}, {0x00,0x00,0xFC,0x98,0x30,0x64,0xFC,0x00}  
    };
 extern int battery_percentage; // Linking from acpi.h


char ind_app_title[50] = "JS Runtime App";
char ind_app_msg[100] = "Hello World";
char ind_app_btn[30] = ""; 
char ind_app_input[30] = ""; 
unsigned int ind_app_bg = 0x002D2D30;
// DAY 162: Z-INDEX WINDOW MANAGER GLOBALS
extern int z_bg_app;
extern int z_bg_x;
extern int z_bg_y;

void draw_scaled_char(char c, int x, int y, unsigned int hex_color, int scale) {
    if (c < 32 || c > 122) return; 
    int font_idx = c - 32;
    for (int row = 0; row < 8; row++) {
        unsigned char row_data = modern_font[font_idx][row];
        for (int col = 0; col < 8; col++) {
            if ((row_data >> (7 - col)) & 1) draw_rounded_rect(x + (col * scale), y + (row * scale), scale, scale, 0, hex_color);
        }
    }
}

void draw_hd_string(char* str, int start_x, int start_y, unsigned int hex_color, int scale) {
    int x = start_x; 
    for(int i = 0; str[i] != '\0'; i++) { draw_scaled_char(str[i], x, start_y, hex_color, scale); x += (8 * scale); }
}

void draw_hd_mouse_pointer(int x, int y) {
    if (x < 0 || x > 1000 || y < 0 || y > 750) return;
    for(int i = 0; i < 15; i++) { 
        for(int j = 0; j <= i/1.5; j++) { 
            if (j == 0 || j == (int)(i/1.5) || i == 14) put_pixel_32(x + j, y + i, 0x000000); 
            else put_pixel_32(x + j, y + i, 0xFFFFFF); 
        } 
    }
}

void draw_app_icon(int x, int y, int type) {
    draw_rounded_rect(x+2, y+2, 40, 40, 8, 0x00111111);
    if (type == 0) { draw_rounded_rect(x, y+5, 40, 30, 4, 0x00E65100); draw_rounded_rect(x, y+10, 40, 25, 4, 0x00FFB300); draw_rounded_rect(x+5, y+5, 15, 10, 2, 0x00FFB300); } 
    else if (type == 1) { draw_rounded_rect(x+5, y, 30, 40, 3, 0x00FFFFFF); draw_rounded_rect(x+5, y, 30, 10, 3, 0x004CAF50); draw_rounded_rect(x+10, y+15, 20, 2, 0, 0x00E0E0E0); draw_rounded_rect(x+10, y+23, 20, 2, 0, 0x00E0E0E0); draw_rounded_rect(x+10, y+31, 15, 2, 0, 0x00E0E0E0); } 
    else if (type == 2) { draw_rounded_rect(x, y, 40, 40, 8, 0x00263238); draw_rounded_rect(x+5, y+5, 30, 10, 2, 0x0081C784); draw_rounded_rect(x+6, y+20, 7, 7, 2, 0x00E53935); draw_rounded_rect(x+16, y+20, 7, 7, 2, 0x00B0BEC5); draw_rounded_rect(x+26, y+20, 7, 7, 2, 0x00B0BEC5); draw_rounded_rect(x+6, y+29, 7, 7, 2, 0x00B0BEC5); draw_rounded_rect(x+16, y+29, 7, 7, 2, 0x00B0BEC5); draw_rounded_rect(x+26, y+29, 7, 7, 2, 0x002196F3); } 
    else if (type == 3) { draw_rounded_rect(x, y, 40, 40, 8, 0x002196F3); draw_rounded_rect(x+6, y+16, 12, 4, 1, 0x00FFFFFF); draw_rounded_rect(x+10, y+12, 4, 12, 1, 0x00FFFFFF); draw_rounded_rect(x+22, y+18, 6, 6, 3, 0x00E53935); draw_rounded_rect(x+30, y+12, 6, 6, 3, 0x00FFEB3B); } 
    else if (type == 4) { draw_rounded_rect(x, y, 40, 40, 8, 0x0078909C); draw_rounded_rect(x+10, y+10, 20, 20, 10, 0x0037474F); draw_rounded_rect(x+15, y+15, 10, 10, 5, 0x0078909C); } 
    else if (type == 5) { draw_rounded_rect(x, y, 40, 40, 5, 0x009C27B0); draw_rounded_rect(x+4, y+10, 8, 20, 1, 0x00FFFFFF); draw_rounded_rect(x+16, y+10, 8, 20, 1, 0x00FFFFFF); draw_rounded_rect(x+28, y+10, 8, 20, 1, 0x00FFFFFF); draw_rounded_rect(x+10, y+10, 6, 10, 1, 0x00000000); draw_rounded_rect(x+22, y+10, 6, 10, 1, 0x00000000); }
    else if (type == 6) { draw_rounded_rect(x, y, 40, 40, 8, 0x001E1E1E); draw_rounded_rect(x+6, y+20, 6, 15, 1, 0x004CAF50); draw_rounded_rect(x+16, y+10, 6, 25, 1, 0x004CAF50); draw_rounded_rect(x+26, y+15, 6, 20, 1, 0x004CAF50); }
    else if (type == 7) { draw_rounded_rect(x, y, 40, 40, 8, 0x00000000); draw_hd_string(">_", x+8, y+12, 0x004CAF50, 1); }
    else if (type == 8) { draw_rounded_rect(x, y, 40, 40, 4, 0x00FFFFFF); draw_rounded_rect(x+5, y+5, 30, 30, 2, 0x0064B5F6); draw_rounded_rect(x+20, y+10, 8, 8, 4, 0x00FFEB3B); }
    else if (type == 9) { draw_rounded_rect(x, y+5, 40, 35, 4, 0x00FFFFFF); draw_rounded_rect(x, y+5, 40, 10, 4, 0x00E53935); draw_rounded_rect(x+8, y+2, 4, 8, 2, 0x00B0BEC5); draw_rounded_rect(x+28, y+2, 4, 8, 2, 0x00B0BEC5); draw_hd_string("15", x+12, y+22, 0x000000, 1); }
    else if (type == 10) { draw_rounded_rect(x, y, 40, 40, 8, 0x00E91E63); draw_rounded_rect(x+10, y+10, 20, 20, 10, 0x00FFFFFF); draw_rounded_rect(x+15, y+15, 10, 10, 5, 0x00E91E63); }
    else if (type == 11) { // About PC (Info Icon)
        draw_rounded_rect(x, y, 40, 40, 8, 0x00607D8B); 
        draw_rounded_rect(x+18, y+8, 4, 4, 2, 0xFFFFFF); // i Dot
        draw_rounded_rect(x+18, y+16, 4, 16, 1, 0xFFFFFF); // i Line
    }
    else if (type == 12) { // Store / Cart Icon
        draw_rounded_rect(x, y, 40, 40, 8, 0x00FF5722); 
        draw_rounded_rect(x+10, y+15, 20, 15, 2, 0xFFFFFF); 
        draw_rounded_rect(x+15, y+10, 10, 5, 2, 0xFFFFFF); 
        draw_rounded_rect(x+15, y+12, 10, 5, 2, 0x00FF5722); 
    }
    else if (type == 13) { // Safar-nama Map Tracker
        draw_rounded_rect(x, y, 40, 40, 8, 0x000288D1); // Blue BG
        draw_rounded_rect(x+15, y+10, 10, 10, 5, 0xFFFFFF); // Pin head
        draw_rounded_rect(x+19, y+20, 2, 10, 1, 0xFFFFFF); // Pin needle
        draw_rounded_rect(x+10, y+30, 20, 4, 2, 0x00B0BEC5); // Map base
    }
    else if (type == 14) { // Browser Globe Icon
        draw_rounded_rect(x, y, 40, 40, 20, 0x001976D2); // Circle base
        draw_rounded_rect(x+6, y+18, 28, 4, 2, 0xFFFFFF); // Equator
        draw_rounded_rect(x+18, y+6, 4, 28, 2, 0xFFFFFF); // Prime Meridian
        draw_rounded_rect(x+12, y+10, 16, 20, 8, 0xFFFFFF); // Ellipse illusion
        draw_rounded_rect(x+14, y+12, 12, 16, 6, 0x001976D2); // Hollow center
    }
    
}

void draw_gradient_wallpaper(int theme_idx) {
    for (int y = 0; y < 768; y++) {
        int r, g, b;
        if (theme_idx == 0) { r = 15; g = 23 + (y * 20 / 768); b = 42 + (y * 40 / 768); } 
        else if (theme_idx == 1) { r = 240 - (y*20/768); g = 248; b = 255; } 
        else if (theme_idx == 2) { r = 10; g = 80 + (y*100/768); b = 150 + (y*50/768); } 
        else { r = 20; g = 60 + (y*80/768); b = 40 + (y*20/768); } 
        unsigned int color = (r << 16) | (g << 8) | b; 
        for (int x = 0; x < 1024; x++) high_res_buffer[y * 1024 + x] = color;
    }
}

void draw_modern_taskbar(int h, int m, int active_app) {
    int tb_width = 420, tb_height = 50, tb_x = (1024 - tb_width) / 2, tb_y = 768 - tb_height - 15;  
    draw_rounded_rect(tb_x + 2, tb_y + 4, tb_width, tb_height, 15, 0x00111111); 
    draw_rounded_rect(tb_x, tb_y, tb_width, tb_height, 15, 0x002D2D30);      
    draw_rounded_rect(tb_x + 20, tb_y + 10, 30, 30, 8, COLOR_ACCENT); draw_hd_string("M", tb_x + 26, tb_y + 18, COLOR_TEXT, 1);
    
    draw_app_icon(tb_x + 70, tb_y + 5, 0); draw_app_icon(tb_x + 120, tb_y + 5, 6); draw_app_icon(tb_x + 170, tb_y + 5, 7); draw_app_icon(tb_x + 220, tb_y + 5, 2); draw_app_icon(tb_x + 270, tb_y + 5, 3); draw_app_icon(tb_x + 320, tb_y + 5, 4); 

    if (active_app == 2) draw_rounded_rect(tb_x + 80, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 3) draw_rounded_rect(tb_x + 130, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 1) draw_rounded_rect(tb_x + 180, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 5) draw_rounded_rect(tb_x + 230, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 6) draw_rounded_rect(tb_x + 280, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 8) draw_rounded_rect(tb_x + 330, tb_y + 45, 20, 3, 1, 0xFFFFFF); 

    draw_rounded_rect(800, 10, 200, 30, 10, 0x00111111); draw_rounded_rect(800, 10, 200, 30, 10, 0x002D2D30);
    char time_str[6] = {'0','0',':','0','0','\0'}; time_str[0] = (h / 10) + '0'; time_str[1] = (h % 10) + '0'; time_str[3] = (m / 10) + '0'; time_str[4] = (m % 10) + '0';
    draw_hd_string(time_str, 930, 18, COLOR_TEXT, 1); draw_hd_string("W", 840, 18, 0x004CAF50, 1); draw_hd_string("B", 880, 18, 0x002196F3, 1);
}

void draw_hd_window(int win_x, int win_y, int w, int h, char* title) {
    draw_rounded_rect(win_x + 5, win_y + 5, w, h, 10, 0x00111111); 
    draw_rounded_rect(win_x, win_y, w, h, 10, 0x002D2D30); 
    draw_rounded_rect(win_x, win_y, w, 30, 10, 0x001E1E1E); 
    draw_hd_string(title, win_x + 15, win_y + 10, COLOR_TEXT, 1); 
    draw_rounded_rect(win_x + w - 30, win_y + 8, 15, 15, 5, COLOR_DANGER);
}

// DAY 154: BOOT SCREEN ANIMATION
void play_boot_animation() {
    for(int i=0; i<250; i++) {
        for(int j=0; j<1024*768; j++) high_res_buffer[j] = 0x000F172A; // Dark background
        draw_hd_string("MICRO OS", 400, 300, 0x004CAF50, 5);
        draw_hd_string("Starting Kernel & GUI...", 410, 360, 0xFFFFFF, 1);
        draw_rounded_rect(360, 400, 300, 10, 5, 0x00333333);
        draw_rounded_rect(360, 400, (i*300)/250, 10, 5, 0x004CAF50); // Progress bar
        swap_buffers_32();
    }
}
void draw_notification(int notif_y, char* msg) {
    if (notif_y < 0) return;
    int nx = 750; 
    draw_rounded_rect(nx + 5, notif_y + 5, 250, 60, 10, 0x00111111); 
    draw_rounded_rect(nx, notif_y, 250, 60, 10, 0x001E293B); 
    draw_rounded_rect(nx + 10, notif_y + 20, 20, 20, 10, 0x004CAF50); 
    draw_hd_string("System Notice", nx + 40, notif_y + 15, 0x0094A3B8, 1);
    draw_hd_string(msg, nx + 40, notif_y + 35, 0xFFFFFF, 1);
}

char hd_term_history[8][50]; int hd_term_lines = 0;       
void hd_print(char* text) {
    if (hd_term_lines >= 8) { for (int i = 1; i < 8; i++) { int c = 0; while (hd_term_history[i][c] != '\0') { hd_term_history[i-1][c] = hd_term_history[i][c]; c++; } hd_term_history[i-1][c] = '\0'; } hd_term_lines = 7; }
    int c = 0; while (text[c] != '\0' && c < 49) { hd_term_history[hd_term_lines][c] = text[c]; c++; } hd_term_history[hd_term_lines][c] = '\0'; hd_term_lines++;
}

void hd_itoa(int n, char* buf) {
    int i = 0, j = 0, temp = n; if (n == 0) { buf[0] = '0'; buf[1] = '\0'; return; }
    while (temp > 0) { buf[i++] = (temp % 10) + '0'; temp /= 10; } buf[i] = '\0';
    for(j = 0; j < i/2; j++) { char t = buf[j]; buf[j] = buf[i - 1 - j]; buf[i - 1 - j] = t; }
}

unsigned int hd_paint_canvas[260 * 200]; int paint_init = 0;

void render_desktop_bg(int mx, int my, int app_state, int win_x, int win_y, char* term_buffer, int h, int m, int start_menu, unsigned int used_ram, int ctx_open, int ctx_x, int ctx_y, int is_minimized, char* calc_display, int theme_idx, int* game_board, int game_winner, int is_screensaver, int ss_x, int ss_y, int* icon_x, int* icon_y, char* pwd_buffer, int uptime, int action_center_open, int ind_loading, int notif_y, char* notif_msg, char* ind_input_buf, int rtc_day, int rtc_month, int rtc_year, int now_playing) {
    
    if (is_screensaver) { for (int i = 0; i < (1024 * 768); i++) high_res_buffer[i] = 0x000000; draw_hd_string("MICRO OS", ss_x, ss_y, COLOR_ACCENT, 3); swap_buffers_32(); return; }

    if (app_state == -1) {
        draw_gradient_wallpaper(theme_idx); 
        char time_str[6] = {'0','0',':','0','0','\0'}; time_str[0] = (h / 10) + '0'; time_str[1] = (h % 10) + '0'; time_str[3] = (m / 10) + '0'; time_str[4] = (m % 10) + '0';
        draw_hd_string(time_str, 380, 150, 0xFFFFFF, 6); 
        draw_rounded_rect(412, 300, 200, 250, 10, 0x001E293B); draw_rounded_rect(462, 330, 100, 100, 20, 0x003B82F6); 
        draw_hd_string("A", 500, 360, 0xFFFFFF, 4); draw_hd_string("Abhikash", 455, 450, 0xFFFFFF, 1);
        draw_rounded_rect(430, 490, 160, 35, 5, 0x000F172A); 
        int p_len = 0; while(pwd_buffer[p_len]) p_len++;
        if (p_len == 0) draw_hd_string("Enter PIN", 460, 500, 0x00475569, 1); else for(int i=0; i<p_len; i++) draw_hd_string("*", 460 + (i*15), 505, 0xFFFFFF, 1);
        draw_hd_mouse_pointer(mx, my); swap_buffers_32(); return;
    }

    draw_gradient_wallpaper(theme_idx);
    
    draw_app_icon(icon_x[0], icon_y[0], 0); draw_hd_string("My PC", icon_x[0], icon_y[0]+45, 0xFFFFFF, 1);
    draw_app_icon(icon_x[1], icon_y[1], 1); draw_hd_string("Notes", icon_x[1], icon_y[1]+45, 0xFFFFFF, 1);
    draw_app_icon(icon_x[2], icon_y[2], 2); draw_hd_string("Calc", icon_x[2]+4, icon_y[2]+45, 0xFFFFFF, 1);
    draw_app_icon(icon_x[3], icon_y[3], 3); draw_hd_string("Game", icon_x[3]+4, icon_y[3]+45, 0xFFFFFF, 1);
    draw_app_icon(icon_x[4], icon_y[4], 4); draw_hd_string("Sets", icon_x[4]+4, icon_y[4]+45, 0xFFFFFF, 1);
    draw_app_icon(icon_x[5], icon_y[5], 5); draw_hd_string("Piano", icon_x[5], icon_y[5]+45, 0xFFFFFF, 1);
    draw_app_icon(icon_x[6], icon_y[6], 9); draw_hd_string("Date", icon_x[6]+4, icon_y[6]+45, 0xFFFFFF, 1); 
    draw_app_icon(icon_x[7], icon_y[7], 10); draw_hd_string("Music", icon_x[7], icon_y[7]+45, 0xFFFFFF, 1);
    draw_app_icon(icon_x[8], icon_y[8], 11); draw_hd_string("About", icon_x[8], icon_y[8]+45, 0xFFFFFF, 1); // 9th Icon
    draw_app_icon(icon_x[9], icon_y[9], 12); draw_hd_string("Store", icon_x[9], icon_y[9]+45, 0xFFFFFF, 1);
    draw_app_icon(icon_x[10], icon_y[10], 13); draw_hd_string("Safar", icon_x[10], icon_y[10]+45, 0xFFFFFF, 1);
    draw_app_icon(icon_x[11], icon_y[11], 14); draw_hd_string("Browser", icon_x[11]-4, icon_y[11]+45, 0xFFFFFF, 1);
    
    if (app_state == 0) { // Sirf Desktop par dikhega
        int wid_x = 780, wid_y = 100;
        draw_rounded_rect(wid_x + 5, wid_y + 5, 200, 140, 10, 0x00111111); // Shadow
        draw_rounded_rect(wid_x, wid_y, 200, 140, 10, 0x001E293B); // Background
        draw_hd_string("Battery Status", wid_x + 15, wid_y + 15, 0xFFFFFF, 1);
        
        draw_rounded_rect(wid_x + 15, wid_y + 40, 60, 30, 3, 0xFFFFFF); // Battery Shell
        draw_rounded_rect(wid_x + 75, wid_y + 48, 5, 14, 2, 0xFFFFFF);  // Battery Nipple
        
        // Dynamic Fill calculation (Red agar < 20%)
        int fill_width = (battery_percentage * 56) / 100;
        unsigned int bat_color = (battery_percentage > 20) ? 0x004CAF50 : 0x00E53935;
        draw_rounded_rect(wid_x + 17, wid_y + 42, fill_width, 26, 2, bat_color); 
        
        // Print Live Percentage
        char bat_str[5]; hd_itoa(battery_percentage, bat_str);
        int b_len = 0; while(bat_str[b_len]) b_len++;
        bat_str[b_len] = '%'; bat_str[b_len+1] = '\0';
        draw_hd_string(bat_str, wid_x + 90, wid_y + 48, 0xFFFFFF, 2);
        
        draw_hd_string("Time Left", wid_x + 15, wid_y + 85, 0x0094A3B8, 1);
        draw_hd_string("3h 45m", wid_x + 15, wid_y + 105, 0xFFFFFF, 1);
        
        draw_hd_string("Power Saver", wid_x + 100, wid_y + 85, 0x0094A3B8, 1);
        draw_rounded_rect(wid_x + 120, wid_y + 105, 30, 15, 7, 0x00333333); 
        draw_rounded_rect(wid_x + 122, wid_y + 107, 11, 11, 5, 0xFFFFFF); // Toggle off
    }
    
    if (app_state > 0 && !is_minimized) { 
        if (app_state == 1) { 
            draw_hd_window(win_x, win_y, 420, 300, "Terminal - Root");
            for(int i = 0; i < hd_term_lines; i++) { draw_hd_string(hd_term_history[i], win_x + 15, win_y + 40 + (i * 20), COLOR_TEXT, 1); }
            int current_y = win_y + 40 + (hd_term_lines * 20); 
            draw_hd_string("root@microos:~# ", win_x + 15, current_y, 0x004CAF50, 1); 
            draw_hd_string(term_buffer, win_x + 155, current_y, COLOR_TEXT, 1);
            
            // DAY 158: Blinking Terminal Cursor
            int t_len = 0; while(term_buffer[t_len]) t_len++;
            if (uptime % 2 == 0) draw_hd_string("_", win_x + 155 + (t_len * 8), current_y, COLOR_TEXT, 1);

            if (ind_loading > 0) {
                draw_rounded_rect(win_x + 50, win_y + 120, 320, 60, 5, 0x00111111); draw_hd_string("Compiling .ind to Runtime...", win_x + 70, win_y + 135, 0xFFFFFF, 1);
                draw_rounded_rect(win_x + 70, win_y + 160, 280, 10, 5, 0x00333333); draw_rounded_rect(win_x + 70, win_y + 160, ind_loading * 2, 10, 5, 0x004CAF50);
            }
        }
        else if (app_state == 2) { 
            draw_hd_window(win_x, win_y, 500, 350, "File Explorer"); draw_rounded_rect(win_x, win_y+30, 500, 40, 0, 0x001E1E1E); draw_hd_string("Path: C:/MicroOS/", win_x + 20, win_y + 45, 0x0094A3B8, 1);
            char count_str[5]; hd_itoa(file_count, count_str); draw_hd_string("Items:", win_x + 400, win_y + 45, 0x0094A3B8, 1); draw_hd_string(count_str, win_x + 460, win_y + 45, COLOR_ACCENT, 1); 
            for(int f = 0; f < file_count && f < 10; f++) { 
                int col = f % 5; int row = f / 5; int fx = win_x + 30 + (col * 90); int fy = win_y + 90 + (row * 100);
                if (file_system[f].name[0] == 'I' && file_system[f].name[1] == 'M' && file_system[f].name[2] == 'G') draw_app_icon(fx, fy, 8); 
                else if (file_system[f].name[0] == 'a' && file_system[f].name[1] == 'p' && file_system[f].name[2] == 'p') draw_app_icon(fx, fy, 7);
                else draw_app_icon(fx, fy, 1); 
                draw_hd_string(file_system[f].name, fx, fy + 45, COLOR_TEXT, 1); 
            }
        }
        else if (app_state == 3) { 
            draw_hd_window(win_x, win_y, 450, 320, "Task Manager"); 
            draw_hd_string("Live Memory Graph", win_x + 20, win_y + 50, COLOR_TEXT, 1); 
            draw_rounded_rect(win_x + 20, win_y + 70, 410, 80, 5, 0x00111111); 
            
            // DAY 157: LIVE DYNAMIC SHIFTING GRAPH
            for(int i=0; i<400; i+=10) {
                int noise = ((used_ram + (uptime * 15) + i) * 17) % 50; 
                draw_rounded_rect(win_x+25+i, win_y+140 - noise, 5, noise+5, 2, 0x004CAF50);
            }

            draw_hd_string("Memory (RAM)", win_x + 20, win_y + 170, COLOR_TEXT, 1); 
            char ram_str[15]; hd_itoa(used_ram/1024, ram_str); 
            draw_hd_string(ram_str, win_x + 20, win_y + 190, 0x002196F3, 2); draw_hd_string(" KB In Use", win_x + 140, win_y + 195, COLOR_TEXT, 1);
            
            draw_rounded_rect(win_x + 20, win_y + 230, 410, 20, 10, 0x00111111); 
            int ram_bar = (used_ram / 500); if(ram_bar > 410) ram_bar = 410; 
            draw_rounded_rect(win_x + 20, win_y + 230, ram_bar, 20, 10, 0x002196F3);
            
            draw_hd_string("System Uptime:", win_x + 20, win_y + 270, COLOR_TEXT, 1); 
            char up_str[10]; hd_itoa(uptime, up_str); 
            draw_hd_string(up_str, win_x + 130, win_y + 270, COLOR_ACCENT, 1); draw_hd_string("secs", win_x + 180, win_y + 270, COLOR_TEXT, 1);
        }
        else if (app_state == 4) { 
            draw_hd_window(win_x, win_y, 400, 300, "HD Notepad"); 
            draw_hd_string("Type your notes below:", win_x + 20, win_y + 50, COLOR_ACCENT, 1); 
            draw_hd_string(term_buffer, win_x + 20, win_y + 90, COLOR_TEXT, 1);
            
            // DAY 158: Notepad Blinking Cursor
            int t_len = 0; while(term_buffer[t_len]) t_len++;
            if (uptime % 2 == 0) draw_hd_string("_", win_x + 20 + (t_len * 8), win_y + 90, COLOR_TEXT, 1);

            draw_rounded_rect(win_x + 280, win_y + 45, 45, 25, 5, 0x004CAF50); draw_hd_string("SAVE", win_x + 285, win_y + 53, 0xFFFFFF, 1); 
            draw_rounded_rect(win_x + 335, win_y + 45, 45, 25, 5, 0x00FFB300); draw_hd_string("LOAD", win_x + 340, win_y + 53, 0xFFFFFF, 1);
        }
        else if (app_state == 5) { 
            draw_hd_window(win_x, win_y, 300, 360, "Calculator"); draw_rounded_rect(win_x + 20, win_y + 45, 260, 50, 5, 0x00111111); int len = 0; while(calc_display[len]) len++; draw_hd_string(calc_display, win_x + 260 - (len * 16), win_y + 55, COLOR_TEXT, 2);
            char* keys = "789/456*123-C0=+"; for(int i=0; i<4; i++) { for(int j=0; j<4; j++) { int bx = win_x + 20 + (j * 65); int by = win_y + 105 + (i * 60); draw_rounded_rect(bx, by, 55, 50, 5, 0x00333333); char lbl[2] = {keys[(i*4)+j], '\0'}; draw_hd_string(lbl, bx + 22, by + 20, COLOR_TEXT, 1); } }
        }
        else if (app_state == 6) { 
            draw_hd_window(win_x, win_y, 300, 360, "Tic-Tac-Toe"); draw_rounded_rect(win_x+105, win_y+50, 5, 280, 2, 0x00555555); draw_rounded_rect(win_x+190, win_y+50, 5, 280, 2, 0x00555555); draw_rounded_rect(win_x+20, win_y+135, 260, 5, 2, 0x00555555); draw_rounded_rect(win_x+20, win_y+235, 260, 5, 2, 0x00555555);
            for(int i=0; i<3; i++) { for(int j=0; j<3; j++) { int cell = game_board[i*3 + j]; int cx = win_x + 40 + (j*85); int cy = win_y + 70 + (i*100); if (cell == 1) draw_hd_string("X", cx, cy, 0x00E53935, 4); if (cell == 2) draw_hd_string("O", cx, cy, 0x002196F3, 4); } }
            if (game_winner != 0) { draw_rounded_rect(win_x + 50, win_y + 150, 200, 60, 10, 0x00111111); if (game_winner == 1) draw_hd_string("P1 WINS!", win_x + 75, win_y + 170, 0x00E53935, 1); else if (game_winner == 2) draw_hd_string("P2 WINS!", win_x + 75, win_y + 170, 0x002196F3, 1); else draw_hd_string(" DRAW! ", win_x + 85, win_y + 170, 0xFFFFFF, 1); }
        }
        else if (app_state == 7) { 
            draw_hd_window(win_x, win_y, 300, 320, "HD Paint"); if (!paint_init) { for(int i=0; i<260*200; i++) hd_paint_canvas[i] = 0xFFFFFF; paint_init = 1; }
            for(int py=0; py<200; py++) { for(int px=0; px<260; px++) { int screen_pos = ((win_y + 40 + py) * 1024) + (win_x + 20 + px); high_res_buffer[screen_pos] = hd_paint_canvas[(py * 260) + px]; } }
            draw_rounded_rect(win_x + 20, win_y + 260, 30, 30, 5, 0x00E53935); draw_rounded_rect(win_x + 60, win_y + 260, 30, 30, 5, 0x004CAF50); draw_rounded_rect(win_x + 100, win_y + 260, 30, 30, 5, 0x002196F3); draw_rounded_rect(win_x + 140, win_y + 260, 30, 30, 5, 0x00000000); draw_rounded_rect(win_x + 180, win_y + 260, 30, 30, 5, 0xFFFFFFFF); draw_rounded_rect(win_x + 225, win_y + 260, 45, 30, 5, 0x00FFB300); draw_hd_string("Save", win_x + 230, win_y + 270, 0x000000, 1);
        }
        else if (app_state == 8) {
            draw_hd_window(win_x, win_y, 300, 200, "Settings"); draw_hd_string("Personalize Theme:", win_x+20, win_y+50, COLOR_TEXT, 1); draw_rounded_rect(win_x+20, win_y+90, 50, 50, 5, 0x001E1E2E); draw_rounded_rect(win_x+85, win_y+90, 50, 50, 5, 0x00F8F9FA); draw_rounded_rect(win_x+150, win_y+90, 50, 50, 5, 0x000F4C75); draw_rounded_rect(win_x+215, win_y+90, 50, 50, 5, 0x001B4332); 
        }
        else if (app_state == 9) {
            draw_hd_window(win_x, win_y, 350, 230, "Mini Piano"); for(int i=0; i<7; i++) { draw_rounded_rect(win_x + 20 + (i*42), win_y + 50, 40, 140, 5, 0xFFFFFF); } for(int i=0; i<6; i++) { if (i == 2) continue; draw_rounded_rect(win_x + 45 + (i*42), win_y + 50, 28, 80, 3, 0x000000); } draw_hd_string("Click keys to play!", win_x + 80, win_y + 200, COLOR_ACCENT, 1);
        }
        else if (app_state == 10) {
            draw_hd_window(win_x, win_y, 300, 280, "Image Gallery"); draw_rounded_rect(win_x + 20, win_y + 50, 260, 200, 5, 0x000000); for(int py=0; py<200; py++) { for(int px=0; px<260; px++) { int screen_pos = ((win_y + 50 + py) * 1024) + (win_x + 20 + px); high_res_buffer[screen_pos] = hd_paint_canvas[(py * 260) + px]; } }
        }
        else if (app_state == 11) {
            draw_hd_window(win_x, win_y, 400, 300, ind_app_title); 
            draw_rounded_rect(win_x+5, win_y+35, 390, 260, 5, ind_app_bg); 
            draw_hd_string(ind_app_msg, win_x + 20, win_y + 60, 0xFFFFFF, 2);
            
            if (ind_app_input[0] != '\0') { 
                draw_rounded_rect(win_x + 20, win_y + 110, 350, 35, 5, 0x00111111); 
                int blen = 0; while(ind_input_buf[blen]) blen++; 
                if (blen == 0) {
                    draw_hd_string(ind_app_input, win_x + 30, win_y + 120, 0x0078909C, 1); 
                } else { 
                    draw_hd_string(ind_input_buf, win_x + 30, win_y + 120, 0xFFFFFF, 1); 
                    // DAY 158: IND App Input Blinking Cursor
                    if (uptime % 2 == 0) draw_hd_string("|", win_x + 30 + (blen * 8), win_y + 120, 0xFFFFFF, 1);
                } 
            }
            if (ind_app_btn[0] != '\0') { 
                draw_rounded_rect(win_x + 20, win_y + 160, 200, 40, 5, 0x004CAF50); 
                draw_hd_string(ind_app_btn, win_x + 40, win_y + 172, 0xFFFFFF, 1); 
            }
        }
        else if (app_state == 12) {
            draw_hd_window(win_x, win_y, 350, 300, "Calendar"); draw_rounded_rect(win_x+5, win_y+35, 340, 80, 5, 0x00E53935); draw_rounded_rect(win_x+5, win_y+115, 340, 180, 5, 0x00FFFFFF); draw_hd_string("TODAY", win_x + 140, win_y + 50, 0xFFFFFF, 1); char d_str[3], m_str[3], y_str[5]; hd_itoa(rtc_day, d_str); hd_itoa(rtc_month, m_str); hd_itoa(rtc_year, y_str); draw_hd_string(d_str, win_x + 130, win_y + 130, 0x00000000, 6); draw_hd_string("Month:", win_x + 80, win_y + 220, 0x0078909C, 1); draw_hd_string(m_str, win_x + 140, win_y + 220, 0x00E53935, 1); draw_hd_string("Year:", win_x + 180, win_y + 220, 0x0078909C, 1); draw_hd_string(y_str, win_x + 230, win_y + 220, 0x00E53935, 1); draw_hd_string("Hardware RTC Synced", win_x + 90, win_y + 260, 0x00B0BEC5, 1);
        }
        else if (app_state == 13) {
            draw_hd_window(win_x, win_y, 360, 250, "Melody Player"); draw_rounded_rect(win_x+20, win_y+50, 320, 80, 10, 0x00111111);
            // DAY 155 FIX: Update UI based on what is playing!
            if (now_playing == 1) draw_hd_string("Now Playing: Nokia...", win_x + 35, win_y + 65, 0x004CAF50, 1);
            else if (now_playing == 2) draw_hd_string("Now Playing: Mario...", win_x + 35, win_y + 65, 0x00FFB300, 1);
            else draw_hd_string("Select a Track:", win_x + 35, win_y + 65, 0x0094A3B8, 1);
            
            draw_rounded_rect(win_x+20, win_y+150, 90, 40, 5, 0x00E91E63); draw_hd_string("Nokia", win_x+35, win_y+165, 0xFFFFFF, 1);
            draw_rounded_rect(win_x+130, win_y+150, 90, 40, 5, 0x002196F3); draw_hd_string("Mario", win_x+145, win_y+165, 0xFFFFFF, 1);
            draw_rounded_rect(win_x+240, win_y+150, 90, 40, 5, 0x00FFB300); draw_hd_string("Stop", win_x+265, win_y+165, 0x000000, 1);
        }
        // DAY 156: ABOUT PC APP
        else if (app_state == 14) {
            draw_hd_window(win_x, win_y, 350, 300, "System Properties");
            draw_rounded_rect(win_x+20, win_y+50, 60, 60, 10, COLOR_ACCENT); draw_hd_string("M", win_x + 35, win_y + 65, 0xFFFFFF, 3);
            draw_hd_string("Micro OS v3.0", win_x + 100, win_y + 60, 0xFFFFFF, 2); draw_hd_string("Licensed to: Abhikash", win_x + 100, win_y + 90, 0x004CAF50, 1);
            draw_rounded_rect(win_x+20, win_y+130, 310, 2, 0, 0x00333333);
            draw_hd_string("Processor: x86 Bare Metal", win_x + 20, win_y + 150, 0x0094A3B8, 1);
            draw_hd_string("Graphics: VESA HD UI Engine", win_x + 20, win_y + 180, 0x0094A3B8, 1);
            draw_hd_string("Kernel: Monolithic Custom", win_x + 20, win_y + 210, 0x0094A3B8, 1);
        }
        // DAY 160: E-COMMERCE NATIVE APP
        else if (app_state == 15) {
            draw_hd_window(win_x, win_y, 470, 320, "Ghar Se Market - Store");
            draw_rounded_rect(win_x+5, win_y+35, 460, 60, 5, 0x004CAF50); 
            draw_hd_string("Aacharindia Premium Store", win_x + 90, win_y + 55, 0xFFFFFF, 2);
            
            // Product 1
            draw_rounded_rect(win_x+20, win_y+110, 120, 120, 5, 0x00111111);
            draw_hd_string("Mango", win_x + 50, win_y + 150, 0x00FFB300, 1);
            draw_rounded_rect(win_x+20, win_y+240, 120, 30, 5, 0x00E53935);
            draw_hd_string("BUY", win_x + 60, win_y + 250, 0xFFFFFF, 1);

            // Product 2
            draw_rounded_rect(win_x+170, win_y+110, 120, 120, 5, 0x00111111);
            draw_hd_string("Lemon", win_x + 200, win_y + 150, 0x004CAF50, 1);
            draw_rounded_rect(win_x+170, win_y+240, 120, 30, 5, 0x00E53935);
            draw_hd_string("BUY", win_x + 210, win_y + 250, 0xFFFFFF, 1);
            
            // Product 3
            draw_rounded_rect(win_x+320, win_y+110, 120, 120, 5, 0x00111111);
            draw_hd_string("Garlic", win_x + 350, win_y + 150, 0xFFFFFF, 1);
            draw_rounded_rect(win_x+320, win_y+240, 120, 30, 5, 0x00E53935);
            draw_hd_string("BUY", win_x + 360, win_y + 250, 0xFFFFFF, 1);
        }
        // DAY 162: SAFAR-NAMA MAP TRACKER
        else if (app_state == 16) {
            draw_hd_window(win_x, win_y, 400, 350, "Safar-nama Tracker");
            draw_rounded_rect(win_x + 10, win_y + 40, 380, 250, 5, 0x001E293B); 
            // Draw Map Grid
            for(int i=0; i<380; i+=20) draw_rounded_rect(win_x+10+i, win_y+40, 1, 250, 0, 0x00334155);
            for(int i=0; i<250; i+=20) draw_rounded_rect(win_x+10, win_y+40+i, 380, 1, 0, 0x00334155);

            // Draw Plotted Points
            for(int i=0; i<game_winner; i++) {
                int px = game_board[i*2];
                int py = game_board[i*2 + 1];
                draw_rounded_rect(win_x + 10 + px - 4, win_y + 40 + py - 4, 8, 8, 4, 0x00E53935);
            }

            // Controls
            draw_rounded_rect(win_x + 10, win_y + 300, 100, 30, 5, 0x00E53935);
            draw_hd_string("CLEAR", win_x + 35, win_y + 310, 0xFFFFFF, 1);
            char pts_str[2] = {game_winner + '0', '\0'};
            draw_hd_string("Points:", win_x + 130, win_y + 310, 0xFFFFFF, 1);
            draw_hd_string(pts_str, win_x + 195, win_y + 310, 0x004CAF50, 1);
        }
        // DAY 164: MICRO BROWSER UI
        else if (app_state == 17) {
            draw_hd_window(win_x, win_y, 500, 360, "Micro Search - Browser");
            
            // Search Bar
            draw_hd_string("MICRO SEARCH", win_x + 160, win_y + 100, 0xFFFFFF, 3);
            draw_rounded_rect(win_x + 50, win_y + 160, 400, 40, 20, 0x001E293B); // Bar BG
            draw_hd_string("Search the web...", win_x + 70, win_y + 175, 0x0094A3B8, 1);
            draw_rounded_rect(win_x + 400, win_y + 165, 40, 30, 15, 0x002196F3); // Blue Search Button
            
            // Quick Links Grid
            draw_rounded_rect(win_x + 100, win_y + 240, 50, 50, 10, 0x00111111);
            draw_hd_string("G", win_x + 115, win_y + 250, 0x004CAF50, 3); // Google
            
            draw_rounded_rect(win_x + 180, win_y + 240, 50, 50, 10, 0x00111111);
            draw_hd_string("Hub", win_x + 185, win_y + 255, 0xFFFFFF, 2); // GitHub
            
            draw_rounded_rect(win_x + 260, win_y + 240, 50, 50, 10, 0x00111111);
            draw_hd_string("YT", win_x + 270, win_y + 255, 0x00E53935, 2); // YouTube
            
            draw_rounded_rect(win_x + 340, win_y + 240, 50, 50, 10, 0x00111111);
            draw_hd_string("W", win_x + 355, win_y + 250, 0x00B0BEC5, 3); // Wikipedia
        }
    } // YAHAN app_state > 0 BLOCK BAND HOTA HAI!

    draw_modern_taskbar(h, m, app_state);

    if (start_menu) {
        int sm_w = 240, sm_h = 320, sm_x = 312, sm_y = 708 - sm_h - 10;
        draw_rounded_rect(sm_x + 5, sm_y + 5, sm_w, sm_h, 10, 0x00111111); draw_rounded_rect(sm_x, sm_y, sm_w, sm_h, 10, 0x00252526); draw_rounded_rect(sm_x+20, sm_y+20, 30, 30, 15, COLOR_ACCENT); draw_hd_string("Micro OS", sm_x + 60, sm_y + 28, 0xFFFFFF, 1); draw_rounded_rect(sm_x + 20, sm_y + 60, sm_w - 40, 2, 0, 0x00444444); 
        draw_rounded_rect(sm_x+20, sm_y+80, 15, 15, 3, 0x004CAF50); draw_hd_string("Notepad", sm_x + 45, sm_y + 83, COLOR_TEXT, 1); draw_rounded_rect(sm_x+20, sm_y+115, 15, 15, 3, 0x00E53935); draw_hd_string("Calculator", sm_x + 45, sm_y + 118, COLOR_TEXT, 1); draw_rounded_rect(sm_x+20, sm_y+150, 15, 15, 3, 0x00FFFFFF); draw_hd_string("Calendar", sm_x + 45, sm_y + 153, COLOR_TEXT, 1); draw_rounded_rect(sm_x+20, sm_y+185, 15, 15, 3, 0x009E9E9E); draw_hd_string("Settings", sm_x + 45, sm_y + 188, COLOR_TEXT, 1); draw_rounded_rect(sm_x+20, sm_y+220, 15, 15, 3, 0x00FFB300); draw_hd_string("HD Paint", sm_x + 45, sm_y + 223, COLOR_TEXT, 1);
        draw_rounded_rect(sm_x + 20, sm_y + 265, sm_w - 40, 35, 5, COLOR_DANGER); draw_hd_string("O", sm_x + 60, sm_y + 276, 0xFFFFFF, 1); draw_hd_string("|", sm_x + 63, sm_y + 272, 0xFFFFFF, 1); draw_hd_string("SHUT DOWN", sm_x + 85, sm_y + 276, 0xFFFFFF, 1);
    }

    if (action_center_open) {
        int ac_w = 250, ac_h = 400, ac_x = 760, ac_y = 50; 
        draw_rounded_rect(ac_x + 5, ac_y + 5, ac_w, ac_h, 15, 0x00111111); draw_rounded_rect(ac_x, ac_y, ac_w, ac_h, 15, 0x002D2D30); draw_hd_string("Control Center", ac_x + 20, ac_y + 20, 0xFFFFFF, 1);
        draw_rounded_rect(ac_x + 20, ac_y + 60, 210, 80, 10, 0x001E1E1E); draw_rounded_rect(ac_x + 30, ac_y + 70, 40, 40, 20, 0x004CAF50); draw_hd_string("W", ac_x + 45, ac_y + 85, 0xFFFFFF, 1); draw_hd_string("Wi-Fi", ac_x + 80, ac_y + 85, 0xFFFFFF, 1);
        draw_rounded_rect(ac_x + 20, ac_y + 160, 210, 80, 10, 0x001E1E1E); draw_hd_string("Volume", ac_x + 30, ac_y + 175, 0xFFFFFF, 1); draw_rounded_rect(ac_x + 30, ac_y + 200, 180, 10, 5, 0x00333333); draw_rounded_rect(ac_x + 30, ac_y + 200, 120, 10, 5, 0x002196F3); draw_rounded_rect(ac_x + 145, ac_y + 195, 10, 20, 5, 0xFFFFFF);
        draw_rounded_rect(ac_x + 20, ac_y + 260, 210, 80, 10, 0x001E1E1E); draw_hd_string("Brightness", ac_x + 30, ac_y + 275, 0xFFFFFF, 1); draw_rounded_rect(ac_x + 30, ac_y + 300, 180, 10, 5, 0x00333333); draw_rounded_rect(ac_x + 30, ac_y + 300, 150, 10, 5, 0x00FFB300); draw_rounded_rect(ac_x + 175, ac_y + 295, 10, 20, 5, 0xFFFFFF);
    }

    if (ctx_open) {
        draw_rounded_rect(ctx_x + 5, ctx_y + 5, 180, 120, 5, 0x00111111); draw_rounded_rect(ctx_x, ctx_y, 180, 120, 5, 0x002D2D30);         
        draw_hd_string("> About PC", ctx_x + 15, ctx_y + 15, COLOR_TEXT, 1); 
        draw_hd_string("> Terminal", ctx_x + 15, ctx_y + 50, COLOR_TEXT, 1); 
        draw_hd_string("> Settings", ctx_x + 15, ctx_y + 85, COLOR_TEXT, 1); 
    }

    draw_notification(notif_y, notif_msg);
    draw_hd_mouse_pointer(mx, my); 
    swap_buffers_32(); // Yeh kabhi block nahi hona chahiye!
}

#endif