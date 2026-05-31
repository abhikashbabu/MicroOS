#ifndef IDT_H
#define IDT_H
#include "../kernel/timer.h" 
#include "../kernel/io.h"

extern void context_switch_handler();

struct idt_entry {
    unsigned short base_low;
    unsigned short sel;
    unsigned char zero;
    unsigned char flags;
    unsigned short base_high;
} __attribute__((packed));

extern void isr32(); 
extern void isr33(); 
extern void isr44(); 

struct idt_ptr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
    idt[num].base_low = (base & 0xFFFF);
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].zero = 0;
    idt[num].flags = flags;
}

void idt_init() {
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (unsigned int)&idt;

    idt_set_gate(32, (unsigned int)isr32, 0x08, 0x8E); 
    idt_set_gate(33, (unsigned int)isr33, 0x08, 0x8E); 
    idt_set_gate(44, (unsigned int)isr44, 0x08, 0x8E); 

    // NAYA FIX: Direct inline assembly se IDT load kar diya! No external load_idt needed.
    __asm__ volatile ("lidt %0" : : "m" (idtp));
}
#endif