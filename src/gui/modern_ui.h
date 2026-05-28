#ifndef MODERN_UI_H
#define MODERN_UI_H

#include "vesa.h"

const unsigned char modern_font[91][8] = {
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, {0x18,0x3C,0x3C,0x18,0x18,0x00,0x18,0x00}, {0x6C,0x6C,0x6C,0x00,0x00,0x00,0x00,0x00}, {0x6C,0x6C,0xFE,0x6C,0xFE,0x6C,0x6C,0x00}, {0x18,0x7E,0xC0,0x7C,0x06,0xFC,0x18,0x00}, {0x00,0xC6,0xCC,0x18,0x30,0x66,0xC6,0x00}, {0x38,0x6C,0x38,0x76,0xDC,0xCC,0x76,0x00}, {0x30,0x30,0x60,0x00,0x00,0x00,0x00,0x00}, {0x18,0x30,0x60,0x60,0x60,0x30,0x18,0x00}, {0x60,0x30,0x18,0x18,0x18,0x30,0x60,0x00}, {0x00,0x66,0x3C,0xFF,0x3C,0x66,0x00,0x00}, {0x00,0x18,0x18,0x7E,0x18,0x18,0x00,0x00}, {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x30}, {0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00}, {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00}, {0x06,0x0C,0x18,0x30,0x60,0xC0,0x80,0x00}, {0x7C,0xC6,0xCE,0xDE,0xF6,0xE6,0x7C,0x00}, {0x30,0x70,0x30,0x30,0x30,0x30,0xFC,0x00}, {0x78,0xCC,0x0C,0x38,0x60,0xCC,0xFC,0x00}, {0x78,0xCC,0x0C,0x38,0x0C,0xCC,0x78,0x00}, {0x1C,0x3C,0x6C,0xCC,0xFE,0x0C,0x1E,0x00}, {0xFC,0xC0,0xF8,0x0C,0x0C,0xCC,0x78,0x00}, {0x38,0x60,0xC0,0xF8,0xCC,0xCC,0x78,0x00}, {0xFC,0xCC,0x0C,0x18,0x30,0x30,0x30,0x00}, {0x78,0xCC,0xCC,0x78,0xCC,0xCC,0x78,0x00}, {0x78,0xCC,0xCC,0x7C,0x0C,0x18,0x70,0x00}, {0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x00}, {0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x30}, {0x18,0x30,0x60,0xC0,0x60,0x30,0x18,0x00}, {0x00,0x00,0x7E,0x00,0x7E,0x00,0x00,0x00}, {0x60,0x30,0x18,0x0C,0x18,0x30,0x60,0x00}, {0x3C,0x66,0x0C,0x18,0x18,0x00,0x18,0x00}, {0x7C,0xC6,0xDE,0xDE,0xDC,0xC0,0x7C,0x00}, {0x38,0x6C,0xC6,0xFE,0xC6,0xC6,0xC6,0x00}, {0xFC,0x66,0x66,0x7C,0x66,0x66,0xFC,0x00}, {0x3C,0x66,0xC0,0xC0,0xC0,0x66,0x3C,0x00}, {0xF8,0x6C,0x66,0x66,0x66,0x6C,0xF8,0x00}, {0xFE,0x62,0x68,0x78,0x68,0x62,0xFE,0x00}, {0xFE,0x62,0x68,0x78,0x68,0x60,0xF0,0x00}, {0x3C,0x66,0xC0,0xCE,0xC6,0x66,0x3E,0x00}, {0xC6,0xC6,0xC6,0xFE,0xC6,0xC6,0xC6,0x00}, {0x3C,0x18,0x18,0x18,0x18,0x18,0x3C,0x00}, {0x1E,0x0C,0x0C,0x0C,0xCC,0xCC,0x78,0x00}, {0xE6,0x66,0x6C,0x78,0x6C,0x66,0xE6,0x00}, {0xF0,0x60,0x60,0x60,0x62,0x66,0xFE,0x00}, {0xC6,0xEE,0xFE,0xFE,0xD6,0xC6,0xC6,0x00}, {0xC6,0xE6,0xF6,0xDE,0xCE,0xC6,0xC6,0x00}, {0x38,0x6C,0xC6,0xC6,0xC6,0x6C,0x38,0x00}, {0xFC,0x66,0x66,0x7C,0x60,0x60,0xF0,0x00}, {0x7C,0xC6,0xC6,0xC6,0xD6,0x7C,0x0E,0x00}, {0xFC,0x66,0x66,0x7C,0x6C,0x66,0xE6,0x00}, {0x7C,0xC6,0xE0,0x78,0x0E,0xC6,0x3E,0x00}, {0xFC,0xB4,0x30,0x30,0x30,0x30,0x78,0x00}, {0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00}, {0xC6,0xC6,0xC6,0xC6,0xC6,0x6C,0x38,0x00}, {0xC6,0xC6,0xC6,0xD6,0xFE,0xEE,0xC6,0x00}, {0xC6,0xC6,0x6C,0x38,0x6C,0xC6,0xC6,0x00}, {0x66,0x66,0x66,0x3C,0x18,0x18,0x3C,0x00}, {0xFE,0x86,0x0C,0x18,0x30,0x61,0xFE,0x00}, {0x3C,0x30,0x30,0x30,0x30,0x30,0x3C,0x00}, {0x00,0x80,0xC0,0x60,0x30,0x18,0x0C,0x06}, {0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C,0x00}, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, {0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00}, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, {0x00,0x00,0x78,0x0C,0x7C,0xCC,0x76,0x00}, {0xE0,0x60,0x60,0x7C,0x66,0x66,0xDC,0x00}, {0x00,0x00,0x78,0xCC,0xC0,0xCC,0x78,0x00}, {0x1C,0x0C,0x0C,0x7C,0xCC,0xCC,0x76,0x00}, {0x00,0x00,0x78,0xCC,0xFC,0xC0,0x78,0x00}, {0x38,0x6C,0x60,0xF0,0x60,0x60,0xF0,0x00}, {0x00,0x00,0x76,0xCC,0xCC,0x7C,0x0C,0xF8}, {0xE0,0x60,0x6C,0x76,0x66,0x66,0xE6,0x00}, {0x18,0x00,0x38,0x18,0x18,0x18,0x3C,0x00}, {0x06,0x00,0x06,0x06,0x06,0x06,0x06,0x3C}, {0xE0,0x60,0x66,0x6C,0x78,0x6C,0xE6,0x00}, {0x38,0x18,0x18,0x18,0x18,0x18,0x3C,0x00}, {0x00,0x00,0xEC,0xFE,0xD6,0xD6,0xD6,0x00}, {0x00,0x00,0xDC,0x66,0x66,0x66,0x66,0x00}, {0x00,0x00,0x78,0xCC,0xCC,0xCC,0x78,0x00}, {0x00,0x00,0xDC,0x66,0x66,0x7C,0x60,0xF0}, {0x00,0x00,0x76,0xCC,0xCC,0x7C,0x0C,0x1E}, {0x00,0x00,0xDC,0x76,0x60,0x60,0xF0,0x00}, {0x00,0x00,0x7C,0xC0,0x78,0x0C,0xF8,0x00}, {0x10,0x30,0x7C,0x30,0x30,0x34,0x18,0x00}, {0x00,0x00,0xCC,0xCC,0xCC,0xCC,0x76,0x00}, {0x00,0x00,0xCC,0xCC,0xCC,0x78,0x30,0x00}, {0x00,0x00,0xC6,0xD6,0xFE,0xFE,0x6C,0x00}, {0x00,0x00,0xC6,0x6C,0x38,0x6C,0xC6,0x00}, {0x00,0x00,0xCC,0xCC,0xCC,0x7C,0x0C,0xF8}, {0x00,0x00,0xFC,0x98,0x30,0x64,0xFC,0x00}  
};

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
    int x = start_x; for(int i = 0; str[i] != '\0'; i++) { draw_scaled_char(str[i], x, start_y, hex_color, scale); x += (8 * scale); }
}
void draw_hd_mouse_pointer(int x, int y) {
    if (x < 0 || x > 1000 || y < 0 || y > 750) return;
    for(int i = 0; i < 15; i++) { for(int j = 0; j <= i/1.5; j++) { if (j == 0 || j == (int)(i/1.5) || i == 14) put_pixel_32(x + j, y + i, 0x000000); else put_pixel_32(x + j, y + i, 0xFFFFFF); } }
}

