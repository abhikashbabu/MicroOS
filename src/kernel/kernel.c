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
#include "../kernel/acpi.h"
#include "../drivers/net.h"
#include "../drivers/ata.h"
#include "../fs/fat32.h"
// DAY 162: Z-Index Memory
int z_bg_app = 0;
int z_bg_x = 340;
int z_bg_y = 230;

// DAY 163: DYNAMIC HARDWARE STATES
int sys_brightness = 150; 
int sys_volume = 120;     
int power_saver = 0;      
int screen_width = 1024;  // Default fallback
int screen_height = 768;  // Default fallback

// ==========================================
// DAY 165: EVENT-DRIVEN IRQ HANDLERS
// ==========================================
int hd_mouse_x = 512, hd_mouse_y = 384;
int left_click = 0, right_click = 0;
int mouse_cycle = 0;
unsigned char m_packet[3];

volatile unsigned char last_scancode = 0; 

void mouse_irq_handler() {
    unsigned char status = inb(0x64);
    if (!(status & 1)) { outb(0xA0, 0x20); outb(0x20, 0x20); return; }
    
    unsigned char b = inb(0x60); 
    switch(mouse_cycle) {
        case 0:
            if (b & 0x08) { m_packet[0] = b; mouse_cycle++; } 
            break;
        case 1:
            m_packet[1] = b; mouse_cycle++; 
            break;
        case 2:
            m_packet[2] = b; mouse_cycle = 0; 
            
            left_click = m_packet[0] & 1;
            right_click = (m_packet[0] & 2) >> 1;
            
            int dx = m_packet[1] - ((m_packet[0] << 4) & 0x100);
            int dy = m_packet[2] - ((m_packet[0] << 3) & 0x100);
            
            hd_mouse_x += dx;
            hd_mouse_y -= dy; 
            
            if(hd_mouse_x < 0) hd_mouse_x = 0;
            if(hd_mouse_y < 0) hd_mouse_y = 0;

            // NAYA DYNAMIC LIMIT:
            if(hd_mouse_x >= screen_width) hd_mouse_x = screen_width - 1;
            if(hd_mouse_y >= screen_height) hd_mouse_y = screen_height - 1;
            break;
    }
    outb(0xA0, 0x20); outb(0x20, 0x20);
}

void keyboard_irq_handler() {
    unsigned char status = inb(0x64);
    if (status & 1) { last_scancode = inb(0x60); }
    outb(0x20, 0x20);
}

void open_window(int new_app, int* fg_app, int* fg_x, int* fg_y) {
    *fg_app = new_app;    
    *fg_x = 312;          
    *fg_y = 200;          
    z_bg_app = 0;         
}

void hd_play_sound(unsigned int nFrequence) {
    unsigned int Div; unsigned char tmp; 
    Div = 1193180 / nFrequence;
    outb(0x43, 0xb6); outb(0x42, (unsigned char) (Div) ); outb(0x42, (unsigned char) (Div >> 8));
    tmp = inb(0x61); if (tmp != (tmp | 3)) { outb(0x61, tmp | 3); }
}

void hd_stop_sound() { unsigned char tmp = inb(0x61) & 0xFC; outb(0x61, tmp); }
void background_test_task() { while(1) { __asm__ volatile ("nop"); } }

