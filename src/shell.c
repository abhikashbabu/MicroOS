#include "shell.h"
#include "display.h"
#include "string.h"
#include "cmos.h"
#include "io.h"
#include "memory.h"  // NAYA: Memory manager include kiya
#include "fs.h"          // NAYA
#include "ind_runner.h"  // NAYA
#include "editor.h"      // NAYA
#include "pci.h"         // NAYA
#include "task.h"        // NAYA

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
        print_string("  create   - Create a file (e.g., create note.txt This is a note)\n"); // HELP ME BHI ADD KIYA
        print_string("  rm       - Delete a file (e.g., rm note.txt)\n"); // HELP ME BHI ADD KIYA
        print_string("  pci      - Scan PCI Hardware\n"); // HELP ME BHI ADD    KIYA
        print_string("  matrix   - The Matrix Screensaver\n"); // HELP ME BHI ADD KIYA 
        print_string("  top      - Show running tasks\n"); // HELP ME BHI ADD KIYA
             



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
    // NAYA: 'top' command (Task Manager)
    else if (strcmp(command, "top") == 0) {
        draw_window(15, 3, 50, 12, "Task Manager", COLOR_MAGENTA);
        set_color(COLOR_WHITE, COLOR_MAGENTA);
        
        cursor_x = 17; cursor_y = 5; update_cursor(cursor_x, cursor_y);
        print_string("PID   | Task Name           | Memory");
        cursor_x = 17; cursor_y = 6; update_cursor(cursor_x, cursor_y);
        print_string("--------------------------------------");
        
        for(int i = 0; i < current_task_count; i++) {
            if(task_list[i].is_active) {
                cursor_x = 17; cursor_y = 7 + i; update_cursor(cursor_x, cursor_y);
                
                // PID
                char id_buf[5]; itoa(task_list[i].id, id_buf);
                print_string(id_buf); print_string("     | ");
                
                // Task Name
                print_string(task_list[i].name);
                
                // Name alignment ke liye extra spaces
                int len = 0; while(task_list[i].name[len] != '\0') len++;
                for(int s = 0; s < (20 - len); s++) print_char(' ');
                
                print_string("| ");
                
                // Memory
                char mem_buf[10]; itoa(task_list[i].memory_used, mem_buf);
                print_string(mem_buf); print_string(" Bytes");
            }
        }
        
        // Output dikhane ke baad wapas normal terminal position set karna
        cursor_x = 0; cursor_y = 21; update_cursor(cursor_x, cursor_y);
        set_color(COLOR_WHITE, COLOR_BLACK);
    }
    else if (command[0] == 'r' && command[1] == 'u' && command[2] == 'n' && command[3] == ' ') {
        char* filename = &command[4];
        int file_index = find_file(filename);
        if (file_index != -1) {
            // NAYA: Ab file ka naam, uska code, aur uska size teeno engine ko bhej rahe hain
            execute_ind_app(filename, file_system[file_index].content, file_system[file_index].size);
        } else {
            print_string("App not found.\n");
        }
    }
    // NAYA: 'kill <pid>' command
    else if (command[0] == 'k' && command[1] == 'i' && command[2] == 'l' && command[3] == 'l' && command[4] == ' ') {
        int target_pid = 0;
        int idx = 5;
        // PID number padhna
        while(command[idx] >= '0' && command[idx] <= '9') {
            target_pid = (target_pid * 10) + (command[idx] - '0');
            idx++;
        }
        
        if(target_pid == 0 || target_pid == 1) {
            print_string("[Error] Cannot kill System Kernel or Shell!\n");
        } else if(target_pid >= current_task_count || task_list[target_pid].is_active == 0) {
            print_string("[Error] Invalid PID or Task already dead.\n");
        } else {
            end_task(target_pid);
            print_string("[OK] Task PID ");
            char kbuf[5]; itoa(target_pid, kbuf); print_string(kbuf);
            print_string(" terminated successfully.\n");
        }
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
    // NAYA (Day 29): PCI Hardware Scanner
    else if (strcmp(command, "pci") == 0) {
        scan_pci_bus();
    }
    // NAYA (Day 30): The Matrix Screensaver
    else if (strcmp(command, "matrix") == 0) {
        clear_screen();
        set_color(COLOR_LIGHT_GREEN, COLOR_BLACK);
        
        // Digital rain animation loop
        for(int m = 0; m < 500; m++) {
            for(int n = 0; n < 80; n++) {
                if((m + n) % 7 == 0 || (m * n) % 13 == 0) {
                    print_char('0' + (m + n) % 2); // Random 0 or 1
                } else {
                    print_char(' ');
                }
            }
            // Delay taaki animation fast na bhage
            for(volatile int d = 0; d < 8000000; d++){} 
        }
        
        // Screensaver khatam hone par sab normal kardo
        set_color(COLOR_WHITE, COLOR_BLACK);
        clear_screen();
        draw_top_bar(" Micro OS v0.1 | .ind Application Runtime");
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
            // NAYA: Ab hum teeno cheezein bhej rahe hain (Name, Content, aur Size)
            execute_ind_app(filename, file_system[file_index].content, file_system[file_index].size);
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