void draw_app_icon(int x, int y, int type) {
    draw_rounded_rect(x+2, y+2, 40, 40, 8, 0x00111111); // Shadow
    if (type == 0) { draw_rounded_rect(x, y+5, 40, 30, 4, 0x00E65100); draw_rounded_rect(x, y+10, 40, 25, 4, 0x00FFB300); draw_rounded_rect(x+5, y+5, 15, 10, 2, 0x00FFB300); } 
    else if (type == 1) { draw_rounded_rect(x+5, y, 30, 40, 3, 0x00FFFFFF); draw_rounded_rect(x+5, y, 30, 10, 3, 0x004CAF50); draw_rounded_rect(x+10, y+15, 20, 2, 0, 0x00E0E0E0); draw_rounded_rect(x+10, y+23, 20, 2, 0, 0x00E0E0E0); draw_rounded_rect(x+10, y+31, 15, 2, 0, 0x00E0E0E0); } 
    else if (type == 2) { draw_rounded_rect(x, y, 40, 40, 8, 0x00263238); draw_rounded_rect(x+5, y+5, 30, 10, 2, 0x0081C784); draw_rounded_rect(x+6, y+20, 7, 7, 2, 0x00E53935); draw_rounded_rect(x+16, y+20, 7, 7, 2, 0x00B0BEC5); draw_rounded_rect(x+26, y+20, 7, 7, 2, 0x00B0BEC5); draw_rounded_rect(x+6, y+29, 7, 7, 2, 0x00B0BEC5); draw_rounded_rect(x+16, y+29, 7, 7, 2, 0x00B0BEC5); draw_rounded_rect(x+26, y+29, 7, 7, 2, 0x002196F3); } 
    else if (type == 3) { draw_rounded_rect(x, y, 40, 40, 8, 0x002196F3); draw_rounded_rect(x+6, y+16, 12, 4, 1, 0x00FFFFFF); draw_rounded_rect(x+10, y+12, 4, 12, 1, 0x00FFFFFF); draw_rounded_rect(x+22, y+18, 6, 6, 3, 0x00E53935); draw_rounded_rect(x+30, y+12, 6, 6, 3, 0x00FFEB3B); } 
    else if (type == 4) { draw_rounded_rect(x, y, 40, 40, 8, 0x0078909C); draw_rounded_rect(x+10, y+10, 20, 20, 10, 0x0037474F); draw_rounded_rect(x+15, y+15, 10, 10, 5, 0x0078909C); } 
    else if (type == 5) { draw_rounded_rect(x, y, 40, 40, 5, 0x009C27B0); draw_rounded_rect(x+4, y+10, 8, 20, 1, 0x00FFFFFF); draw_rounded_rect(x+16, y+10, 8, 20, 1, 0x00FFFFFF); draw_rounded_rect(x+28, y+10, 8, 20, 1, 0x00FFFFFF); draw_rounded_rect(x+10, y+10, 6, 10, 1, 0x00000000); draw_rounded_rect(x+22, y+10, 6, 10, 1, 0x00000000); }
    else if (type == 6) { draw_rounded_rect(x, y, 40, 40, 8, 0x001E1E1E); draw_rounded_rect(x+6, y+20, 6, 15, 1, 0x004CAF50); draw_rounded_rect(x+16, y+10, 6, 25, 1, 0x004CAF50); draw_rounded_rect(x+26, y+15, 6, 20, 1, 0x004CAF50); }
    else if (type == 7) { draw_rounded_rect(x, y, 40, 40, 8, 0x00000000); draw_hd_string(">_", x+8, y+12, 0x004CAF50, 1); }
}

