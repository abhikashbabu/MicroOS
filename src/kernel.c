#include "display.h"

void kernel_main() {
    clear_screen();
    
    // Ab hum kitni bhi lines easily print kar sakte hain!
    print_string("Booting Micro OS...\n");
    print_string("[OK] Kernel Loaded\n");
    print_string("[OK] VGA Text Driver Initialized\n");
    print_string("\n");
    print_string("Micro OS - Day 2 Complete! Ready for .ind Apps architecture.\n");
}