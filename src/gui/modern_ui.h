#ifndef MODERN_UI_H
#define MODERN_UI_H

#include "vesa.h"

// ----------------------------------------------------
// DAY 138: THE NEW MODERN SMOOTH FONT ENGINE (8x8)
// ----------------------------------------------------
// Yeh ek clean, modern 8x8 font hai (ASCII 32 to 122)
const unsigned char modern_font[91][8] = {
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // Space
    {0x18,0x3C,0x3C,0x18,0x18,0x00,0x18,0x00}, // !
    {0x6C,0x6C,0x6C,0x00,0x00,0x00,0x00,0x00}, // "
    {0x6C,0x6C,0xFE,0x6C,0xFE,0x6C,0x6C,0x00}, // #
    {0x18,0x7E,0xC0,0x7C,0x06,0xFC,0x18,0x00}, // $
    {0x00,0xC6,0xCC,0x18,0x30,0x66,0xC6,0x00}, // %
    {0x38,0x6C,0x38,0x76,0xDC,0xCC,0x76,0x00}, // &
    {0x30,0x30,0x60,0x00,0x00,0x00,0x00,0x00}, // '
    {0x18,0x30,0x60,0x60,0x60,0x30,0x18,0x00}, // (
    {0x60,0x30,0x18,0x18,0x18,0x30,0x60,0x00}, // )
    {0x00,0x66,0x3C,0xFF,0x3C,0x66,0x00,0x00}, // *
    {0x00,0x18,0x18,0x7E,0x18,0x18,0x00,0x00}, // +
    {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x30}, // ,
    {0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00}, // -
    {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00}, // .
    {0x06,0x0C,0x18,0x30,0x60,0xC0,0x80,0x00}, // /
    {0x7C,0xC6,0xCE,0xDE,0xF6,0xE6,0x7C,0x00}, // 0
    {0x30,0x70,0x30,0x30,0x30,0x30,0xFC,0x00}, // 1
    {0x78,0xCC,0x0C,0x38,0x60,0xCC,0xFC,0x00}, // 2
    {0x78,0xCC,0x0C,0x38,0x0C,0xCC,0x78,0x00}, // 3
    {0x1C,0x3C,0x6C,0xCC,0xFE,0x0C,0x1E,0x00}, // 4
    {0xFC,0xC0,0xF8,0x0C,0x0C,0xCC,0x78,0x00}, // 5
    {0x38,0x60,0xC0,0xF8,0xCC,0xCC,0x78,0x00}, // 6
    {0xFC,0xCC,0x0C,0x18,0x30,0x30,0x30,0x00}, // 7
    {0x78,0xCC,0xCC,0x78,0xCC,0xCC,0x78,0x00}, // 8
    {0x78,0xCC,0xCC,0x7C,0x0C,0x18,0x70,0x00}, // 9
    {0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x00}, // :
    {0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x30}, // ;
    {0x18,0x30,0x60,0xC0,0x60,0x30,0x18,0x00}, // <
    {0x00,0x00,0x7E,0x00,0x7E,0x00,0x00,0x00}, // =
    {0x60,0x30,0x18,0x0C,0x18,0x30,0x60,0x00}, // >
    {0x3C,0x66,0x0C,0x18,0x18,0x00,0x18,0x00}, // ?
    {0x7C,0xC6,0xDE,0xDE,0xDC,0xC0,0x7C,0x00}, // @
    {0x38,0x6C,0xC6,0xFE,0xC6,0xC6,0xC6,0x00}, // A
    {0xFC,0x66,0x66,0x7C,0x66,0x66,0xFC,0x00}, // B
    {0x3C,0x66,0xC0,0xC0,0xC0,0x66,0x3C,0x00}, // C
    {0xF8,0x6C,0x66,0x66,0x66,0x6C,0xF8,0x00}, // D
    {0xFE,0x62,0x68,0x78,0x68,0x62,0xFE,0x00}, // E
    {0xFE,0x62,0x68,0x78,0x68,0x60,0xF0,0x00}, // F
    {0x3C,0x66,0xC0,0xCE,0xC6,0x66,0x3E,0x00}, // G
    {0xC6,0xC6,0xC6,0xFE,0xC6,0xC6,0xC6,0x00}, // H
    {0x3C,0x18,0x18,0x18,0x18,0x18,0x3C,0x00}, // I
    {0x1E,0x0C,0x0C,0x0C,0xCC,0xCC,0x78,0x00}, // J
    {0xE6,0x66,0x6C,0x78,0x6C,0x66,0xE6,0x00}, // K
    {0xF0,0x60,0x60,0x60,0x62,0x66,0xFE,0x00}, // L
    {0xC6,0xEE,0xFE,0xFE,0xD6,0xC6,0xC6,0x00}, // M
    {0xC6,0xE6,0xF6,0xDE,0xCE,0xC6,0xC6,0x00}, // N
    {0x38,0x6C,0xC6,0xC6,0xC6,0x6C,0x38,0x00}, // O
    {0xFC,0x66,0x66,0x7C,0x60,0x60,0xF0,0x00}, // P
    {0x7C,0xC6,0xC6,0xC6,0xD6,0x7C,0x0E,0x00}, // Q
    {0xFC,0x66,0x66,0x7C,0x6C,0x66,0xE6,0x00}, // R
    {0x7C,0xC6,0xE0,0x78,0x0E,0xC6,0x3E,0x00}, // S
    {0xFC,0xB4,0x30,0x30,0x30,0x30,0x78,0x00}, // T
    {0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00}, // U
    {0xC6,0xC6,0xC6,0xC6,0xC6,0x6C,0x38,0x00}, // V
    {0xC6,0xC6,0xC6,0xD6,0xFE,0xEE,0xC6,0x00}, // W
    {0xC6,0xC6,0x6C,0x38,0x6C,0xC6,0xC6,0x00}, // X
    {0x66,0x66,0x66,0x3C,0x18,0x18,0x3C,0x00}, // Y
    {0xFE,0x86,0x0C,0x18,0x30,0x61,0xFE,0x00}, // Z
    {0x3C,0x30,0x30,0x30,0x30,0x30,0x3C,0x00}, // [
    {0x00,0x80,0xC0,0x60,0x30,0x18,0x0C,0x06}, // '\'
    {0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C,0x00}, // ]
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // ^
    {0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00}, // _
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // `
    {0x00,0x00,0x78,0x0C,0x7C,0xCC,0x76,0x00}, // a
    {0xE0,0x60,0x60,0x7C,0x66,0x66,0xDC,0x00}, // b
    {0x00,0x00,0x78,0xCC,0xC0,0xCC,0x78,0x00}, // c
    {0x1C,0x0C,0x0C,0x7C,0xCC,0xCC,0x76,0x00}, // d
    {0x00,0x00,0x78,0xCC,0xFC,0xC0,0x78,0x00}, // e
    {0x38,0x6C,0x60,0xF0,0x60,0x60,0xF0,0x00}, // f
    {0x00,0x00,0x76,0xCC,0xCC,0x7C,0x0C,0xF8}, // g
    {0xE0,0x60,0x6C,0x76,0x66,0x66,0xE6,0x00}, // h
    {0x18,0x00,0x38,0x18,0x18,0x18,0x3C,0x00}, // i
    {0x06,0x00,0x06,0x06,0x06,0x06,0x06,0x3C}, // j
    {0xE0,0x60,0x66,0x6C,0x78,0x6C,0xE6,0x00}, // k
    {0x38,0x18,0x18,0x18,0x18,0x18,0x3C,0x00}, // l
    {0x00,0x00,0xEC,0xFE,0xD6,0xD6,0xD6,0x00}, // m
    {0x00,0x00,0xDC,0x66,0x66,0x66,0x66,0x00}, // n
    {0x00,0x00,0x78,0xCC,0xCC,0xCC,0x78,0x00}, // o
    {0x00,0x00,0xDC,0x66,0x66,0x7C,0x60,0xF0}, // p
    {0x00,0x00,0x76,0xCC,0xCC,0x7C,0x0C,0x1E}, // q
    {0x00,0x00,0xDC,0x76,0x60,0x60,0xF0,0x00}, // r
    {0x00,0x00,0x7C,0xC0,0x78,0x0C,0xF8,0x00}, // s
    {0x10,0x30,0x7C,0x30,0x30,0x34,0x18,0x00}, // t
    {0x00,0x00,0xCC,0xCC,0xCC,0xCC,0x76,0x00}, // u
    {0x00,0x00,0xCC,0xCC,0xCC,0x78,0x30,0x00}, // v
    {0x00,0x00,0xC6,0xD6,0xFE,0xFE,0x6C,0x00}, // w
    {0x00,0x00,0xC6,0x6C,0x38,0x6C,0xC6,0x00}, // x
    {0x00,0x00,0xCC,0xCC,0xCC,0x7C,0x0C,0xF8}, // y
    {0x00,0x00,0xFC,0x98,0x30,0x64,0xFC,0x00}  // z
};

