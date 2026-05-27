#ifndef PAGING_H
#define PAGING_H

#include "../drivers/display.h"

// Page directory: 1024 entries
unsigned int page_directory[1024] __attribute__((aligned(4096)));

// NAYA: Ab hum 1 table (4MB) ki jagah 4 tables (16MB) map karenge!
unsigned int base_page_tables[4][1024] __attribute__((aligned(4096)));

// VESA Screen ke liye ek alag Page Table (3GB waale address ke liye)
unsigned int vesa_page_table[1024] __attribute__((aligned(4096)));

void init_paging() {
    // 1. Identity map the first 16 MB of memory (Kernel + High-Res Buffer)
    for(int t = 0; t < 4; t++) {
        for(int i = 0; i < 1024; i++) {
            base_page_tables[t][i] = ((t * 0x400000) + (i * 0x1000)) | 3; 
        }
        page_directory[t] = ((unsigned int)base_page_tables[t]) | 3;
    }
    
    // 2. Baaki directory entries ko 'Not Present' mark karo
    for(int i = 4; i < 1024; i++) {
        page_directory[i] = 0 | 2; 
    }

    // 3. Paging ON karo
    __asm__ __volatile__(
        "mov %0, %%cr3\n"
        "mov %%cr0, %%eax\n"
        "or $0x80000000, %%eax\n" 
        "mov %%eax, %%cr0\n"
        : : "r"(page_directory) : "eax"
    );
}

// 4. GRUB jo HD address dega, usko Safe (Map) karna
void map_vesa_memory(unsigned int phys_addr) {
    unsigned int pd_index = phys_addr >> 22;

    for(int i = 0; i < 1024; i++) {
        vesa_page_table[i] = (phys_addr + (i * 0x1000)) | 3; 
    }

    page_directory[pd_index] = ((unsigned int)vesa_page_table) | 3;

    // Flush TLB (Memory Reload)
    __asm__ __volatile__(
        "mov %%cr3, %%eax\n"
        "mov %%eax, %%cr3\n"
        : : : "eax"
    );
}

#endif