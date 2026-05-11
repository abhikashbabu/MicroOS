#include "display.h"
#include "keyboard.h"
#include "fs.h" // NAYA

void kernel_main() {
    set_color(COLOR_WHITE, COLOR_BLACK);
    clear_screen();
    
    draw_top_bar(" Micro OS v0.1 | .ind Application Runtime");
    
    set_color(COLOR_LIGHT_GREEN, COLOR_BLACK);
    print_string("[OK] Kernel Loaded Successfully\n");
    print_string("[OK] Color VGA Driver Initialized\n");
    
    // File system initialize karo
    init_fs();
    print_string("[OK] Virtual File System Mounted\n");
    
    print_string("[OK] Shell Environment Ready\n\n");
    
    set_color(COLOR_WHITE, COLOR_BLACK);
    print_string("Welcome to Micro OS CLI! Type 'help' to start.\n\n");
    
    keyboard_read_loop();
}