// NAYA FONT RENDERER
void draw_scaled_char(char c, int x, int y, unsigned int hex_color, int scale) {
    if (c < 32 || c > 122) return; 
    int font_idx = c - 32;
    for (int row = 0; row < 8; row++) {
        unsigned char row_data = modern_font[font_idx][row];
        for (int col = 0; col < 8; col++) {
            if ((row_data >> (7 - col)) & 1) {
                // Drawing pixels based on the modern 8x8 font grid
                draw_rounded_rect(x + (col * scale), y + (row * scale), scale, scale, 0, hex_color);
            }
        }
    }
}

void draw_hd_string(char* str, int start_x, int start_y, unsigned int hex_color, int scale) {
    int x = start_x; 
    for(int i = 0; str[i] != '\0'; i++) { 
        draw_scaled_char(str[i], x, start_y, hex_color, scale); 
        x += (8 * scale); // New spacing for 8x8 font
    }
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

// ----------------------------------------------------
// DAY 139: THE GRADIENT & IMAGE ENGINE
// ----------------------------------------------------
void draw_gradient_wallpaper(int theme_idx) {
    for (int y = 0; y < 768; y++) {
        int r, g, b;
        if (theme_idx == 0) { r = 15; g = 23 + (y * 20 / 768); b = 42 + (y * 40 / 768); } // Mac Dark Mode Gradient
        else if (theme_idx == 1) { r = 240 - (y*20/768); g = 248; b = 255; } // Mac Light Mode Gradient
        else if (theme_idx == 2) { r = 10; g = 80 + (y*100/768); b = 150 + (y*50/768); } // Ocean Gradient
        else { r = 20; g = 60 + (y*80/768); b = 40 + (y*20/768); } // Forest Gradient
        
        unsigned int color = (r << 16) | (g << 8) | b;
        for (int x = 0; x < 1024; x++) {
            high_res_buffer[y * 1024 + x] = color;
        }
    }
}

// Future Image Engine Placeholder (RGB Array Support)
void draw_rgb_image(int start_x, int start_y, int w, int h, const unsigned int* img_data) {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            unsigned int color = img_data[(y * w) + x];
            if (color != 0xFF00FF) { // 0xFF00FF can be our transparent mask
                put_pixel_32(start_x + x, start_y + y, color);
            }
        }
    }
}

