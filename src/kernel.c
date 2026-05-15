#include "display.h"
#include "keyboard.h"
#include "fs.h"
#include "gdt.h" // NAYA
#include "idt.h" // NAYA

void kernel_main() {
    set_color(COLOR_WHITE, COLOR_BLACK);
    clear_screen();
    
    draw_top_bar(" Micro OS v0.1 | .ind Application Runtime");
    
    // Day 15: GDT Setup
    init_gdt();
    print_string("[OK] GDT Initialized (Memory Protected)\n");
    
    // Day 16: IDT Setup
    init_idt();
    print_string("[OK] IDT Initialized (Interrupts Enabled)\n");
    
    set_color(COLOR_LIGHT_GREEN, COLOR_BLACK);
    print_string("[OK] Kernel Loaded Successfully\n");
    
    init_fs();
    print_string("[OK] Virtual File System Mounted\n");
    
    print_string("[OK] Shell Environment Ready\n\n");
    
    set_color(COLOR_WHITE, COLOR_BLACK);
    print_string("Welcome to Micro OS! Build your .ind ecosystem.\n\n");
    
    keyboard_read_loop();
}