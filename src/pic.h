#ifndef PIC_H
#define PIC_H

#include "io.h"

// PIC chips ke ports (Master aur Slave)
#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1

void init_pic() {
    // 1. PIC chips ko "Initialize" command bhejna
    outb(PIC1_COMMAND, 0x11);
    outb(PIC2_COMMAND, 0x11);

    // 2. Remapping: IRQ 0-7 ko INT 32-39 par shift karna (CPU exceptions se bachne ke liye)
    outb(PIC1_DATA, 0x20);
    outb(PIC2_DATA, 0x28);

    // 3. Master aur Slave chip ko aapas mein jodna
    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);

    // 4. x86 Mode set karna
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);

  

    // 5. MASKING (Update)
    // 0xFE ka matlab hai: Sirf bit 0 (Timer) ko allow karo, baaki sab mask rakho.
    outb(PIC1_DATA, 0xFE); 
    outb(PIC2_DATA, 0xFF);
}

#endif