void draw_modern_taskbar(int h, int m, int active_app) {
    int tb_width = 800, tb_height = 50, tb_x = (1024 - tb_width) / 2, tb_y = 768 - tb_height - 10;  
    
    // Windows 11 style centered taskbar with alpha simulation
    draw_rounded_rect(tb_x + 2, tb_y + 4, tb_width, tb_height, 10, 0x00111111);
    draw_rounded_rect(tb_x, tb_y, tb_width, tb_height, 10, 0x00202020); // Sleek Dark Gray     
    
    draw_rounded_rect(tb_x + 20, tb_y + 10, 30, 30, 8, COLOR_ACCENT); draw_hd_string("M", tb_x + 26, tb_y + 18, COLOR_TEXT, 1);

    draw_rounded_rect(tb_x + 70, tb_y + 10, 30, 30, 8, 0x00FFB300); 
    draw_rounded_rect(tb_x + 120, tb_y + 10, 30, 30, 8, 0x004CAF50); 
    draw_rounded_rect(tb_x + 170, tb_y + 10, 30, 30, 8, 0x009C27B0); 
    draw_rounded_rect(tb_x + 220, tb_y + 10, 30, 30, 8, 0x00E53935); 
    draw_rounded_rect(tb_x + 270, tb_y + 10, 30, 30, 8, 0x002196F3); 
    draw_rounded_rect(tb_x + 320, tb_y + 10, 30, 30, 8, 0x009E9E9E); 

    if (active_app == 2) draw_rounded_rect(tb_x + 75, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 3) draw_rounded_rect(tb_x + 125, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 1) draw_rounded_rect(tb_x + 175, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 5) draw_rounded_rect(tb_x + 225, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 6) draw_rounded_rect(tb_x + 275, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 7) draw_rounded_rect(tb_x + 20, tb_y + 45, 30, 3, 1, 0xFFFFFF);
    if (active_app == 8) draw_rounded_rect(tb_x + 325, tb_y + 45, 20, 3, 1, 0xFFFFFF); 
    if (active_app == 9) draw_rounded_rect(tb_x + 20, tb_y + 45, 30, 3, 1, 0xFFFFFF); 
    if (active_app == 10) draw_rounded_rect(tb_x + 20, tb_y + 45, 30, 3, 1, 0xFFFFFF); 

    char time_str[6] = {'0','0',':','0','0','\0'};
    time_str[0] = (h / 10) + '0'; time_str[1] = (h % 10) + '0'; time_str[3] = (m / 10) + '0'; time_str[4] = (m % 10) + '0';
    draw_hd_string(time_str, tb_x + tb_width - 80, tb_y + 18, COLOR_TEXT, 2);
}

