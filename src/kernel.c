// VGA text mode buffer memory location
volatile unsigned short* vga_buffer = (unsigned short*)0xB8000;

void kernel_main() {
    // Screen clear karne ke liye index
    int i = 0;
    
    // Screen clear karna (Space character with black background)
    for (i = 0; i < 80 * 25; i++) {
        vga_buffer[i] = (unsigned short)' ' | (0x0F << 8); 
    }

    // Apni string print karna
    const char* str = "Welcome to Micro OS - Day 1!";
    i = 0;
    while (str[i] != '\0') {
        // 0x0F means White text (F) on Black background (0)
        vga_buffer[i] = (unsigned short)str[i] | (0x0F << 8);
        i++;
    }
}