void draw_gradient_wallpaper(int theme_idx) {
    for (int y = 0; y < 768; y++) {
        int r, g, b;
        if (theme_idx == 0) { r = 15; g = 23 + (y * 20 / 768); b = 42 + (y * 40 / 768); } else if (theme_idx == 1) { r = 240 - (y*20/768); g = 248; b = 255; } else if (theme_idx == 2) { r = 10; g = 80 + (y*100/768); b = 150 + (y*50/768); } else { r = 20; g = 60 + (y*80/768); b = 40 + (y*20/768); } 
        unsigned int color = (r << 16) | (g << 8) | b; for (int x = 0; x < 1024; x++) high_res_buffer[y * 1024 + x] = color;
    }
}

// ----------------------------------------------------
// DAY 144: THE MAC-STYLE FLOATING DOCK
// ----------------------------------------------------
void draw_modern_taskbar(int h, int m, int active_app) {
    int tb_width = 420, tb_height = 50, tb_x = (1024 - tb_width) / 2, tb_y = 768 - tb_height - 15;  
    
    // Transparent Floating Dock
    draw_rounded_rect(tb_x + 2, tb_y + 4, tb_width, tb_height, 15, 0x00111111);
    draw_rounded_rect(tb_x, tb_y, tb_width, tb_height, 15, 0x002D2D30);      
    draw_rounded_rect(tb_x + 20, tb_y + 10, 30, 30, 8, COLOR_ACCENT); draw_hd_string("M", tb_x + 26, tb_y + 18, COLOR_TEXT, 1);

    draw_app_icon(tb_x + 70, tb_y + 5, 0); draw_app_icon(tb_x + 120, tb_y + 5, 6); draw_app_icon(tb_x + 170, tb_y + 5, 7); 
    draw_app_icon(tb_x + 220, tb_y + 5, 2); draw_app_icon(tb_x + 270, tb_y + 5, 3); draw_app_icon(tb_x + 320, tb_y + 5, 4); 

    if (active_app == 2) draw_rounded_rect(tb_x + 80, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 3) draw_rounded_rect(tb_x + 130, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 1) draw_rounded_rect(tb_x + 180, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 5) draw_rounded_rect(tb_x + 230, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 6) draw_rounded_rect(tb_x + 280, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 8) draw_rounded_rect(tb_x + 330, tb_y + 45, 20, 3, 1, 0xFFFFFF); 

    // DAY 144: TOP RIGHT CLOCK & STATUS BAR
    draw_rounded_rect(800, 10, 200, 30, 10, 0x00111111);
    draw_rounded_rect(800, 10, 200, 30, 10, 0x002D2D30);
    char time_str[6] = {'0','0',':','0','0','\0'};
    time_str[0] = (h / 10) + '0'; time_str[1] = (h % 10) + '0'; time_str[3] = (m / 10) + '0'; time_str[4] = (m % 10) + '0';
    draw_hd_string(time_str, 930, 18, COLOR_TEXT, 1);
    // Fake icons for Wifi/Battery
    draw_hd_string("W", 840, 18, 0x004CAF50, 1); draw_hd_string("B", 880, 18, 0x002196F3, 1);
}