void draw_hd_window(int win_x, int win_y, int w, int h, char* title) {
    draw_rounded_rect(win_x + 5, win_y + 5, w, h, 10, 0x00111111); // Shadow
    draw_rounded_rect(win_x, win_y, w, h, 10, 0x002D2D30); // Lighter gray like VS Code
    draw_rounded_rect(win_x, win_y, w, 30, 10, 0x001E1E1E); // Darker title bar
    draw_hd_string(title, win_x + 15, win_y + 10, COLOR_TEXT, 1);
    draw_rounded_rect(win_x + w - 30, win_y + 8, 15, 15, 5, COLOR_DANGER);
}

char hd_term_history[8][50]; int hd_term_lines = 0;       
void hd_print(char* text) {
    if (hd_term_lines >= 8) {
        for (int i = 1; i < 8; i++) { int c = 0; while (hd_term_history[i][c] != '\0') { hd_term_history[i-1][c] = hd_term_history[i][c]; c++; } hd_term_history[i-1][c] = '\0'; }
        hd_term_lines = 7;
    }
    int c = 0; while (text[c] != '\0' && c < 49) { hd_term_history[hd_term_lines][c] = text[c]; c++; }
    hd_term_history[hd_term_lines][c] = '\0'; hd_term_lines++;
}

void hd_itoa(int n, char* buf) {
    int i = 0, j = 0, temp = n;
    if (n == 0) { buf[0] = '0'; buf[1] = '\0'; return; }
    while (temp > 0) { buf[i++] = (temp % 10) + '0'; temp /= 10; } buf[i] = '\0';
    for(j = 0; j < i/2; j++) { char t = buf[j]; buf[j] = buf[i - 1 - j]; buf[i - 1 - j] = t; }
}

unsigned int hd_paint_canvas[260 * 200];
int paint_init = 0;

