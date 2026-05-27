#include "../drivers/display.h"
#include "../drivers/keyboard.h"
#include "../fs/fs.h"
#include "../kernel/gdt.h" 
#include "../kernel/idt.h" 
#include "../kernel/pic.h"        
#include "../runtime/ind_runner.h" 
#include "../drivers/mouse.h"      
#include "../kernel/paging.h" 
#include "../kernel/memory.h" 
#include "../kernel/task.h"   
#include "../kernel/multiboot.h" 
#include "../gui/modern_ui.h" 

void kernel_main(unsigned int magic, unsigned int addr) {
    if (magic == 0x2BADB002) { 
        multiboot_info_t* mbi = (multiboot_info_t*) addr;
        if (mbi->flags & (1 << 12)) {
            init_gdt(); init_paging();
            unsigned int fb_addr = (unsigned int)mbi->framebuffer_addr;
            map_vesa_memory(fb_addr);

            init_task_manager(); init_idt(); init_pic(); init_fs(); init_mouse();
            __asm__ volatile ("sti"); 
            vesa_framebuffer = (unsigned int*) fb_addr;

            int hd_mouse_x = 512, hd_mouse_y = 384; 
            int app_state = 0; 
            int win_x = 312, win_y = 200;
            int is_dragging = 0, start_menu_open = 0, is_minimized = 0;
            int ctx_open = 0, ctx_x = 0, ctx_y = 0;
            char term_buffer[50] = {0}; int term_idx = 0;

            char calc_display[20] = "0"; int calc_op = 0, calc_num1 = 0, calc_new_num = 1;
            int theme_idx = 0; unsigned int themes[4] = {0x001E1E2E, 0x00F8F9FA, 0x000F4C75, 0x001B4332}; 
            int game_board[9] = {0}; int game_turn = 1, game_winner = 0;

            // DAY 128 FIX: Real-Time Hardware Clock based Screensaver!
            int idle_seconds = 0;
            int is_screensaver = 0;
            int ss_x = 100, ss_y = 100, ss_dx = 3, ss_dy = 3;
            int last_rtc_s = -1;

            // DAY 129: Paint variables
            unsigned int brush_color = 0x000000;

            int prev_left_click = 0;
            char key_map[128] = {0};
            key_map[0x1E]='a'; key_map[0x30]='b'; key_map[0x2E]='c'; key_map[0x20]='d'; key_map[0x12]='e'; key_map[0x21]='f'; key_map[0x22]='g'; key_map[0x23]='h'; key_map[0x17]='i'; key_map[0x24]='j'; key_map[0x25]='k'; key_map[0x26]='l'; key_map[0x32]='m'; key_map[0x31]='n'; key_map[0x18]='o'; key_map[0x19]='p'; key_map[0x10]='q'; key_map[0x13]='r'; key_map[0x1F]='s'; key_map[0x14]='t'; key_map[0x16]='u'; key_map[0x2F]='v'; key_map[0x11]='w'; key_map[0x2D]='x'; key_map[0x15]='y'; key_map[0x2C]='z'; key_map[0x39]=' '; 
            
            while(1) {
                // HARDWARE CLOCK READING
                outb(0x70, 0x04); unsigned char rtc_h = inb(0x71);
                outb(0x70, 0x02); unsigned char rtc_m = inb(0x71);
                outb(0x70, 0x00); unsigned char rtc_s = inb(0x71);
                
                int h = (rtc_h & 0x0F) + ((rtc_h / 16) * 10);
                int m = (rtc_m & 0x0F) + ((rtc_m / 16) * 10);
                int s = (rtc_s & 0x0F) + ((rtc_s / 16) * 10);

                // REAL-TIME SCREENSAVER LOGIC!
                if (s != last_rtc_s) {
                    last_rtc_s = s;
                    idle_seconds++;
                }
                if (idle_seconds >= 10) is_screensaver = 1; 

                if (is_screensaver) {
                    ss_x += ss_dx; ss_y += ss_dy;
                    if (ss_x <= 0 || ss_x >= 850) ss_dx = -ss_dx;
                    if (ss_y <= 0 || ss_y >= 740) ss_dy = -ss_dy;
                }

                unsigned int current_ram = get_used_memory();
                unsigned char k_status = inb(0x64);
                if (k_status & 1) { 
                    unsigned char data = inb(0x60); 
                    if (k_status & 0x20) { // --- MOUSE ---
                        unsigned char m1 = data;
                        if (m1 & 0x08) {
                            mouse_wait(0); unsigned char m2 = inb(0x60);
                            mouse_wait(0); unsigned char m3 = inb(0x60);
                            int rel_x = m2 - ((m1 << 4) & 0x100);
                            int rel_y = m3 - ((m1 << 3) & 0x100);
                            int left_click = m1 & 1; int right_click = m1 & 2; 

                            int just_clicked = (left_click && !prev_left_click);
                            prev_left_click = left_click;

                            // Reset Screensaver on ACTUAL movement
                            if (rel_x > 2 || rel_x < -2 || rel_y > 2 || rel_y < -2 || left_click || right_click) {
                                idle_seconds = 0; is_screensaver = 0;
                            }

                            hd_mouse_x += rel_x; hd_mouse_y -= rel_y; 
                            if (hd_mouse_x < 0) hd_mouse_x = 0; if (hd_mouse_x > 1000) hd_mouse_x = 1000;
                            if (hd_mouse_y < 0) hd_mouse_y = 0; if (hd_mouse_y > 750) hd_mouse_y = 750;

                            if (right_click && !is_screensaver) { ctx_open = 1; ctx_x = hd_mouse_x; ctx_y = hd_mouse_y; }

                            if (left_click && !is_screensaver) {
                                if (ctx_open) {
                                    if (hd_mouse_x >= ctx_x && hd_mouse_x <= ctx_x + 160 && hd_mouse_y >= ctx_y && hd_mouse_y <= ctx_y + 120) {
                                        if (hd_mouse_y <= ctx_y + 40) { }
                                        else if (hd_mouse_y <= ctx_y + 80) { if (just_clicked) theme_idx = (theme_idx + 1) % 4; } 
                                        else { app_state = 3; win_x = 312; win_y = 200; is_minimized = 0; }
                                    }
                                    if (just_clicked) ctx_open = 0; 
                                }
                                else { 
                                    if (app_state > 0 && !is_minimized && hd_mouse_x >= win_x && hd_mouse_x <= win_x + 370 && hd_mouse_y >= win_y && hd_mouse_y <= win_y + 30) {
                                        is_dragging = 1; start_menu_open = 0;
                                    }
                                    if (is_dragging) { win_x += rel_x; win_y -= rel_y; }
                                    
                                    if (app_state > 0 && !is_minimized && hd_mouse_x >= win_x + 370 && hd_mouse_x <= win_x + 385 && hd_mouse_y >= win_y + 8 && hd_mouse_y <= win_y + 23) {
                                        if (just_clicked) { app_state = 0; is_dragging = 0; }
                                    }

                                    // DAY 129: HD PAINT APP LOGIC
                                    if (app_state == 7 && !is_minimized && !is_dragging) {
                                        // Drawing on canvas
                                        if (hd_mouse_x >= win_x+20 && hd_mouse_x < win_x+280 && hd_mouse_y >= win_y+40 && hd_mouse_y < win_y+240) {
                                            int px = hd_mouse_x - (win_x+20);
                                            int py = hd_mouse_y - (win_y+40);
                                            // Brush stroke (3x3 pixels)
                                            for(int i=-1; i<=1; i++) {
                                                for(int j=-1; j<=1; j++) {
                                                    if(py+i >= 0 && py+i < 200 && px+j >= 0 && px+j < 260) {
                                                        hd_paint_canvas[(py+i)*260 + (px+j)] = brush_color;
                                                    }
                                                }
                                            }
                                        }
                                        // Palette Click
                                        if (just_clicked && hd_mouse_y >= win_y+260 && hd_mouse_y <= win_y+290) {
                                            if (hd_mouse_x >= win_x+20 && hd_mouse_x <= win_x+50) brush_color = 0x00E53935; // Red
                                            else if (hd_mouse_x >= win_x+60 && hd_mouse_x <= win_x+90) brush_color = 0x004CAF50; // Green
                                            else if (hd_mouse_x >= win_x+100 && hd_mouse_x <= win_x+130) brush_color = 0x002196F3; // Blue
                                            else if (hd_mouse_x >= win_x+140 && hd_mouse_x <= win_x+170) brush_color = 0x00000000; // Black
                                            else if (hd_mouse_x >= win_x+180 && hd_mouse_x <= win_x+210) brush_color = 0xFFFFFFFF; // Eraser
                                            else if (hd_mouse_x >= win_x+220 && hd_mouse_x <= win_x+250) {
                                                for(int i=0; i<260*200; i++) hd_paint_canvas[i] = 0xFFFFFF; // Clear
                                            }
                                        }
                                    }
                                    
                                    // Tic-Tac-Toe
                                    if (app_state == 6 && !is_minimized && !is_dragging) {
                                        if (hd_mouse_x >= win_x+20 && hd_mouse_x <= win_x+280 && hd_mouse_y >= win_y+50 && hd_mouse_y <= win_y+330) {
                                            if (just_clicked) { 
                                                if (game_winner != 0) {
                                                    for(int i=0; i<9; i++) game_board[i]=0;
                                                    game_winner=0; game_turn=1;
                                                } else {
                                                    int col = (hd_mouse_x - (win_x + 20)) / 90;
                                                    int row = (hd_mouse_y - (win_y + 50)) / 95;
                                                    if (col >= 0 && col < 3 && row >= 0 && row < 3) {
                                                        int cell = (row * 3) + col;
                                                        if (game_board[cell] == 0) {
                                                            game_board[cell] = game_turn;
                                                            int w[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
                                                            for(int i=0; i<8; i++) if(game_board[w[i][0]] != 0 && game_board[w[i][0]] == game_board[w[i][1]] && game_board[w[i][1]] == game_board[w[i][2]]) game_winner = game_board[w[i][0]];
                                                            if (game_winner == 0) { int full = 1; for(int i=0;i<9;i++) if(game_board[i]==0) full=0; if (full) game_winner = 3; }
                                                            game_turn = (game_turn == 1) ? 2 : 1;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    // Calculator
                                    if (app_state == 5 && !is_minimized && !is_dragging) {
                                        if (hd_mouse_x >= win_x + 20 && hd_mouse_x <= win_x + 280 && hd_mouse_y >= win_y + 105 && hd_mouse_y <= win_y + 345) {
                                            if (just_clicked) { 
                                                int col = (hd_mouse_x - (win_x + 20)) / 65; int row = (hd_mouse_y - (win_y + 105)) / 60;
                                                if (col >= 0 && col < 4 && row >= 0 && row < 4) {
                                                    char keys[16] = {'7','8','9','/','4','5','6','*','1','2','3','-','C','0','=','+'};
                                                    char k = keys[(row * 4) + col];
                                                    if (k >= '0' && k <= '9') {
                                                        if (calc_new_num) { calc_display[0] = k; calc_display[1] = '\0'; calc_new_num = 0; }
                                                        else { int dlen = 0; while(calc_display[dlen]) dlen++; if (dlen < 10) { calc_display[dlen] = k; calc_display[dlen+1] = '\0'; } }
                                                    } else if (k == 'C') { calc_display[0] = '0'; calc_display[1] = '\0'; calc_num1 = 0; calc_op = 0; calc_new_num = 1; } 
                                                    else if (k == '+' || k == '-' || k == '*' || k == '/') {
                                                        int val=0, sign=1, idx=0; if(calc_display[0]=='-'){sign=-1;idx=1;} while(calc_display[idx]){val=val*10+(calc_display[idx]-'0');idx++;} calc_num1 = val * sign; calc_op = (k=='+')?1:(k=='-')?2:(k=='*')?3:4; calc_new_num = 1;
                                                    } else if (k == '=') {
                                                        int val=0, sign=1, idx=0; if(calc_display[0]=='-'){sign=-1;idx=1;} while(calc_display[idx]){val=val*10+(calc_display[idx]-'0');idx++;} int calc_num2 = val * sign; int res = 0;
                                                        if (calc_op == 1) res = calc_num1 + calc_num2; else if (calc_op == 2) res = calc_num1 - calc_num2; else if (calc_op == 3) res = calc_num1 * calc_num2; else if (calc_op == 4) { if(calc_num2!=0) res = calc_num1 / calc_num2; else res = 0; }
                                                        idx = 0; if(res == 0) { calc_display[0]='0'; calc_display[1]='\0'; } else { int is_neg=0; if(res<0){is_neg=1; res=-res;} char tmp[20]; int t=0; while(res>0){ tmp[t++]=(res%10)+'0'; res/=10; } if(is_neg) tmp[t++]='-'; while(t>0){ calc_display[idx++] = tmp[--t]; } calc_display[idx]='\0'; } calc_new_num = 1; calc_op = 0;
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    // TASKBAR
                                    if (!is_dragging && hd_mouse_y >= 708 && hd_mouse_y <= 758) {
                                        if (just_clicked) {
                                            if (hd_mouse_x >= 132 && hd_mouse_x <= 162) { start_menu_open = !start_menu_open; }
                                            else if (hd_mouse_x >= 182 && hd_mouse_x <= 212) { if (app_state == 2) is_minimized = !is_minimized; else { app_state = 2; win_x = 312; win_y = 200; is_minimized = 0; } start_menu_open = 0; }
                                            else if (hd_mouse_x >= 232 && hd_mouse_x <= 262) { if (app_state == 3) is_minimized = !is_minimized; else { app_state = 3; win_x = 312; win_y = 200; is_minimized = 0; } start_menu_open = 0; }
                                            else if (hd_mouse_x >= 282 && hd_mouse_x <= 312) { if (app_state == 1) is_minimized = !is_minimized; else { app_state = 1; win_x = 312; win_y = 200; is_minimized = 0; } start_menu_open = 0; term_buffer[0] = '\0'; term_idx = 0; }
                                            else if (hd_mouse_x >= 332 && hd_mouse_x <= 362) { if (app_state == 5) is_minimized = !is_minimized; else { app_state = 5; win_x = 350; win_y = 150; is_minimized = 0; } start_menu_open = 0; }
                                            else if (hd_mouse_x >= 382 && hd_mouse_x <= 412) { if (app_state == 6) is_minimized = !is_minimized; else { app_state = 6; win_x = 350; win_y = 150; is_minimized = 0; } start_menu_open = 0; }
                                        }
                                    }
                                    
                                    // DAY 130: LIVE START MENU CLICKS
                                    if (start_menu_open && just_clicked) {
                                        int sm_x = 120, sm_y = 398; // 708 - 300 - 10
                                        if (hd_mouse_x >= sm_x + 20 && hd_mouse_x <= sm_x + 200) {
                                            if (hd_mouse_y >= sm_y + 70 && hd_mouse_y <= sm_y + 90) { app_state = 4; win_x = 312; win_y = 200; start_menu_open = 0; is_minimized = 0; term_buffer[0] = '\0'; term_idx = 0; }
                                            else if (hd_mouse_y >= sm_y + 100 && hd_mouse_y <= sm_y + 120) { app_state = 5; win_x = 312; win_y = 200; start_menu_open = 0; is_minimized = 0; }
                                            else if (hd_mouse_y >= sm_y + 130 && hd_mouse_y <= sm_y + 150) { app_state = 6; win_x = 312; win_y = 200; start_menu_open = 0; is_minimized = 0; }
                                            else if (hd_mouse_y >= sm_y + 160 && hd_mouse_y <= sm_y + 180) { app_state = 7; win_x = 312; win_y = 200; start_menu_open = 0; is_minimized = 0; }
                                        }
                                        // Shut down
                                        if (hd_mouse_x >= sm_x + 20 && hd_mouse_x <= sm_x + 180 && hd_mouse_y >= sm_y + 240 && hd_mouse_y <= sm_y + 280) {
                                            __asm__ volatile ("outw %0, %1" : : "a"((unsigned short)0x2000), "Nd"((unsigned short)0x604)); 
                                            __asm__ volatile ("outw %0, %1" : : "a"((unsigned short)0x2000), "Nd"((unsigned short)0xB004));
                                        }
                                    }

                                    // DESKTOP ICONS
                                    if (!is_dragging && app_state == 0 && start_menu_open == 0) {
                                        if (just_clicked && hd_mouse_x >= 20 && hd_mouse_x <= 60) {
                                            if (hd_mouse_y >= 20 && hd_mouse_y <= 60) { app_state = 2; win_x = 312; win_y = 200; is_minimized = 0; }
                                            else if (hd_mouse_y >= 100 && hd_mouse_y <= 140) { app_state = 4; win_x = 312; win_y = 200; is_minimized = 0; term_buffer[0] = '\0'; term_idx = 0; }
                                            else if (hd_mouse_y >= 180 && hd_mouse_y <= 220) { app_state = 5; win_x = 350; win_y = 150; is_minimized = 0; }
                                            else if (hd_mouse_y >= 260 && hd_mouse_y <= 300) { app_state = 6; win_x = 350; win_y = 150; is_minimized = 0; }
                                        }
                                    }
                                }
                            } else { is_dragging = 0; }
                        }
                    } else { // KEYBOARD
                        if (!(data & 0x80)) { 
                            idle_seconds = 0; is_screensaver = 0; // RESET
                            if (data == 0x1C) { 
                                if (term_idx > 0 && app_state == 1 && !is_minimized) { 
                                    char echo_buf[55] = "> "; int e_idx = 0;
                                    while (term_buffer[e_idx] != '\0') { echo_buf[e_idx + 2] = term_buffer[e_idx]; e_idx++; } echo_buf[e_idx + 2] = '\0'; hd_print(echo_buf);
                                    if (term_buffer[0]=='h' && term_buffer[1]=='e' && term_buffer[2]=='l' && term_buffer[3]=='p') hd_print("HD Commands: help, about, clear"); else if (term_buffer[0]=='c' && term_buffer[1]=='l' && term_buffer[2]=='e' && term_buffer[3]=='a' && term_buffer[4]=='r') hd_term_lines = 0; else if (term_buffer[0]=='a' && term_buffer[1]=='b' && term_buffer[2]=='o' && term_buffer[3]=='u' && term_buffer[4]=='t') hd_print("Micro OS v3.0 (HD Desktop Mode)"); else hd_print("Command not found."); term_buffer[0] = '\0'; term_idx = 0;
                                } else if (app_state == 4 && !is_minimized) { term_buffer[0] = '\0'; term_idx = 0; }
                            }
                            else if (data == 0x0E) { if (term_idx > 0) { term_idx--; term_buffer[term_idx] = '\0'; } }
                            else if ((app_state == 1 || app_state == 4) && term_idx < 45 && !is_minimized) { char c = key_map[data]; if (c != 0) { term_buffer[term_idx] = c; term_idx++; term_buffer[term_idx] = '\0'; } }
                        }
                    }
                }
                render_desktop_bg(hd_mouse_x, hd_mouse_y, app_state, win_x, win_y, term_buffer, h, m, start_menu_open, current_ram, ctx_open, ctx_x, ctx_y, is_minimized, calc_display, themes[theme_idx], game_board, game_winner, is_screensaver, ss_x, ss_y); 
            }
        }
    }

    init_gdt(); init_paging(); init_task_manager(); init_idt(); init_pic(); init_fs(); init_mouse();
    __asm__ volatile ("sti"); 
    set_color(COLOR_WHITE, COLOR_BLACK); clear_screen();
    draw_top_bar(" Micro OS v0.1 | .ind Application Runtime");
    print_string("[OK] Fallback System Loaded\n\n"); print_string("Micro OS CLI Ready. Type 'help' to start.\n\n");
    keyboard_read_loop();
}