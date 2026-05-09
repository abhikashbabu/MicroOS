#include "display.h"
#include "keyboard.h"

void kernel_main() {
    // Screen clear karna default color se
    set_color(COLOR_WHITE, COLOR_BLACK);
    clear_screen();
    
    // Naya UI: Top Bar Draw karna
    draw_top_bar(" Micro OS v0.1 | .ind Application Runtime");
    
    // System boot messages ko green color mein dikhate hain
    set_color(COLOR_LIGHT_GREEN, COLOR_BLACK);
    print_string("[OK] Kernel Loaded Successfully\n");
    print_string("[OK] Color VGA Driver Initialized\n");
    print_string("[OK] Shell Environment Ready\n\n");
    
    // Normal text ke liye wapas white color set kar lo
    set_color(COLOR_WHITE, COLOR_BLACK);
    print_string("Welcome to Micro OS CLI! Type 'help' to start.\n\n");
    
    // Start shell
    keyboard_read_loop();
}