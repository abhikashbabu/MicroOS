#ifndef DISPLAY_H
#define DISPLAY_H

// VGA Standard 16 Colors
#define COLOR_BLACK 0
#define COLOR_BLUE 1
#define COLOR_GREEN 2
#define COLOR_CYAN 3
#define COLOR_RED 4
#define COLOR_MAGENTA 5
#define COLOR_BROWN 6
#define COLOR_LIGHT_GREY 7
#define COLOR_DARK_GREY 8
#define COLOR_LIGHT_BLUE 9
#define COLOR_LIGHT_GREEN 10
#define COLOR_LIGHT_CYAN 11
#define COLOR_LIGHT_RED 12
#define COLOR_LIGHT_MAGENTA 13
#define COLOR_YELLOW 14
#define COLOR_WHITE 15

// Naye functions declare kar rahe hain
void set_color(unsigned char fg, unsigned char bg);
void draw_top_bar(const char* title);
void clear_screen();
void scroll_screen();
void print_string(const char* str);
void print_char(char c);

#endif