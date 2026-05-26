#ifndef VESA_H
#define VESA_H

// ----------------------------------------------------
// NAYA (DAY 102): VBE 32-BIT TRUE COLOR ENGINE
// Resolution: 1024 x 768
// Colors: 16.7 Million (ARGB)
// ----------------------------------------------------

// VESA Framebuffer ka physical address (Bootloader set karega)
unsigned int* vesa_framebuffer = (unsigned int*) 0xFD000000; // Example address

// VESA Information Block
typedef struct {
    unsigned short attributes;
    unsigned char window_a;
    unsigned char window_b;
    unsigned short granularity;
    unsigned short window_size;
    unsigned short segment_a;
    unsigned short segment_b;
    unsigned int win_func_ptr;
    unsigned short pitch;         // Bytes per horizontal line
    unsigned short width;         // 1024
    unsigned short height;        // 768
    unsigned char w_char;
    unsigned char y_char;
    unsigned char planes;
    unsigned char bpp;            // 32-bit (Bits Per Pixel)
    unsigned char banks;
    unsigned char memory_model;
    unsigned char bank_size;
    unsigned char image_pages;
    unsigned char reserved0;
} __attribute__((packed)) vbe_mode_info_t;

// NAYA: 1024x768 Screen ke liye Bada Back Buffer (3 MB RAM lagegi!)
unsigned int high_res_buffer[1024 * 768];

// NAYA 32-bit Put Pixel (Ab Colors 0-15 nahi, balki 0xRRGGBB honge!)
void put_pixel_32(int x, int y, unsigned int hex_color) {
    if (x >= 0 && x < 1024 && y >= 0 && y < 768) {
        high_res_buffer[(y * 1024) + x] = hex_color;
    }
}

// Buffer Swap function for High-Res
void swap_buffers_32() {
    for (int i = 0; i < (1024 * 768); i++) {
        vesa_framebuffer[i] = high_res_buffer[i];
    }
}

// NAYA: Modern Rounded Rectangle (Aesthetic UI ke liye)
void draw_rounded_rect(int x, int y, int w, int h, int radius, unsigned int hex_color) {
    for (int i = y; i < y + h; i++) {
        for (int j = x; j < x + w; j++) {
            // Basic corner clipping for rounded effect
            if ((i < y + radius && j < x + radius) || 
                (i < y + radius && j > x + w - radius) || 
                (i > y + h - radius && j < x + radius) || 
                (i > y + h - radius && j > x + w - radius)) {
                continue; // Skip corners
            }
            put_pixel_32(j, i, hex_color);
        }
    }
}

// ----------------------------------------------------
// COLOR PALETTE (Modern HEX Colors)
// ----------------------------------------------------
#define COLOR_DARK_BG   0x001E1E1E  // Modern Dark Mode Background
#define COLOR_TASKBAR   0x002D2D30
#define COLOR_ACCENT    0x00007ACC  // Windows/Micro OS Blue
#define COLOR_TEXT      0x00E0E0E0  // Soft White
#define COLOR_DANGER    0x00FF4C4C  // Modern Red

#endif