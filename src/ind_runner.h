#ifndef IND_RUNNER_H
#define IND_RUNNER_H

#include "display.h"
#include "fs.h"
#include "sound.h"  
#include "task.h"   
#include "io.h"     

extern void itoa(int n, char s[]); 
extern const char keyboard_map[128]; 
extern unsigned int timer_ticks; 

static inline int get_user_number() {
    int num = 0;
    int started = 0; 
    while(1) {
        unsigned char status = inb(0x64);
        if ((status & 1) && !(status & 0x20)) { 
            unsigned char scancode = inb(0x60);
            if (!(scancode & 0x80)) { 
                char c = keyboard_map[scancode];
                if (c == '\n' && started) {
                    print_char('\n');
                    break;
                }
                if (c >= '0' && c <= '9') {
                    print_char(c); 
                    num = (num * 10) + (c - '0');
                    started = 1;
                }
            }
        } else if (status & 0x20) {
            inb(0x60); 
        }
    }
    return num;
}

static inline void execute_ind_app(char* filename, const char* code, unsigned int app_size) {
    
    int pid = create_task(filename, app_size);

    set_color(COLOR_YELLOW, COLOR_BLACK);
    print_string("--- Running .ind App (PID: ");
    char pid_buf[5]; itoa(pid, pid_buf); print_string(pid_buf);
    print_string(") ---\n");

    int vars[26] = {0}; 
    int i = 0;
    
    while (code[i] != '\0') {
        while(code[i] == ' ' || code[i] == '\n' || code[i] == '\r') { i++; }
        if (code[i] == '\0') break;

        // Command: 'print:'
        if (code[i] == 'p' && code[i+1] == 'r' && code[i+2] == 'i' && code[i+3] == 'n' && code[i+4] == 't' && code[i+5] == ':') {
            i += 6;
            while(code[i] != ';' && code[i] != '\0') { 
                print_char(code[i]); 
                i++; 
            }
            print_char('\n'); 
            if (code[i] == ';') { i++; }
        }
        // Command: 'clear:'
        else if (code[i] == 'c' && code[i+1] == 'l' && code[i+2] == 'e' && code[i+3] == 'a' && code[i+4] == 'r' && code[i+5] == ':') {
            clear_screen(); 
            i += 6; 
            if (code[i] == ';') { i++; }
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
            if (code[i] == ';') { i++; }
        }
        // COMMAND: 'window:'
        else if (code[i] == 'w' && code[i+1] == 'i' && code[i+2] == 'n' && code[i+3] == 'd' && code[i+4] == 'o' && code[i+5] == 'w' && code[i+6] == ':') {
            i += 7; 
            char title[30]; 
            int t_idx = 0;
            while(code[i] != ';' && code[i] != '\0' && t_idx < 29) { 
                title[t_idx++] = code[i++]; 
            }
            title[t_idx] = '\0';
            draw_window(10, 5, 60, 15, title, COLOR_BLUE);
            set_color(COLOR_WHITE, COLOR_BLUE); 
            if (code[i] == ';') { i++; }
        }
        // COMMAND: 'delay:'
        else if (code[i] == 'd' && code[i+1] == 'e' && code[i+2] == 'l' && code[i+3] == 'a' && code[i+4] == 'y' && code[i+5] == ':') {
            i += 6; 
            int count = 0;
            while(code[i] >= '0' && code[i] <= '9') { 
                count = (count * 10) + (code[i] - '0'); 
                i++; 
            }
            for(volatile int d = 0; d < count * 20000000; d++) { } 
            if (code[i] == ';') { i++; }
        }
        // COMMAND: 'beep:'
        else if (code[i] == 'b' && code[i+1] == 'e' && code[i+2] == 'e' && code[i+3] == 'p' && code[i+4] == ':') {
            i += 5; 
            int freq = 0;
            while(code[i] >= '0' && code[i] <= '9') { 
                freq = (freq * 10) + (code[i] - '0'); 
                i++; 
            }
            if(freq > 0) {
                play_sound(freq);
                for(volatile int d = 0; d < 40000000; d++) { } 
                stop_sound();
            }
            if (code[i] == ';') { i++; }
        }
        // COMMAND: 'var'
        else if (code[i] == 'v' && code[i+1] == 'a' && code[i+2] == 'r' && code[i+3] == ' ') {
            i += 4; 
            while(code[i] == ' ') { i++; } 
            char v_name = code[i]; 
            i++;
            while(code[i] == ' ') { i++; } 
            int val = 0;
            while(code[i] >= '0' && code[i] <= '9') { 
                val = (val * 10) + (code[i] - '0'); 
                i++; 
            }
            if (v_name >= 'a' && v_name <= 'z') vars[v_name - 'a'] = val;
            while(code[i] == ' ') { i++; } 
            if (code[i] == ';') { i++; }
        }
        // COMMAND: 'add'
        else if (code[i] == 'a' && code[i+1] == 'd' && code[i+2] == 'd' && code[i+3] == ' ') {
            i += 4; 
            while(code[i] == ' ') { i++; } 
            char v_name = code[i]; 
            i++;
            while(code[i] == ' ') { i++; } 
            int val = 0;
            while(code[i] >= '0' && code[i] <= '9') { 
                val = (val * 10) + (code[i] - '0'); 
                i++; 
            }
            if (v_name >= 'a' && v_name <= 'z') vars[v_name - 'a'] += val;
            while(code[i] == ' ') { i++; } 
            if (code[i] == ';') { i++; }
        }
        // COMMAND: 'sub'
        else if (code[i] == 's' && code[i+1] == 'u' && code[i+2] == 'b' && code[i+3] == ' ') {
            i += 4; 
            while(code[i] == ' ') { i++; } 
            char v_name = code[i]; 
            i++;
            while(code[i] == ' ') { i++; } 
            int val = 0;
            while(code[i] >= '0' && code[i] <= '9') { 
                val = (val * 10) + (code[i] - '0'); 
                i++; 
            }
            if (v_name >= 'a' && v_name <= 'z') vars[v_name - 'a'] -= val;
            while(code[i] == ' ') { i++; } 
            if (code[i] == ';') { i++; }
        }
        // COMMAND: 'mul'
        else if (code[i] == 'm' && code[i+1] == 'u' && code[i+2] == 'l' && code[i+3] == ' ') {
            i += 4; 
            while(code[i] == ' ') { i++; } 
            char v_name = code[i]; 
            i++;
            while(code[i] == ' ') { i++; } 
            int val = 0;
            while(code[i] >= '0' && code[i] <= '9') { 
                val = (val * 10) + (code[i] - '0'); 
                i++; 
            }
            if (v_name >= 'a' && v_name <= 'z') vars[v_name - 'a'] *= val;
            while(code[i] == ' ') { i++; } 
            if (code[i] == ';') { i++; }
        }
        // COMMAND: 'input'
        else if (code[i] == 'i' && code[i+1] == 'n' && code[i+2] == 'p' && code[i+3] == 'u' && code[i+4] == 't' && code[i+5] == ' ') {
            i += 6; 
            while(code[i] == ' ') { i++; } 
            char v_name = code[i]; 
            i++;
            if (v_name >= 'a' && v_name <= 'z') {
                vars[v_name - 'a'] = get_user_number(); 
            }
            while(code[i] == ' ') { i++; } 
            if (code[i] == ';') { i++; }
        }
        // COMMAND: 'printvar'
        else if (code[i] == 'p' && code[i+1] == 'r' && code[i+2] == 'i' && code[i+3] == 'n' && code[i+4] == 't' && code[i+5] == 'v' && code[i+6] == 'a' && code[i+7] == 'r' && code[i+8] == ' ') {
            i += 9; 
            while(code[i] == ' ') { i++; } 
            char v_name = code[i]; 
            i++;
            if (v_name >= 'a' && v_name <= 'z') { 
                char buf[16]; 
                itoa(vars[v_name - 'a'], buf); 
                print_string(buf); 
                print_char('\n'); 
            }
            while(code[i] == ' ') { i++; } 
            if (code[i] == ';') { i++; }
        }
        
        // ---------------------------------------------------------
        // LOGIC AND LOOPS 🚀
        // ---------------------------------------------------------

        // COMMAND: 'rand <char>;' -> Creates random number (0 to 99)
        else if (code[i] == 'r' && code[i+1] == 'a' && code[i+2] == 'n' && code[i+3] == 'd' && code[i+4] == ' ') {
            i += 5; 
            while(code[i] == ' ') { i++; } 
            char v_name = code[i]; 
            i++;
            if (v_name >= 'a' && v_name <= 'z') {
                vars[v_name - 'a'] = (timer_ticks % 100); 
            }
            while(code[i] == ' ') { i++; } 
            if (code[i] == ';') { i++; }
        }

        // COMMAND: 'ifeq <char> <char>;' -> If Equal
        else if (code[i] == 'i' && code[i+1] == 'f' && code[i+2] == 'e' && code[i+3] == 'q' && code[i+4] == ' ') {
            i += 5; 
            while(code[i] == ' ') { i++; } 
            char v1 = code[i]; 
            i++;
            while(code[i] == ' ') { i++; } 
            char v2 = code[i]; 
            i++;
            
            int condition = 0;
            if (v1 >= 'a' && v1 <= 'z' && v2 >= 'a' && v2 <= 'z') {
                if (vars[v1 - 'a'] == vars[v2 - 'a']) condition = 1;
            }
            while(code[i] == ' ') { i++; } 
            if (code[i] == ';') { i++; }
            
            if (!condition) {
                while(code[i] != ';' && code[i] != '\0') { i++; }
                if (code[i] == ';') { i++; }
            }
        }

        // COMMAND: 'ifgt <char> <char>;' -> If Greater Than (v1 > v2)
        else if (code[i] == 'i' && code[i+1] == 'f' && code[i+2] == 'g' && code[i+3] == 't' && code[i+4] == ' ') {
            i += 5; 
            while(code[i] == ' ') { i++; } 
            char v1 = code[i]; 
            i++;
            while(code[i] == ' ') { i++; } 
            char v2 = code[i]; 
            i++;
            
            int condition = 0;
            if (v1 >= 'a' && v1 <= 'z' && v2 >= 'a' && v2 <= 'z') {
                if (vars[v1 - 'a'] > vars[v2 - 'a']) condition = 1;
            }
            while(code[i] == ' ') { i++; } 
            if (code[i] == ';') { i++; }
            
            if (!condition) {
                while(code[i] != ';' && code[i] != '\0') { i++; }
                if (code[i] == ';') { i++; }
            }
        }

        // COMMAND: 'lbl <char>;' -> Creates a Bookmark
        else if (code[i] == 'l' && code[i+1] == 'b' && code[i+2] == 'l' && code[i+3] == ' ') {
            i += 4; 
            while(code[i] == ' ') { i++; } 
            i++; // skip char name
            while(code[i] == ' ') { i++; } 
            if (code[i] == ';') { i++; }
        }

        // COMMAND: 'goto <char>;' -> Jump to Bookmark
        else if (code[i] == 'g' && code[i+1] == 'o' && code[i+2] == 't' && code[i+3] == 'o' && code[i+4] == ' ') {
            i += 5; 
            while(code[i] == ' ') { i++; } 
            char target = code[i]; 
            i++;
            while(code[i] == ' ') { i++; } 
            if (code[i] == ';') { i++; }
            
            int s_idx = 0;
            while(code[s_idx] != '\0') {
                if (code[s_idx] == 'l' && code[s_idx+1] == 'b' && code[s_idx+2] == 'l' && code[s_idx+3] == ' ') {
                    int tmp = s_idx + 4;
                    while(code[tmp] == ' ') { tmp++; }
                    if (code[tmp] == target) {
                        while(code[tmp] != ';' && code[tmp] != '\0') { tmp++; }
                        if(code[tmp] == ';') { tmp++; }
                        i = tmp; // TELEPORT!
                        break;
                    }
                }
                s_idx++;
            }
        }

        // SAFE ERROR HANDLER
        else {
            set_color(COLOR_LIGHT_RED, COLOR_BLACK);
            print_string("[Warning] Skipping unknown syntax!\n");
            while(code[i] != ';' && code[i] != '\0') { i++; }
            if (code[i] == ';') { i++; }
            set_color(COLOR_WHITE, COLOR_BLACK); 
        }
    }

    set_color(COLOR_YELLOW, COLOR_BLACK);
    print_string("--- App Terminated ---\n");
    set_color(COLOR_WHITE, COLOR_BLACK);

    if(pid != -1) {
        end_task(pid);
    }
}

#endif