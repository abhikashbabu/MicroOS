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

// ----------------------------------------------------
// NAYA (DAY 108): THE MODERN UI ENGINE LINK!
// Is line ke bina OS ko VESA aur HD Taskbar ka pata nahi chalega
// ----------------------------------------------------
#include "../gui/modern_ui.h" 

void kernel_main(unsigned int magic, unsigned int addr) {
    
    // ----------------------------------------------------
    // VESA HD BOOT SEQUENCE
    // ----------------------------------------------------
    if (magic == 0x2BADB002) { 
        multiboot_info_t* mbi = (multiboot_info_t*) addr;
        
        if (mbi->flags & (1 << 12)) {
            // 1. Start GDT & Paging 
            init_gdt();
            init_paging();

            // 2. VIP PASS: Map the VESA Screen Memory!
            unsigned int fb_addr = (unsigned int)mbi->framebuffer_addr;
            map_vesa_memory(fb_addr);

            // 3. Start remaining background services safely
            init_task_manager();
            init_idt();
            init_pic(); 
            init_fs();
            init_mouse();
            __asm__ volatile ("sti"); 

            // 4. Connect GUI Engine to the Real Screen
            vesa_framebuffer = (unsigned int*) fb_addr;

            // ----------------------------------------------------
            // DAY 118 to 123: THE MASTER GUI ENGINE!
            // ----------------------------------------------------
            int hd_mouse_x = 512, hd_mouse_y = 384; 
            int app_state = 0; // 0=Desktop, 1=Term, 2=Explorer, 3=SysMon, 4=Notepad
            
            int win_x = 312, win_y = 200;
            int is_dragging = 0, start_menu_open = 0;
            
            // DAY 122: Context Menu variables
            int ctx_open = 0, ctx_x = 0, ctx_y = 0;
            
            char term_buffer[50] = {0};
            int term_idx = 0;

            char key_map[128] = {0};
            key_map[0x1E] = 'a'; key_map[0x30] = 'b'; key_map[0x2E] = 'c'; key_map[0x20] = 'd';
            key_map[0x12] = 'e'; key_map[0x21] = 'f'; key_map[0x22] = 'g'; key_map[0x23] = 'h';
            key_map[0x17] = 'i'; key_map[0x24] = 'j'; key_map[0x25] = 'k'; key_map[0x26] = 'l';
            key_map[0x32] = 'm'; key_map[0x31] = 'n'; key_map[0x18] = 'o'; key_map[0x19] = 'p';
            key_map[0x10] = 'q'; key_map[0x13] = 'r'; key_map[0x1F] = 's'; key_map[0x14] = 't';
            key_map[0x16] = 'u'; key_map[0x2F] = 'v'; key_map[0x11] = 'w'; key_map[0x2D] = 'x';
            key_map[0x15] = 'y'; key_map[0x2C] = 'z'; key_map[0x39] = ' '; 
            
            while(1) {
                // Read RTC Clock
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
                            int right_click = m1 & 2; // DAY 122: Right Click Detect

                            hd_mouse_x += rel_x; hd_mouse_y -= rel_y; 
                            if (hd_mouse_x < 0) hd_mouse_x = 0; if (hd_mouse_x > 1000) hd_mouse_x = 1000;
                            if (hd_mouse_y < 0) hd_mouse_y = 0; if (hd_mouse_y > 750) hd_mouse_y = 750;

                            // DAY 122: Right Click Context Menu Open
                            if (right_click) {
                                ctx_open = 1; ctx_x = hd_mouse_x; ctx_y = hd_mouse_y;
                            }

                            if (left_click) {
                                // DAY 122: Context Menu Clicks
                                if (ctx_open) {
                                    if (hd_mouse_x >= ctx_x && hd_mouse_x <= ctx_x + 160 && hd_mouse_y >= ctx_y && hd_mouse_y <= ctx_y + 120) {
                                        if (hd_mouse_y <= ctx_y + 40) { /* Refresh - Desktop reload (do nothing) */ }
                                        else if (hd_mouse_y <= ctx_y + 80) { app_state = 1; win_x = 312; win_y = 200; term_buffer[0] = '\0'; term_idx = 0; }
                                        else { app_state = 3; win_x = 312; win_y = 200; }
                                    }
                                    ctx_open = 0; // Kisi bhi click par menu band
                                }
                                else { // Normal UI Clicks
                                    // Window Drag
                                    if (app_state > 0 && !is_dragging) {
                                        if (hd_mouse_x >= win_x && hd_mouse_x <= win_x + 370 && hd_mouse_y >= win_y && hd_mouse_y <= win_y + 30) {
                                            is_dragging = 1; start_menu_open = 0;
                                        }
                                    }
                                    if (is_dragging) {
                                        win_x += rel_x; win_y -= rel_y;
                                    }
                                    
                                    // Window Close Button
                                    if (app_state > 0 && hd_mouse_x >= win_x + 370 && hd_mouse_x <= win_x + 385 && hd_mouse_y >= win_y + 8 && hd_mouse_y <= win_y + 23) {
                                        app_state = 0; is_dragging = 0;
                                    }
                                    
                                    // Taskbar
                                    if (!is_dragging && hd_mouse_y >= 708 && hd_mouse_y <= 758) {
                                        if (hd_mouse_x >= 132 && hd_mouse_x <= 162) { start_menu_open = !start_menu_open; }
                                        else if (hd_mouse_x >= 182 && hd_mouse_x <= 212) { app_state = 2; win_x = 312; win_y = 200; start_menu_open = 0; }
                                        else if (hd_mouse_x >= 232 && hd_mouse_x <= 262) { app_state = 3; win_x = 312; win_y = 200; start_menu_open = 0; }
                                        else if (hd_mouse_x >= 282 && hd_mouse_x <= 312) { app_state = 1; win_x = 312; win_y = 200; start_menu_open = 0; term_buffer[0] = '\0'; term_idx = 0; }
                                    }
                                    
                                    // Start Menu Power Button
                                    if (start_menu_open && hd_mouse_x >= 140 && hd_mouse_x <= 300 && hd_mouse_y >= 638 && hd_mouse_y <= 678) {
                                        __asm__ volatile ("outw %0, %1" : : "a"((unsigned short)0x2000), "Nd"((unsigned short)0x604)); 
                                        __asm__ volatile ("outw %0, %1" : : "a"((unsigned short)0x2000), "Nd"((unsigned short)0xB004));
                                    }

                                    // DAY 121: DESKTOP ICONS CLICK
                                    if (!is_dragging && app_state == 0 && start_menu_open == 0) {
                                        if (hd_mouse_x >= 20 && hd_mouse_x <= 60) {
                                            if (hd_mouse_y >= 20 && hd_mouse_y <= 60) { app_state = 2; win_x = 312; win_y = 200; } // My PC
                                            else if (hd_mouse_y >= 100 && hd_mouse_y <= 140) { app_state = 4; win_x = 312; win_y = 200; term_buffer[0] = '\0'; term_idx = 0; } // Notes
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
                                if (term_idx > 0 && app_state == 1) { 
                                    char echo_buf[55] = "> "; int e_idx = 0;
                                    while (term_buffer[e_idx] != '\0') { echo_buf[e_idx + 2] = term_buffer[e_idx]; e_idx++; }
                                    echo_buf[e_idx + 2] = '\0'; hd_print(echo_buf);
                                    
                                    if (term_buffer[0]=='h' && term_buffer[1]=='e' && term_buffer[2]=='l' && term_buffer[3]=='p') hd_print("HD Commands: help, about, clear");
                                    else if (term_buffer[0]=='c' && term_buffer[1]=='l' && term_buffer[2]=='e' && term_buffer[3]=='a' && term_buffer[4]=='r') hd_term_lines = 0; 
                                    else if (term_buffer[0]=='a' && term_buffer[1]=='b' && term_buffer[2]=='o' && term_buffer[3]=='u' && term_buffer[4]=='t') hd_print("Micro OS v3.0 (HD Desktop Mode)");
                                    else hd_print("Command not found.");
                                    
                                    term_buffer[0] = '\0'; term_idx = 0;
                                } else if (app_state == 4) {
                                    term_buffer[0] = '\0'; term_idx = 0; // Clear notepad line on enter
                                }
                            }
                            else if (data == 0x0E) { // Backspace Key
                                if (term_idx > 0) { term_idx--; term_buffer[term_idx] = '\0'; }
                            }
                            else if ((app_state == 1 || app_state == 4) && term_idx < 45) { // Terminal or Notepad Typing
                                char c = key_map[data];
                                if (c != 0) { term_buffer[term_idx] = c; term_idx++; term_buffer[term_idx] = '\0'; }
                            }
                        }
                    }
                }
                
                // MAIN HD RENDER CALL
                render_desktop_bg(hd_mouse_x, hd_mouse_y, app_state, win_x, win_y, term_buffer, h, m, start_menu_open, current_ram, ctx_open, ctx_x, ctx_y); 
            }
        }
    }

    // ----------------------------------------------------
    // FALLBACK: Agar VESA fail hua, toh Purana Text Mode Chalega
    // ----------------------------------------------------
    init_gdt();
    init_paging();
    init_task_manager();
    init_idt();
    init_pic(); 
    init_fs();
    init_mouse();
    __asm__ volatile ("sti"); 

    set_color(COLOR_WHITE, COLOR_BLACK);
    clear_screen();
    draw_top_bar(" Micro OS v0.1 | .ind Application Runtime");
    
    print_string("[OK] GDT Initialized\n");
    print_string("[OK] Memory Paging Enabled (4KB Pages)\n");
    print_string("[OK] Task Manager Initialized\n");
    print_string("[OK] IDT Initialized\n");
    print_string("[OK] PIC Hardware Remapped\n");
    print_string("[OK] Virtual File System Mounted\n");
    print_string("[OK] PS/2 Mouse Activated\n");
    
    print_string("\n--- Booting .ind Ecosystem ---\n");
    
    create_file("init.ind", "color:11;beep:1500;print:Welcome to Micro OS Ecosystem...;delay:3;color:10;print:Loading Core Services...;delay:3;clear:;");    
    int boot_script = find_file("init.ind");
    if(boot_script != -1) {
        execute_ind_app(file_system[boot_script].name, file_system[boot_script].content, file_system[boot_script].size);    
    }
    
    set_color(COLOR_WHITE, COLOR_BLACK);
    print_string("Micro OS CLI Ready. Type 'help' to start.\n\n");
    
    keyboard_read_loop();
}