void draw_hd_window(int win_x, int win_y, int w, int h, char* title) {
    draw_rounded_rect(win_x + 5, win_y + 5, w, h, 10, 0x00111111); draw_rounded_rect(win_x, win_y, w, h, 10, 0x002D2D30); draw_rounded_rect(win_x, win_y, w, 30, 10, 0x001E1E1E); 
    draw_hd_string(title, win_x + 15, win_y + 10, COLOR_TEXT, 1); draw_rounded_rect(win_x + w - 30, win_y + 8, 15, 15, 5, COLOR_DANGER);
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

void render_desktop_bg(int mx, int my, int app_state, int win_x, int win_y, char* term_buffer, int h, int m, int start_menu, unsigned int used_ram, int ctx_open, int ctx_x, int ctx_y, int is_minimized, char* calc_display, int theme_idx, int* game_board, int game_winner, int is_screensaver, int ss_x, int ss_y, int* icon_x, int* icon_y, char* pwd_buffer, int uptime, int action_center_open, int ind_loading) {
    
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

    draw_modern_taskbar(h, m, app_state);
    
    if (app_state > 0 && !is_minimized) {
        if (app_state == 1) { 
            draw_hd_window(win_x, win_y, 420, 300, "Terminal - Root");
            for(int i = 0; i < hd_term_lines; i++) draw_hd_string(hd_term_history[i], win_x + 15, win_y + 40 + (i * 20), COLOR_TEXT, 1);
            int current_y = win_y + 40 + (hd_term_lines * 20);
            draw_hd_string("root@microos:~# ", win_x + 15, current_y, 0x004CAF50, 1); draw_hd_string(term_buffer, win_x + 155, current_y, COLOR_TEXT, 1);
            
            // DAY 145: .IND EXECUTION BRIDGE UI (Fake loading bar)
            if (ind_loading > 0) {
                draw_rounded_rect(win_x + 50, win_y + 120, 320, 60, 5, 0x00111111);
                draw_hd_string("Compiling .ind to Runtime...", win_x + 70, win_y + 135, 0xFFFFFF, 1);
                draw_rounded_rect(win_x + 70, win_y + 160, 280, 10, 5, 0x00333333);
                draw_rounded_rect(win_x + 70, win_y + 160, ind_loading * 2, 10, 5, 0x004CAF50);
            }
        } 
        else if (app_state == 2) { 
            draw_hd_window(win_x, win_y, 400, 300, "File Explorer");
            char count_str[5]; hd_itoa(file_count, count_str);
            draw_hd_string("Virtual Disk (Total Files: ", win_x + 20, win_y + 50, COLOR_TEXT, 1); draw_hd_string(count_str, win_x + 250, win_y + 50, COLOR_ACCENT, 1); draw_hd_string(")", win_x + 270, win_y + 50, COLOR_TEXT, 1);
            for(int f = 0; f < file_count && f < 5; f++) { draw_app_icon(win_x + 20, win_y + 80 + (f * 45), 1); draw_hd_string(file_system[f].name, win_x + 70, win_y + 95 + (f * 45), COLOR_TEXT, 1); }
        }
        else if (app_state == 3) { 
            draw_hd_window(win_x, win_y, 450, 320, "Task Manager");
            draw_hd_string("CPU Performance (Simulated)", win_x + 20, win_y + 50, COLOR_TEXT, 1); draw_rounded_rect(win_x + 20, win_y + 70, 410, 80, 5, 0x00111111); for(int i=0; i<400; i+=10) draw_rounded_rect(win_x+25+i, win_y+140 - (i%40), 5, (i%40)+5, 2, 0x004CAF50);
            draw_hd_string("Memory (RAM)", win_x + 20, win_y + 170, COLOR_TEXT, 1); char ram_str[15]; hd_itoa(used_ram/1024, ram_str); draw_hd_string(ram_str, win_x + 20, win_y + 190, 0x002196F3, 2); draw_hd_string(" KB In Use", win_x + 140, win_y + 195, COLOR_TEXT, 1);
            draw_rounded_rect(win_x + 20, win_y + 230, 410, 20, 10, 0x00111111); int ram_bar = (used_ram / 500); if(ram_bar > 410) ram_bar = 410; draw_rounded_rect(win_x + 20, win_y + 230, ram_bar, 20, 10, 0x002196F3);
            draw_hd_string("System Uptime:", win_x + 20, win_y + 270, COLOR_TEXT, 1); char up_str[10]; hd_itoa(uptime, up_str); draw_hd_string(up_str, win_x + 130, win_y + 270, COLOR_ACCENT, 1); draw_hd_string("secs", win_x + 180, win_y + 270, COLOR_TEXT, 1);
        }
        else if (app_state == 4) { 
            draw_hd_window(win_x, win_y, 400, 300, "HD Notepad");
            draw_hd_string("Type your notes below:", win_x + 20, win_y + 50, COLOR_ACCENT, 1); draw_hd_string(term_buffer, win_x + 20, win_y + 90, COLOR_TEXT, 1);
            draw_rounded_rect(win_x + 280, win_y + 45, 45, 25, 5, 0x004CAF50); draw_hd_string("SAVE", win_x + 285, win_y + 53, 0xFFFFFF, 1);
            draw_rounded_rect(win_x + 335, win_y + 45, 45, 25, 5, 0x00FFB300); draw_hd_string("LOAD", win_x + 340, win_y + 53, 0xFFFFFF, 1);
        }
        else if (app_state == 5) { 
            draw_hd_window(win_x, win_y, 300, 360, "Calculator");
            draw_rounded_rect(win_x + 20, win_y + 45, 260, 50, 5, 0x00111111); int len = 0; while(calc_display[len]) len++; draw_hd_string(calc_display, win_x + 260 - (len * 16), win_y + 55, COLOR_TEXT, 2);
            char* keys = "789/456*123-C0=+"; for(int i=0; i<4; i++) { for(int j=0; j<4; j++) { int bx = win_x + 20 + (j * 65); int by = win_y + 105 + (i * 60); draw_rounded_rect(bx, by, 55, 50, 5, 0x00333333); char lbl[2] = {keys[(i*4)+j], '\0'}; draw_hd_string(lbl, bx + 22, by + 20, COLOR_TEXT, 1); } }
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
            draw_hd_window(win_x, win_y, 300, 200, "Settings"); draw_hd_string("Personalize Theme:", win_x+20, win_y+50, COLOR_TEXT, 1);
            draw_rounded_rect(win_x+20, win_y+90, 50, 50, 5, 0x001E1E2E); draw_rounded_rect(win_x+85, win_y+90, 50, 50, 5, 0x00F8F9FA); draw_rounded_rect(win_x+150, win_y+90, 50, 50, 5, 0x000F4C75); draw_rounded_rect(win_x+215, win_y+90, 50, 50, 5, 0x001B4332); 
        }
        else if (app_state == 9) {
            draw_hd_window(win_x, win_y, 350, 230, "Mini Piano");
            for(int i=0; i<7; i++) draw_rounded_rect(win_x + 20 + (i*42), win_y + 50, 40, 140, 5, 0xFFFFFF); for(int i=0; i<6; i++) { if (i == 2) continue; draw_rounded_rect(win_x + 45 + (i*42), win_y + 50, 28, 80, 3, 0x000000); } draw_hd_string("Click keys to play!", win_x + 80, win_y + 200, COLOR_ACCENT, 1);
        }
        else if (app_state == 10) {
            draw_hd_window(win_x, win_y, 300, 280, "Image Gallery"); draw_rounded_rect(win_x + 20, win_y + 50, 260, 200, 5, 0x000000); 
            for(int py=0; py<200; py++) { for(int px=0; px<260; px++) { int screen_pos = ((win_y + 50 + py) * 1024) + (win_x + 20 + px); high_res_buffer[screen_pos] = hd_paint_canvas[(py * 260) + px]; } }
        }
    }

    if (start_menu) {
        int sm_w = 240, sm_h = 320, sm_x = 312, sm_y = 708 - sm_h - 10; // Aligned with new Dock
        draw_rounded_rect(sm_x + 5, sm_y + 5, sm_w, sm_h, 10, 0x00111111); draw_rounded_rect(sm_x, sm_y, sm_w, sm_h, 10, 0x00252526);
        draw_rounded_rect(sm_x+20, sm_y+20, 30, 30, 15, COLOR_ACCENT); draw_hd_string("Micro OS", sm_x + 60, sm_y + 28, 0xFFFFFF, 1); draw_rounded_rect(sm_x + 20, sm_y + 60, sm_w - 40, 2, 0, 0x00444444); 
        draw_rounded_rect(sm_x+20, sm_y+80, 15, 15, 3, 0x004CAF50); draw_hd_string("Notepad", sm_x + 45, sm_y + 83, COLOR_TEXT, 1); draw_rounded_rect(sm_x+20, sm_y+115, 15, 15, 3, 0x00E53935); draw_hd_string("Calculator", sm_x + 45, sm_y + 118, COLOR_TEXT, 1); draw_rounded_rect(sm_x+20, sm_y+150, 15, 15, 3, 0x002196F3); draw_hd_string("Tic-Tac-Toe", sm_x + 45, sm_y + 153, COLOR_TEXT, 1); draw_rounded_rect(sm_x+20, sm_y+185, 15, 15, 3, 0x009E9E9E); draw_hd_string("Settings", sm_x + 45, sm_y + 188, COLOR_TEXT, 1); draw_rounded_rect(sm_x+20, sm_y+220, 15, 15, 3, 0x00FFB300); draw_hd_string("HD Paint", sm_x + 45, sm_y + 223, COLOR_TEXT, 1);
        draw_rounded_rect(sm_x + 20, sm_y + 265, sm_w - 40, 35, 5, COLOR_DANGER); draw_hd_string("O", sm_x + 60, sm_y + 276, 0xFFFFFF, 1); draw_hd_string("|", sm_x + 63, sm_y + 272, 0xFFFFFF, 1); draw_hd_string("SHUT DOWN", sm_x + 85, sm_y + 276, 0xFFFFFF, 1);
    }

    // DAY 144: CONTROL PANEL (ACTION CENTER)
    if (action_center_open) {
        int ac_w = 250, ac_h = 400, ac_x = 760, ac_y = 50; 
        draw_rounded_rect(ac_x + 5, ac_y + 5, ac_w, ac_h, 15, 0x00111111);
        draw_rounded_rect(ac_x, ac_y, ac_w, ac_h, 15, 0x002D2D30);
        draw_hd_string("Control Center", ac_x + 20, ac_y + 20, 0xFFFFFF, 1);
        
        draw_rounded_rect(ac_x + 20, ac_y + 60, 210, 80, 10, 0x001E1E1E);
        draw_rounded_rect(ac_x + 30, ac_y + 70, 40, 40, 20, 0x004CAF50); // Wi-Fi Active
        draw_hd_string("W", ac_x + 45, ac_y + 85, 0xFFFFFF, 1);
        draw_hd_string("Wi-Fi", ac_x + 80, ac_y + 85, 0xFFFFFF, 1);

        draw_rounded_rect(ac_x + 20, ac_y + 160, 210, 80, 10, 0x001E1E1E);
        draw_hd_string("Volume", ac_x + 30, ac_y + 175, 0xFFFFFF, 1);
        draw_rounded_rect(ac_x + 30, ac_y + 200, 180, 10, 5, 0x00333333);
        draw_rounded_rect(ac_x + 30, ac_y + 200, 120, 10, 5, 0x002196F3); // Slider
        draw_rounded_rect(ac_x + 145, ac_y + 195, 10, 20, 5, 0xFFFFFF); // Knob

        draw_rounded_rect(ac_x + 20, ac_y + 260, 210, 80, 10, 0x001E1E1E);
        draw_hd_string("Brightness", ac_x + 30, ac_y + 275, 0xFFFFFF, 1);
        draw_rounded_rect(ac_x + 30, ac_y + 300, 180, 10, 5, 0x00333333);
        draw_rounded_rect(ac_x + 30, ac_y + 300, 150, 10, 5, 0x00FFB300); // Slider
        draw_rounded_rect(ac_x + 175, ac_y + 295, 10, 20, 5, 0xFFFFFF); // Knob
    }

    if (ctx_open) {
        draw_rounded_rect(ctx_x + 5, ctx_y + 5, 160, 85, 5, 0x00111111); draw_rounded_rect(ctx_x, ctx_y, 160, 85, 5, 0x002D2D30);         
        draw_hd_string("> Refresh", ctx_x + 15, ctx_y + 15, COLOR_TEXT, 1); draw_hd_string("> Terminal", ctx_x + 15, ctx_y + 50, COLOR_TEXT, 1); 
    }
    draw_hd_mouse_pointer(mx, my); swap_buffers_32();
}
#endif