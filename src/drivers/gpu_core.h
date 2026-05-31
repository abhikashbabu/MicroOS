#ifndef GPU_CORE_H
#define GPU_CORE_H

// ==========================================
// OS FRAMEBUFFER BRIGHTNESS DRIVER
// ==========================================

void apply_hardware_brightness(unsigned int* buffer, int brightness, int width, int height) {
    // Agar slider full hai (150), toh CPU cycle bachane ke liye function skip kar do
    if (brightness >= 150) return; 

    // Brightness slider (0-150) ko RGB multiplier (0-255) mein convert karna
    int multiplier = (brightness * 255) / 150;
    int total_pixels = width * height;

    // Poore VESA memory buffer ke har ek pixel ko dynamically dark karna
    for (int i = 0; i < total_pixels; i++) {
        unsigned int pixel = buffer[i];
        
        // Pixel ke andar se Red, Green aur Blue colors ko alag karna
        unsigned int r = (pixel >> 16) & 0xFF;
        unsigned int g = (pixel >> 8) & 0xFF;
        unsigned int b = pixel & 0xFF;

        // Multiplier ke hisaab se colors ko dark karna
        r = (r * multiplier) / 255;
        g = (g * multiplier) / 255;
        b = (b * multiplier) / 255;

        // Wapas 32-bit memory mein pack karke save karna
        buffer[i] = (r << 16) | (g << 8) | b;
    }
}

#endif