#ifndef MODERN_UI_H
#define MODERN_UI_H
#include "../drivers/gpu_core.h" // NAYA: Hardware GPU Driver
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
extern int battery_percentage; 
extern int sys_brightness;
extern int sys_volume;
extern int power_saver;
extern int screen_width;
extern int screen_height;
// ==============================================================
// DAY 166: ALPHA BLENDING ENGINE (GLASS UI / ACRYLIC EFFECT)
// ==============================================================
void draw_glass_rect(int start_x, int start_y, int w, int h, int radius, unsigned int hex_color, int alpha) {
    unsigned int fg_r = (hex_color >> 16) & 0xFF;
    unsigned int fg_g = (hex_color >> 8) & 0xFF;
    unsigned int fg_b = hex_color & 0xFF;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            // Smooth Curved Corners (Pure Integer Math, No math.h!)
            if (x < radius && y < radius) {
                if ((radius - x) * (radius - x) + (radius - y) * (radius - y) > radius * radius) continue;
            } else if (x >= w - radius && y < radius) {
                if ((x - (w - radius - 1)) * (x - (w - radius - 1)) + (radius - y) * (radius - y) > radius * radius) continue;
            } else if (x < radius && y >= h - radius) {
                if ((radius - x) * (radius - x) + (y - (h - radius - 1)) * (y - (h - radius - 1)) > radius * radius) continue;
            } else if (x >= w - radius && y >= h - radius) {
                if ((x - (w - radius - 1)) * (x - (w - radius - 1)) + (y - (h - radius - 1)) * (y - (h - radius - 1)) > radius * radius) continue;
            }

            int px = start_x + x;
            int py = start_y + y;
            if (px < 0 || px >= screen_width || py < 0 || py >= screen_height) continue;

            // 1. Zameen (Background) ka asil rang uthao
           unsigned int bg_color = high_res_buffer[py * screen_width + px];
            unsigned int bg_r = (bg_color >> 16) & 0xFF;
            unsigned int bg_g = (bg_color >> 8) & 0xFF;
            unsigned int bg_b = bg_color & 0xFF;

            // 2. Alpha Formula (Rangon ko mix karo - 0 to 255)
            unsigned int out_r = (fg_r * alpha + bg_r * (255 - alpha)) / 255;
            unsigned int out_g = (fg_g * alpha + bg_g * (255 - alpha)) / 255;
            unsigned int out_b = (fg_b * alpha + bg_b * (255 - alpha)) / 255;

            // 3. Wapas VRAM mein daalo
          high_res_buffer[py * screen_width + px] = (out_r << 16) | (out_g << 8) | out_b;
        }
    }
}
// ==============================================================
// DAY 169: PSF VECTOR STROKE ENGINE (SMOOTH SCALABLE TEXT)
// ==============================================================
void draw_scaled_char(char c, int x, int y, unsigned int hex_color, int scale) {
    if (c < 32 || c > 122) return; 
    int font_idx = c - 32;
    
    for (int row = 0; row < 8; row++) {
        unsigned char row_data = modern_font[font_idx][row];
        for (int col = 0; col < 8; col++) {
            
            // Agar yeh pixel ON hai
            if ((row_data >> (7 - col)) & 1) {
                int px = x + (col * scale);
                int py = y + (row * scale);
                
                if (scale <= 2) {
                    // Chhote text par pixel art hi theek lagta hai (fast render)
                    draw_rounded_rect(px, py, scale, scale, 0, hex_color);
                } else {
                    // ==========================================
                    // BADE TEXT PAR: Vector Bridging Magic!
                    // ==========================================
                    
                    // 1. Core Vector Dot (Perfect Circle banayega)
                    draw_rounded_rect(px, py, scale, scale, scale / 2, hex_color);
                    
                    // 2. Horizontal Bridge (Right wale circle se smooth connection)
                    if (col < 7 && ((row_data >> (7 - (col + 1))) & 1)) {
                        draw_rounded_rect(px + (scale / 2), py, scale, scale, 0, hex_color);
                    }
                    
                    // 3. Vertical Bridge (Neeche wale circle se smooth connection)
                    if (row < 7 && ((modern_font[font_idx][row + 1] >> (7 - col)) & 1)) {
                        draw_rounded_rect(px, py + (scale / 2), scale, scale, 0, hex_color);
                    }
                    
                    // 4. Forward Diagonal Bridge (\ stroke)
                    if (col < 7 && row < 7 && ((modern_font[font_idx][row + 1] >> (7 - (col + 1))) & 1)) {
                        draw_rounded_rect(px + (scale / 2), py + (scale / 2), scale, scale, 0, hex_color);
                    }
                    
                    // 5. Backward Diagonal Bridge (/ stroke)
                    if (col > 0 && row < 7 && ((modern_font[font_idx][row + 1] >> (7 - (col - 1))) & 1)) {
                        draw_rounded_rect(px - (scale / 2), py + (scale / 2), scale, scale, 0, hex_color);
                    }
                }
            }
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
if (theme_idx == 0) { r = 15; g = 23 + (y * 20 / screen_height); b = 42 + (y * 40 / screen_height); }
        else if (theme_idx == 1) { r = 240 - (y*20/768); g = 248; b = 255; } 
        else if (theme_idx == 2) { r = 10; g = 80 + (y*100/768); b = 150 + (y*50/768); } 
        else { r = 20; g = 60 + (y*80/768); b = 40 + (y*20/768); } 
     unsigned int color = (r << 16) | (g << 8) | b; 
        for (int x = 0; x < screen_width; x++) high_res_buffer[y * screen_width + x] = color;
    }
}

void draw_modern_taskbar(int h, int m, int active_app) {
    int tb_width = 420, tb_height = 50;
    int tb_x = (screen_width - tb_width) / 2;  
    int tb_y = screen_height - tb_height - 15;
    // Main Taskbar Glass
draw_glass_rect(tb_x, tb_y, tb_width, tb_height, 15, 0x00111122, 170);    
    // Start Button & App Icons
    draw_rounded_rect(tb_x + 20, tb_y + 10, 30, 30, 8, COLOR_ACCENT);
    draw_app_icon(tb_x + 70, tb_y + 5, 0); 
    draw_app_icon(tb_x + 120, tb_y + 5, 6); 
    draw_app_icon(tb_x + 170, tb_y + 5, 7); 
    draw_app_icon(tb_x + 220, tb_y + 5, 2); 
    draw_app_icon(tb_x + 270, tb_y + 5, 3); 
    draw_app_icon(tb_x + 320, tb_y + 5, 4); 

    // Active App Line Indicators
    if (active_app == 2) draw_rounded_rect(tb_x + 80, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 3) draw_rounded_rect(tb_x + 130, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 1) draw_rounded_rect(tb_x + 180, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 5) draw_rounded_rect(tb_x + 230, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 6) draw_rounded_rect(tb_x + 280, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 8) draw_rounded_rect(tb_x + 330, tb_y + 45, 20, 3, 1, 0xFFFFFF); 

    // Top Right System Tray / Time (Bhi Glassy kar diya!)
draw_glass_rect(screen_width - 224, 10, 200, 30, 10, 0x00111122, 170);    
    char time_str[6] = {'0','0',':','0','0','\0'}; 
    time_str[0] = (h / 10) + '0'; time_str[1] = (h % 10) + '0'; 
    time_str[3] = (m / 10) + '0'; time_str[4] = (m % 10) + '0';
    
    draw_hd_string(time_str, 930, 18, COLOR_TEXT, 1); 
    draw_hd_string("W", 840, 18, 0x004CAF50, 1); 
    draw_hd_string("B", 880, 18, 0x002196F3, 1);
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
    
    // 1. Screensaver Check (Dynamic Resolution Update)
    if (is_screensaver) { 
        for (int i = 0; i < (screen_width * screen_height); i++) high_res_buffer[i] = 0x000000; 
        draw_hd_string("MICRO OS", ss_x, ss_y, COLOR_ACCENT, 3); 
        swap_buffers_32(); return; 
    }

    // 2. Lock Screen (app_state == -1)
    if (app_state == -1) {
        draw_gradient_wallpaper(theme_idx); 
        char time_str[6] = {'0','0',':','0','0','\0'}; time_str[0] = (h / 10) + '0'; time_str[1] = (h % 10) + '0'; time_str[3] = (m / 10) + '0'; time_str[4] = (m % 10) + '0';
        
        // Relative Positioning for Lock Screen
        int center_x = screen_width / 2;
        int center_y = screen_height / 2;
        
        draw_hd_string(time_str, center_x - 132, center_y - 234, 0xFFFFFF, 6); 
        draw_rounded_rect(center_x - 100, center_y - 84, 200, 250, 10, 0x001E293B); 
        draw_rounded_rect(center_x - 50, center_y - 54, 100, 100, 20, 0x003B82F6); 
        draw_hd_string("A", center_x - 12, center_y - 24, 0xFFFFFF, 4); 
        draw_hd_string("Abhikash", center_x - 57, center_y + 66, 0xFFFFFF, 1);
        draw_rounded_rect(center_x - 82, center_y + 106, 160, 35, 5, 0x000F172A); 
        
        int p_len = 0; while(pwd_buffer[p_len]) p_len++;
        if (p_len == 0) draw_hd_string("Enter PIN", center_x - 52, center_y + 116, 0x00475569, 1); 
        else for(int i=0; i<p_len; i++) draw_hd_string("*", center_x - 52 + (i*15), center_y + 121, 0xFFFFFF, 1);
        
        draw_hd_mouse_pointer(mx, my); swap_buffers_32(); return;
    }

    draw_gradient_wallpaper(theme_idx);
    
    // 3. Desktop Icons
    draw_app_icon(icon_x[0], icon_y[0], 0); draw_hd_string("My PC", icon_x[0], icon_y[0]+45, 0xFFFFFF, 1);
    draw_app_icon(icon_x[1], icon_y[1], 1); draw_hd_string("Notes", icon_x[1], icon_y[1]+45, 0xFFFFFF, 1);
    draw_app_icon(icon_x[2], icon_y[2], 2); draw_hd_string("Calc", icon_x[2]+4, icon_y[2]+45, 0xFFFFFF, 1);
    draw_app_icon(icon_x[3], icon_y[3], 3); draw_hd_string("Game", icon_x[3]+4, icon_y[3]+45, 0xFFFFFF, 1);
    draw_app_icon(icon_x[4], icon_y[4], 4); draw_hd_string("Sets", icon_x[4]+4, icon_y[4]+45, 0xFFFFFF, 1);
    draw_app_icon(icon_x[5], icon_y[5], 5); draw_hd_string("Piano", icon_x[5], icon_y[5]+45, 0xFFFFFF, 1);
    draw_app_icon(icon_x[6], icon_y[6], 9); draw_hd_string("Date", icon_x[6]+4, icon_y[6]+45, 0xFFFFFF, 1); 
    draw_app_icon(icon_x[7], icon_y[7], 10); draw_hd_string("Music", icon_x[7], icon_y[7]+45, 0xFFFFFF, 1);
    draw_app_icon(icon_x[8], icon_y[8], 11); draw_hd_string("About", icon_x[8], icon_y[8]+45, 0xFFFFFF, 1); 
    draw_app_icon(icon_x[9], icon_y[9], 12); draw_hd_string("Store", icon_x[9], icon_y[9]+45, 0xFFFFFF, 1);
    draw_app_icon(icon_x[10], icon_y[10], 13); draw_hd_string("Safar", icon_x[10], icon_y[10]+45, 0xFFFFFF, 1);
    draw_app_icon(icon_x[11], icon_y[11], 14); draw_hd_string("Browser", icon_x[11]-4, icon_y[11]+45, 0xFFFFFF, 1);
    
    // 4. Desktop Widgets (Relative to Screen Right Edge)
    if (app_state == 0) { 
        int wid_x = screen_width - 244, wid_y = 100;
        draw_rounded_rect(wid_x + 5, wid_y + 5, 200, 140, 10, 0x00111111); draw_rounded_rect(wid_x, wid_y, 200, 140, 10, 0x001E293B); 
        draw_hd_string("Battery Status", wid_x + 15, wid_y + 15, 0xFFFFFF, 1);
        draw_rounded_rect(wid_x + 15, wid_y + 40, 60, 30, 3, 0xFFFFFF); draw_rounded_rect(wid_x + 75, wid_y + 48, 5, 14, 2, 0xFFFFFF); 
        int fill_width = (battery_percentage * 56) / 100; unsigned int bat_color = (battery_percentage > 20) ? 0x004CAF50 : 0x00E53935;
        draw_rounded_rect(wid_x + 17, wid_y + 42, fill_width, 26, 2, bat_color); 
        char bat_str[5]; hd_itoa(battery_percentage, bat_str); int b_len = 0; while(bat_str[b_len]) b_len++; bat_str[b_len] = '%'; bat_str[b_len+1] = '\0';
        draw_hd_string(bat_str, wid_x + 90, wid_y + 48, 0xFFFFFF, 2);
        draw_hd_string("Time Left", wid_x + 15, wid_y + 85, 0x0094A3B8, 1); draw_hd_string("3h 45m", wid_x + 15, wid_y + 105, 0xFFFFFF, 1);
        draw_hd_string("Power Saver", wid_x + 100, wid_y + 85, 0x0094A3B8, 1);
        draw_rounded_rect(wid_x + 120, wid_y + 105, 30, 15, 7, power_saver ? 0x004CAF50 : 0x00333333); 
        draw_rounded_rect(wid_x + (power_saver ? 135 : 122), wid_y + 107, 11, 11, 5, 0xFFFFFF);
    }
    
    // =========================================================================
    // 5. Z-INDEX LOOP
    // =========================================================================
    int layers_to_draw[2] = {z_bg_app, app_state};
    int layer_x[2] = {z_bg_x, win_x};
    int layer_y[2] = {z_bg_y, win_y};

    for (int layer = 0; layer < 2; layer++) {
        int current_app = layers_to_draw[layer];
        int cx = layer_x[layer];
        int cy = layer_y[layer];

        if (current_app <= 0) continue;
        if (layer == 1 && is_minimized) continue;

        if (current_app == 1) { 
            draw_hd_window(cx, cy, 420, 300, "Terminal - Root");
            for(int i = 0; i < hd_term_lines; i++) { draw_hd_string(hd_term_history[i], cx + 15, cy + 40 + (i * 20), COLOR_TEXT, 1); }
            int current_y = cy + 40 + (hd_term_lines * 20); 
            draw_hd_string("root@microos:~# ", cx + 15, current_y, 0x004CAF50, 1); draw_hd_string(term_buffer, cx + 155, current_y, COLOR_TEXT, 1);
            int t_len = 0; while(term_buffer[t_len]) t_len++;
            if (uptime % 2 == 0) draw_hd_string("_", cx + 155 + (t_len * 8), current_y, COLOR_TEXT, 1);
            if (ind_loading > 0) {
                draw_rounded_rect(cx + 50, cy + 120, 320, 60, 5, 0x00111111); draw_hd_string("Compiling .ind to Runtime...", cx + 70, cy + 135, 0xFFFFFF, 1);
                draw_rounded_rect(cx + 70, cy + 160, 280, 10, 5, 0x00333333); draw_rounded_rect(cx + 70, cy + 160, ind_loading * 2, 10, 5, 0x004CAF50);
            }
        }
        else if (current_app == 2) { 
            draw_hd_window(cx, cy, 500, 350, "File Explorer"); draw_rounded_rect(cx, cy+30, 500, 40, 0, 0x001E1E1E); draw_hd_string("Path: C:/MicroOS/", cx + 20, cy + 45, 0x0094A3B8, 1);
            char count_str[5]; hd_itoa(file_count, count_str); draw_hd_string("Items:", cx + 400, cy + 45, 0x0094A3B8, 1); draw_hd_string(count_str, cx + 460, cy + 45, COLOR_ACCENT, 1); 
            for(int f = 0; f < file_count && f < 10; f++) { 
                int col = f % 5; int row = f / 5; int fx = cx + 30 + (col * 90); int fy = cy + 90 + (row * 100);
                if (file_system[f].name[0] == 'I' && file_system[f].name[1] == 'M' && file_system[f].name[2] == 'G') draw_app_icon(fx, fy, 8); 
                else if (file_system[f].name[0] == 'a' && file_system[f].name[1] == 'p' && file_system[f].name[2] == 'p') draw_app_icon(fx, fy, 7);
                else draw_app_icon(fx, fy, 1); 
                draw_hd_string(file_system[f].name, fx, fy + 45, COLOR_TEXT, 1); 
            }
        }
        else if (current_app == 3) { 
            draw_hd_window(cx, cy, 450, 320, "Task Manager"); draw_hd_string("Live Memory Graph", cx + 20, cy + 50, COLOR_TEXT, 1); draw_rounded_rect(cx + 20, cy + 70, 410, 80, 5, 0x00111111); 
            for(int i=0; i<400; i+=10) { int noise = ((used_ram + (uptime * 15) + i) * 17) % 50; draw_rounded_rect(cx+25+i, cy+140 - noise, 5, noise+5, 2, 0x004CAF50); }
            draw_hd_string("Memory (RAM)", cx + 20, cy + 170, COLOR_TEXT, 1); char ram_str[15]; hd_itoa(used_ram/1024, ram_str); 
            draw_hd_string(ram_str, cx + 20, cy + 190, 0x002196F3, 2); draw_hd_string(" KB In Use", cx + 140, cy + 195, COLOR_TEXT, 1);
            draw_rounded_rect(cx + 20, cy + 230, 410, 20, 10, 0x00111111); int ram_bar = (used_ram / 500); if(ram_bar > 410) ram_bar = 410; 
            draw_rounded_rect(cx + 20, cy + 230, ram_bar, 20, 10, 0x002196F3);
            draw_hd_string("System Uptime:", cx + 20, cy + 270, COLOR_TEXT, 1); char up_str[10]; hd_itoa(uptime, up_str); 
            draw_hd_string(up_str, cx + 130, cy + 270, COLOR_ACCENT, 1); draw_hd_string("secs", cx + 180, cy + 270, COLOR_TEXT, 1);
        }
        else if (current_app == 4) { 
            draw_hd_window(cx, cy, 400, 300, "HD Notepad"); draw_hd_string("Type your notes below:", cx + 20, cy + 50, COLOR_ACCENT, 1); draw_hd_string(term_buffer, cx + 20, cy + 90, COLOR_TEXT, 1);
            int t_len = 0; while(term_buffer[t_len]) t_len++; if (uptime % 2 == 0) draw_hd_string("_", cx + 20 + (t_len * 8), cy + 90, COLOR_TEXT, 1);
            draw_rounded_rect(cx + 280, cy + 45, 45, 25, 5, 0x004CAF50); draw_hd_string("SAVE", cx + 285, cy + 53, 0xFFFFFF, 1); draw_rounded_rect(cx + 335, cy + 45, 45, 25, 5, 0x00FFB300); draw_hd_string("LOAD", cx + 340, cy + 53, 0xFFFFFF, 1);
        }
        else if (current_app == 5) { 
            draw_hd_window(cx, cy, 300, 360, "Calculator"); draw_rounded_rect(cx + 20, cy + 45, 260, 50, 5, 0x00111111); int len = 0; while(calc_display[len]) len++; draw_hd_string(calc_display, cx + 260 - (len * 16), cy + 55, COLOR_TEXT, 2);
            char* keys = "789/456*123-C0=+"; for(int i=0; i<4; i++) { for(int j=0; j<4; j++) { int bx = cx + 20 + (j * 65); int by = cy + 105 + (i * 60); draw_rounded_rect(bx, by, 55, 50, 5, 0x00333333); char lbl[2] = {keys[(i*4)+j], '\0'}; draw_hd_string(lbl, bx + 22, by + 20, COLOR_TEXT, 1); } }
        }
        else if (current_app == 6) { 
            draw_hd_window(cx, cy, 300, 360, "Tic-Tac-Toe"); draw_rounded_rect(cx+105, cy+50, 5, 280, 2, 0x00555555); draw_rounded_rect(cx+190, cy+50, 5, 280, 2, 0x00555555); draw_rounded_rect(cx+20, cy+135, 260, 5, 2, 0x00555555); draw_rounded_rect(cx+20, cy+235, 260, 5, 2, 0x00555555);
            for(int i=0; i<3; i++) { for(int j=0; j<3; j++) { int cell = game_board[i*3 + j]; int g_cx = cx + 40 + (j*85); int g_cy = cy + 70 + (i*100); if (cell == 1) draw_hd_string("X", g_cx, g_cy, 0x00E53935, 4); if (cell == 2) draw_hd_string("O", g_cx, g_cy, 0x002196F3, 4); } }
            if (game_winner != 0) { draw_rounded_rect(cx + 50, cy + 150, 200, 60, 10, 0x00111111); if (game_winner == 1) draw_hd_string("P1 WINS!", cx + 75, cy + 170, 0x00E53935, 1); else if (game_winner == 2) draw_hd_string("P2 WINS!", cx + 75, cy + 170, 0x002196F3, 1); else draw_hd_string(" DRAW! ", cx + 85, cy + 170, 0xFFFFFF, 1); }
        }
        else if (current_app == 7) { 
            draw_hd_window(cx, cy, 300, 320, "HD Paint"); if (!paint_init) { for(int i=0; i<260*200; i++) hd_paint_canvas[i] = 0xFFFFFF; paint_init = 1; }
            for(int py=0; py<200; py++) { for(int px=0; px<260; px++) { int screen_pos = ((cy + 40 + py) * screen_width) + (cx + 20 + px); high_res_buffer[screen_pos] = hd_paint_canvas[(py * 260) + px]; } }
            draw_rounded_rect(cx + 20, cy + 260, 30, 30, 5, 0x00E53935); draw_rounded_rect(cx + 60, cy + 260, 30, 30, 5, 0x004CAF50); draw_rounded_rect(cx + 100, cy + 260, 30, 30, 5, 0x002196F3); draw_rounded_rect(cx + 140, cy + 260, 30, 30, 5, 0x00000000); draw_rounded_rect(cx + 180, cy + 260, 30, 30, 5, 0xFFFFFFFF); draw_rounded_rect(cx + 225, cy + 260, 45, 30, 5, 0x00FFB300); draw_hd_string("Save", cx + 230, cy + 270, 0x000000, 1);
        }
        else if (current_app == 8) {
            draw_hd_window(cx, cy, 300, 200, "Settings"); draw_hd_string("Personalize Theme:", cx+20, cy+50, COLOR_TEXT, 1); draw_rounded_rect(cx+20, cy+90, 50, 50, 5, 0x001E1E2E); draw_rounded_rect(cx+85, cy+90, 50, 50, 5, 0x00F8F9FA); draw_rounded_rect(cx+150, cy+90, 50, 50, 5, 0x000F4C75); draw_rounded_rect(cx+215, cy+90, 50, 50, 5, 0x001B4332); 
        }
        else if (current_app == 9) {
            draw_hd_window(cx, cy, 350, 230, "Mini Piano"); for(int i=0; i<7; i++) { draw_rounded_rect(cx + 20 + (i*42), cy + 50, 40, 140, 5, 0xFFFFFF); } for(int i=0; i<6; i++) { if (i == 2) continue; draw_rounded_rect(cx + 45 + (i*42), cy + 50, 28, 80, 3, 0x000000); } draw_hd_string("Click keys to play!", cx + 80, cy + 200, COLOR_ACCENT, 1);
        }
        else if (current_app == 10) {
            draw_hd_window(cx, cy, 300, 280, "Image Gallery"); draw_rounded_rect(cx + 20, cy + 50, 260, 200, 5, 0x000000); for(int py=0; py<200; py++) { for(int px=0; px<260; px++) { int screen_pos = ((cy + 50 + py) * screen_width) + (cx + 20 + px); high_res_buffer[screen_pos] = hd_paint_canvas[(py * 260) + px]; } }
        }
        else if (current_app == 11) {
            draw_hd_window(cx, cy, 400, 300, ind_app_title); draw_rounded_rect(cx+5, cy+35, 390, 260, 5, ind_app_bg); draw_hd_string(ind_app_msg, cx + 20, cy + 60, 0xFFFFFF, 2);
            if (ind_app_input[0] != '\0') { 
                draw_rounded_rect(cx + 20, cy + 110, 350, 35, 5, 0x00111111); int blen = 0; while(ind_input_buf[blen]) blen++; 
                if (blen == 0) draw_hd_string(ind_app_input, cx + 30, cy + 120, 0x0078909C, 1); else { draw_hd_string(ind_input_buf, cx + 30, cy + 120, 0xFFFFFF, 1); if (uptime % 2 == 0) draw_hd_string("|", cx + 30 + (blen * 8), cy + 120, 0xFFFFFF, 1); } 
            }
            if (ind_app_btn[0] != '\0') { draw_rounded_rect(cx + 20, cy + 160, 200, 40, 5, 0x004CAF50); draw_hd_string(ind_app_btn, cx + 40, cy + 172, 0xFFFFFF, 1); }
        }
        else if (current_app == 12) {
            draw_hd_window(cx, cy, 350, 300, "Calendar"); draw_rounded_rect(cx+5, cy+35, 340, 80, 5, 0x00E53935); draw_rounded_rect(cx+5, cy+115, 340, 180, 5, 0x00FFFFFF); draw_hd_string("TODAY", cx + 140, cy + 50, 0xFFFFFF, 1); char d_str[3], m_str[3], y_str[5]; hd_itoa(rtc_day, d_str); hd_itoa(rtc_month, m_str); hd_itoa(rtc_year, y_str); draw_hd_string(d_str, cx + 130, cy + 130, 0x00000000, 6); draw_hd_string("Month:", cx + 80, cy + 220, 0x0078909C, 1); draw_hd_string(m_str, cx + 140, cy + 220, 0x00E53935, 1); draw_hd_string("Year:", cx + 180, cy + 220, 0x0078909C, 1); draw_hd_string(y_str, cx + 230, cy + 220, 0x00E53935, 1); draw_hd_string("Hardware RTC Synced", cx + 90, cy + 260, 0x00B0BEC5, 1);
        }
        else if (current_app == 13) {
            draw_hd_window(cx, cy, 360, 250, "Melody Player"); draw_rounded_rect(cx+20, cy+50, 320, 80, 10, 0x00111111);
            if (now_playing == 1) draw_hd_string("Now Playing: Nokia...", cx + 35, cy + 65, 0x004CAF50, 1); else if (now_playing == 2) draw_hd_string("Now Playing: Mario...", cx + 35, cy + 65, 0x00FFB300, 1); else draw_hd_string("Select a Track:", cx + 35, cy + 65, 0x0094A3B8, 1);
            draw_rounded_rect(cx+20, cy+150, 90, 40, 5, 0x00E91E63); draw_hd_string("Nokia", cx+35, cy+165, 0xFFFFFF, 1); draw_rounded_rect(cx+130, cy+150, 90, 40, 5, 0x002196F3); draw_hd_string("Mario", cx+145, cy+165, 0xFFFFFF, 1); draw_rounded_rect(cx+240, cy+150, 90, 40, 5, 0x00FFB300); draw_hd_string("Stop", cx+265, cy+165, 0x000000, 1);
        }
        else if (current_app == 14) {
            draw_hd_window(cx, cy, 350, 300, "System Properties"); draw_rounded_rect(cx+20, cy+50, 60, 60, 10, COLOR_ACCENT); draw_hd_string("M", cx + 35, cy + 65, 0xFFFFFF, 3); draw_hd_string("Micro OS v3.0", cx + 100, cy + 60, 0xFFFFFF, 2); draw_hd_string("Licensed to: Abhikash", cx + 100, cy + 90, 0x004CAF50, 1); draw_rounded_rect(cx+20, cy+130, 310, 2, 0, 0x00333333); draw_hd_string("Processor: x86 Bare Metal", cx + 20, cy + 150, 0x0094A3B8, 1); draw_hd_string("Graphics: VESA HD UI Engine", cx + 20, cy + 180, 0x0094A3B8, 1); draw_hd_string("Kernel: Monolithic Custom", cx + 20, cy + 210, 0x0094A3B8, 1);
        }
        else if (current_app == 15) {
            draw_hd_window(cx, cy, 470, 320, "Ghar Se Market - Store"); draw_rounded_rect(cx+5, cy+35, 460, 60, 5, 0x004CAF50); draw_hd_string("Aacharindia Premium Store", cx + 90, cy + 55, 0xFFFFFF, 2);
            draw_rounded_rect(cx+20, cy+110, 120, 120, 5, 0x00111111); draw_hd_string("Mango", cx + 50, cy + 150, 0x00FFB300, 1); draw_rounded_rect(cx+20, cy+240, 120, 30, 5, 0x00E53935); draw_hd_string("BUY", cx + 60, cy + 250, 0xFFFFFF, 1);
            draw_rounded_rect(cx+170, cy+110, 120, 120, 5, 0x00111111); draw_hd_string("Lemon", cx + 200, cy + 150, 0x004CAF50, 1); draw_rounded_rect(cx+170, cy+240, 120, 30, 5, 0x00E53935); draw_hd_string("BUY", cx + 210, cy + 250, 0xFFFFFF, 1);
            draw_rounded_rect(cx+320, cy+110, 120, 120, 5, 0x00111111); draw_hd_string("Garlic", cx + 350, cy + 150, 0xFFFFFF, 1); draw_rounded_rect(cx+320, cy+240, 120, 30, 5, 0x00E53935); draw_hd_string("BUY", cx + 360, cy + 250, 0xFFFFFF, 1);
        }
   else if (current_app == 16) {
            draw_hd_window(cx, cy, 400, 350, "Safar-nama Tracker"); 
            draw_rounded_rect(cx + 10, cy + 40, 380, 250, 5, 0x001E293B); 
            
            // Warning fix: Brackets {} add kar diye
            for(int i=0; i<380; i+=20) { draw_rounded_rect(cx+10+i, cy+40, 1, 250, 0, 0x00334155); }
            for(int i=0; i<250; i+=20) { draw_rounded_rect(cx+10, cy+40+i, 380, 1, 0, 0x00334155); }
            
            for(int i=0; i<game_winner; i++) { 
                int px = game_board[i*2]; 
                int py = game_board[i*2 + 1]; 
                draw_rounded_rect(cx + 10 + px - 4, cy + 40 + py - 4, 8, 8, 4, 0x00E53935); 
            }
            
            draw_rounded_rect(cx + 10, cy + 300, 100, 30, 5, 0x00E53935); 
            draw_hd_string("CLEAR", cx + 35, cy + 310, 0xFFFFFF, 1); 
            char pts_str[2] = {game_winner + '0', '\0'}; 
            draw_hd_string("Points:", cx + 130, cy + 310, 0xFFFFFF, 1); 
            draw_hd_string(pts_str, cx + 195, cy + 310, 0x004CAF50, 1);
        }
        else if (current_app == 17) {
            draw_hd_window(cx, cy, 500, 360, "Micro Search - Browser"); draw_hd_string("MICRO SEARCH", cx + 160, cy + 100, 0xFFFFFF, 3);
            draw_rounded_rect(cx + 50, cy + 160, 400, 40, 20, 0x001E293B); draw_hd_string("Search the web...", cx + 70, cy + 175, 0x0094A3B8, 1); draw_rounded_rect(cx + 400, cy + 165, 40, 30, 15, 0x002196F3); 
            draw_rounded_rect(cx + 100, cy + 240, 50, 50, 10, 0x00111111); draw_hd_string("G", cx + 115, cy + 250, 0x004CAF50, 3); 
            draw_rounded_rect(cx + 180, cy + 240, 50, 50, 10, 0x00111111); draw_hd_string("Hub", cx + 185, cy + 255, 0xFFFFFF, 2); 
            draw_rounded_rect(cx + 260, cy + 240, 50, 50, 10, 0x00111111); draw_hd_string("YT", cx + 270, cy + 255, 0x00E53935, 2); 
            draw_rounded_rect(cx + 340, cy + 240, 50, 50, 10, 0x00111111); draw_hd_string("W", cx + 355, cy + 250, 0x00B0BEC5, 3); 
        }

      // =========================================================================
        // 6. THE SLEEP OVERLAY FOR BACKGROUND APP (Sirf Layer 0)
        // =========================================================================
        if (layer == 0) {
            int w = 300; 
            if(current_app==1) w=420; else if(current_app==2) w=500; else if(current_app==3) w=450;
            else if(current_app==4) w=400; else if(current_app==11) w=400; else if(current_app==12) w=350;
            else if(current_app==13) w=360; else if(current_app==14) w=350; else if(current_app==15) w=470;
            else if(current_app==16) w=400; else if(current_app==17) w=500;
            
            draw_glass_rect(cx, cy, w, 350, 10, 0x00000000, 140);
        }
    } // Z-INDEX LOOP ENDS HERE

    // 7. System UI Elements (Topmost layer)
    draw_modern_taskbar(h, m, app_state);

    if (start_menu) {
        int sm_w = 240, sm_h = 320;
        int sm_x = (screen_width - 420) / 2 + 10; 
        int sm_y = screen_height - sm_h - 75;
        
        draw_glass_rect(sm_x, sm_y, sm_w, sm_h, 10, 0x00111122, 190); 
        draw_rounded_rect(sm_x+20, sm_y+20, 30, 30, 15, COLOR_ACCENT); draw_hd_string("Micro OS", sm_x + 60, sm_y + 28, 0xFFFFFF, 1);
        draw_rounded_rect(sm_x + 20, sm_y + 60, sm_w - 40, 2, 0, 0x00444444); draw_rounded_rect(sm_x+20, sm_y+80, 15, 15, 3, 0x004CAF50); draw_hd_string("Notepad", sm_x + 45, sm_y + 83, COLOR_TEXT, 1); draw_rounded_rect(sm_x+20, sm_y+115, 15, 15, 3, 0x00E53935); draw_hd_string("Calculator", sm_x + 45, sm_y + 118, COLOR_TEXT, 1); draw_rounded_rect(sm_x+20, sm_y+150, 15, 15, 3, 0x00FFFFFF); draw_hd_string("Calendar", sm_x + 45, sm_y + 153, COLOR_TEXT, 1); draw_rounded_rect(sm_x+20, sm_y+185, 15, 15, 3, 0x009E9E9E); draw_hd_string("Settings", sm_x + 45, sm_y + 188, COLOR_TEXT, 1); draw_rounded_rect(sm_x+20, sm_y+220, 15, 15, 3, 0x00FFB300); draw_hd_string("HD Paint", sm_x + 45, sm_y + 223, COLOR_TEXT, 1);
        draw_rounded_rect(sm_x + 20, sm_y + 265, sm_w - 40, 35, 5, COLOR_DANGER); draw_hd_string("O", sm_x + 60, sm_y + 276, 0xFFFFFF, 1); draw_hd_string("|", sm_x + 63, sm_y + 272, 0xFFFFFF, 1); draw_hd_string("SHUT DOWN", sm_x + 85, sm_y + 276, 0xFFFFFF, 1);
    }
    
    if (action_center_open) {
        int ac_w = 250, ac_h = 400;
        int ac_x = screen_width - ac_w - 24; 
        int ac_y = 50; 
        
        draw_glass_rect(ac_x, ac_y, ac_w, ac_h, 15, 0x000F0F1A, 200); 
        draw_hd_string("Control Center", ac_x + 20, ac_y + 20, 0xFFFFFF, 1);
        draw_rounded_rect(ac_x + 20, ac_y + 60, 210, 80, 10, 0x001E1E1E); draw_rounded_rect(ac_x + 30, ac_y + 70, 40, 40, 20, 0x004CAF50); draw_hd_string("W", ac_x + 45, ac_y + 85, 0xFFFFFF, 1); draw_hd_string("Wi-Fi", ac_x + 80, ac_y + 85, 0xFFFFFF, 1);
        draw_rounded_rect(ac_x + 20, ac_y + 160, 210, 80, 10, 0x001E1E1E); draw_hd_string("Volume", ac_x + 30, ac_y + 175, 0xFFFFFF, 1); draw_rounded_rect(ac_x + 30, ac_y + 200, 180, 10, 5, 0x00333333); draw_rounded_rect(ac_x + 30, ac_y + 200, sys_volume, 10, 5, 0x002196F3); draw_rounded_rect(ac_x + 30 + sys_volume - 5, ac_y + 195, 10, 20, 5, 0xFFFFFF); 
        draw_rounded_rect(ac_x + 20, ac_y + 260, 210, 80, 10, 0x001E1E1E); draw_hd_string("Brightness", ac_x + 30, ac_y + 275, 0xFFFFFF, 1); draw_rounded_rect(ac_x + 30, ac_y + 300, 180, 10, 5, 0x00333333); draw_rounded_rect(ac_x + 30, ac_y + 300, sys_brightness, 10, 5, 0x00FFB300); draw_rounded_rect(ac_x + 30 + sys_brightness - 5, ac_y + 295, 10, 20, 5, 0xFFFFFF); 
    }
    
    if (ctx_open) {
        draw_glass_rect(ctx_x, ctx_y, 180, 120, 5, 0x00111122, 200); 
        draw_hd_string("> About PC", ctx_x + 15, ctx_y + 15, COLOR_TEXT, 1); draw_hd_string("> Terminal", ctx_x + 15, ctx_y + 50, COLOR_TEXT, 1); draw_hd_string("> Settings", ctx_x + 15, ctx_y + 85, COLOR_TEXT, 1); 
    }
    
    // NAYA: Notification bhi relative hui (Right side se)
    if (notif_y >= 0) {
        int nx = screen_width - 274; 
        draw_rounded_rect(nx + 5, notif_y + 5, 250, 60, 10, 0x00111111); 
        draw_rounded_rect(nx, notif_y, 250, 60, 10, 0x001E293B); 
        draw_rounded_rect(nx + 10, notif_y + 20, 20, 20, 10, 0x004CAF50); 
        draw_hd_string("System Notice", nx + 40, notif_y + 15, 0x0094A3B8, 1);
        draw_hd_string(notif_msg, nx + 40, notif_y + 35, 0xFFFFFF, 1);
    }
    
    draw_hd_mouse_pointer(mx, my); 
    
    // NAYA: Hardware brightness ab screen variables use karegi
    apply_hardware_brightness(high_res_buffer, sys_brightness, screen_width, screen_height);

    swap_buffers_32();
}

#endif