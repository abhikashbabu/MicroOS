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
// NAYA (DAY 105): HD MOUSE CURSOR (White with Black Border)
// ----------------------------------------------------
void draw_hd_mouse_pointer(int x, int y) {
    // Agar mouse screen ke bahar ja raha hai toh ruk jao
    if (x < 0 || x > 1000 || y < 0 || y > 750) return;

    // Draw a modern scalable pointer (15 pixels tall)
    for(int i = 0; i < 15; i++) {
        for(int j = 0; j <= i/1.5; j++) {
            // Black border effect (outer pixels)
            if (j == 0 || j == (int)(i/1.5) || i == 14) {
                put_pixel_32(x + j, y + i, 0x000000); // Black
            } else {
                put_pixel_32(x + j, y + i, 0xFFFFFF); // White inner fill
            }
        }
    }
}
// ... (Upar ka font aur draw_rounded_rect wala code same rahega) ...

void draw_modern_taskbar(int h, int m, int active_app) {
    int tb_width = 800;
    int tb_height = 50;
    int tb_x = (1024 - tb_width) / 2; 
    int tb_y = 768 - tb_height - 10;  

    draw_rounded_rect(tb_x + 2, tb_y + 4, tb_width, tb_height, 10, 0x00111111);
    draw_rounded_rect(tb_x, tb_y, tb_width, tb_height, 10, COLOR_TASKBAR);      

    draw_rounded_rect(tb_x + 20, tb_y + 10, 30, 30, 8, COLOR_ACCENT);
    draw_hd_string("M", tb_x + 28, tb_y + 15, COLOR_TEXT, 2);

    draw_rounded_rect(tb_x + 70, tb_y + 10, 30, 30, 8, 0x00FFB300); // Explorer
    draw_rounded_rect(tb_x + 120, tb_y + 10, 30, 30, 8, 0x004CAF50); // SysMon
    draw_rounded_rect(tb_x + 170, tb_y + 10, 30, 30, 8, 0x009C27B0); // Terminal
    
    // NAYA (Day 124): Calculator Icon
    draw_rounded_rect(tb_x + 220, tb_y + 10, 30, 30, 8, 0x00E53935); // Calc (Red)
    draw_hd_string("C", tb_x + 228, tb_y + 16, COLOR_TEXT, 2);

    // DAY 125: ACTIVE APP INDICATOR (White line under open app icon)
    if (active_app == 2) draw_rounded_rect(tb_x + 75, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 3) draw_rounded_rect(tb_x + 125, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 1) draw_rounded_rect(tb_x + 175, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 5) draw_rounded_rect(tb_x + 225, tb_y + 45, 20, 3, 1, 0xFFFFFF);

    char time_str[6] = {'0','0',':','0','0','\0'};
    time_str[0] = (h / 10) + '0'; time_str[1] = (h % 10) + '0';
    time_str[3] = (m / 10) + '0'; time_str[4] = (m % 10) + '0';
    draw_hd_string(time_str, tb_x + tb_width - 80, tb_y + 18, COLOR_TEXT, 2);
}

void draw_hd_window(int win_x, int win_y, int w, int h, char* title) {
    draw_rounded_rect(win_x + 5, win_y + 5, w, h, 10, 0x00111111);
    draw_rounded_rect(win_x, win_y, w, h, 10, 0x00252526);
    draw_rounded_rect(win_x, win_y, w, 30, 10, 0x00333333);
    draw_hd_string(title, win_x + 15, win_y + 8, COLOR_TEXT, 2);
    draw_rounded_rect(win_x + w - 30, win_y + 8, 15, 15, 5, COLOR_DANGER);
}
// ----------------------------------------------------
// DAY 116: HD TERMINAL HISTORY ENGINE
// ----------------------------------------------------
char hd_term_history[8][50]; // 8 lines ka output yaad rakhega
int hd_term_lines = 0;       // Kitni lines print ho chuki hain

