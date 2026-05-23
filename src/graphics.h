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
        else if (c == '>') pattern = (row==0||row==4)?4:(row==1||row==3)?2:1; 
        else if (c == '<') pattern = (row==0||row==4)?1:(row==1||row==3)?2:4; 
        else if (c == '.') pattern = (row==4)?2:0; 
        else if (c == '_') pattern = (row == 4) ? 7 : 0; 
        else if (c == '[') pattern = (row==0||row==4)?3:2; 
        else if (c == ']') pattern = (row==0||row==4)?6:2; 
        else if (c == '/') pattern = (row==0)?1:(row==1)?2:(row==2)?2:(row==3)?4:(row==4)?4:0; 
        else return;

        if(pattern & 4) put_pixel(x,   y + row, color);
        if(pattern & 2) put_pixel(x + 1, y + row, color);
        if(pattern & 1) put_pixel(x + 2, y + row, color);
    }
}

void draw_gui_string(char* str, int start_x, int start_y, unsigned char color, int max_width) {
    int x = start_x;
    int y = start_y;
    for(int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') { x = start_x; y += 8; continue; }
        draw_char(str[i], x, y, color);
        x += 4; 
        if (x > start_x + max_width) { x = start_x; y += 8; }
    }
}

void draw_desktop_dynamic(int win_x, int win_y, int app_mode, int start_menu_open, char* note_text, int note_saved, char* cmd_out, char* cmd_in, int current_lba, char* disk_buffer, unsigned char bg_color, unsigned char win_color) {
    clear_graphics(bg_color); 
    
    draw_rect(10, 10, 32, 32, 14); draw_rect(14, 14, 24, 24, 15); draw_gui_string("PNT", 15, 45, 15, 100); 
    draw_rect(60, 10, 32, 32, 15); draw_rect(64, 14, 24, 24, 11); draw_gui_string("NOT", 65, 45, 15, 100); 
    draw_rect(110, 10, 32, 32, 8); draw_rect(114, 14, 24, 24, 0); draw_gui_string(">_", 118, 22, 2, 100); draw_gui_string("CMD", 115, 45, 15, 100); 
    draw_rect(160, 10, 32, 32, 5); draw_rect(164, 14, 24, 24, 13); draw_gui_string("HD", 170, 22, 0, 100); draw_gui_string("DSK", 165, 45, 15, 100);
    draw_rect(210, 10, 32, 32, 7); draw_rect(214, 14, 24, 24, 8); draw_gui_string("SET", 215, 22, 15, 100); draw_gui_string("THEME", 210, 45, 15, 100);
    
    draw_rect(0, 180, 320, 20, 7); draw_rect(2, 182, 30, 16, 2); draw_gui_string("OS", 10, 187, 15, 100); 
    
    if (app_mode > 0) {
        draw_rect(win_x, win_y, 200, 135, 15); 
        draw_rect(win_x, win_y, 200, 15, win_color); 
        draw_rect(win_x + 185, win_y + 2, 12, 11, 4); draw_char('X', win_x + 189, win_y + 5, 15); 
        
        if (app_mode == 1) { 
            draw_gui_string("MICRO PAINT", win_x + 5, win_y + 5, 15, 180);
            draw_rect(win_x + 2, win_y + 17, 196, 95, 7); 
            draw_rect(win_x + 5, win_y + 116, 15, 15, 0); draw_rect(win_x + 25, win_y + 116, 15, 15, 4);  
            draw_rect(win_x + 45, win_y + 116, 15, 15, 2); draw_rect(win_x + 65, win_y + 116, 15, 15, 1);  
            draw_rect(win_x + 85, win_y + 116, 15, 15, 14); draw_rect(win_x + 105, win_y + 116, 15, 15, 7); 
            draw_rect(win_x + 135, win_y + 116, 40, 15, 4); draw_gui_string("CLEAR", win_x + 140, win_y + 121, 15, 50);
        } 
        else if (app_mode == 2) { 
            draw_gui_string("MINI NOTES", win_x + 5, win_y + 5, 15, 180);
            draw_rect(win_x + 2, win_y + 17, 196, 95, 15); 
            draw_gui_string(note_text, win_x + 5, win_y + 22, 0, 190);
            if (note_saved) { draw_rect(win_x + 155, win_y + 116, 40, 15, 14); draw_gui_string("SAVD", win_x + 163, win_y + 121, 0, 50); } 
            else { draw_rect(win_x + 155, win_y + 116, 40, 15, 2); draw_gui_string("SAVE", win_x + 163, win_y + 121, 15, 50); }
        }
        else if (app_mode == 3) { 
            draw_gui_string("TERMINAL", win_x + 5, win_y + 5, 15, 180);
            draw_rect(win_x + 2, win_y + 17, 196, 115, 0); 
            draw_gui_string(cmd_out, win_x + 5, win_y + 22, 2, 190);
            draw_gui_string(">", win_x + 5, win_y + 120, 15, 10); draw_gui_string(cmd_in, win_x + 12, win_y + 120, 15, 180);
        }
        else if (app_mode == 4) { 
            draw_gui_string("DISK VIEWER", win_x + 5, win_y + 5, 15, 180);
            draw_rect(win_x + 2, win_y + 17, 196, 115, 0); 
            
            draw_gui_string("LBA SECTOR:", win_x + 5, win_y + 22, 14, 190); 
            int num_x = win_x + 55;
            if(current_lba >= 100) { draw_char((current_lba/100)+'0', num_x, win_y+22, 14); num_x+=4; }
            if(current_lba >= 10)  { draw_char(((current_lba/10)%10)+'0', num_x, win_y+22, 14); num_x+=4; }
            draw_char((current_lba%10)+'0', num_x, win_y+22, 14);

            draw_rect(win_x + 120, win_y + 19, 30, 12, 4); draw_gui_string("<PREV", win_x + 123, win_y + 23, 15, 30);
            draw_rect(win_x + 160, win_y + 19, 30, 12, 2); draw_gui_string("NEXT>", win_x + 163, win_y + 23, 15, 30);

            draw_gui_string("RAW DISK BYTES:\n", win_x + 5, win_y + 35, 2, 190);  
            
            int tx = win_x + 5; int ty = win_y + 50;
            for(int i = 0; i < 140; i++) { 
                char c = disk_buffer[i];
                if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == ' ') { draw_char(c, tx, ty, 15); } 
                else { draw_char('.', tx, ty, 8); }
                tx += 4; if (tx > win_x + 190) { tx = win_x + 5; ty += 8; }
            }
        }
        else if (app_mode == 5) {
            draw_gui_string("CONTROL PANEL", win_x + 5, win_y + 5, 15, 180);
            draw_rect(win_x + 2, win_y + 17, 196, 115, 7); 
            
            draw_gui_string("BACKGROUND THEME:", win_x + 10, win_y + 25, 0, 180);
            draw_rect(win_x + 10, win_y + 40, 20, 20, 1); 
            draw_rect(win_x + 40, win_y + 40, 20, 20, 0); 
            draw_rect(win_x + 70, win_y + 40, 20, 20, 3); 
            draw_rect(win_x + 100, win_y + 40, 20, 20, 8); 

            draw_gui_string("WINDOW COLOR:", win_x + 10, win_y + 70, 0, 180);
            draw_rect(win_x + 10, win_y + 85, 20, 20, 9); 
            draw_rect(win_x + 40, win_y + 85, 20, 20, 4); 
            draw_rect(win_x + 70, win_y + 85, 20, 20, 2); 
            draw_rect(win_x + 100, win_y + 85, 20, 20, 5); 
        }
    }

    if (start_menu_open) {
        draw_rect(2, 20, 120, 160, 7); 
        draw_gui_string("MENU", 10, 23, 0, 50);
        
        draw_rect(10, 35, 15, 15, 14); draw_gui_string("PAINT", 35, 40, 0, 50); 
        draw_rect(10, 55, 15, 15, 11); draw_gui_string("NOTES", 35, 60, 0, 50); 
        draw_rect(10, 75, 15, 15, 0); draw_gui_string("CMD", 35, 80, 0, 50); 
        draw_rect(10, 95, 15, 15, 13); draw_gui_string("DISK", 35, 100, 0, 50); 
        draw_rect(10, 115, 15, 15, 8); draw_gui_string("THEME", 35, 120, 0, 50); 
        
        draw_rect(10, 135, 15, 15, 1); draw_gui_string("CLOSE", 35, 140, 0, 50); 
        draw_rect(10, 155, 15, 15, 4); draw_gui_string("REBOOT", 35, 160, 0, 50); 
    }
}

void draw_boot_screen() {
    clear_graphics(1); 
    draw_rect(60, 50, 200, 100, 15); 
    draw_rect(65, 55, 190, 90, 9);   
    draw_gui_string("MICRO OS", 125, 75, 15, 200);       
    draw_gui_string("VERSION 3.0", 115, 95, 14, 200);    
    draw_gui_string("LOADING ENGINE...", 105, 120, 7, 200); 
}

void draw_gui_time(int h, int m) {
    draw_rect(275, 185, 40, 10, 7); 
    draw_char((h / 10) + '0', 275, 187, 0); draw_char((h % 10) + '0', 279, 187, 0); 
    draw_char(':', 284, 187, 0);
    draw_char((m / 10) + '0', 289, 187, 0); draw_char((m % 10) + '0', 293, 187, 0); 
}

#endif