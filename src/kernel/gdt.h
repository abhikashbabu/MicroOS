// ==============================================================
// RING 3 & TSS READY GDT (GLOBAL DESCRIPTOR TABLE)
// ==============================================================
#ifndef GDT_H
#define GDT_H

struct gdt_entry {
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char  base_middle;
    unsigned char  access;
    unsigned char  granularity;
    unsigned char  base_high;
} __attribute__((packed));

struct gdt_ptr {
    unsigned short limit;
    unsigned int   base;
} __attribute__((packed));

// NAYA: TSS Structure (Ring 3 se Ring 0 wapas aane ke liye)
struct tss_entry_struct {
    unsigned int prev_tss; 
    unsigned int esp0;       // Kernel Stack Pointer
    unsigned int ss0;        // Kernel Stack Segment
    unsigned int esp1; unsigned int ss1; unsigned int esp2; unsigned int ss2;
    unsigned int cr3; unsigned int eip; unsigned int eflags;
    unsigned int eax; unsigned int ecx; unsigned int edx; unsigned int ebx;
    unsigned int esp; unsigned int ebp; unsigned int esi; unsigned int edi;
    unsigned int es; unsigned int cs; unsigned int ss; unsigned int ds;
    unsigned int fs; unsigned int gs; unsigned int ldt; unsigned short trap;
    unsigned short iomap_base;
} __attribute__((packed));

struct gdt_entry gdt[6]; // Null, K-Code, K-Data, U-Code, U-Data, TSS
struct gdt_ptr gp;
struct tss_entry_struct tss_entry;

void gdt_set_gate(int num, unsigned int base, unsigned int limit, unsigned char access, unsigned char gran) {
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

// NAYA: TSS Setup Function
void write_tss(int num, unsigned short ss0, unsigned int esp0) {
    unsigned int base = (unsigned int) &tss_entry;
    unsigned int limit = sizeof(tss_entry);

    gdt_set_gate(num, base, limit, 0xE9, 0x00);
    
    // TSS memory ko zero se saaf karo
    unsigned char* tss_ptr = (unsigned char*)&tss_entry;
    for (unsigned int i = 0; i < sizeof(tss_entry); i++) tss_ptr[i] = 0;

    tss_entry.ss0  = ss0;  // Kernel Stack Segment (0x10)
    tss_entry.esp0 = esp0; // Kernel Stack Pointer
    tss_entry.cs   = 0x08 | 0x3; 
    tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x10 | 0x3;
    tss_entry.iomap_base = sizeof(tss_entry);
}

extern void gdt_flush();
extern void tss_flush();

void init_gdt() {
    gp.limit = (sizeof(struct gdt_entry) * 6) - 1;
    gp.base = (unsigned int)&gdt;

    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel Data segment
    
    // NAYA: User Mode Segments!
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // Ring 3 User Code
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // Ring 3 User Data
    
    // NAYA: Write TSS to GDT entry 5
    write_tss(5, 0x10, 0x0); // ESP0 baad mein task switch ke time set hoga

    gdt_flush();
    tss_flush(); // Hardware ko batao ki TSS lag gaya hai
}
#endif