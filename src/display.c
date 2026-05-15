#include "display.h"
#include "io.h"  // NAYA: Hardware ports se baat karne ke liye io.h zaroori hai

volatile unsigned short* vga_buffer = (unsigned short*)0xB8000;
int cursor_x = 0;
int cursor_y = 0;

// Default color: White text on Black background
unsigned char current_color = (COLOR_BLACK << 4) | COLOR_WHITE; 

// 🚀 NAYA FUNCTION: Hardware blinking cursor ko update karne ke liye
void update_cursor(int x, int y) {
    unsigned short pos = y * 80 + x;
    
    // Low byte
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(pos & 0xFF));
    
    // High byte
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
}

void set_color(unsigned char fg, unsigned char bg) {
    // Background ko shift karke foreground ke saath merge karna
    current_color = (bg << 4) | fg;
}

void clear_screen() {
    for (int i = 0; i < 80 * 25; i++) {
        // Space character print karo current background color ke saath
        vga_buffer[i] = (unsigned short)' ' | (current_color << 8);
    }
    cursor_x = 0;
    cursor_y = 0;
    update_cursor(cursor_x, cursor_y); // YAHAN ADD KIYA
}

// Scrolling function
void scroll_screen() {
    // VGA screen mein 25 rows hoti hain (index 0 se 24).
    if (cursor_y >= 25) {
        // Taskbar (Row 0 aur 1) ko chhod kar baki sab ek line upar shift karo
        for (int y = 2; y < 24; y++) {
            for (int x = 0; x < 80; x++) {
                // Niche wali line ko upar wali line mein copy karo
                vga_buffer[y * 80 + x] = vga_buffer[(y + 1) * 80 + x];
            }
        }
        
        // Sabse aakhiri line (Row 24) ko clear kar do
        for (int x = 0; x < 80; x++) {
            vga_buffer[24 * 80 + x] = (unsigned short)' ' | (current_color << 8);
        }
        
        // Cursor ko last line par set kar do
        cursor_y = 24;
        update_cursor(cursor_x, cursor_y); // YAHAN ADD KIYA
    }
}

// print_char function
void print_char(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
        scroll_screen(); 
    } 
    else if (c == '\b') {
        if (cursor_x > 0) cursor_x--;
        // FIXED: cursor_y > 2 rakha hai taaki Taskbar galti se delete na ho
        else if (cursor_y > 2) { cursor_y--; cursor_x = 79; } 
        
        int index = (cursor_y * 80) + cursor_x;
        vga_buffer[index] = (unsigned short)' ' | (current_color << 8);
    } 
    else {
        int index = (cursor_y * 80) + cursor_x;
        vga_buffer[index] = (unsigned short)c | (current_color << 8);
        cursor_x++;
        if (cursor_x >= 80) {
            cursor_x = 0;
            cursor_y++;
            scroll_screen(); 
        }
    }
    
    update_cursor(cursor_x, cursor_y); // YAHAN ADD KIYA: Hardware ko current position bhejo
}

void print_string(const char* str) {
    int i = 0;
    while (str[i] != '\0') {
        print_char(str[i]);
        i++;
    }
}
// NAYA: Pop-up Window bananane ka framework
void draw_window(int start_x, int start_y, int width, int height, const char* title, unsigned char bg_color) {
    unsigned char old_color = current_color;
    set_color(COLOR_WHITE, bg_color);

    // 1. Top and Bottom Borders (Hex \xC4 = Horizontal Line '─')
    for (int x = start_x + 1; x < start_x + width - 1; x++) {
        vga_buffer[start_y * 80 + x] = (unsigned short)'\xC4' | (current_color << 8);
        vga_buffer[(start_y + height - 1) * 80 + x] = (unsigned short)'\xC4' | (current_color << 8);
    }
    
    // 2. Side Borders & Background Fill (Hex \xB3 = Vertical Line '│')
    for (int y = start_y + 1; y < start_y + height - 1; y++) {
        vga_buffer[y * 80 + start_x] = (unsigned short)'\xB3' | (current_color << 8);
        vga_buffer[y * 80 + start_x + width - 1] = (unsigned short)'\xB3' | (current_color << 8);
        
        // Andar ka space fill karna
        for (int x = start_x + 1; x < start_x + width - 1; x++) {
            vga_buffer[y * 80 + x] = (unsigned short)' ' | (current_color << 8);
        }
    }
    
    // 3. 4 Corners lagana
    vga_buffer[start_y * 80 + start_x] = (unsigned short)'\xDA' | (current_color << 8);             // Top-Left ┌
    vga_buffer[start_y * 80 + start_x + width - 1] = (unsigned short)'\xBF' | (current_color << 8); // Top-Right ┐
    vga_buffer[(start_y + height - 1) * 80 + start_x] = (unsigned short)'\xC0' | (current_color << 8); // Bottom-Left └
    vga_buffer[(start_y + height - 1) * 80 + start_x + width - 1] = (unsigned short)'\xD9' | (current_color << 8); // Bottom-Right ┘

    // 4. Window ka Title print karna
    int title_x = start_x + 2;
    int i = 0;
    while(title[i] != '\0' && i < width - 4) {
        vga_buffer[start_y * 80 + title_x + i] = (unsigned short)title[i] | (current_color << 8);
        i++;
    }

    // Color wapas normal kar do
    current_color = old_color;
    
    // Cursor ko window ke theek andar set kar do, taaki aage ka text window mein type ho!
    cursor_x = start_x + 2;
    cursor_y = start_y + 2;
    update_cursor(cursor_x, cursor_y);
}

// Top Taskbar banane ka function
void draw_top_bar(const char* title) {
    // Taskbar ka color: White text on Blue background
    set_color(COLOR_WHITE, COLOR_BLUE);
    cursor_x = 0;
    cursor_y = 0;

    // Pura 1st row (80 columns) space se fill kar do background color ke liye
    for (int i = 0; i < 80; i++) {
        print_char(' ');
    }

    // Title ko row ke starting me likho
    cursor_x = 2;
    cursor_y = 0;
    print_string(title);

    // Color wapas default (Black/White) kar do OS area ke liye
    set_color(COLOR_WHITE, COLOR_BLACK);
    
    // Cursor ko line 1 (Taskbar ke niche) set kar do
    cursor_x = 0;
    cursor_y = 2; 
    update_cursor(cursor_x, cursor_y); // YAHAN ADD KIYA
}