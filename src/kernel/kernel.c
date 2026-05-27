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
            init_gdt();
            init_paging();

            unsigned int fb_addr = (unsigned int)mbi->framebuffer_addr;
            map_vesa_memory(fb_addr);

            init_task_manager();
            init_idt();
            init_pic(); 
            init_fs();
            init_mouse();
            __asm__ volatile ("sti"); 

            vesa_framebuffer = (unsigned int*) fb_addr;

            // ----------------------------------------------------
            // DAY 124 & 125: MASTER INTERACTION ENGINE
            // ----------------------------------------------------
            int hd_mouse_x = 512, hd_mouse_y = 384; 
            int app_state = 0; // 5 = Calculator
            
            int win_x = 312, win_y = 200;
            int is_dragging = 0, start_menu_open = 0;
            int is_minimized = 0; // DAY 125: Minimization flag
            
            int ctx_open = 0, ctx_x = 0, ctx_y = 0;
            
            char term_buffer[50] = {0};
            int term_idx = 0;

            // DAY 124: Calculator Logic Variables
            char calc_display[20] = "0";
            int calc_op = 0, calc_num1 = 0, calc_new_num = 1;
            unsigned int last_click = 0;

            char key_map[128] = {0};
            key_map[0x1E] = 'a'; key_map[0x30] = 'b'; key_map[0x2E] = 'c'; key_map[0x20] = 'd';
            key_map[0x12] = 'e'; key_map[0x21] = 'f'; key_map[0x22] = 'g'; key_map[0x23] = 'h';
            key_map[0x17] = 'i'; key_map[0x24] = 'j'; key_map[0x25] = 'k'; key_map[0x26] = 'l';
            key_map[0x32] = 'm'; key_map[0x31] = 'n'; key_map[0x18] = 'o'; key_map[0x19] = 'p';
            key_map[0x10] = 'q'; key_map[0x13] = 'r'; key_map[0x1F] = 's'; key_map[0x14] = 't';
            key_map[0x16] = 'u'; key_map[0x2F] = 'v'; key_map[0x11] = 'w'; key_map[0x2D] = 'x';
            key_map[0x15] = 'y'; key_map[0x2C] = 'z'; key_map[0x39] = ' '; 
            
            while(1) {
                outb(0x70, 0x04); unsigned char rtc_h = inb(0x71);
                outb(0x70, 0x02); unsigned char rtc_m = inb(0x71);
                int h = (rtc_h & 0x0F) + ((rtc_h / 16) * 10);
                int m = (rtc_m & 0x0F) + ((rtc_m / 16) * 10);
                unsigned int current_ram = get_used_memory();

                unsigned char k_status = inb(0x64);
                if (k_status & 1) { 
                    unsigned char data = inb(0x60); 
                    
                    if (k_status & 0x20) { // --- MOUSE DATA ---
                        unsigned char m1 = data;
                        if (m1 & 0x08) {
                            mouse_wait(0); unsigned char m2 = inb(0x60);
                            mouse_wait(0); unsigned char m3 = inb(0x60);

                            int rel_x = m2 - ((m1 << 4) & 0x100);
                            int rel_y = m3 - ((m1 << 3) & 0x100);
                            int left_click = m1 & 1;
                            int right_click = m1 & 2; 

                            hd_mouse_x += rel_x; hd_mouse_y -= rel_y; 
                            if (hd_mouse_x < 0) hd_mouse_x = 0; if (hd_mouse_x > 1000) hd_mouse_x = 1000;
                            if (hd_mouse_y < 0) hd_mouse_y = 0; if (hd_mouse_y > 750) hd_mouse_y = 750;

                            if (right_click) { ctx_open = 1; ctx_x = hd_mouse_x; ctx_y = hd_mouse_y; }

                            if (left_click) {
                                if (ctx_open) {
                                    if (hd_mouse_x >= ctx_x && hd_mouse_x <= ctx_x + 160 && hd_mouse_y >= ctx_y && hd_mouse_y <= ctx_y + 120) {
                                        if (hd_mouse_y <= ctx_y + 40) { }
                                        else if (hd_mouse_y <= ctx_y + 80) { app_state = 1; win_x = 312; win_y = 200; is_minimized = 0; }
                                        else { app_state = 3; win_x = 312; win_y = 200; is_minimized = 0; }
                                    }
                                    ctx_open = 0; 
                                }
                                else { 
                                    // Window Drag (Only if not minimized)
                                    if (app_state > 0 && !is_dragging && !is_minimized) {
                                        if (hd_mouse_x >= win_x && hd_mouse_x <= win_x + 370 && hd_mouse_y >= win_y && hd_mouse_y <= win_y + 30) {
                                            is_dragging = 1; start_menu_open = 0;
                                        }
                                    }
                                    if (is_dragging) { win_x += rel_x; win_y -= rel_y; }
                                    
                                    // Window Close Button
                                    if (app_state > 0 && !is_minimized && hd_mouse_x >= win_x + 370 && hd_mouse_x <= win_x + 385 && hd_mouse_y >= win_y + 8 && hd_mouse_y <= win_y + 23) {
                                        app_state = 0; is_dragging = 0;
                                    }
                                    
                                    // DAY 124: CALCULATOR BUTTON LOGIC
                                    if (app_state == 5 && !is_minimized && !is_dragging) {
                                        if (hd_mouse_x >= win_x + 20 && hd_mouse_x <= win_x + 280 && hd_mouse_y >= win_y + 105 && hd_mouse_y <= win_y + 345) {
                                            // Crude debounce using a loop counter (since we don't have timer_ticks here easily)
                                            static int debounce = 0;
                                            if (debounce == 0) {
                                                int col = (hd_mouse_x - (win_x + 20)) / 65;
                                                int row = (hd_mouse_y - (win_y + 105)) / 60;
                                                if (col >= 0 && col < 4 && row >= 0 && row < 4) {
                                                    char keys[16] = {'7','8','9','/','4','5','6','*','1','2','3','-','C','0','=','+'};
                                                    char k = keys[(row * 4) + col];
                                                    if (k >= '0' && k <= '9') {
                                                        if (calc_new_num) { calc_display[0] = k; calc_display[1] = '\0'; calc_new_num = 0; }
                                                        else { int dlen = 0; while(calc_display[dlen]) dlen++; if (dlen < 10) { calc_display[dlen] = k; calc_display[dlen+1] = '\0'; } }
                                                    } 
                                                    else if (k == 'C') { calc_display[0] = '0'; calc_display[1] = '\0'; calc_num1 = 0; calc_op = 0; calc_new_num = 1; } 
                                                    else if (k == '+' || k == '-' || k == '*' || k == '/') {
                                                        int val=0, sign=1, idx=0; if(calc_display[0]=='-'){sign=-1;idx=1;} while(calc_display[idx]){val=val*10+(calc_display[idx]-'0');idx++;}
                                                        calc_num1 = val * sign; calc_op = (k=='+')?1:(k=='-')?2:(k=='*')?3:4; calc_new_num = 1;
                                                    } 
                                                    else if (k == '=') {
                                                        int val=0, sign=1, idx=0; if(calc_display[0]=='-'){sign=-1;idx=1;} while(calc_display[idx]){val=val*10+(calc_display[idx]-'0');idx++;}
                                                        int calc_num2 = val * sign; int res = 0;
                                                        if (calc_op == 1) res = calc_num1 + calc_num2; else if (calc_op == 2) res = calc_num1 - calc_num2;
                                                        else if (calc_op == 3) res = calc_num1 * calc_num2; else if (calc_op == 4) { if(calc_num2!=0) res = calc_num1 / calc_num2; else res = 0; }
                                                        
                                                        idx = 0;
                                                        if(res == 0) { calc_display[0]='0'; calc_display[1]='\0'; }
                                                        else {
                                                            int is_neg=0; if(res<0){is_neg=1; res=-res;}
                                                            char tmp[20]; int t=0; while(res>0){ tmp[t++]=(res%10)+'0'; res/=10; }
                                                            if(is_neg) tmp[t++]='-';
                                                            while(t>0){ calc_display[idx++] = tmp[--t]; } calc_display[idx]='\0';
                                                        }
                                                        calc_new_num = 1; calc_op = 0;
                                                    }
                                                    debounce = 10; // Block clicks for a few frames
                                                }
                                            } else { debounce--; }
                                        }
                                    }

                                    // DAY 125: TASKBAR MINIMIZATION LOGIC
                                    if (!is_dragging && hd_mouse_y >= 708 && hd_mouse_y <= 758) {
                                        if (hd_mouse_x >= 132 && hd_mouse_x <= 162) { start_menu_open = !start_menu_open; }
                                        else if (hd_mouse_x >= 182 && hd_mouse_x <= 212) { 
                                            if (app_state == 2) is_minimized = !is_minimized; else { app_state = 2; win_x = 312; win_y = 200; is_minimized = 0; } start_menu_open = 0; 
                                        }
                                        else if (hd_mouse_x >= 232 && hd_mouse_x <= 262) { 
                                            if (app_state == 3) is_minimized = !is_minimized; else { app_state = 3; win_x = 312; win_y = 200; is_minimized = 0; } start_menu_open = 0; 
                                        }
                                        else if (hd_mouse_x >= 282 && hd_mouse_x <= 312) { 
                                            if (app_state == 1) is_minimized = !is_minimized; else { app_state = 1; win_x = 312; win_y = 200; is_minimized = 0; } start_menu_open = 0; term_buffer[0] = '\0'; term_idx = 0; 
                                        }
                                        else if (hd_mouse_x >= 332 && hd_mouse_x <= 362) { 
                                            if (app_state == 5) is_minimized = !is_minimized; else { app_state = 5; win_x = 350; win_y = 150; is_minimized = 0; } start_menu_open = 0;
                                        }
                                    }
                                    
                                    // Start Menu Shutdown
                                    if (start_menu_open && hd_mouse_x >= 140 && hd_mouse_x <= 300 && hd_mouse_y >= 638 && hd_mouse_y <= 678) {
                                        __asm__ volatile ("outw %0, %1" : : "a"((unsigned short)0x2000), "Nd"((unsigned short)0x604)); 
                                        __asm__ volatile ("outw %0, %1" : : "a"((unsigned short)0x2000), "Nd"((unsigned short)0xB004));
                                    }

                                    // DESKTOP ICONS CLICK
                                    if (!is_dragging && app_state == 0 && start_menu_open == 0) {
                                        if (hd_mouse_x >= 20 && hd_mouse_x <= 60) {
                                            if (hd_mouse_y >= 20 && hd_mouse_y <= 60) { app_state = 2; win_x = 312; win_y = 200; is_minimized = 0; }
                                            else if (hd_mouse_y >= 100 && hd_mouse_y <= 140) { app_state = 4; win_x = 312; win_y = 200; is_minimized = 0; term_buffer[0] = '\0'; term_idx = 0; }
                                            else if (hd_mouse_y >= 180 && hd_mouse_y <= 220) { app_state = 5; win_x = 350; win_y = 150; is_minimized = 0; }
                                        }
                                    }
                                }
                            } else {
                                is_dragging = 0; 
                            }
                        }
                    } 
                    else {
                        // --- KEYBOARD DATA ---
                        if (!(data & 0x80)) { 
                            if (data == 0x1C) { // Enter Key
                                if (term_idx > 0 && app_state == 1 && !is_minimized) { 
                                    char echo_buf[55] = "> "; int e_idx = 0;
                                    while (term_buffer[e_idx] != '\0') { echo_buf[e_idx + 2] = term_buffer[e_idx]; e_idx++; }
                                    echo_buf[e_idx + 2] = '\0'; hd_print(echo_buf);
                                    
                                    if (term_buffer[0]=='h' && term_buffer[1]=='e' && term_buffer[2]=='l' && term_buffer[3]=='p') hd_print("HD Commands: help, about, clear");
                                    else if (term_buffer[0]=='c' && term_buffer[1]=='l' && term_buffer[2]=='e' && term_buffer[3]=='a' && term_buffer[4]=='r') hd_term_lines = 0; 
                                    else if (term_buffer[0]=='a' && term_buffer[1]=='b' && term_buffer[2]=='o' && term_buffer[3]=='u' && term_buffer[4]=='t') hd_print("Micro OS v3.0 (HD Desktop Mode)");
                                    else hd_print("Command not found.");
                                    
                                    term_buffer[0] = '\0'; term_idx = 0;
                                } else if (app_state == 4 && !is_minimized) {
                                    term_buffer[0] = '\0'; term_idx = 0; 
                                }
                            }
                            else if (data == 0x0E) { 
                                if (term_idx > 0) { term_idx--; term_buffer[term_idx] = '\0'; }
                            }
                            else if ((app_state == 1 || app_state == 4) && term_idx < 45 && !is_minimized) { 
                                char c = key_map[data];
                                if (c != 0) { term_buffer[term_idx] = c; term_idx++; term_buffer[term_idx] = '\0'; }
                            }
                        }
                    }
                }
                
                // MAIN HD RENDER CALL (Now passing is_minimized & calc_display)
                render_desktop_bg(hd_mouse_x, hd_mouse_y, app_state, win_x, win_y, term_buffer, h, m, start_menu_open, current_ram, ctx_open, ctx_x, ctx_y, is_minimized, calc_display); 
            }
        }
    }

    // ----------------------------------------------------
    // FALLBACK
    // ----------------------------------------------------
    init_gdt(); init_paging(); init_task_manager(); init_idt(); init_pic(); init_fs(); init_mouse();
    __asm__ volatile ("sti"); 

    set_color(COLOR_WHITE, COLOR_BLACK); clear_screen();
    draw_top_bar(" Micro OS v0.1 | .ind Application Runtime");
    
    print_string("[OK] Fallback System Loaded\n\n");
    print_string("Micro OS CLI Ready. Type 'help' to start.\n\n");
    
    keyboard_read_loop();
}