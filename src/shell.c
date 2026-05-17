#include "shell.h"
#include "display.h"
#include "string.h"
#include "cmos.h"
#include "io.h"
#include "memory.h"  // NAYA: Memory manager include kiya
#include "fs.h"          // NAYA
#include "ind_runner.h"  // NAYA
#include "editor.h"      // NAYA

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
        print_string("  edit    - Edit a file (e.g., edit readme.txt)\n"); // HELP ME BHI ADD KIYA
        print_string("  explorer - Browse files\n"); // HELP ME BHI ADD KIYA

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
    // NAYA: 'create <filename> <content>' command (Live Coding!)
    else if (command[0] == 'c' && command[1] == 'r' && command[2] == 'e' && command[3] == 'a' && command[4] == 't' && command[5] == 'e' && command[6] == ' ') {
        int idx = 7;
        char filename[32];
        int f_idx = 0;
        
        // 1. Pehle space tak file ka naam nikalna
        while(command[idx] != ' ' && command[idx] != '\0' && f_idx < 31) {
            filename[f_idx++] = command[idx++];
        }
        filename[f_idx] = '\0'; // Naam close kiya
        
        if (command[idx] == ' ') idx++; // Space skip karo
        
        // 2. Baaki bacha hua pura text file ke andar save kar do
        create_file(filename, &command[idx]);
        
        print_string("App generated successfully! Type 'ls' to view it.\n");
    }
    // NAYA: 'rm <filename>' command (Delete file)
    else if (command[0] == 'r' && command[1] == 'm' && command[2] == ' ') {
        char* filename = &command[3];
        int file_index = find_file(filename);
        if (file_index != -1) {
            delete_file(filename);
            print_string("File deleted successfully.\n");
        } else {
            print_string("Error: File not found.\n");
        }
    }
    // NAYA: 'append <filename> <content>' command (File me line add karna)
    else if (command[0] == 'a' && command[1] == 'p' && command[2] == 'p' && command[3] == 'e' && command[4] == 'n' && command[5] == 'd' && command[6] == ' ') {
        int idx = 7;
        char filename[32];
        int f_idx = 0;
        
        while(command[idx] != ' ' && command[idx] != '\0' && f_idx < 31) {
            filename[f_idx++] = command[idx++];
        }
        filename[f_idx] = '\0';
        
        if (command[idx] == ' ') idx++; 
        
        append_file(filename, &command[idx]);
        print_string("Content appended successfully.\n");
    }
    // NAYA: 'date' command
    else if (strcmp(command, "date") == 0) {
        int d, m, y;
        get_date(&d, &m, &y);
        char buffer[10];
        
        print_string("Current Date: ");
        if (d < 10) print_char('0');
        itoa(d, buffer); print_string(buffer);
        print_char('/');
        
        if (m < 10) print_char('0');
        itoa(m, buffer); print_string(buffer);
        print_char('/');
        
        print_string("20"); // 2000s Century
        if (y < 10) print_char('0');
        itoa(y, buffer); print_string(buffer);
        print_string("\n");
    }
    // NAYA: Visual File Explorer
    else if (strcmp(command, "explorer") == 0) {
        draw_window(10, 4, 60, 16, "Micro Explorer - Files", COLOR_CYAN);
        set_color(COLOR_BLACK, COLOR_CYAN);
        
        int start_y = 6;
        for(int j = 0; j < file_count; j++) {
            cursor_x = 13; cursor_y = start_y + j; update_cursor(cursor_x, cursor_y);
            print_string("-> ");
            print_string(file_system[j].name);
            print_string(" (");
            char sb[10]; itoa(file_system[j].size, sb); print_string(sb);
            print_string(" bytes)");
        }
        
        // Wapas normal color set karo shell ke liye
        cursor_x = 0; cursor_y = 21; update_cursor(cursor_x, cursor_y);
        set_color(COLOR_WHITE, COLOR_BLACK);
    }
    // NAYA: Live Code Editor
    else if (command[0] == 'e' && command[1] == 'd' && command[2] == 'i' && command[3] == 't' && command[4] == ' ') {
        char filename[32];
        int i = 5, j = 0;
        while (command[i] != '\0' && j < 31) {
            filename[j++] = command[i++];
        }
        filename[j] = '\0';
        
        // Editor start karo
        run_editor(filename);
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