// HD Screen par naya text print karne ka function
void hd_print(char* text) {
    // Agar 8 lines bhar jayein, toh purani lines ko upar khiska do (Scroll)
    if (hd_term_lines >= 8) {
        for (int i = 1; i < 8; i++) {
            int c = 0;
            while (hd_term_history[i][c] != '\0') {
                hd_term_history[i-1][c] = hd_term_history[i][c];
                c++;
            }
            hd_term_history[i-1][c] = '\0';
        }
        hd_term_lines = 7;
    }
    
    // Nayi line ko copy karo
    int c = 0;
    while (text[c] != '\0' && c < 49) {
        hd_term_history[hd_term_lines][c] = text[c];
        c++;
    }
    hd_term_history[hd_term_lines][c] = '\0';
    hd_term_lines++;
}
// ----------------------------------------------------
// Number ko String mein badalne ka HD function
// ----------------------------------------------------
void hd_itoa(int n, char* buf) {
    int i = 0, j = 0, temp = n;
    if (n == 0) { buf[0] = '0'; buf[1] = '\0'; return; }
    while (temp > 0) { buf[i++] = (temp % 10) + '0'; temp /= 10; }
    buf[i] = '\0';
    for(j = 0; j < i/2; j++) { char t = buf[j]; buf[j] = buf[i - 1 - j]; buf[i - 1 - j] = t; }
}
void render_desktop_bg(int mx, int my, int app_state, int win_x, int win_y, char* term_buffer, int h, int m, int start_menu, unsigned int used_ram, int ctx_open, int ctx_x, int ctx_y, int is_minimized, char* calc_display) {
    // 1. Fill background 
    for (int i = 0; i < (1024 * 768); i++) {
        high_res_buffer[i] = COLOR_DARK_BG;
    }
    
    // DESKTOP ICONS
    draw_rounded_rect(20, 20, 40, 40, 5, 0x00FFB300); // My PC
    draw_hd_string("My PC", 15, 65, COLOR_TEXT, 1);
    draw_rounded_rect(20, 100, 40, 40, 5, 0x004CAF50); // Notepad
    draw_hd_string("Notes", 18, 145, COLOR_TEXT, 1);
    
    // NAYA: Calculator Desktop Icon
    draw_rounded_rect(20, 180, 40, 40, 5, 0x00E53935); // Calc
    draw_hd_string("Calc", 22, 225, COLOR_TEXT, 1);

    // 2. Draw Taskbar
    draw_modern_taskbar(h, m, app_state);
    
    // 3. Draw App Windows (Only if NOT minimized!)
    if (app_state > 0 && !is_minimized) {
        if (app_state == 1) { // TERMINAL
            draw_hd_window(win_x, win_y, 420, 300, "Terminal - Root");
            for(int i = 0; i < hd_term_lines; i++) {
                draw_hd_string(hd_term_history[i], win_x + 15, win_y + 40 + (i * 25), COLOR_TEXT, 2);
            }
            int current_y = win_y + 40 + (hd_term_lines * 25);
            draw_hd_string("root@microos:~# ", win_x + 15, current_y, 0x004CAF50, 2);
            draw_hd_string(term_buffer, win_x + 155, current_y, COLOR_TEXT, 2);
        } 
        else if (app_state == 2) { // FILE EXPLORER
            draw_hd_window(win_x, win_y, 400, 300, "File Explorer");
            char count_str[5]; hd_itoa(file_count, count_str);
            draw_hd_string("Virtual Disk (Total Files: ", win_x + 20, win_y + 50, COLOR_TEXT, 2);
            draw_hd_string(count_str, win_x + 280, win_y + 50, COLOR_ACCENT, 2);
            draw_hd_string(")", win_x + 300, win_y + 50, COLOR_TEXT, 2);
            for(int f = 0; f < file_count && f < 5; f++) {
                draw_rounded_rect(win_x + 20, win_y + 90 + (f * 40), 30, 30, 5, 0x00FFB300); 
                draw_hd_string(file_system[f].name, win_x + 60, win_y + 95 + (f * 40), COLOR_TEXT, 2);
            }
        }
        else if (app_state == 3) { // SYSTEM MONITOR
            draw_hd_window(win_x, win_y, 400, 300, "System Monitor");
            draw_hd_string("Micro OS Performance", win_x + 20, win_y + 50, COLOR_ACCENT, 2);
            draw_hd_string("RAM Usage:", win_x + 20, win_y + 90, COLOR_TEXT, 2);
            char ram_str[15]; hd_itoa(used_ram, ram_str);
            draw_hd_string(ram_str, win_x + 20, win_y + 120, 0x004CAF50, 2);
            draw_hd_string(" Bytes", win_x + 100, win_y + 120, COLOR_TEXT, 2);
            draw_rounded_rect(win_x + 20, win_y + 150, 300, 20, 5, 0x00111111); 
            draw_rounded_rect(win_x + 20, win_y + 150, (used_ram / 500) + 10, 20, 5, 0x004CAF50); 
        }
        else if (app_state == 4) { // NOTEPAD
            draw_hd_window(win_x, win_y, 400, 300, "HD Notepad");
            draw_hd_string("Type your notes below:", win_x + 20, win_y + 50, COLOR_ACCENT, 2);
            draw_hd_string(term_buffer, win_x + 20, win_y + 90, COLOR_TEXT, 2);
        }
        else if (app_state == 5) { // DAY 124: HD CALCULATOR APP
            draw_hd_window(win_x, win_y, 300, 360, "Calculator");
            
            // Screen
            draw_rounded_rect(win_x + 20, win_y + 45, 260, 50, 5, 0x00111111);
            int len = 0; while(calc_display[len]) len++;
            draw_hd_string(calc_display, win_x + 260 - (len * 16), win_y + 55, COLOR_TEXT, 3);
            
            // Buttons
            char* keys = "789/456*123-C0=+";
            for(int i=0; i<4; i++) {
                for(int j=0; j<4; j++) {
                    int bx = win_x + 20 + (j * 65);
                    int by = win_y + 105 + (i * 60);
                    draw_rounded_rect(bx, by, 55, 50, 5, 0x00333333);
                    char lbl[2] = {keys[(i*4)+j], '\0'};
                    draw_hd_string(lbl, bx + 22, by + 16, COLOR_TEXT, 2);
                }
            }
        }
    }

    // 4. DRAW START MENU
    if (start_menu) {
        int sm_w = 220, sm_h = 300, sm_x = 120, sm_y = 708 - sm_h - 10;
        draw_rounded_rect(sm_x + 5, sm_y + 5, sm_w, sm_h, 10, 0x00111111);
        draw_rounded_rect(sm_x, sm_y, sm_w, sm_h, 10, 0x00252526);
        draw_hd_string("Micro OS v3.0", sm_x + 20, sm_y + 20, COLOR_ACCENT, 2);
        draw_rounded_rect(sm_x + 20, sm_y + 50, sm_w - 40, 2, 0, 0x00444444); 
        draw_hd_string("> Settings", sm_x + 20, sm_y + 70, COLOR_TEXT, 2);
        draw_hd_string("> Network", sm_x + 20, sm_y + 110, COLOR_TEXT, 2);
        draw_rounded_rect(sm_x + 20, sm_y + 240, sm_w - 40, 40, 5, COLOR_DANGER);
        draw_hd_string("SHUT DOWN", sm_x + 55, sm_y + 252, COLOR_TEXT, 2);
    }

    // 5. DRAW CONTEXT MENU
    if (ctx_open) {
        draw_rounded_rect(ctx_x + 5, ctx_y + 5, 160, 120, 5, 0x00111111); 
        draw_rounded_rect(ctx_x, ctx_y, 160, 120, 5, 0x002D2D30);         
        draw_hd_string("> Refresh", ctx_x + 15, ctx_y + 15, COLOR_TEXT, 2);
        draw_hd_string("> Terminal", ctx_x + 15, ctx_y + 50, COLOR_TEXT, 2);
        draw_hd_string("> System", ctx_x + 15, ctx_y + 85, COLOR_TEXT, 2);
    }

    // 6. Draw mouse on top
    draw_hd_mouse_pointer(mx, my);
    swap_buffers_32();
}
#endif