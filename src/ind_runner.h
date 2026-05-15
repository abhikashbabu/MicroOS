#ifndef IND_RUNNER_H
#define IND_RUNNER_H

#include "display.h"
#include "fs.h"
#include "sound.h"  // YEH WALI LINE ADD HUI HAI! 🔊

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
        // Command: 'color:'
        else if (code[i] == 'c' && code[i+1] == 'o' && code[i+2] == 'l' && code[i+3] == 'o' && code[i+4] == 'r' && code[i+5] == ':') {
            i += 6;
            int col = 0;
            while(code[i] >= '0' && code[i] <= '9') {
                col = (col * 10) + (code[i] - '0');
                i++;
            }
            set_color((unsigned char)col, COLOR_BLACK);
            if (code[i] == ';') i++;
        }
        // NAYA COMMAND: 'window:' (Draw a GUI Window!)
        else if (code[i] == 'w' && code[i+1] == 'i' && code[i+2] == 'n' && code[i+3] == 'd' && code[i+4] == 'o' && code[i+5] == 'w' && code[i+6] == ':') {
            i += 7;
            char title[30];
            int t_idx = 0;
            // Title extract karo
            while(code[i] != ';' && code[i] != '\0' && t_idx < 29) {
                title[t_idx++] = code[i++];
            }
            title[t_idx] = '\0';
            
            // Ek pop-up window draw karo (Centered, Blue background ke sath)
            draw_window(10, 5, 60, 15, title, COLOR_BLUE);
            
            // Ab iske baad aane wala text directly Blue window ke andar print hoga!
            set_color(COLOR_WHITE, COLOR_BLUE); 
            
            if (code[i] == ';') i++;
        }
        // Command: 'delay:'
        else if (code[i] == 'd' && code[i+1] == 'e' && code[i+2] == 'l' && code[i+3] == 'a' && code[i+4] == 'y' && code[i+5] == ':') {
            i += 6;
            int count = 0;
            while(code[i] >= '0' && code[i] <= '9') {
                count = (count * 10) + (code[i] - '0');
                i++;
            }
            for(volatile int d = 0; d < count * 20000000; d++) { }
            if (code[i] == ';') i++;
        }
        // NAYA COMMAND: 'beep:'
        else if (code[i] == 'b' && code[i+1] == 'e' && code[i+2] == 'e' && code[i+3] == 'p' && code[i+4] == ':') {
            i += 5;
            int freq = 0;
            while(code[i] >= '0' && code[i] <= '9') {
                freq = (freq * 10) + (code[i] - '0');
                i++;
            }
            if(freq > 0) {
                play_sound(freq);
                // CPU ko thodi der rukne do taaki beep sunayi de
                for(volatile int d = 0; d < 40000000; d++) { } 
                stop_sound();
            }
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