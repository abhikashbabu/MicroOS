#include "display.h"
#include "keyboard.h"
#include "fs.h"
#include "gdt.h" 
#include "idt.h" 
#include "pic.h"        // NAYA: Day 17
#include "ind_runner.h" // NAYA: Day 18 ke liye zaroori hai
#include "mouse.h"      // NAYA

void kernel_main() {
    set_color(COLOR_WHITE, COLOR_BLACK);
    clear_screen();
    draw_top_bar(" Micro OS v0.1 | .ind Application Runtime");
    
    // System Tables Init
    init_gdt();
    print_string("[OK] GDT Initialized\n");
    
    init_idt();
    print_string("[OK] IDT Initialized\n");
    
    init_pic(); // DAY 17: PIC yahan start ho raha hai
    print_string("[OK] PIC Hardware Remapped\n");
    
    init_fs();
    print_string("[OK] Virtual File System Mounted\n");
    
    // DAY 18: The Auto-Exec Script Logic
    print_string("\n--- Booting .ind Ecosystem ---\n");
    
    init_mouse();       // NAYA: Mouse Start kiya
    print_string("[OK] PS/2 Mouse Activated\n");

    // NAYA: Ye line CPU ko bolti hai ki ab Interrupts sun-na shuru karo!
    __asm__ volatile ("sti");
    // Hum khud kernel se ek startup script memory mein dal rahe hain
// Hum khud kernel se ek startup script memory mein dal rahe hain (Ab Beep ke saath!)
    create_file("init.ind", "color:11;beep:1500;print:Welcome to Micro OS Ecosystem...;delay:3;color:10;print:Loading Core Services...;delay:3;clear:;");    
    // Ab check karte hain kya script successfully ban gayi
    int boot_script = find_file("init.ind");
    if(boot_script != -1) {
        execute_ind_app(file_system[boot_script].content); // Auto-run!
    }
    
    // Script khatam hone ke baad normal shell start karo
    set_color(COLOR_WHITE, COLOR_BLACK);
    print_string("Micro OS CLI Ready. Type 'help' to start.\n\n");
    
    keyboard_read_loop();
}