void render_desktop_bg(int mx, int my, int app_state, int win_x, int win_y, char* term_buffer, int h, int m, int start_menu, unsigned int used_ram, int ctx_open, int ctx_x, int ctx_y, int is_minimized, char* calc_display, int theme_idx, int* game_board, int game_winner, int is_screensaver, int ss_x, int ss_y, int* icon_x, int* icon_y, char* pwd_buffer) {
    
    if (is_screensaver) {
        for (int i = 0; i < (1024 * 768); i++) high_res_buffer[i] = 0x000000;
        draw_hd_string("MICRO OS", ss_x, ss_y, COLOR_ACCENT, 3);
        swap_buffers_32();
        return; 
    }

    if (app_state == -1) {
        draw_gradient_wallpaper(theme_idx); // Lock screen par bhi mast wallpaper!
        char time_str[6] = {'0','0',':','0','0','\0'}; time_str[0] = (h / 10) + '0'; time_str[1] = (h % 10) + '0'; time_str[3] = (m / 10) + '0'; time_str[4] = (m % 10) + '0';
        draw_hd_string(time_str, 380, 150, 0xFFFFFF, 6); 
        draw_rounded_rect(412, 300, 200, 250, 10, 0x001E293B); draw_rounded_rect(462, 330, 100, 100, 20, 0x003B82F6); 
        draw_hd_string("A", 500, 360, 0xFFFFFF, 4); draw_hd_string("Abhikash", 455, 450, 0xFFFFFF, 1);
        draw_rounded_rect(430, 490, 160, 35, 5, 0x000F172A); 
        int p_len = 0; while(pwd_buffer[p_len]) p_len++;
        if (p_len == 0) draw_hd_string("Enter PIN", 460, 500, 0x00475569, 1); else for(int i=0; i<p_len; i++) draw_hd_string("*", 460 + (i*15), 505, 0xFFFFFF, 1);
        draw_hd_mouse_pointer(mx, my); swap_buffers_32(); return;
    }

    // DAY 139: RENDER SMOOTH GRADIENT WALLPAPER
    draw_gradient_wallpaper(theme_idx);
    
    // Desktop Icons
    draw_rounded_rect(icon_x[0], icon_y[0], 40, 40, 5, 0x00FFB300); draw_hd_string("My PC", icon_x[0]-5, icon_y[0]+45, 0xFFFFFF, 1);
    draw_rounded_rect(icon_x[1], icon_y[1], 40, 40, 5, 0x004CAF50); draw_hd_string("Notes", icon_x[1]-5, icon_y[1]+45, 0xFFFFFF, 1);
    draw_rounded_rect(icon_x[2], icon_y[2], 40, 40, 5, 0x00E53935); draw_hd_string("Calc", icon_x[2]-2, icon_y[2]+45, 0xFFFFFF, 1);
    draw_rounded_rect(icon_x[3], icon_y[3], 40, 40, 5, 0x002196F3); draw_hd_string("Game", icon_x[3]-2, icon_y[3]+45, 0xFFFFFF, 1);
    draw_rounded_rect(icon_x[4], icon_y[4], 40, 40, 5, 0x009E9E9E); draw_hd_string("Sets", icon_x[4]-2, icon_y[4]+45, 0xFFFFFF, 1);
    draw_rounded_rect(icon_x[5], icon_y[5], 40, 40, 5, 0x009C27B0); draw_hd_string("Piano", icon_x[5]-5, icon_y[5]+45, 0xFFFFFF, 1);

    draw_modern_taskbar(h, m, app_state);
    
    if (app_state > 0 && !is_minimized) {
        if (app_state == 1) { 
            draw_hd_window(win_x, win_y, 420, 300, "Terminal - Root");
            for(int i = 0; i < hd_term_lines; i++) draw_hd_string(hd_term_history[i], win_x + 15, win_y + 40 + (i * 20), COLOR_TEXT, 1);
            int current_y = win_y + 40 + (hd_term_lines * 20);
            draw_hd_string("root@microos:~# ", win_x + 15, current_y, 0x004CAF50, 1); draw_hd_string(term_buffer, win_x + 155, current_y, COLOR_TEXT, 1);
        } 
        else if (app_state == 2) { 
            draw_hd_window(win_x, win_y, 400, 300, "File Explorer");
            char count_str[5]; hd_itoa(file_count, count_str);
            draw_hd_string("Virtual Disk (Total Files: ", win_x + 20, win_y + 50, COLOR_TEXT, 1); draw_hd_string(count_str, win_x + 250, win_y + 50, COLOR_ACCENT, 1); draw_hd_string(")", win_x + 270, win_y + 50, COLOR_TEXT, 1);
            for(int f = 0; f < file_count && f < 5; f++) {
                draw_rounded_rect(win_x + 20, win_y + 80 + (f * 40), 30, 30, 5, 0x00FFB300); draw_hd_string(file_system[f].name, win_x + 60, win_y + 90 + (f * 40), COLOR_TEXT, 1);
            }
        }
        else if (app_state == 3) { 
            draw_hd_window(win_x, win_y, 400, 300, "System Monitor");
            draw_hd_string("Micro OS Performance", win_x + 20, win_y + 50, COLOR_ACCENT, 1); draw_hd_string("RAM Usage:", win_x + 20, win_y + 90, COLOR_TEXT, 1);
            char ram_str[15]; hd_itoa(used_ram, ram_str);
            draw_hd_string(ram_str, win_x + 20, win_y + 120, 0x004CAF50, 1); draw_hd_string(" Bytes", win_x + 100, win_y + 120, COLOR_TEXT, 1);
            draw_rounded_rect(win_x + 20, win_y + 150, 300, 20, 5, 0x00111111); draw_rounded_rect(win_x + 20, win_y + 150, (used_ram / 500) + 10, 20, 5, 0x004CAF50); 
        }
        else if (app_state == 4) { 
            draw_hd_window(win_x, win_y, 400, 300, "HD Notepad");
            draw_hd_string("Type your notes below:", win_x + 20, win_y + 50, COLOR_ACCENT, 1); draw_hd_string(term_buffer, win_x + 20, win_y + 90, COLOR_TEXT, 1);
            draw_rounded_rect(win_x + 280, win_y + 45, 45, 25, 5, 0x004CAF50); draw_hd_string("SAVE", win_x + 285, win_y + 53, 0xFFFFFF, 1);
            draw_rounded_rect(win_x + 335, win_y + 45, 45, 25, 5, 0x00FFB300); draw_hd_string("LOAD", win_x + 340, win_y + 53, 0xFFFFFF, 1);
        }
        else if (app_state == 5) { 
            draw_hd_window(win_x, win_y, 300, 360, "Calculator");
            draw_rounded_rect(win_x + 20, win_y + 45, 260, 50, 5, 0x00111111);
            int len = 0; while(calc_display[len]) len++; draw_hd_string(calc_display, win_x + 260 - (len * 16), win_y + 55, COLOR_TEXT, 2);
            char* keys = "789/456*123-C0=+";
            for(int i=0; i<4; i++) { for(int j=0; j<4; j++) { int bx = win_x + 20 + (j * 65); int by = win_y + 105 + (i * 60); draw_rounded_rect(bx, by, 55, 50, 5, 0x00333333); char lbl[2] = {keys[(i*4)+j], '\0'}; draw_hd_string(lbl, bx + 22, by + 20, COLOR_TEXT, 1); } }
        }
        else if (app_state == 6) { 
            draw_hd_window(win_x, win_y, 300, 360, "Tic-Tac-Toe");
            draw_rounded_rect(win_x+105, win_y+50, 5, 280, 2, 0x00555555); draw_rounded_rect(win_x+190, win_y+50, 5, 280, 2, 0x00555555); draw_rounded_rect(win_x+20, win_y+135, 260, 5, 2, 0x00555555); draw_rounded_rect(win_x+20, win_y+235, 260, 5, 2, 0x00555555);
            for(int i=0; i<3; i++) { for(int j=0; j<3; j++) { int cell = game_board[i*3 + j]; int cx = win_x + 40 + (j*85); int cy = win_y + 70 + (i*100); if (cell == 1) draw_hd_string("X", cx, cy, 0x00E53935, 4); if (cell == 2) draw_hd_string("O", cx, cy, 0x002196F3, 4); } }
            if (game_winner != 0) { draw_rounded_rect(win_x + 50, win_y + 150, 200, 60, 10, 0x00111111); if (game_winner == 1) draw_hd_string("P1 WINS!", win_x + 75, win_y + 170, 0x00E53935, 1); else if (game_winner == 2) draw_hd_string("P2 WINS!", win_x + 75, win_y + 170, 0x002196F3, 1); else draw_hd_string(" DRAW! ", win_x + 85, win_y + 170, 0xFFFFFF, 1); }
        }
        else if (app_state == 7) { 
            draw_hd_window(win_x, win_y, 300, 320, "HD Paint");
            if (!paint_init) { for(int i=0; i<260*200; i++) hd_paint_canvas[i] = 0xFFFFFF; paint_init = 1; }
            for(int py=0; py<200; py++) { for(int px=0; px<260; px++) { int screen_pos = ((win_y + 40 + py) * 1024) + (win_x + 20 + px); high_res_buffer[screen_pos] = hd_paint_canvas[(py * 260) + px]; } }
            draw_rounded_rect(win_x + 20, win_y + 260, 30, 30, 5, 0x00E53935); draw_rounded_rect(win_x + 60, win_y + 260, 30, 30, 5, 0x004CAF50); draw_rounded_rect(win_x + 100, win_y + 260, 30, 30, 5, 0x002196F3); draw_rounded_rect(win_x + 140, win_y + 260, 30, 30, 5, 0x00000000); draw_rounded_rect(win_x + 180, win_y + 260, 30, 30, 5, 0xFFFFFFFF); 
            draw_rounded_rect(win_x + 225, win_y + 260, 45, 30, 5, 0x00FFB300); draw_hd_string("Save", win_x + 230, win_y + 270, 0x000000, 1);
        }
        else if (app_state == 8) {
            draw_hd_window(win_x, win_y, 300, 200, "Settings");
            draw_hd_string("Personalize Theme:", win_x+20, win_y+50, COLOR_TEXT, 1);
            draw_rounded_rect(win_x+20, win_y+90, 50, 50, 5, 0x001E1E2E); draw_rounded_rect(win_x+85, win_y+90, 50, 50, 5, 0x00F8F9FA); draw_rounded_rect(win_x+150, win_y+90, 50, 50, 5, 0x000F4C75); draw_rounded_rect(win_x+215, win_y+90, 50, 50, 5, 0x001B4332); 
        }
        else if (app_state == 9) {
            draw_hd_window(win_x, win_y, 350, 230, "Mini Piano");
            for(int i=0; i<7; i++) draw_rounded_rect(win_x + 20 + (i*42), win_y + 50, 40, 140, 5, 0xFFFFFF); 
            for(int i=0; i<6; i++) { if (i == 2) continue; draw_rounded_rect(win_x + 45 + (i*42), win_y + 50, 28, 80, 3, 0x000000); }
            draw_hd_string("Click keys to play!", win_x + 80, win_y + 200, COLOR_ACCENT, 1);
        }
        else if (app_state == 10) {
            draw_hd_window(win_x, win_y, 300, 280, "Image Gallery");
            draw_rounded_rect(win_x + 20, win_y + 50, 260, 200, 5, 0x000000); 
            for(int py=0; py<200; py++) { for(int px=0; px<260; px++) { int screen_pos = ((win_y + 50 + py) * 1024) + (win_x + 20 + px); high_res_buffer[screen_pos] = hd_paint_canvas[(py * 260) + px]; } }
        }
    }

    if (start_menu) {
        int sm_w = 220, sm_h = 300, sm_x = 120, sm_y = 708 - sm_h - 10;
        draw_rounded_rect(sm_x + 5, sm_y + 5, sm_w, sm_h, 10, 0x00111111); draw_rounded_rect(sm_x, sm_y, sm_w, sm_h, 10, 0x00252526);
        draw_hd_string("Micro OS v3.0", sm_x + 20, sm_y + 20, COLOR_ACCENT, 1); draw_rounded_rect(sm_x + 20, sm_y + 50, sm_w - 40, 2, 0, 0x00444444); 
        draw_hd_string("> Notepad", sm_x + 20, sm_y + 70, COLOR_TEXT, 1); draw_hd_string("> Calculator", sm_x + 20, sm_y + 100, COLOR_TEXT, 1); draw_hd_string("> Tic-Tac-Toe", sm_x + 20, sm_y + 130, COLOR_TEXT, 1); draw_hd_string("> Settings", sm_x + 20, sm_y + 160, 0x002196F3, 1); draw_hd_string("> HD Paint", sm_x + 20, sm_y + 190, 0x00E53935, 1);
        draw_rounded_rect(sm_x + 20, sm_y + 240, sm_w - 40, 40, 5, COLOR_DANGER); draw_hd_string("SHUT DOWN", sm_x + 65, sm_y + 252, COLOR_TEXT, 1);
    }

    if (ctx_open) {
        draw_rounded_rect(ctx_x + 5, ctx_y + 5, 160, 85, 5, 0x00111111); draw_rounded_rect(ctx_x, ctx_y, 160, 85, 5, 0x002D2D30);         
        draw_hd_string("> Refresh", ctx_x + 15, ctx_y + 15, COLOR_TEXT, 1); draw_hd_string("> Terminal", ctx_x + 15, ctx_y + 50, COLOR_TEXT, 1); 
    }
    draw_hd_mouse_pointer(mx, my); swap_buffers_32();
}
#endif