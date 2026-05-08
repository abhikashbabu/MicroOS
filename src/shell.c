#include "shell.h"
#include "display.h"
#include "string.h"

void execute_command(char* command) {
    // Agar input empty hai
    if (command[0] == '\0') {
        return;
    }
    
    // Commands check karna
    if (strcmp(command, "help") == 0) {
        print_string("Available commands:\n");
        print_string("  help  - Show this message\n");
        print_string("  clear - Clear the screen\n");
        print_string("  about - Show OS info\n");
    } 
    else if (strcmp(command, "clear") == 0) {
        clear_screen();
    } 
    else if (strcmp(command, "about") == 0) {
        print_string("Micro OS v0.1\n");
        print_string("Built for the .ind ecosystem.\n");
        print_string("Developer: Abhikash\n");
    } 
    else {
        // Agar command samajh na aaye
        print_string("Unknown command: ");
        print_string(command);
        print_string("\nType 'help' for a list of commands.\n");
    }
}