#ifndef MODERN_UI_H
#define MODERN_UI_H

#include "vesa.h"

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

        if(pattern & 4) draw_rounded_rect(x, y + (row * scale), scale, scale, 0, hex_color);
        if(pattern & 2) draw_rounded_rect(x + scale, y + (row * scale), scale, scale, 0, hex_color);
        if(pattern & 1) draw_rounded_rect(x + (scale * 2), y + (row * scale), scale, scale, 0, hex_color);
    }
}

void draw_hd_string(char* str, int start_x, int start_y, unsigned int hex_color, int scale) {
    int x = start_x; 
    for(int i = 0; str[i] != '\0'; i++) { draw_scaled_char(str[i], x, start_y, hex_color, scale); x += (4 * scale); }
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

void draw_modern_taskbar(int h, int m, int active_app) {
    int tb_width = 800, tb_height = 50, tb_x = (1024 - tb_width) / 2, tb_y = 768 - tb_height - 10;  
    draw_rounded_rect(tb_x + 2, tb_y + 4, tb_width, tb_height, 10, 0x00111111);
    draw_rounded_rect(tb_x, tb_y, tb_width, tb_height, 10, COLOR_TASKBAR);      
    draw_rounded_rect(tb_x + 20, tb_y + 10, 30, 30, 8, COLOR_ACCENT); draw_hd_string("M", tb_x + 28, tb_y + 15, COLOR_TEXT, 2);

    draw_rounded_rect(tb_x + 70, tb_y + 10, 30, 30, 8, 0x00FFB300); 
    draw_rounded_rect(tb_x + 120, tb_y + 10, 30, 30, 8, 0x004CAF50); 
    draw_rounded_rect(tb_x + 170, tb_y + 10, 30, 30, 8, 0x009C27B0); 
    draw_rounded_rect(tb_x + 220, tb_y + 10, 30, 30, 8, 0x00E53935); 
    draw_rounded_rect(tb_x + 270, tb_y + 10, 30, 30, 8, 0x002196F3); 
    draw_rounded_rect(tb_x + 320, tb_y + 10, 30, 30, 8, 0x009E9E9E); // NAYA: Settings Icon on Taskbar

    if (active_app == 2) draw_rounded_rect(tb_x + 75, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 3) draw_rounded_rect(tb_x + 125, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 1) draw_rounded_rect(tb_x + 175, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 5) draw_rounded_rect(tb_x + 225, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 6) draw_rounded_rect(tb_x + 275, tb_y + 45, 20, 3, 1, 0xFFFFFF);
    if (active_app == 7) draw_rounded_rect(tb_x + 20, tb_y + 45, 30, 3, 1, 0xFFFFFF);
    if (active_app == 8) draw_rounded_rect(tb_x + 325, tb_y + 45, 20, 3, 1, 0xFFFFFF); // Settings indicator

    char time_str[6] = {'0','0',':','0','0','\0'};
    time_str[0] = (h / 10) + '0'; time_str[1] = (h % 10) + '0'; time_str[3] = (m / 10) + '0'; time_str[4] = (m % 10) + '0';
    draw_hd_string(time_str, tb_x + tb_width - 80, tb_y + 18, COLOR_TEXT, 2);
}

void draw_hd_window(int win_x, int win_y, int w, int h, char* title) {
    draw_rounded_rect(win_x + 5, win_y + 5, w, h, 10, 0x00111111);
    draw_rounded_rect(win_x, win_y, w, h, 10, 0x00252526);
    draw_rounded_rect(win_x, win_y, w, 30, 10, 0x00333333);
    draw_hd_string(title, win_x + 15, win_y + 8, COLOR_TEXT, 2);
    draw_rounded_rect(win_x + w - 30, win_y + 8, 15, 15, 5, COLOR_DANGER);
}

char hd_term_history[8][50]; 
int hd_term_lines = 0;       
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

void render_desktop_bg(int mx, int my, int app_state, int win_x, int win_y, char* term_buffer, int h, int m, int start_menu, unsigned int used_ram, int ctx_open, int ctx_x, int ctx_y, int is_minimized, char* calc_display, unsigned int theme_bg, int* game_board, int game_winner, int is_screensaver, int ss_x, int ss_y, int* icon_x, int* icon_y) {
    
    if (is_screensaver) {
        for (int i = 0; i < (1024 * 768); i++) high_res_buffer[i] = 0x000000;
        draw_hd_string("MICRO OS", ss_x, ss_y, COLOR_ACCENT, 4);
        swap_buffers_32();
        return; 
    }

    for (int i = 0; i < (1024 * 768); i++) high_res_buffer[i] = theme_bg;
    
    // DAY 132: DYNAMIC DESKTOP ICONS (Based on array coordinates)
    draw_rounded_rect(icon_x[0], icon_y[0], 40, 40, 5, 0x00FFB300); draw_hd_string("My PC", icon_x[0]-5, icon_y[0]+45, 0xFFFFFF, 1);
    draw_rounded_rect(icon_x[1], icon_y[1], 40, 40, 5, 0x004CAF50); draw_hd_string("Notes", icon_x[1]-5, icon_y[1]+45, 0xFFFFFF, 1);
    draw_rounded_rect(icon_x[2], icon_y[2], 40, 40, 5, 0x00E53935); draw_hd_string("Calc", icon_x[2]-2, icon_y[2]+45, 0xFFFFFF, 1);
    draw_rounded_rect(icon_x[3], icon_y[3], 40, 40, 5, 0x002196F3); draw_hd_string("Game", icon_x[3]-2, icon_y[3]+45, 0xFFFFFF, 1);
    draw_rounded_rect(icon_x[4], icon_y[4], 40, 40, 5, 0x009E9E9E); draw_hd_string("Sets", icon_x[4]-2, icon_y[4]+45, 0xFFFFFF, 1);

    draw_modern_taskbar(h, m, app_state);
    
    if (app_state > 0 && !is_minimized) {
        if (app_state == 1) { 
            draw_hd_window(win_x, win_y, 420, 300, "Terminal - Root");
            for(int i = 0; i < hd_term_lines; i++) draw_hd_string(hd_term_history[i], win_x + 15, win_y + 40 + (i * 25), COLOR_TEXT, 2);
            int current_y = win_y + 40 + (hd_term_lines * 25);
            draw_hd_string("root@microos:~# ", win_x + 15, current_y, 0x004CAF50, 2); draw_hd_string(term_buffer, win_x + 155, current_y, COLOR_TEXT, 2);
        } 
        else if (app_state == 2) { 
            draw_hd_window(win_x, win_y, 400, 300, "File Explorer");
            char count_str[5]; hd_itoa(file_count, count_str);
            draw_hd_string("Virtual Disk (Total Files: ", win_x + 20, win_y + 50, COLOR_TEXT, 2);
            draw_hd_string(count_str, win_x + 280, win_y + 50, COLOR_ACCENT, 2); draw_hd_string(")", win_x + 300, win_y + 50, COLOR_TEXT, 2);
            for(int f = 0; f < file_count && f < 5; f++) {
                draw_rounded_rect(win_x + 20, win_y + 90 + (f * 40), 30, 30, 5, 0x00FFB300); draw_hd_string(file_system[f].name, win_x + 60, win_y + 95 + (f * 40), COLOR_TEXT, 2);
            }
        }
        else if (app_state == 3) { 
            draw_hd_window(win_x, win_y, 400, 300, "System Monitor");
            draw_hd_string("Micro OS Performance", win_x + 20, win_y + 50, COLOR_ACCENT, 2); draw_hd_string("RAM Usage:", win_x + 20, win_y + 90, COLOR_TEXT, 2);
            char ram_str[15]; hd_itoa(used_ram, ram_str);
            draw_hd_string(ram_str, win_x + 20, win_y + 120, 0x004CAF50, 2); draw_hd_string(" Bytes", win_x + 100, win_y + 120, COLOR_TEXT, 2);
            draw_rounded_rect(win_x + 20, win_y + 150, 300, 20, 5, 0x00111111); draw_rounded_rect(win_x + 20, win_y + 150, (used_ram / 500) + 10, 20, 5, 0x004CAF50); 
        }
        else if (app_state == 4) { 
            draw_hd_window(win_x, win_y, 400, 300, "HD Notepad");
            draw_hd_string("Type your notes below:", win_x + 20, win_y + 50, COLOR_ACCENT, 2);
            draw_hd_string(term_buffer, win_x + 20, win_y + 90, COLOR_TEXT, 2);
            
            // DAY 131: SAVE AND LOAD BUTTONS
            draw_rounded_rect(win_x + 280, win_y + 45, 45, 25, 5, 0x004CAF50); draw_hd_string("SAVE", win_x + 285, win_y + 50, 0xFFFFFF, 1);
            draw_rounded_rect(win_x + 335, win_y + 45, 45, 25, 5, 0x00FFB300); draw_hd_string("LOAD", win_x + 340, win_y + 50, 0xFFFFFF, 1);
        }
        else if (app_state == 5) { 
            draw_hd_window(win_x, win_y, 300, 360, "Calculator");
            draw_rounded_rect(win_x + 20, win_y + 45, 260, 50, 5, 0x00111111);
            int len = 0; while(calc_display[len]) len++; draw_hd_string(calc_display, win_x + 260 - (len * 16), win_y + 55, COLOR_TEXT, 3);
            char* keys = "789/456*123-C0=+";
            for(int i=0; i<4; i++) { for(int j=0; j<4; j++) { int bx = win_x + 20 + (j * 65); int by = win_y + 105 + (i * 60); draw_rounded_rect(bx, by, 55, 50, 5, 0x00333333); char lbl[2] = {keys[(i*4)+j], '\0'}; draw_hd_string(lbl, bx + 22, by + 16, COLOR_TEXT, 2); } }
        }
        else if (app_state == 6) { 
            draw_hd_window(win_x, win_y, 300, 360, "Tic-Tac-Toe");
            draw_rounded_rect(win_x+105, win_y+50, 5, 280, 2, 0x00555555); draw_rounded_rect(win_x+190, win_y+50, 5, 280, 2, 0x00555555); draw_rounded_rect(win_x+20, win_y+135, 260, 5, 2, 0x00555555); draw_rounded_rect(win_x+20, win_y+235, 260, 5, 2, 0x00555555);
            for(int i=0; i<3; i++) { for(int j=0; j<3; j++) { int cell = game_board[i*3 + j]; int cx = win_x + 40 + (j*85); int cy = win_y + 70 + (i*100); if (cell == 1) draw_hd_string("X", cx, cy, 0x00E53935, 6); if (cell == 2) draw_hd_string("O", cx, cy, 0x002196F3, 6); } }
            if (game_winner != 0) { draw_rounded_rect(win_x + 50, win_y + 150, 200, 60, 10, 0x00111111); if (game_winner == 1) draw_hd_string("P1 WINS!", win_x + 75, win_y + 170, 0x00E53935, 2); else if (game_winner == 2) draw_hd_string("P2 WINS!", win_x + 75, win_y + 170, 0x002196F3, 2); else draw_hd_string(" DRAW! ", win_x + 85, win_y + 170, 0xFFFFFF, 2); }
        }
        else if (app_state == 7) { 
            draw_hd_window(win_x, win_y, 300, 320, "HD Paint");
            if (!paint_init) { for(int i=0; i<260*200; i++) hd_paint_canvas[i] = 0xFFFFFF; paint_init = 1; }
            for(int py=0; py<200; py++) { for(int px=0; px<260; px++) { int screen_pos = ((win_y + 40 + py) * 1024) + (win_x + 20 + px); high_res_buffer[screen_pos] = hd_paint_canvas[(py * 260) + px]; } }
            draw_rounded_rect(win_x + 20, win_y + 260, 30, 30, 5, 0x00E53935); draw_rounded_rect(win_x + 60, win_y + 260, 30, 30, 5, 0x004CAF50); draw_rounded_rect(win_x + 100, win_y + 260, 30, 30, 5, 0x002196F3); draw_rounded_rect(win_x + 140, win_y + 260, 30, 30, 5, 0x00000000); draw_rounded_rect(win_x + 180, win_y + 260, 30, 30, 5, 0xFFFFFFFF); draw_hd_string("Clr", win_x + 225, win_y + 270, 0x00E53935, 1);
        }
        // DAY 133: THE SETTINGS APP (THEME CHANGER)
        else if (app_state == 8) {
            draw_hd_window(win_x, win_y, 300, 200, "Settings");
            draw_hd_string("Personalize Theme:", win_x+20, win_y+50, COLOR_TEXT, 2);
            draw_rounded_rect(win_x+20, win_y+90, 50, 50, 5, 0x001E1E2E); // Dark
            draw_rounded_rect(win_x+85, win_y+90, 50, 50, 5, 0x00F8F9FA); // Light
            draw_rounded_rect(win_x+150, win_y+90, 50, 50, 5, 0x000F4C75); // Ocean
            draw_rounded_rect(win_x+215, win_y+90, 50, 50, 5, 0x001B4332); // Forest
        }
    }

    if (start_menu) {
        int sm_w = 220, sm_h = 300, sm_x = 120, sm_y = 708 - sm_h - 10;
        draw_rounded_rect(sm_x + 5, sm_y + 5, sm_w, sm_h, 10, 0x00111111);
        draw_rounded_rect(sm_x, sm_y, sm_w, sm_h, 10, 0x00252526);
        draw_hd_string("Micro OS v3.0", sm_x + 20, sm_y + 20, COLOR_ACCENT, 2);
        draw_rounded_rect(sm_x + 20, sm_y + 50, sm_w - 40, 2, 0, 0x00444444); 
        
        draw_hd_string("> Notepad", sm_x + 20, sm_y + 70, COLOR_TEXT, 2);
        draw_hd_string("> Calculator", sm_x + 20, sm_y + 100, COLOR_TEXT, 2);
        draw_hd_string("> Tic-Tac-Toe", sm_x + 20, sm_y + 130, COLOR_TEXT, 2);
        draw_hd_string("> Settings", sm_x + 20, sm_y + 160, 0x002196F3, 2);

        draw_rounded_rect(sm_x + 20, sm_y + 240, sm_w - 40, 40, 5, COLOR_DANGER);
        draw_hd_string("SHUT DOWN", sm_x + 55, sm_y + 252, COLOR_TEXT, 2);
    }

    if (ctx_open) {
        draw_rounded_rect(ctx_x + 5, ctx_y + 5, 160, 85, 5, 0x00111111); 
        draw_rounded_rect(ctx_x, ctx_y, 160, 85, 5, 0x002D2D30);         
        draw_hd_string("> Refresh", ctx_x + 15, ctx_y + 15, COLOR_TEXT, 2);
        draw_hd_string("> Terminal", ctx_x + 15, ctx_y + 50, COLOR_TEXT, 2); 
    }

    draw_hd_mouse_pointer(mx, my);
    swap_buffers_32();
}
#endif