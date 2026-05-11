#include "shell.h"
#include "display.h"
#include "string.h"
#include "cmos.h"
#include "io.h"
#include "memory.h"  // NAYA: Memory manager include kiya
#include "fs.h"          // NAYA
#include "ind_runner.h"  // NAYA

void execute_command(char* command) {
    if (command[0] == '\0') return;
    
    if (strcmp(command, "help") == 0) {
        print_string("Available commands:\n");
        print_string("  help    - Show this message\n");
        print_string("  clear   - Clear the screen\n");
        print_string("  about   - Show OS info\n");
        print_string("  time    - Show current hardware time\n");
        print_string("  reboot  - Restart the computer\n");
        print_string("  meminfo - Show RAM usage\n");
        print_string("  echo    - Print text to screen\n");
        print_string("  ls      - List all files\n");               // HELP ME BHI ADD KIYA
        print_string("  cat     - Read file (e.g., cat readme.txt)\n"); // HELP ME BHI ADD KIYA
        print_string("  run     - Run .ind app (e.g., run hello.ind)\n"); // HELP ME BHI ADD KIYA
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
    else if (strcmp(command, "meminfo") == 0) { 
        unsigned int used_bytes = get_used_memory();
        char buffer[16];
        
        print_string("System Memory Status:\n");
        print_string("Base Address : 0x200000 (2 MB)\n");
        print_string("Used Memory  : ");
        itoa(used_bytes, buffer);
        print_string(buffer);
        print_string(" Bytes\n");
        
        kmalloc(10); 
    }
   else if (strcmp(command, "ls") == 0) { 
        print_string("Name                  Size (Bytes)\n");
        print_string("----------------------------------\n");
        for (int i = 0; i < file_count; i++) {
            print_string(file_system[i].name);
            
            // \t\t ki jagah humne manual spaces daal diye hain
            print_string("          "); 
            
            char buf[10];
            itoa(file_system[i].size, buf);
            print_string(buf);
            print_string("\n");
        }
    }
    // 👆 ------------------------------------ 👆
    else if (command[0] == 'c' && command[1] == 'a' && command[2] == 't' && command[3] == ' ') {
        char* filename = &command[4];
        int file_index = find_file(filename);
        if (file_index != -1) {
            print_string(file_system[file_index].content);
            print_string("\n");
        } else {
            print_string("File not found.\n");
        }
    }
    else if (command[0] == 'r' && command[1] == 'u' && command[2] == 'n' && command[3] == ' ') {
        char* filename = &command[4];
        int file_index = find_file(filename);
        if (file_index != -1) {
            execute_ind_app(file_system[file_index].content);
        } else {
            print_string("App not found.\n");
        }
    }
    else if (command[0] == 'e' && command[1] == 'c' && command[2] == 'h' && command[3] == 'o' && command[4] == ' ') {
        print_string(&command[5]);
        print_string("\n");
    }
    else {
        print_string("Unknown command: ");
        print_string(command);
        print_string("\nType 'help' for a list of commands.\n");
    }
}