#ifndef TIMER_H
#define TIMER_H

#include "../drivers/display.h"
#include "../kernel/io.h"
#include "../runtime/string.h"

extern void context_switch_handler();

// OS ke dusre files se variables aur functions lana (extern ka jaadu)
extern unsigned char current_color;
extern int cursor_x;
extern int cursor_y;
void update_cursor(int x, int y);

unsigned int timer_ticks = 0;

// FIX: Yahan se __attribute__ aur (void* frame) hata diya gaya hai!
// Kyunki ab isr.asm (Assembly Wrapper) isko safe tarike se call karega.
void timer_handler() {
    timer_ticks++;
    
    // PIT by default ~18.2 Hz par chalta hai. (18 ticks = approx 1 second)
    if (timer_ticks % 18 == 0) {
        unsigned char old_c = current_color;
        int old_x = cursor_x;
        int old_y = cursor_y;
        
        // Taskbar ke top-right corner mein "Uptime" print karna
        set_color(COLOR_YELLOW, COLOR_BLUE);
        cursor_x = 65; 
        cursor_y = 0;
        print_string(" Uptime: ");
        
        char buf[5];
        itoa((timer_ticks / 18), buf); // Seconds
        print_string(buf);
        print_char('s');
        
        // Cursor ko wapas uski original jagah rakh do taaki user ki typing disturb na ho
        cursor_x = old_x; 
        cursor_y = old_y;
        current_color = old_c;
        update_cursor(cursor_x, cursor_y);
    }
    
    // Hardware ko signal bhejo ki "Mera kaam ho gaya" (EOI - End of Interrupt)
    outb(0x20, 0x20);
    context_switch_handler();
}

#endif