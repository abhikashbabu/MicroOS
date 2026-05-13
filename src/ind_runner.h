#ifndef IND_RUNNER_H
#define IND_RUNNER_H

#include "display.h"
#include "fs.h"

static inline void execute_ind_app(const char* code) {
    set_color(COLOR_YELLOW, COLOR_BLACK);
    print_string("--- Running .ind App ---\n");

    int i = 0;
    while (code[i] != '\0') {
        while(code[i] == ' ' || code[i] == '\n') i++;
        if (code[i] == '\0') break;

        // Command: 'print:'
        if (code[i] == 'p' && code[i+1] == 'r' && code[i+2] == 'i' && code[i+3] == 'n' && code[i+4] == 't' && code[i+5] == ':') {
            i += 6;
            while(code[i] != ';' && code[i] != '\0') {
                print_char(code[i]);
                i++;
            }
            print_char('\n');
            if (code[i] == ';') i++;
        }
        // Command: 'clear:'
        else if (code[i] == 'c' && code[i+1] == 'l' && code[i+2] == 'e' && code[i+3] == 'a' && code[i+4] == 'r' && code[i+5] == ':') {
            clear_screen();
            i += 6;
            if (code[i] == ';') i++;
        }
        // NAYA COMMAND: 'color:' (Text ka color badalna)
        else if (code[i] == 'c' && code[i+1] == 'o' && code[i+2] == 'l' && code[i+3] == 'o' && code[i+4] == 'r' && code[i+5] == ':') {
            i += 6;
            int col = 0;
            while(code[i] >= '0' && code[i] <= '9') {
                col = (col * 10) + (code[i] - '0');
                i++;
            }
            // Background black rakhenge, text color user wala hoga
            set_color((unsigned char)col, COLOR_BLACK);
            if (code[i] == ';') i++;
        }
        // NAYA COMMAND: 'delay:' (Loop lagakar animation banana)
        else if (code[i] == 'd' && code[i+1] == 'e' && code[i+2] == 'l' && code[i+3] == 'a' && code[i+4] == 'y' && code[i+5] == ':') {
            i += 6;
            int count = 0;
            while(code[i] >= '0' && code[i] <= '9') {
                count = (count * 10) + (code[i] - '0');
                i++;
            }
            // CPU ko wait karwane ke liye ek dummy loop (Volatile zaroori hai taaki compiler ise delete na kare)
            for(volatile int d = 0; d < count * 20000000; d++) { }
            if (code[i] == ';') i++;
        }
        else {
            set_color(COLOR_LIGHT_RED, COLOR_BLACK);
            print_string("[Error] Unknown syntax inside .ind app!\n");
            break; 
        }
    }

    set_color(COLOR_YELLOW, COLOR_BLACK);
    print_string("--- App Terminated ---\n");
    set_color(COLOR_WHITE, COLOR_BLACK);
}

#endif