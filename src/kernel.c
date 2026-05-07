#include "display.h"
#include "keyboard.h"

void kernel_main() {
    clear_screen();
    
    print_string("Booting Micro OS...\n");
    print_string("[OK] Kernel Loaded\n");
    print_string("[OK] VGA Text Driver Initialized\n");
    print_string("[OK] Keyboard Polling Driver Started\n");
    print_string("-------------------------------------------\n");
    print_string("Type something! (Pressing keys will show up below)\n\n");
    
    // Keyboard loop start kar do (Ye infinite loop hai)
    keyboard_read_loop();
}