void kernel_main(unsigned int magic, unsigned int addr) {
    if (magic == 0x2BADB002) { 
        multiboot_info_t* mbi = (multiboot_info_t*) addr;
        if (mbi->flags & (1 << 12)) {
            init_gdt(); init_paging();
            unsigned int fb_addr = (unsigned int)mbi->framebuffer_addr;
            screen_width = mbi->framebuffer_width;
            screen_height = mbi->framebuffer_height;
            map_vesa_memory(fb_addr);
            
            init_task_manager(); 
            create_os_task(background_test_task, 999); 
            idt_init(); 
            pic_init(); 
            init_fs(); 
            init_mouse();
            init_acpi(); 
            
            __asm__ volatile ("sti"); 
            vesa_framebuffer = (unsigned int*) fb_addr;

          play_boot_animation();
            create_file("app.ind", "T:Welcome App;M:What is your name?;I:Enter Name;B:Submit;");
            
            // ==============================================================
            // 1. NETWORK SYSTEM INITIALIZE
            // ==============================================================
            if (pci_get_rtl8139_mac()) {
                char mac_str[30] = "MAC: ";
                char hex_chars[] = "0123456789ABCDEF";
                int idx = 5;
                for(int i = 0; i < 6; i++) {
                    mac_str[idx++] = hex_chars[(rtl_mac[i] >> 4) & 0x0F];
                    mac_str[idx++] = hex_chars[rtl_mac[i] & 0x0F];
                    if(i < 5) mac_str[idx++] = ':';
                }
                mac_str[idx] = '\0';
                hd_print(mac_str);
                
                rtl8139_init();
                hd_print("[OK] RTL8139 Driver Initialized!");
                net_send_arp_request();
            } else {
                hd_print("[FAIL] No Network Card Found.");
            }

            // ==============================================================
            // 2. HARD DRIVE & FAT32 INITIALIZE (CLEANED UP!)
            // ==============================================================
            hd_print("[HDD] Mounting C: Drive...");
            init_fat32();
            fat32_list_root();

            // Yahan se tumhare saare variables shuru hote hain
            int app_state = -1; int win_x = 312, win_y = 200; 
            int is_dragging = 0, start_menu_open = 0, is_minimized = 0;
            int ctx_open = 0, ctx_x = 0, ctx_y = 0; 
            char term_buffer[50] = {0}; int term_idx = 0;
            char pwd_buffer[10] = {0}; int pwd_idx = 0; 
            char calc_display[20] = "0"; int calc_op = 0, calc_num1 = 0, calc_new_num = 1;
            int theme_idx = 0; 
            int game_board[9] = {0}; int game_turn = 1, game_winner = 0;
            int idle_seconds = 0, is_screensaver = 0; 
            int ss_x = 100, ss_y = 100, ss_dx = 3, ss_dy = 3; 
            int last_rtc_s = -1; int system_uptime = 0; 
            unsigned int brush_color = 0x000000;

            int icon_x[12] = {20, 20, 20, 20, 20, 100, 100, 100, 100, 100, 180, 180}; 
            int icon_y[12] = {20, 100, 180, 260, 340, 20, 100, 180, 260, 340, 20, 100};
            int dragging_icon = -1, icon_moved = 0; 
            int prev_left_click = 0;
            int prev_hd_mouse_x = 512, prev_hd_mouse_y = 384; 

            int action_center_open = 0, ind_loading = 0, target_ind_file = -1; 
            char ind_input_buf[30] = ""; int ind_input_idx = 0;
            int app_widths[18] = {0, 420, 500, 450, 400, 300, 300, 300, 300, 350, 300, 400, 350, 360, 350, 470, 400, 500};
            char notif_msg[50] = ""; int notif_timer = 0; int notif_y = -100;
            int now_playing = 0;

            char key_map[128] = {0}; 
            key_map[0x1E]='a'; key_map[0x30]='b'; key_map[0x2E]='c'; key_map[0x20]='d'; 
            key_map[0x12]='e'; key_map[0x21]='f'; key_map[0x22]='g'; key_map[0x23]='h'; 
            key_map[0x17]='i'; key_map[0x24]='j'; key_map[0x25]='k'; key_map[0x26]='l'; 
            key_map[0x32]='m'; key_map[0x31]='n'; key_map[0x18]='o'; key_map[0x19]='p'; 
            key_map[0x10]='q'; key_map[0x13]='r'; key_map[0x1F]='s'; key_map[0x14]='t'; 
            key_map[0x16]='u'; key_map[0x2F]='v'; key_map[0x11]='w'; key_map[0x2D]='x'; 
            key_map[0x15]='y'; key_map[0x2C]='z'; key_map[0x39]=' '; 
            key_map[0x02]='1'; key_map[0x03]='2'; key_map[0x04]='3'; key_map[0x05]='4'; 
            key_map[0x06]='5'; key_map[0x07]='6'; key_map[0x08]='7'; key_map[0x09]='8'; 
            key_map[0x0A]='9'; key_map[0x0B]='0';
            key_map[0x4F]='1'; key_map[0x50]='2'; key_map[0x51]='3'; key_map[0x4B]='4'; 
            key_map[0x4C]='5'; key_map[0x4D]='6'; key_map[0x47]='7'; key_map[0x48]='8'; 
            key_map[0x49]='9'; key_map[0x52]='0';

            while(1) {
                net_poll_rx();
                outb(0x70, 0x04); unsigned char rtc_h = inb(0x71); 
                outb(0x70, 0x02); unsigned char rtc_m = inb(0x71); 
                outb(0x70, 0x00); unsigned char rtc_s = inb(0x71);
                outb(0x70, 0x07); unsigned char rtc_d = inb(0x71); 
                outb(0x70, 0x08); unsigned char rtc_mon = inb(0x71); 
                outb(0x70, 0x09); unsigned char rtc_y = inb(0x71);
                int h = (rtc_h & 0x0F) + ((rtc_h / 16) * 10); 
                int m = (rtc_m & 0x0F) + ((rtc_m / 16) * 10); 
                int s = (rtc_s & 0x0F) + ((rtc_s / 16) * 10);
                int day = (rtc_d & 0x0F) + ((rtc_d / 16) * 10); 
                int month = (rtc_mon & 0x0F) + ((rtc_mon / 16) * 10); 
                int year = (rtc_y & 0x0F) + ((rtc_y / 16) * 10) + 2000;

                if (s != last_rtc_s) { 
                    last_rtc_s = s; idle_seconds++; system_uptime++; 
                    process_power_drain(system_uptime); 
                    if (notif_timer > 0) notif_timer--; 
                }
                
                if (notif_timer > 0 && notif_y < 20) { notif_y += 5; } 
                else if (notif_timer <= 0 && notif_y > -100) { notif_y -= 5; }

                if (idle_seconds >= 10 && app_state != -1) { is_screensaver = 1; }
                
                if (is_screensaver) { 
                    ss_x += ss_dx; ss_y += ss_dy; 
                    if (ss_x <= 0 || ss_x >= screen_width-150) ss_dx = -ss_dx; 
                    if (ss_y <= 0 || ss_y >= screen_height-50) ss_dy = -ss_dy; 
                }

                if (ind_loading > 0 && ind_loading < 140) {
                    ind_loading++;
                    if (ind_loading == 139) {
                        ind_loading = 0;
                        if (target_ind_file != -1) {
                            char* content = file_system[target_ind_file].content;
                            int i = 0, t_idx = 0, m_idx = 0, b_idx = 0, in_idx = 0, mode = 0;
                            ind_app_btn[0] = '\0'; ind_app_input[0] = '\0'; ind_input_buf[0] = '\0'; ind_input_idx = 0;
                            
                            while(content[i] != '\0') {
                                if (content[i] == 'T' && content[i+1] == ':') { mode = 1; i+=2; continue; }
                                if (content[i] == 'M' && content[i+1] == ':') { mode = 2; i+=2; continue; }
                                if (content[i] == 'B' && content[i+1] == ':') { mode = 3; i+=2; continue; } 
                                if (content[i] == 'I' && content[i+1] == ':') { mode = 4; i+=2; continue; } 
                                if (content[i] == ';') { mode = 0; i++; continue; }
                                
                                if (mode == 1 && t_idx < 49) ind_app_title[t_idx++] = content[i];
                                if (mode == 2 && m_idx < 99) ind_app_msg[m_idx++] = content[i];
                                if (mode == 3 && b_idx < 29) ind_app_btn[b_idx++] = content[i];
                                if (mode == 4 && in_idx < 29) ind_app_input[in_idx++] = content[i];
                                i++;
                            }
                            ind_app_title[t_idx] = '\0'; ind_app_msg[m_idx] = '\0'; ind_app_btn[b_idx] = '\0'; ind_app_input[in_idx] = '\0';
                            app_state = 11; win_x = 312; win_y = 200; is_minimized = 0;
                        }
                    }
                }

                unsigned int current_ram = get_used_memory();
                int rel_x = hd_mouse_x - prev_hd_mouse_x;
                int rel_y = prev_hd_mouse_y - hd_mouse_y; 
                prev_hd_mouse_x = hd_mouse_x; prev_hd_mouse_y = hd_mouse_y;
                
                unsigned char data = last_scancode; last_scancode = 0;
                int just_clicked = (left_click && !prev_left_click); 
                prev_left_click = left_click;

                if (left_click || right_click) { idle_seconds = 0; is_screensaver = 0; }
                

                if (data != 0 && !(data & 0x80)) {
                    idle_seconds = 0; is_screensaver = 0; 
                    if (app_state == -1) {
                        if (data == 0x1C || data == 0x9C) { 
                            if (pwd_buffer[0]=='1' && pwd_buffer[1]=='2' && pwd_buffer[2]=='3' && pwd_buffer[3]=='4' && pwd_buffer[4]=='\0') { app_state = 0; } 
                            pwd_buffer[0] = '\0'; pwd_idx = 0; 
                        }
                        else if (data == 0x0E) { if (pwd_idx > 0) { pwd_idx--; pwd_buffer[pwd_idx] = '\0'; } }
                        else if (pwd_idx < 8) { char c = key_map[data]; if (c >= '0' && c <= '9') { pwd_buffer[pwd_idx++] = c; pwd_buffer[pwd_idx] = '\0'; } }
                    } else {
                        if (data == 0x1C || data == 0x9C) { 
                            if (term_idx > 0 && app_state == 1 && !is_minimized) { 
                                char echo_buf[55] = "> "; int e_idx = 0;
                                while (term_buffer[e_idx] != '\0') { echo_buf[e_idx + 2] = term_buffer[e_idx]; e_idx++; } 
                                echo_buf[e_idx + 2] = '\0'; hd_print(echo_buf);
                                
                                if (term_buffer[0]=='r' && term_buffer[1]=='u' && term_buffer[2]=='n') { target_ind_file = find_file("app.ind"); if (target_ind_file != -1) ind_loading = 1; else hd_print("Error: app.ind not found!"); }
                                else if (term_buffer[0]=='h' && term_buffer[1]=='e' && term_buffer[2]=='l' && term_buffer[3]=='p') { hd_print("Commands: help, about, clear, run [app]"); }
                                else if (term_buffer[0]=='c' && term_buffer[1]=='l' && term_buffer[2]=='e' && term_buffer[3]=='a' && term_buffer[4]=='r') { hd_term_lines = 0; }
                                else if (term_buffer[0]=='a' && term_buffer[1]=='b' && term_buffer[2]=='o' && term_buffer[3]=='u' && term_buffer[4]=='t') { hd_print("Micro OS JS Bridge Ready"); }
                                // ================================================
                                // NAYA: PING COMMAND
                                // ================================================
                                else if (term_buffer[0]=='p' && term_buffer[1]=='i' && term_buffer[2]=='n' && term_buffer[3]=='g') { 
                                    if (network_ready) {
                                        net_ping_google();
                                    } else {
                                        hd_print("Error: Connect to Network First!");
                                    }
                                }
                            
                                else { hd_print("Command not found."); }
                                term_buffer[0] = '\0'; term_idx = 0;
                            } 
                            else if (app_state == 4 && !is_minimized) { term_buffer[0] = '\0'; term_idx = 0; }
                        }
                        else if (data == 0x0E) { 
                            if (app_state == 1 || app_state == 4) { if (term_idx > 0) { term_idx--; term_buffer[term_idx] = '\0'; } }
                            else if (app_state == 11 && ind_input_idx > 0 && !is_minimized) { ind_input_idx--; ind_input_buf[ind_input_idx] = '\0'; }
                        }
                        else if (!is_minimized) { 
                            char c = key_map[data]; 
                            if (c != 0) { 
                                if (app_state == 1 || app_state == 4) { if (term_idx < 45) { term_buffer[term_idx] = c; term_idx++; term_buffer[term_idx] = '\0'; } }
                                else if (app_state == 11 && ind_input_idx < 25) { ind_input_buf[ind_input_idx] = c; ind_input_idx++; ind_input_buf[ind_input_idx] = '\0'; }
                            } 
                        }
                    }
                }

                if (app_state == -1) {
                    render_desktop_bg(hd_mouse_x, hd_mouse_y, app_state, win_x, win_y, term_buffer, h, m, start_menu_open, current_ram, ctx_open, ctx_x, ctx_y, is_minimized, calc_display, theme_idx, game_board, game_winner, is_screensaver, ss_x, ss_y, icon_x, icon_y, pwd_buffer, system_uptime, action_center_open, ind_loading, notif_y, notif_msg, ind_input_buf, day, month, year, now_playing);
                    continue; 
                }
                
                if (right_click && !is_screensaver) { ctx_open = 1; ctx_x = hd_mouse_x; ctx_y = hd_mouse_y; }

                if (left_click && !is_screensaver) {
                    int ac_btn_x = screen_width - 224; // Action center button box x (approx)
                    if (just_clicked && hd_mouse_x >= ac_btn_x && hd_mouse_y <= 40) { 
                        action_center_open = !action_center_open; just_clicked = 0;
                    }
                    if (action_center_open && just_clicked) {
                        int ac_x = screen_width - 274, ac_y = 50; // Dynamic action center box
                        if (hd_mouse_x >= ac_x + 30 && hd_mouse_x <= ac_x + 210 && hd_mouse_y >= ac_y + 195 && hd_mouse_y <= ac_y + 215) {
                            sys_volume = hd_mouse_x - (ac_x + 30); just_clicked = 0;
                        }
                        if (hd_mouse_x >= ac_x + 30 && hd_mouse_x <= ac_x + 210 && hd_mouse_y >= ac_y + 295 && hd_mouse_y <= ac_y + 315) {
                            sys_brightness = hd_mouse_x - (ac_x + 30); just_clicked = 0;
                        }
                    }

                    if (app_state == 0 && just_clicked) {
                        int wid_x = screen_width - 244, wid_y = 100;
                        if (hd_mouse_x >= wid_x + 120 && hd_mouse_x <= wid_x + 150 && hd_mouse_y >= wid_y + 105 && hd_mouse_y <= wid_y + 120) {
                            power_saver = !power_saver; just_clicked = 0;
                        }
                    }

                    if (ctx_open && just_clicked) {
                        if (hd_mouse_x >= ctx_x && hd_mouse_x <= ctx_x + 180 && hd_mouse_y >= ctx_y && hd_mouse_y <= ctx_y + 120) {
                            if (hd_mouse_y <= ctx_y + 40) { app_state = 14; win_x = 312; win_y = 200; is_minimized = 0; } 
                            else if (hd_mouse_y <= ctx_y + 80) { app_state = 1; win_x = 312; win_y = 200; is_minimized = 0; } 
                            else { app_state = 8; win_x = 312; win_y = 200; is_minimized = 0; } 
                        }
                        ctx_open = 0; just_clicked = 0; 
                    }
                    
                    int w = app_widths[app_state]; int bg_w = app_widths[z_bg_app];

                    if (z_bg_app > 0 && just_clicked) {
                        if (hd_mouse_x >= z_bg_x && hd_mouse_x <= z_bg_x + bg_w && hd_mouse_y >= z_bg_y && hd_mouse_y <= z_bg_y + 350) {
                            int clicked_fg = (app_state > 0 && hd_mouse_x >= win_x && hd_mouse_x <= win_x + w && hd_mouse_y >= win_y && hd_mouse_y <= win_y + 350);
                            if (!clicked_fg) { open_window(z_bg_app, &app_state, &win_x, &win_y); just_clicked = 0; }
                        }
                    }

                    if (app_state > 0 && !is_minimized && hd_mouse_x >= win_x && hd_mouse_x <= win_x + (w - 35) && hd_mouse_y >= win_y && hd_mouse_y <= win_y + 30) {
                        is_dragging = 1; start_menu_open = 0; action_center_open = 0; dragging_icon = -1;
                    }
                    if (is_dragging) { win_x += rel_x; win_y -= rel_y; }
                    
                    if (app_state > 0 && !is_minimized && hd_mouse_x >= win_x + w - 30 && hd_mouse_x <= win_x + w - 15 && hd_mouse_y >= win_y + 8 && hd_mouse_y <= win_y + 23) {
                        if (just_clicked) { app_state = z_bg_app; win_x = z_bg_x; win_y = z_bg_y; z_bg_app = 0; is_dragging = 0; hd_stop_sound(); now_playing = 0; just_clicked = 0; }
                    }

                    if (app_state == 15 && !is_minimized && !is_dragging && just_clicked) {
                        if (hd_mouse_y >= win_y+240 && hd_mouse_y <= win_y+270) {
                            if (hd_mouse_x >= win_x+20 && hd_mouse_x <= win_x+140) { int k=0; char* sm = "Mango Pickle added to Cart!"; while(sm[k]) { notif_msg[k]=sm[k]; k++; } notif_msg[k]='\0'; notif_timer = 3; just_clicked = 0; }
                            else if (hd_mouse_x >= win_x+170 && hd_mouse_x <= win_x+290) { int k=0; char* sm = "Lemon Pickle added to Cart!"; while(sm[k]) { notif_msg[k]=sm[k]; k++; } notif_msg[k]='\0'; notif_timer = 3; just_clicked = 0; }
                            else if (hd_mouse_x >= win_x+320 && hd_mouse_x <= win_x+440) { int k=0; char* sm = "Garlic Pickle added to Cart!"; while(sm[k]) { notif_msg[k]=sm[k]; k++; } notif_msg[k]='\0'; notif_timer = 3; just_clicked = 0; }
                        }
                    }

                    if (app_state == 2 && !is_minimized && !is_dragging && just_clicked) {
                        for(int f=0; f<file_count && f<10; f++) {
                            int col = f % 5; int row = f / 5; int fx = win_x + 30 + (col * 90); int fy = win_y + 90 + (row * 100);
                            if (hd_mouse_x >= fx && hd_mouse_x <= fx+40 && hd_mouse_y >= fy && hd_mouse_y <= fy+40) {
                                if (file_system[f].name[0] == 'I' && file_system[f].name[1] == 'M' && file_system[f].name[2] == 'G') { app_state = 10; } 
                                else if (file_system[f].name[0] == 'a' && file_system[f].name[1] == 'p' && file_system[f].name[2] == 'p') { target_ind_file = f; ind_loading = 1; app_state = 1; } 
                                else { app_state = 4; int c = 0; while(file_system[f].content[c] != '\0' && c < 45) { term_buffer[c] = file_system[f].content[c]; c++; } term_buffer[c] = '\0'; term_idx = c; }
                                win_x = 312; win_y = 200; is_minimized = 0; just_clicked = 0; break;
                            }
                        }
                    }

                    if (app_state == 11 && !is_minimized && !is_dragging && just_clicked) {
                        if (ind_app_btn[0] != '\0' && hd_mouse_x >= win_x+20 && hd_mouse_x <= win_x+220 && hd_mouse_y >= win_y+160 && hd_mouse_y <= win_y+200) {
                            int k=0, j=0; char* prefix = "Welcome, ";
                            while(prefix[k]) { notif_msg[k]=prefix[k]; k++; }
                            while(ind_input_buf[j]) { notif_msg[k] = ind_input_buf[j]; k++; j++; }
                            if (j == 0) { char* nf = "Guest!"; while(nf[j]) { notif_msg[k]=nf[j]; k++; j++; } }
                            notif_msg[k]='\0'; notif_timer = 4; just_clicked = 0;
                        }
                    }

               if (app_state == 4 && !is_minimized && !is_dragging && just_clicked) {
                        
                        // ============================================
                        // THE SAVE BUTTON (Save to C:\NOTE.TXT)
                        // ============================================
                        if (hd_mouse_x >= win_x+280 && hd_mouse_x <= win_x+325 && hd_mouse_y >= win_y+45 && hd_mouse_y <= win_y+70) {
                            
                            // Ab yahan sirf "NOTE" likhna hai, baaki backend khud sambhal lega!
                            fat32_write_file("NOTE", "TXT", term_buffer, term_idx);
                            
                            int k=0; char* sm = "Saved to Hard Drive!"; 
                            while(sm[k]) { notif_msg[k]=sm[k]; k++; } notif_msg[k]='\0'; 
                            notif_timer = 3; just_clicked = 0;
                        }
                        
                        // ============================================
                        // THE LOAD BUTTON (Read from C:\NOTE.TXT)
                        // ============================================
                        if (hd_mouse_x >= win_x+335 && hd_mouse_x <= win_x+380 && hd_mouse_y >= win_y+45 && hd_mouse_y <= win_y+70) {
                            
                            int file_len = 0;
                            // Yahan bhi sirf "NOTE" aayega
                            if (fat32_read_file("NOTE", "TXT", term_buffer, &file_len)) {
                                term_buffer[file_len] = '\0'; 
                                term_idx = file_len; 
                                
                                int k=0; char* sm = "Loaded from HDD!"; 
                                while(sm[k]) { notif_msg[k]=sm[k]; k++; } notif_msg[k]='\0'; 
                                notif_timer = 3;
                            } else {
                                int k=0; char* sm = "File not found!"; 
                                while(sm[k]) { notif_msg[k]=sm[k]; k++; } notif_msg[k]='\0'; 
                                notif_timer = 3;
                            }
                            just_clicked = 0;
                        }
                    }
                    if (app_state == 8 && !is_minimized && !is_dragging && just_clicked) {
                        if (hd_mouse_y >= win_y+90 && hd_mouse_y <= win_y+140) {
                            if (hd_mouse_x >= win_x+20 && hd_mouse_x <= win_x+70) theme_idx = 0; else if (hd_mouse_x >= win_x+85 && hd_mouse_x <= win_x+135) theme_idx = 1; else if (hd_mouse_x >= win_x+150 && hd_mouse_x <= win_x+200) theme_idx = 2; else if (hd_mouse_x >= win_x+215 && hd_mouse_x <= win_x+265) theme_idx = 3;
                            just_clicked = 0;
                        }
                    }

                    if (app_state == 7 && !is_minimized && !is_dragging) {
                        if (hd_mouse_x >= win_x+20 && hd_mouse_x < win_x+280 && hd_mouse_y >= win_y+40 && hd_mouse_y < win_y+240) {
                            int px = hd_mouse_x - (win_x+20); int py = hd_mouse_y - (win_y+40);
                            for(int i=-1; i<=1; i++) { for(int j=-1; j<=1; j++) { if(py+i >= 0 && py+i < 200 && px+j >= 0 && px+j < 260) { hd_paint_canvas[(py+i)*260 + (px+j)] = brush_color; } } }
                        }
                        if (just_clicked && hd_mouse_y >= win_y+260 && hd_mouse_y <= win_y+290) {
                            if (hd_mouse_x >= win_x+20 && hd_mouse_x <= win_x+50) brush_color = 0x00E53935; else if (hd_mouse_x >= win_x+60 && hd_mouse_x <= win_x+90) brush_color = 0x004CAF50; else if (hd_mouse_x >= win_x+100 && hd_mouse_x <= win_x+130) brush_color = 0x002196F3; else if (hd_mouse_x >= win_x+140 && hd_mouse_x <= win_x+170) brush_color = 0x00000000; else if (hd_mouse_x >= win_x+180 && hd_mouse_x <= win_x+210) brush_color = 0xFFFFFFFF; 
                            else if (hd_mouse_x >= win_x + 225 && hd_mouse_x <= win_x + 270) {
                                    if (find_file("IMG.BMP") != -1) { delete_file("IMG.BMP"); }
                                    create_file("IMG.BMP", "IMAGE DATA");
                                    int k = 0; char * sm = "Image Saved to Disk"; while (sm[k]) { notif_msg[k] = sm[k]; k++; } notif_msg[k] = '\0'; notif_timer = 2;
                            }
                            just_clicked = 0;
                        }
                    }

                    if (app_state == 9 && !is_minimized && !is_dragging && just_clicked) {
                        if (hd_mouse_y >= win_y + 50 && hd_mouse_y <= win_y + 190) {
                            int key_idx = (hd_mouse_x - (win_x + 20)) / 42;
                            if (key_idx >= 0 && key_idx < 7) { 
                                int freqs[7] = {261, 293, 329, 349, 392, 440, 493}; 
                                hd_play_sound(freqs[key_idx]); 
                                for(volatile int d=0; d<8000000; d++) {} hd_stop_sound(); 
                            }
                        }
                    }

                    if (app_state == 13 && !is_minimized && !is_dragging && just_clicked) {
                        if (hd_mouse_y >= win_y+150 && hd_mouse_y <= win_y+190) {
                            if (hd_mouse_x >= win_x+20 && hd_mouse_x <= win_x+110) { 
                                now_playing = 1; render_desktop_bg(hd_mouse_x, hd_mouse_y, app_state, win_x, win_y, term_buffer, h, m, start_menu_open, current_ram, ctx_open, ctx_x, ctx_y, is_minimized, calc_display, theme_idx, game_board, game_winner, is_screensaver, ss_x, ss_y, icon_x, icon_y, pwd_buffer, system_uptime, action_center_open, ind_loading, notif_y, notif_msg, ind_input_buf, day, month, year, now_playing);
                                int f[] = {659, 587, 370, 415, 494, 440, 277, 330, 440, 392, 247, 294, 440};
                                for(int i=0; i<13; i++) { hd_play_sound(f[i]); for(volatile int d=0; d<9000000; d++); hd_stop_sound(); for(volatile int d=0; d<1000000; d++); }
                                now_playing = 0; just_clicked = 0;
                            }
                            else if (hd_mouse_x >= win_x+130 && hd_mouse_x <= win_x+220) { 
                                now_playing = 2; render_desktop_bg(hd_mouse_x, hd_mouse_y, app_state, win_x, win_y, term_buffer, h, m, start_menu_open, current_ram, ctx_open, ctx_x, ctx_y, is_minimized, calc_display, theme_idx, game_board, game_winner, is_screensaver, ss_x, ss_y, icon_x, icon_y, pwd_buffer, system_uptime, action_center_open, ind_loading, notif_y, notif_msg, ind_input_buf, day, month, year, now_playing);
                                int f[] = {659, 659, 0, 659, 0, 523, 659, 0, 784};
                                for(int i=0; i<9; i++) { if(f[i]==0) { hd_stop_sound(); for(volatile int d=0; d<9000000; d++); } else { hd_play_sound(f[i]); for(volatile int d=0; d<9000000; d++); hd_stop_sound(); } for(volatile int d=0; d<1000000; d++); }
                                now_playing = 0; just_clicked = 0;
                            }
                            else if (hd_mouse_x >= win_x+240 && hd_mouse_x <= win_x+330) { hd_stop_sound(); now_playing = 0; just_clicked = 0; }
                        }
                    }
                    
                    if (app_state == 6 && !is_minimized && !is_dragging && just_clicked) {
                        if (hd_mouse_x >= win_x+20 && hd_mouse_x <= win_x+280 && hd_mouse_y >= win_y+50 && hd_mouse_y <= win_y+330) {
                            if (game_winner != 0) { for(int i=0; i<9; i++) game_board[i]=0; game_winner=0; game_turn=1; just_clicked = 0; } else {
                                int col = (hd_mouse_x - (win_x + 20)) / 90; int row = (hd_mouse_y - (win_y + 50)) / 95;
                                if (col >= 0 && col < 3 && row >= 0 && row < 3) { 
                                    int cell = (row * 3) + col; 
                                    if (game_board[cell] == 0) { 
                                        game_board[cell] = game_turn; 
                                        int w[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}}; 
                                        for(int i=0; i<8; i++) { if(game_board[w[i][0]] != 0 && game_board[w[i][0]] == game_board[w[i][1]] && game_board[w[i][1]] == game_board[w[i][2]]) game_winner = game_board[w[i][0]]; }
                                        if (game_winner == 0) { int full = 1; for(int i=0;i<9;i++) { if(game_board[i]==0) full=0; } if (full) game_winner = 3; } 
                                        game_turn = (game_turn == 1) ? 2 : 1; just_clicked = 0; 
                                    } 
                                }
                            }
                        }
                    }

                    if (app_state == 16 && !is_minimized && !is_dragging && just_clicked) {
                        if (hd_mouse_x >= win_x + 10 && hd_mouse_x <= win_x + 390 && hd_mouse_y >= win_y + 40 && hd_mouse_y <= win_y + 290) {
                            if (game_winner < 4) { 
                                game_board[game_winner * 2] = hd_mouse_x - (win_x + 10);
                                game_board[game_winner * 2 + 1] = hd_mouse_y - (win_y + 40);
                                game_winner++;
                            }
                            just_clicked = 0;
                        }
                        else if (hd_mouse_y >= win_y + 300 && hd_mouse_y <= win_y + 330 && hd_mouse_x >= win_x + 10 && hd_mouse_x <= win_x + 110) {
                            game_winner = 0; just_clicked = 0;
                        }
                    }

                    if (app_state == 5 && !is_minimized && !is_dragging && just_clicked) {
                        if (hd_mouse_x >= win_x + 20 && hd_mouse_x <= win_x + 280 && hd_mouse_y >= win_y + 105 && hd_mouse_y <= win_y + 345) {
                            int col = (hd_mouse_x - (win_x + 20)) / 65; int row = (hd_mouse_y - (win_y + 105)) / 60;
                            if (col >= 0 && col < 4 && row >= 0 && row < 4) {
                                char keys[16] = {'7','8','9','/','4','5','6','*','1','2','3','-','C','0','=','+'}; char k = keys[(row * 4) + col];
                                if (k >= '0' && k <= '9') { if (calc_new_num) { calc_display[0] = k; calc_display[1] = '\0'; calc_new_num = 0; } else { int dlen = 0; while(calc_display[dlen]) dlen++; if (dlen < 10) { calc_display[dlen] = k; calc_display[dlen+1] = '\0'; } } } 
                                else if (k == 'C') { calc_display[0] = '0'; calc_display[1] = '\0'; calc_num1 = 0; calc_op = 0; calc_new_num = 1; } 
                                else if (k == '+' || k == '-' || k == '*' || k == '/') { int val=0, sign=1, idx=0; if(calc_display[0]=='-'){sign=-1;idx=1;} while(calc_display[idx]){val=val*10+(calc_display[idx]-'0');idx++;} calc_num1 = val * sign; if (k == '+') calc_op = 1; else if (k == '-') calc_op = 2; else if (k == '*') calc_op = 3; else if (k == '/') calc_op = 4; calc_new_num = 1; } 
                                else if (k == '=') { int val=0, sign=1, idx=0; if(calc_display[0]=='-'){sign=-1;idx=1;} while(calc_display[idx]){val=val*10+(calc_display[idx]-'0');idx++;} int calc_num2 = val * sign; int res = 0; if (calc_op == 1) res = calc_num1 + calc_num2; else if (calc_op == 2) res = calc_num1 - calc_num2; else if (calc_op == 3) res = calc_num1 * calc_num2; else if (calc_op == 4) { if(calc_num2!=0) res = calc_num1 / calc_num2; else res = 0; } idx = 0; if(res == 0) { calc_display[0]='0'; calc_display[1]='\0'; } else { int is_neg=0; if(res<0){is_neg=1; res=-res;} char tmp[20]; int t=0; while(res>0){ tmp[t++]=(res%10)+'0'; res/=10; } if(is_neg) tmp[t++]='-'; while(t>0){ calc_display[idx++] = tmp[--t]; } calc_display[idx]='\0'; } calc_new_num = 1; calc_op = 0; }
                                just_clicked = 0;
                            }
                        }
                    }
                    
                    // ==============================================================
                    // SMART Z-INDEX TASKBAR DISPATCHER (DYNAMIC CLICKS)
                    // ==============================================================
                    int tb_width = 420, tb_x = (screen_width - tb_width) / 2, tb_y = screen_height - 50 - 15;
                    
                    if (!is_dragging && hd_mouse_y >= tb_y && hd_mouse_y <= tb_y + 50 && just_clicked) {
                        
                        if (hd_mouse_x >= tb_x+20 && hd_mouse_x <= tb_x+50) { 
                            start_menu_open = !start_menu_open; just_clicked = 0; 
                        }
                        else {
                            int clicked_app = -1;
                            if (hd_mouse_x >= tb_x+70 && hd_mouse_x <= tb_x+100) clicked_app = 2; 
                            else if (hd_mouse_x >= tb_x+120 && hd_mouse_x <= tb_x+150) clicked_app = 3; 
                            else if (hd_mouse_x >= tb_x+170 && hd_mouse_x <= tb_x+200) clicked_app = 1; 
                            else if (hd_mouse_x >= tb_x+220 && hd_mouse_x <= tb_x+250) clicked_app = 5; 
                            else if (hd_mouse_x >= tb_x+270 && hd_mouse_x <= tb_x+300) clicked_app = 6; 
                            else if (hd_mouse_x >= tb_x+320 && hd_mouse_x <= tb_x+350) clicked_app = 8; 
                            
                            if (clicked_app != -1) {
                                if (app_state == clicked_app) { is_minimized = !is_minimized; } 
                                else if (z_bg_app == clicked_app) {
                                    open_window(z_bg_app, &app_state, &win_x, &win_y); is_minimized = 0;
                                } 
                                else {
                                    if (app_state > 0 && !is_minimized) {
                                        z_bg_app = app_state; z_bg_x = win_x; z_bg_y = win_y; 
                                    }
                                    app_state = clicked_app; win_x = 312; win_y = 200; is_minimized = 0; 
                                }
                                start_menu_open = 0; 
                                if (clicked_app == 1) { term_buffer[0] = '\0'; term_idx = 0; }
                                just_clicked = 0; 
                            }
                        }
                    }
                    
                    // START MENU CLICKS (DYNAMIC)
                    if (start_menu_open && just_clicked) {
                        int sm_h = 320;
                        int sm_x = (screen_width - 420) / 2 + 10; 
                        int sm_y = screen_height - sm_h - 75;

                        if (hd_mouse_x >= sm_x + 20 && hd_mouse_x <= sm_x + 200) {
                            if (hd_mouse_y >= sm_y + 80 && hd_mouse_y <= sm_y + 100) { app_state = 4; win_x = 312; win_y = 200; start_menu_open = 0; is_minimized = 0; term_buffer[0] = '\0'; term_idx = 0; just_clicked = 0; }
                            else if (hd_mouse_y >= sm_y + 115 && hd_mouse_y <= sm_y + 135) { app_state = 5; win_x = 312; win_y = 200; start_menu_open = 0; is_minimized = 0; just_clicked = 0; }
                            else if (hd_mouse_y >= sm_y + 150 && hd_mouse_y <= sm_y + 170) { app_state = 12; win_x = 312; win_y = 200; start_menu_open = 0; is_minimized = 0; just_clicked = 0; } 
                            else if (hd_mouse_y >= sm_y + 185 && hd_mouse_y <= sm_y + 205) { app_state = 8; win_x = 312; win_y = 200; start_menu_open = 0; is_minimized = 0; just_clicked = 0; } 
                            else if (hd_mouse_y >= sm_y + 220 && hd_mouse_y <= sm_y + 240) { app_state = 7; win_x = 312; win_y = 200; start_menu_open = 0; is_minimized = 0; just_clicked = 0; } 
                        }
                        if (hd_mouse_x >= sm_x + 20 && hd_mouse_x <= sm_x + 200 && hd_mouse_y >= sm_y + 265 && hd_mouse_y <= sm_y + 300) {
                            __asm__ volatile ("outw %0, %1" : : "a"((unsigned short)0x2000), "Nd"((unsigned short)0x604)); 
                            __asm__ volatile ("outw %0, %1" : : "a"((unsigned short)0x2000), "Nd"((unsigned short)0xB004));
                        }
                    }

                    if (!is_dragging && just_clicked) {
                        if (start_menu_open || action_center_open || ctx_open) {
                            start_menu_open = 0; action_center_open = 0; ctx_open = 0; just_clicked = 0; 
                        } 
                        else if (app_state == 0) { 
                            icon_moved = 0;
                            for(int i=0; i<12; i++) { 
                                if (hd_mouse_x >= icon_x[i] && hd_mouse_x <= icon_x[i]+40 && hd_mouse_y >= icon_y[i] && hd_mouse_y <= icon_y[i]+40) { 
                                    dragging_icon = i; 
                                }
                            }
                        }
                    }
                    
                    if (dragging_icon != -1) {
                        if (rel_x != 0 || rel_y != 0) icon_moved = 1;
                        icon_x[dragging_icon] += rel_x; 
                        icon_y[dragging_icon] -= rel_y;
                    }
                } else { 
                    is_dragging = 0; 
                    if (dragging_icon != -1) {
                        if (!icon_moved) { 
                            if (dragging_icon == 0) { app_state = 2; win_x = 312; win_y = 200; is_minimized = 0; }
                            else if (dragging_icon == 1) { app_state = 4; win_x = 312; win_y = 200; is_minimized = 0; term_buffer[0] = '\0'; term_idx = 0; }
                            else if (dragging_icon == 2) { app_state = 5; win_x = 350; win_y = 150; is_minimized = 0; }
                            else if (dragging_icon == 3) { app_state = 6; win_x = 350; win_y = 150; is_minimized = 0; }
                            else if (dragging_icon == 4) { app_state = 8; win_x = 350; win_y = 150; is_minimized = 0; }
                            else if (dragging_icon == 5) { app_state = 9; win_x = 350; win_y = 150; is_minimized = 0; }
                            else if (dragging_icon == 6) { app_state = 12; win_x = 350; win_y = 150; is_minimized = 0; }
                            else if (dragging_icon == 7) { app_state = 13; win_x = 350; win_y = 150; is_minimized = 0; }
                            else if (dragging_icon == 8) { app_state = 14; win_x = 350; win_y = 150; is_minimized = 0; }
                            else if (dragging_icon == 9) { app_state = 15; win_x = 280; win_y = 150; is_minimized = 0; } 
                            else if (dragging_icon == 10) { app_state = 16; win_x = 312; win_y = 150; is_minimized = 0; game_winner = 0; } 
                            else if (dragging_icon == 11) { app_state = 17; win_x = 312; win_y = 150; is_minimized = 0; } 
                        }
                        dragging_icon = -1;
                    }
                }
                
                render_desktop_bg(hd_mouse_x, hd_mouse_y, app_state, win_x, win_y, term_buffer, h, m, start_menu_open, current_ram, ctx_open, ctx_x, ctx_y, is_minimized, calc_display, theme_idx, game_board, game_winner, is_screensaver, ss_x, ss_y, icon_x, icon_y, pwd_buffer, system_uptime, action_center_open, ind_loading, notif_y, notif_msg, ind_input_buf, day, month, year, now_playing); 
            }
        }
    }
}