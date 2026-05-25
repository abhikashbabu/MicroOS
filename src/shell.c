#include "shell.h"
#include "display.h"
#include "string.h"
#include "cmos.h"
#include "io.h"
#include "memory.h"  // NAYA: Memory manager include kiya
#include "fs.h"          // NAYA
#include "ind_runner.h"  // NAYA
#include "editor.h"      // NAYA
#include "pci.h"         // NAYA
#include "task.h"        // NAYA
#include "mouse.h"
#include "vga.h"
#include "graphics.h"
#include "disk.h" // ISKO UPAR ADD KARNA HAI
#include "sound.h"

void execute_command(char* command) {
    if (command[0] == '\0') return;
    
    if (strcmp(command, "help") == 0) {
        print_string("Available commands:\n");
        print_string("  help    - Show this message\n");
        print_string("  clear   - Clear the screen\n");
        print_string("  about   - Show OS info\n");
        print_string("  time    - Show current hardware time\n");
        print_string("  reboot  - Restart the computer\n");
        print_string("  meminfo - Show RAM usage\n");
        print_string("  echo    - Print text to screen\n");
        print_string("  ls      - List all files\n");               // HELP ME BHI ADD KIYA
        print_string("  cat     - Read file (e.g., cat readme.txt)\n"); // HELP ME BHI ADD KIYA
        print_string("  run     - Run .ind app (e.g., run hello.ind)\n"); // HELP ME BHI ADD KIYA
        print_string("  edit    - Edit a file (e.g., edit readme.txt)\n"); // HELP ME BHI ADD KIYA
        print_string("  explorer - Browse files\n"); // HELP ME BHI ADD KIYA
        print_string("  create   - Create a file (e.g., create note.txt This is a note)\n"); // HELP ME BHI ADD KIYA
        print_string("  rm       - Delete a file (e.g., rm note.txt)\n"); // HELP ME BHI ADD KIYA
        print_string("  pci      - Scan PCI Hardware\n"); // HELP ME BHI ADD    KIYA
        print_string("  matrix   - The Matrix Screensaver\n"); // HELP ME BHI ADD KIYA 
        print_string("  top      - Show running tasks\n"); // HELP ME BHI ADD KIYA
             



    } 
    else if (strcmp(command, "clear") == 0) {
        clear_screen();
        draw_top_bar(" Micro OS v0.1 | .ind Application Runtime");
    } 
    else if (strcmp(command, "about") == 0) {
        print_string("Micro OS v0.1\n");
        print_string("Built for the .ind ecosystem.\n");
        print_string("Developer: Abhikash\n");
    } 
// --------------------------------------------------------
    // ULTIMATE GUI COMMAND (DAY 89/90) - Real Kernel Memory
    // --------------------------------------------------------
    else if (strcmp(command, "gui") == 0) {
        init_vga_graphics(); 
        
        // NAYA: Tumhare asli memory.c se kmalloc() use kar rahe hain
        if (paint_canvas == 0) {
            paint_canvas = (unsigned char*)kmalloc(18620); // 196x95 bytes allocation!
            init_paint_canvas();
        }
        
        draw_boot_screen();
        os_beep(800, 3); os_beep(1200, 6);
        for(volatile int delay = 0; delay < 60000000; delay++) {} 
        
        int win_x = 50, win_y = 40;
        int app_mode = 0; 
        int is_dragging = 0;
        unsigned int last_click_time = 0; 
        int brush_color = 0; 
        int start_menu_open = 0; 
        
        unsigned char bg_color = 1; unsigned char win_color = 9; 
        
        char note_text[512] = {0}; read_sector_lba28(10, (unsigned char*)note_text); 
        int note_len = 0; while(note_text[note_len] != '\0' && note_len < 199) { note_len++; }
        int note_saved = 0; 
        
        char cmd_in[50] = {0}; int cmd_len = 0;
        char cmd_out[400] = "MICRO OS v3.0\nSYSTEM ACTIVE\n------------------\n";
        
        int current_lba = 10; char disk_buffer[512] = {0};
        
        char calc_display[20] = "0"; int calc_op = 0; int calc_num1 = 0; int calc_new_num = 1; 
        int game_board[9] = {0,0,0, 0,0,0, 0,0,0}; int game_turn = 1; int game_winner = 0; 
        char file_list_str[400] = {0};
        
        unsigned int last_input_tick = timer_ticks; 
        int ss_x = 100, ss_y = 100; int ss_dx = 2, ss_dy = 2;  
        
        int gui_running = 1;
        while(gui_running) {
            
            unsigned char k_status = inb(0x64);
            if (k_status & 1) { 
                if (!(k_status & 0x20)) { 
                    unsigned char scancode = inb(0x60); 
                    last_input_tick = timer_ticks;
                    if(app_mode == 99) app_mode = 0;
                    
                    if (scancode == 0x01) { outb(0x64, 0xFE); } 
                    
                    else if (app_mode == 2 && !(scancode & 0x80)) { 
                        if (scancode == 0x0E && note_len > 0) { note_text[--note_len] = '\0'; note_saved = 0; } 
                        else if (scancode == 0x39 && note_len < 199) { note_text[note_len++] = ' '; note_text[note_len] = '\0'; note_saved = 0; }
                        else if (note_len < 199 && keyboard_map[scancode] != 0) {
                            note_text[note_len++] = keyboard_map[scancode]; note_text[note_len] = '\0'; note_saved = 0; 
                        }
                    }
                    else if (app_mode == 3 && !(scancode & 0x80)) {
                        if (scancode == 0x0E && cmd_len > 0) { cmd_in[--cmd_len] = '\0'; } 
                        else if (scancode == 0x1C) { 
                            int out_len = 0; while(cmd_out[out_len] != '\0') out_len++;
                            if (out_len > 300) { cmd_out[0] = '\0'; out_len = 0; }
                            cmd_out[out_len++] = '>'; cmd_out[out_len] = '\0';
                            int i = 0; while(cmd_in[i] != '\0') { cmd_out[out_len++] = cmd_in[i++]; }
                            cmd_out[out_len++] = '\n'; cmd_out[out_len] = '\0';
                            
                            if (cmd_in[0] == 'l' && cmd_in[1] == 's') {
                                if (file_count == 0) { char* msg = "NO FILES\n"; int k=0; while(msg[k]!='\0') cmd_out[out_len++] = msg[k++]; } 
                                else {
                                    for(int f = 0; f < file_count; f++) {
                                        int k = 0; while(file_system[f].name[k] != '\0') cmd_out[out_len++] = file_system[f].name[k++];
                                        cmd_out[out_len++] = ' ';
                                    } cmd_out[out_len++] = '\n';
                                }
                            }
                            else if (cmd_in[0]=='c' && cmd_in[1]=='a' && cmd_in[2]=='t' && cmd_in[3]==' ') {
                                int f_idx = find_file(&cmd_in[4]);
                                if (f_idx != -1) {
                                    int k = 0; while(file_system[f_idx].content[k] != '\0') cmd_out[out_len++] = file_system[f_idx].content[k++];
                                    cmd_out[out_len++] = '\n';
                                } else { char* msg = "NOT FOUND\n"; int k=0; while(msg[k]!='\0') cmd_out[out_len++] = msg[k++]; }
                            }
                            else if (cmd_in[0]=='c' && cmd_in[1]=='l') { cmd_out[0] = '\0'; out_len = 0; }
                            else { char* msg = "UNKNOWN\n"; int k=0; while(msg[k]!='\0') cmd_out[out_len++] = msg[k++]; }
                            cmd_out[out_len] = '\0'; cmd_len = 0; cmd_in[0] = '\0'; 
                        }
                        else if (scancode == 0x39 && cmd_len < 40) { cmd_in[cmd_len++] = ' '; cmd_in[cmd_len] = '\0'; }
                        else if (cmd_len < 40 && keyboard_map[scancode] != 0) { cmd_in[cmd_len++] = keyboard_map[scancode]; cmd_in[cmd_len] = '\0'; }
                    }
                } 
                else { 
                    unsigned char mouse_bytes[3]; mouse_bytes[0] = inb(0x60);
                    if (!(mouse_bytes[0] & 0x08)) continue; 
                    mouse_wait(0); mouse_bytes[1] = inb(0x60); mouse_wait(0); mouse_bytes[2] = inb(0x60);
                    int rel_x = mouse_bytes[1] - ((mouse_bytes[0] << 4) & 0x100); int rel_y = mouse_bytes[2] - ((mouse_bytes[0] << 3) & 0x100);
                    int left_click = mouse_bytes[0] & 1;

                    if(rel_x != 0 || rel_y != 0 || left_click) {
                        last_input_tick = timer_ticks;
                        if(app_mode == 99) app_mode = 0; 
                    }

                    mouse_x += (rel_x / 2); mouse_y -= (rel_y / 2);
                    if (mouse_x < 0) { mouse_x = 0; } if (mouse_x > 313) { mouse_x = 313; }
                    if (mouse_y < 0) { mouse_y = 0; } if (mouse_y > 193) { mouse_y = 193; }

                    if (left_click) {
                        if (app_mode > 0 && app_mode != 99 && !is_dragging && mouse_x >= win_x && mouse_x <= win_x + 180 && mouse_y >= win_y && mouse_y <= win_y + 15) {
                            start_menu_open = 0; is_dragging = 1;
                        }
                    } else { is_dragging = 0; }

                    if (is_dragging) { win_x += (rel_x / 2); win_y -= (rel_y / 2); }

                    if (left_click && !is_dragging && app_mode != 99) {
                        if (mouse_x >= 2 && mouse_x <= 32 && mouse_y >= 182 && mouse_y <= 198) {
                            if (timer_ticks - last_click_time > 10) { os_beep(1000, 1); start_menu_open = !start_menu_open; last_click_time = timer_ticks; }
                        }
                        else if (start_menu_open && mouse_x >= 2 && mouse_x <= 182 && mouse_y >= 50 && mouse_y <= 180) {
                            os_beep(1500, 2); 
                            if (mouse_x < 90) { 
                                if (mouse_y >= 65 && mouse_y <= 80) { app_mode = 1; start_menu_open = 0; } 
                                else if (mouse_y >= 85 && mouse_y <= 100) { app_mode = 2; start_menu_open = 0; } 
                                else if (mouse_y >= 105 && mouse_y <= 120) { app_mode = 3; start_menu_open = 0; } 
                                else if (mouse_y >= 125 && mouse_y <= 140) { app_mode = 4; start_menu_open = 0; for(int i=0; i<512; i++) { disk_buffer[i]=0; } read_sector_lba28(current_lba, (unsigned char*)disk_buffer); } 
                                else if (mouse_y >= 145 && mouse_y <= 160) { 
                                    app_mode = 9; start_menu_open = 0; 
                                    int f_len = 0; char* hdr = "NAME        SIZE\n----------------\n";
                                    while(hdr[f_len]) { file_list_str[f_len] = hdr[f_len]; f_len++; }
                                    if(file_count == 0) { char* nf = "NO FILES SAVED"; int k=0; while(nf[k]) file_list_str[f_len++] = nf[k++]; } 
                                    else { for(int f=0; f<file_count; f++) { int k=0; while(file_system[f].name[k]) file_list_str[f_len++] = file_system[f].name[k++]; file_list_str[f_len++] = ' '; file_list_str[f_len++] = ' '; file_list_str[f_len++] = '4'; file_list_str[f_len++] = 'K'; file_list_str[f_len++] = 'B'; file_list_str[f_len++] = '\n'; } }
                                    file_list_str[f_len] = '\0';
                                } 
                            } else { 
                                if (mouse_y >= 65 && mouse_y <= 80) { app_mode = 5; start_menu_open = 0; } 
                                else if (mouse_y >= 85 && mouse_y <= 100) { app_mode = 6; start_menu_open = 0; } 
                                else if (mouse_y >= 105 && mouse_y <= 120) { app_mode = 7; start_menu_open = 0; } 
                                else if (mouse_y >= 125 && mouse_y <= 140) { app_mode = 8; start_menu_open = 0; } 
                                else if (mouse_y >= 145 && mouse_y <= 160) { outb(0x64, 0xFE); } 
                            }
                        }
                        else if (start_menu_open) { start_menu_open = 0; }
                        else {
                            if (app_mode == 0) { 
                                if (timer_ticks - last_click_time > 0 && timer_ticks - last_click_time < 20) {
                                    if (mouse_y >= 10 && mouse_y <= 42) {
                                        if (mouse_x >= 10 && mouse_x <= 42) { os_beep(1500, 2); app_mode = 1; }
                                        else if (mouse_x >= 60 && mouse_x <= 92) { os_beep(1500, 2); app_mode = 2; }
                                        else if (mouse_x >= 110 && mouse_x <= 142) { os_beep(1500, 2); app_mode = 3; }
                                        else if (mouse_x >= 160 && mouse_x <= 192) { os_beep(1500, 2); app_mode = 4; for(int i=0; i<512; i++){disk_buffer[i]=0;} read_sector_lba28(current_lba, (unsigned char*)disk_buffer); }
                                        else if (mouse_x >= 210 && mouse_x <= 242) { os_beep(1500, 2); app_mode = 5; }
                                        else if (mouse_x >= 260 && mouse_x <= 292) { os_beep(1500, 2); app_mode = 6; }
                                    }
                                    else if (mouse_y >= 60 && mouse_y <= 92) {
                                        if (mouse_x >= 10 && mouse_x <= 42) { os_beep(1500, 2); app_mode = 7; } 
                                        else if (mouse_x >= 60 && mouse_x <= 92) { os_beep(1500, 2); app_mode = 8; }
                                        else if (mouse_x >= 110 && mouse_x <= 142) { 
                                            os_beep(1500, 2); app_mode = 9; 
                                            int f_len = 0; char* hdr = "NAME        SIZE\n----------------\n";
                                            while(hdr[f_len]) { file_list_str[f_len] = hdr[f_len]; f_len++; }
                                            if(file_count == 0) { char* nf = "NO FILES SAVED"; int k=0; while(nf[k]) file_list_str[f_len++] = nf[k++]; } 
                                            else { for(int f=0; f<file_count; f++) { int k=0; while(file_system[f].name[k]) file_list_str[f_len++] = file_system[f].name[k++]; file_list_str[f_len++] = ' '; file_list_str[f_len++] = ' '; file_list_str[f_len++] = '4'; file_list_str[f_len++] = 'K'; file_list_str[f_len++] = 'B'; file_list_str[f_len++] = '\n'; } }
                                            file_list_str[f_len] = '\0';
                                        } 
                                    }
                                } last_click_time = timer_ticks;
                            }
                            if (app_mode > 0 && mouse_x >= win_x + 185 && mouse_x <= win_x + 197 && mouse_y >= win_y + 2 && mouse_y <= win_y + 13) { app_mode = 0; }
                            
                            if (app_mode == 1 && paint_canvas != 0) { 
                                if (mouse_y >= win_y + 116 && mouse_y <= win_y + 131) {
                                    if (mouse_x >= win_x + 5 && mouse_x <= win_x + 20) brush_color = 0; else if (mouse_x >= win_x + 25 && mouse_x <= win_x + 40) brush_color = 4; else if (mouse_x >= win_x + 45 && mouse_x <= win_x + 60) brush_color = 2; else if (mouse_x >= win_x + 65 && mouse_x <= win_x + 80) brush_color = 1; else if (mouse_x >= win_x + 85 && mouse_x <= win_x + 100) brush_color = 14; else if (mouse_x >= win_x + 105 && mouse_x <= win_x + 120) brush_color = 7; else if (mouse_x >= win_x + 135 && mouse_x <= win_x + 175) { init_paint_canvas(); }
                                }
                                if (mouse_x >= win_x + 2 && mouse_x <= win_x + 195 && mouse_y >= win_y + 17 && mouse_y <= win_y + 109) { 
                                    for(int by=0; by<3; by++) { for(int bx=0; bx<3; bx++) { int cx = (mouse_x - (win_x + 2)) + bx; int cy = (mouse_y - (win_y + 17)) + by; if(cx >= 0 && cx < 196 && cy >= 0 && cy < 95) { paint_canvas[(cy * 196) + cx] = brush_color; } } }
                                }
                            }
                            else if (app_mode == 2) { 
                                if (mouse_y >= win_y + 116 && mouse_y <= win_y + 131 && mouse_x >= win_x + 155 && mouse_x <= win_x + 195) {
                                    if (note_len > 0 && note_saved == 0) { write_sector_lba28(10, (unsigned char*)note_text); note_saved = 1; os_beep(2000, 2); }
                                }
                            }
                            else if (app_mode == 4) {
                                if (mouse_y >= win_y + 19 && mouse_y <= win_y + 31) {
                                    if (mouse_x >= win_x + 120 && mouse_x <= win_x + 150) { if (current_lba > 0) { current_lba--; for(int i=0; i<512; i++) { disk_buffer[i]=0; } read_sector_lba28(current_lba, (unsigned char*)disk_buffer); } }
                                    else if (mouse_x >= win_x + 160 && mouse_x <= win_x + 190) { if (current_lba < 999) { current_lba++; for(int i=0; i<512; i++) { disk_buffer[i]=0; } read_sector_lba28(current_lba, (unsigned char*)disk_buffer); } }
                                }
                            }
                            else if (app_mode == 5) {
                                if (mouse_y >= win_y + 40 && mouse_y <= win_y + 60) {
                                    if (mouse_x >= win_x + 10 && mouse_x <= win_x + 30) bg_color = 1; else if (mouse_x >= win_x + 40 && mouse_x <= win_x + 60) bg_color = 0; else if (mouse_x >= win_x + 70 && mouse_x <= win_x + 90) bg_color = 3; else if (mouse_x >= win_x + 100 && mouse_x <= win_x + 120) bg_color = 8; 
                                }
                                else if (mouse_y >= win_y + 85 && mouse_y <= win_y + 105) {
                                    if (mouse_x >= win_x + 10 && mouse_x <= win_x + 30) win_color = 9; else if (mouse_x >= win_x + 40 && mouse_x <= win_x + 60) win_color = 4; else if (mouse_x >= win_x + 70 && mouse_x <= win_x + 90) win_color = 2; else if (mouse_x >= win_x + 100 && mouse_x <= win_x + 120) win_color = 5;
                                }
                            }
                            else if (app_mode == 7) {
                                if (timer_ticks - last_click_time > 10) { 
                                    int bx = -1, by = -1;
                                    if(mouse_x >= win_x+15 && mouse_x <= win_x+50) bx = 0; else if(mouse_x >= win_x+60 && mouse_x <= win_x+95) bx = 1; else if(mouse_x >= win_x+105 && mouse_x <= win_x+140) bx = 2; else if(mouse_x >= win_x+150 && mouse_x <= win_x+185) bx = 3;
                                    if(mouse_y >= win_y+50 && mouse_y <= win_y+65) by = 0; else if(mouse_y >= win_y+70 && mouse_y <= win_y+85) by = 1; else if(mouse_y >= win_y+90 && mouse_y <= win_y+105) by = 2; else if(mouse_y >= win_y+110 && mouse_y <= win_y+125) by = 3;

                                    if(bx != -1 && by != -1) {
                                        os_beep(1200, 1); char keys[4][4] = { {'7','8','9','/'}, {'4','5','6','*'}, {'1','2','3','-'}, {'C','0','=','+'} }; char k = keys[by][bx];
                                        if (k >= '0' && k <= '9') {
                                            if (calc_new_num) { calc_display[0] = k; calc_display[1] = '\0'; calc_new_num = 0; } 
                                            else { int dlen = 0; while(calc_display[dlen]) dlen++; if(dlen < 10) { calc_display[dlen] = k; calc_display[dlen+1] = '\0'; } }
                                        } 
                                        else if (k == 'C') { calc_display[0] = '0'; calc_display[1] = '\0'; calc_num1 = 0; calc_op = 0; calc_new_num = 1; } 
                                        else if (k == '+' || k == '-' || k == '*' || k == '/') {
                                            int val=0, sign=1, idx=0; if(calc_display[0]=='-'){sign=-1;idx=1;} while(calc_display[idx]){val=val*10+(calc_display[idx]-'0');idx++;}
                                            calc_num1 = val * sign; calc_op = (k=='+')?1:(k=='-')?2:(k=='*')?3:4; calc_new_num = 1;
                                        } 
                                        else if (k == '=') {
                                            int val=0, sign=1, idx=0; if(calc_display[0]=='-'){sign=-1;idx=1;} while(calc_display[idx]){val=val*10+(calc_display[idx]-'0');idx++;}
                                            int calc_num2 = val * sign; int res = 0;
                                            if (calc_op == 1) res = calc_num1 + calc_num2; else if (calc_op == 2) res = calc_num1 - calc_num2; else if (calc_op == 3) res = calc_num1 * calc_num2; else if (calc_op == 4) { if(calc_num2!=0) res = calc_num1 / calc_num2; else res = 0; }
                                            idx = 0; if(res == 0) { calc_display[0]='0'; calc_display[1]='\0'; } 
                                            else {
                                                int is_neg=0; if(res<0){is_neg=1; res=-res;} char tmp[20]; int t=0;
                                                while(res>0){ tmp[t++]=(res%10)+'0'; res/=10; } if(is_neg) tmp[t++]='-';
                                                while(t>0){ calc_display[idx++] = tmp[--t]; } calc_display[idx]='\0';
                                            }
                                            calc_new_num = 1; calc_op = 0;
                                        } last_click_time = timer_ticks;
                                    }
                                }
                            }
                            else if (app_mode == 8) {
                                if (timer_ticks - last_click_time > 10) {
                                    if (mouse_x >= win_x + 145 && mouse_x <= win_x + 190 && mouse_y >= win_y + 115 && mouse_y <= win_y + 127) {
                                        for(int i=0; i<9; i++) game_board[i] = 0; game_winner = 0; game_turn = 1; os_beep(1000, 2); last_click_time = timer_ticks;
                                    }
                                    else if (game_winner == 0) {
                                        int col = -1, row = -1;
                                        if(mouse_x >= win_x+35 && mouse_x <= win_x+65) col = 0; else if(mouse_x > win_x+65 && mouse_x <= win_x+105) col = 1; else if(mouse_x > win_x+105 && mouse_x <= win_x+135) col = 2;
                                        if(mouse_y >= win_y+25 && mouse_y <= win_y+55) row = 0; else if(mouse_y > win_y+55 && mouse_y <= win_y+85) row = 1; else if(mouse_y > win_y+85 && mouse_y <= win_y+115) row = 2;
                                        if(col != -1 && row != -1) {
                                            int cell = (row * 3) + col;
                                            if(game_board[cell] == 0) {
                                                game_board[cell] = game_turn; os_beep(1500, 1);
                                                int w[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
                                                for(int i=0; i<8; i++) { if(game_board[w[i][0]] != 0 && game_board[w[i][0]] == game_board[w[i][1]] && game_board[w[i][1]] == game_board[w[i][2]]) { game_winner = game_board[w[i][0]]; os_beep(2000, 4); } }
                                                if(game_winner == 0) { int full = 1; for(int i=0; i<9; i++) if(game_board[i] == 0) full = 0; if(full) game_winner = 3; }
                                                game_turn = (game_turn == 1) ? 2 : 1; last_click_time = timer_ticks;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            if (timer_ticks - last_input_tick > 150) {
                app_mode = 99; 
                ss_x += ss_dx; ss_y += ss_dy;
                if (ss_x <= 0 || ss_x >= 280) ss_dx = -ss_dx;
                if (ss_y <= 0 || ss_y >= 190) ss_dy = -ss_dy;
            }

            // NAYA: Tumhare memory.c ka function - get_used_memory() lagaya hai
            draw_desktop_dynamic(win_x, win_y, app_mode, start_menu_open, note_text, note_saved, cmd_out, cmd_in, current_lba, disk_buffer, bg_color, win_color, timer_ticks, calc_display, game_board, game_winner, file_list_str, ss_x, ss_y, get_used_memory());
            
            if (app_mode != 99) {
                int h, m, s; get_time(&h, &m, &s); draw_gui_time(h, m); 
                draw_mouse_pointer(mouse_x, mouse_y);
            }
            
            swap_buffers(); 
        }
        init_vga_graphics(); outb(0x64, 0xFE); 
    }
    else if (strcmp(command, "time") == 0) {
        int h, m, s;
        get_time(&h, &m, &s);
        char buffer[10];
        print_string("Current Time (UTC): ");
        if (h < 10) print_char('0');
        itoa(h, buffer); print_string(buffer);
        print_char(':');
        if (m < 10) print_char('0');
        itoa(m, buffer); print_string(buffer);
        print_char(':');
        if (s < 10) print_char('0');
        itoa(s, buffer); print_string(buffer);
        print_string("\n");
    }

    // NAYA (DAY 42): Mouse hardware test
    else if (strcmp(command, "mousetest") == 0) {
        clear_screen();
        set_color(COLOR_WHITE, COLOR_BLUE);
        draw_window(0, 0, 80, 25, "Mouse Diagnostic Mode - Press [ESC] to Exit", COLOR_BLUE);
        
        // Mouse packet data (3 bytes aate hain har movement par)
        char mouse_bytes[3];
        
        while(1) {
            // Check Keyboard for ESC Key (Exit)
            unsigned char k_status = inb(0x64);
            if (k_status & 1) {
                if (!(k_status & 0x20)) { // Data from Keyboard
                    unsigned char scancode = inb(0x60);
                    if (scancode == 0x01) break; // 0x01 is ESC
                } else {
                    // Data from Mouse (Bit 5 is set)
                    mouse_bytes[0] = inb(0x60);
                    mouse_wait(0); mouse_bytes[1] = inb(0x60);
                    mouse_wait(0); mouse_bytes[2] = inb(0x60);
                    
                    // Purana cursor mitana (Black space)
                    cursor_x = mouse_x; cursor_y = mouse_y; update_cursor(cursor_x, cursor_y);
                    print_char(' ');

                    // X aur Y update karna (Packet 1 aur 2 mein movement hoti hai)
                    // Mouse bytes[1] is X movement, bytes[2] is Y movement
                    int rel_x = mouse_bytes[1] - ((mouse_bytes[0] << 4) & 0x100);
                    int rel_y = mouse_bytes[2] - ((mouse_bytes[0] << 3) & 0x100);

                    mouse_x += (rel_x / 2); // Divide by 2 for speed control
                    mouse_y -= (rel_y / 2); // Y is inverted

                    // Screen limits
                    if (mouse_x < 0) mouse_x = 0;
                    if (mouse_x > 79) mouse_x = 79;
                    if (mouse_y < 1) mouse_y = 1;
                    if (mouse_y > 24) mouse_y = 24;

                    // Naya cursor draw karna (Red block)
                    set_color(COLOR_LIGHT_RED, COLOR_LIGHT_RED);
                    cursor_x = mouse_x; cursor_y = mouse_y; update_cursor(cursor_x, cursor_y);
                    print_char('X'); // X character ko red print kar rahe hain
                    set_color(COLOR_WHITE, COLOR_BLUE);
                }
            }
        }
        
        // Test close hone par wapas OS mode
        set_color(COLOR_WHITE, COLOR_BLACK);
        clear_screen();
        draw_top_bar(" Micro OS v0.1 | .ind Application Runtime");
    }

    else if (strcmp(command, "reboot") == 0) {
        print_string("Rebooting Micro OS...\n");
        outb(0x64, 0xFE);
    }
    else if (strcmp(command, "meminfo") == 0) { 
        unsigned int used_bytes = get_used_memory();
        char buffer[16];
        
        print_string("System Memory Status:\n");
        print_string("Base Address : 0x200000 (2 MB)\n");
        print_string("Used Memory  : ");
        itoa(used_bytes, buffer);
        print_string(buffer);
        print_string(" Bytes\n");
        
        kmalloc(10); 
    }
    // NAYA: 'top' command (Task Manager)
    else if (strcmp(command, "top") == 0) {
        draw_window(15, 3, 50, 12, "Task Manager", COLOR_MAGENTA);
        set_color(COLOR_WHITE, COLOR_MAGENTA);
        
        cursor_x = 17; cursor_y = 5; update_cursor(cursor_x, cursor_y);
        print_string("PID   | Task Name           | Memory");
        cursor_x = 17; cursor_y = 6; update_cursor(cursor_x, cursor_y);
        print_string("--------------------------------------");
        
        for(int i = 0; i < current_task_count; i++) {
            if(task_list[i].is_active) {
                cursor_x = 17; cursor_y = 7 + i; update_cursor(cursor_x, cursor_y);
                
                // PID
                char id_buf[5]; itoa(task_list[i].id, id_buf);
                print_string(id_buf); print_string("     | ");
                
                // Task Name
                print_string(task_list[i].name);
                
                // Name alignment ke liye extra spaces
                int len = 0; while(task_list[i].name[len] != '\0') len++;
                for(int s = 0; s < (20 - len); s++) print_char(' ');
                
                print_string("| ");
                
                // Memory
                char mem_buf[10]; itoa(task_list[i].memory_used, mem_buf);
                print_string(mem_buf); print_string(" Bytes");
            }
        }
        
        // Output dikhane ke baad wapas normal terminal position set karna
        cursor_x = 0; cursor_y = 21; update_cursor(cursor_x, cursor_y);
        set_color(COLOR_WHITE, COLOR_BLACK);
    }
    else if (command[0] == 'r' && command[1] == 'u' && command[2] == 'n' && command[3] == ' ') {
        char* filename = &command[4];
        int file_index = find_file(filename);
        if (file_index != -1) {
            // NAYA: Ab file ka naam, uska code, aur uska size teeno engine ko bhej rahe hain
            execute_ind_app(filename, file_system[file_index].content, file_system[file_index].size);
        } else {
            print_string("App not found.\n");
        }
    }
    // NAYA: 'kill <pid>' command
    else if (command[0] == 'k' && command[1] == 'i' && command[2] == 'l' && command[3] == 'l' && command[4] == ' ') {
        int target_pid = 0;
        int idx = 5;
        // PID number padhna
        while(command[idx] >= '0' && command[idx] <= '9') {
            target_pid = (target_pid * 10) + (command[idx] - '0');
            idx++;
        }
        
        if(target_pid == 0 || target_pid == 1) {
            print_string("[Error] Cannot kill System Kernel or Shell!\n");
        } else if(target_pid >= current_task_count || task_list[target_pid].is_active == 0) {
            print_string("[Error] Invalid PID or Task already dead.\n");
        } else {
            end_task(target_pid);
            print_string("[OK] Task PID ");
            char kbuf[5]; itoa(target_pid, kbuf); print_string(kbuf);
            print_string(" terminated successfully.\n");
        }
    }
   else if (strcmp(command, "ls") == 0) { 
        print_string("Name                  Size (Bytes)\n");
        print_string("----------------------------------\n");
        for (int i = 0; i < file_count; i++) {
            print_string(file_system[i].name);
            
            // \t\t ki jagah humne manual spaces daal diye hain
            print_string("          "); 
            
            char buf[10];
            itoa(file_system[i].size, buf);
            print_string(buf);
            print_string("\n");
        }
    }
    // NAYA: 'create <filename> <content>' command (Live Coding!)
    else if (command[0] == 'c' && command[1] == 'r' && command[2] == 'e' && command[3] == 'a' && command[4] == 't' && command[5] == 'e' && command[6] == ' ') {
        int idx = 7;
        char filename[32];
        int f_idx = 0;
        
        // 1. Pehle space tak file ka naam nikalna
        while(command[idx] != ' ' && command[idx] != '\0' && f_idx < 31) {
            filename[f_idx++] = command[idx++];
        }
        filename[f_idx] = '\0'; // Naam close kiya
        
        if (command[idx] == ' ') idx++; // Space skip karo
        
        // 2. Baaki bacha hua pura text file ke andar save kar do
        create_file(filename, &command[idx]);
        
        print_string("App generated successfully! Type 'ls' to view it.\n");
    }
    // NAYA: 'rm <filename>' command (Delete file)
    else if (command[0] == 'r' && command[1] == 'm' && command[2] == ' ') {
        char* filename = &command[3];
        int file_index = find_file(filename);
        if (file_index != -1) {
            delete_file(filename);
            print_string("File deleted successfully.\n");
        } else {
            print_string("Error: File not found.\n");
        }
    }
    // NAYA (Day 29): PCI Hardware Scanner
    else if (strcmp(command, "pci") == 0) {
        scan_pci_bus();
    }
    // NAYA (Day 30): The Matrix Screensaver
    else if (strcmp(command, "matrix") == 0) {
        clear_screen();
        set_color(COLOR_LIGHT_GREEN, COLOR_BLACK);
        
        // Digital rain animation loop
        for(int m = 0; m < 500; m++) {
            for(int n = 0; n < 80; n++) {
                if((m + n) % 7 == 0 || (m * n) % 13 == 0) {
                    print_char('0' + (m + n) % 2); // Random 0 or 1
                } else {
                    print_char(' ');
                }
            }
            // Delay taaki animation fast na bhage
            for(volatile int d = 0; d < 8000000; d++){} 
        }
        
        // Screensaver khatam hone par sab normal kardo
        set_color(COLOR_WHITE, COLOR_BLACK);
        clear_screen();
        draw_top_bar(" Micro OS v0.1 | .ind Application Runtime");
    }
    // NAYA: 'append <filename> <content>' command (File me line add karna)
    else if (command[0] == 'a' && command[1] == 'p' && command[2] == 'p' && command[3] == 'e' && command[4] == 'n' && command[5] == 'd' && command[6] == ' ') {
        int idx = 7;
        char filename[32];
        int f_idx = 0;
        
        while(command[idx] != ' ' && command[idx] != '\0' && f_idx < 31) {
            filename[f_idx++] = command[idx++];
        }
        filename[f_idx] = '\0';
        
        if (command[idx] == ' ') idx++; 
        
        append_file(filename, &command[idx]);
        print_string("Content appended successfully.\n");
    }
    
    // NAYA: 'date' command
    else if (strcmp(command, "date") == 0) {
        int d, m, y;
        get_date(&d, &m, &y);
        char buffer[10];
        
        print_string("Current Date: ");
        if (d < 10) print_char('0');
        itoa(d, buffer); print_string(buffer);
        print_char('/');
        
        if (m < 10) print_char('0');
        itoa(m, buffer); print_string(buffer);
        print_char('/');
        
        print_string("20"); // 2000s Century
        if (y < 10) print_char('0');
        itoa(y, buffer); print_string(buffer);
        print_string("\n");
    }
    // NAYA: Visual File Explorer
    else if (strcmp(command, "explorer") == 0) {
        draw_window(10, 4, 60, 16, "Micro Explorer - Files", COLOR_CYAN);
        set_color(COLOR_BLACK, COLOR_CYAN);
        
        int start_y = 6;
        for(int j = 0; j < file_count; j++) {
            cursor_x = 13; cursor_y = start_y + j; update_cursor(cursor_x, cursor_y);
            print_string("-> ");
            print_string(file_system[j].name);
            print_string(" (");
            char sb[10]; itoa(file_system[j].size, sb); print_string(sb);
            print_string(" bytes)");
        }
        
        // Wapas normal color set karo shell ke liye
        cursor_x = 0; cursor_y = 21; update_cursor(cursor_x, cursor_y);
        set_color(COLOR_WHITE, COLOR_BLACK);
    }
    // NAYA: Live Code Editor
    else if (command[0] == 'e' && command[1] == 'd' && command[2] == 'i' && command[3] == 't' && command[4] == ' ') {
        char filename[32];
        int i = 5, j = 0;
        while (command[i] != '\0' && j < 31) {
            filename[j++] = command[i++];
        }
        filename[j] = '\0';
        
        // Editor start karo
        run_editor(filename);
    }
    // 👆 ------------------------------------ 👆
    else if (command[0] == 'c' && command[1] == 'a' && command[2] == 't' && command[3] == ' ') {
        char* filename = &command[4];
        int file_index = find_file(filename);
        if (file_index != -1) {
            print_string(file_system[file_index].content);
            print_string("\n");
        } else {
            print_string("File not found.\n");
        }
    }
   else if (command[0] == 'r' && command[1] == 'u' && command[2] == 'n' && command[3] == ' ') {
        char* filename = &command[4];
        int file_index = find_file(filename);
        if (file_index != -1) {
            // NAYA: Ab hum teeno cheezein bhej rahe hain (Name, Content, aur Size)
            execute_ind_app(filename, file_system[file_index].content, file_system[file_index].size);
        } else {
            print_string("App not found.\n");
        }
    }
    else if (command[0] == 'e' && command[1] == 'c' && command[2] == 'h' && command[3] == 'o' && command[4] == ' ') {
        print_string(&command[5]);
        print_string("\n");
    }
    else {
        print_string("Unknown command: ");
        print_string(command);
        print_string("\nType 'help' for a list of commands.\n");
    }
}