#include "shell.h"
#include "display.h"
#include "string.h"
#include "cmos.h"
#include "io.h"
#include "memory.h"  // NAYA: Memory manager include kiya

void execute_command(char* command) {
    if (command[0] == '\0') return;
    
    if (strcmp(command, "help") == 0) {
        print_string("Available commands:\n");
        print_string("  help    - Show this message\n");
        print_string("  clear   - Clear the screen\n");
        print_string("  about   - Show OS info\n");
        print_string("  time    - Show current hardware time\n");
        print_string("  reboot  - Restart the computer\n");
        print_string("  meminfo - Show RAM usage\n");      // NAYA
        print_string("  echo    - Print text to screen\n"); // NAYA
    } 
    else if (strcmp(command, "clear") == 0) {
        clear_screen();
        draw_top_bar(" Micro OS v0.1 | .ind Application Runtime");
    } 
    else if (strcmp(command, "about") == 0) {
        print_string("Micro OS v0.1\n");
        print_string("Built for the .ind ecosystem.\n");
        print_string("Developer: Abhikash\n");
    } 
    else if (strcmp(command, "time") == 0) {
        int h, m, s;
        get_time(&h, &m, &s);
        char buffer[10];
        print_string("Current Time (UTC): ");
        if (h < 10) print_char('0');
        itoa(h, buffer); print_string(buffer);
        print_char(':');
        if (m < 10) print_char('0');
        itoa(m, buffer); print_string(buffer);
        print_char(':');
        if (s < 10) print_char('0');
        itoa(s, buffer); print_string(buffer);
        print_string("\n");
    }
    else if (strcmp(command, "reboot") == 0) {
        print_string("Rebooting Micro OS...\n");
        outb(0x64, 0xFE);
    }
    else if (strcmp(command, "meminfo") == 0) { // NAYA LOGIC: RAM Status
        unsigned int used_bytes = get_used_memory();
        char buffer[16];
        
        print_string("System Memory Status:\n");
        print_string("Base Address : 0x200000 (2 MB)\n");
        print_string("Used Memory  : ");
        itoa(used_bytes, buffer);
        print_string(buffer);
        print_string(" Bytes\n");
        
        // Memory allocate karke test karna (Jab bhi meminfo type karoge, 10 bytes memory allocate hogi)
        kmalloc(10); 
    }
    // NAYA LOGIC: Echo command (check kar rahe hain agar shuruat "echo " se ho rahi hai)
    else if (command[0] == 'e' && command[1] == 'c' && command[2] == 'h' && command[3] == 'o' && command[4] == ' ') {
        // 'echo ' ke baad wale characters print karo (index 5 se)
        print_string(&command[5]);
        print_string("\n");
    }
    else {
        print_string("Unknown command: ");
        print_string(command);
        print_string("\nType 'help' for a list of commands.\n");
    }
}