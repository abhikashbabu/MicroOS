#ifndef IND_RUNNER_H
#define IND_RUNNER_H

#include "display.h"
#include "fs.h"

// .ind file ke andar ke code ko chalane ka engine
static inline void execute_ind_app(const char* code) {
        // App start hone par UI color change karenge
    set_color(COLOR_YELLOW, COLOR_BLACK);
    print_string("--- Running .ind App ---\n");

    // Ek bohot basic parser: Check karte hain kya code "print:" se shuru hota hai
    if (code[0] == 'p' && code[1] == 'r' && code[2] == 'i' && code[3] == 'n' && code[4] == 't' && code[5] == ':') {
        int i = 6; // ":" ke baad wale text se start karo
        while(code[i] != ';' && code[i] != '\0') {
            print_char(code[i]);
            i++;
        }
        print_char('\n');
    } else {
        set_color(COLOR_LIGHT_RED, COLOR_BLACK);
        print_string("Error: Invalid .ind syntax or unknown command.\n");
    }

    set_color(COLOR_YELLOW, COLOR_BLACK);
    print_string("--- App Terminated ---\n");
    
    // Wapas normal color par aa jao
    set_color(COLOR_WHITE, COLOR_BLACK);
}

#endif