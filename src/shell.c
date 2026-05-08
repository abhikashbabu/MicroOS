#include "shell.h"
#include "display.h"
#include "string.h"
#include "cmos.h"  // YEH ADD KIYA HAI

void execute_command(char* command) {
    if (command[0] == '\0') return;
    
    if (strcmp(command, "help") == 0) {
        print_string("Available commands:\n");
        print_string("  help  - Show this message\n");
        print_string("  clear - Clear the screen\n");
        print_string("  about - Show OS info\n");
        print_string("  time  - Show current hardware time\n"); // NAYA COMMAND
    } 
    else if (strcmp(command, "clear") == 0) {
        clear_screen();
    } 
    else if (strcmp(command, "about") == 0) {
        print_string("Micro OS v0.1\n");
        print_string("Built for the .ind ecosystem.\n");
        print_string("Developer: Abhikash\n");
    } 
    else if (strcmp(command, "time") == 0) {    // NAYA LOGIC
        int h, m, s;
        get_time(&h, &m, &s);
        
        char buffer[10];
        
        print_string("Current Time (UTC): ");
        
        // Hours
        if (h < 10) print_char('0');
        itoa(h, buffer); print_string(buffer);
        print_char(':');
        
        // Minutes
        if (m < 10) print_char('0');
        itoa(m, buffer); print_string(buffer);
        print_char(':');
        
        // Seconds
        if (s < 10) print_char('0');
        itoa(s, buffer); print_string(buffer);
        print_string("\n");
    }
    else {
        print_string("Unknown command: ");
        print_string(command);
        print_string("\nType 'help' for a list of commands.\n");
    }
}