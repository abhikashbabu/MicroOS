#ifndef PAGING_H
#define PAGING_H

#include "display.h"

// 1024 entries = 4MB memory per table (4KB per page)
// '__attribute__((aligned(4096)))' ensures memory is exactly on a 4KB boundary
unsigned int page_directory[1024] __attribute__((aligned(4096)));
unsigned int first_page_table[1024] __attribute__((aligned(4096)));

void init_paging() {
    // 1. Identity map the first 4MB of memory
    for(int i = 0; i < 1024; i++) {
        // Flag 3 = Present (1) | Read/Write (2)
        first_page_table[i] = (i * 0x1000) | 3; 
    }

    // 2. Set the first entry of the directory to our page table
    page_directory[0] = ((unsigned int)first_page_table) | 3;
    
    // 3. Mark the rest of the directory as not present (Flag 2 = Read/Write, Not Present)
    for(int i = 1; i < 1024; i++) {
        page_directory[i] = 0 | 2; 
    }

    // 4. Load the page directory into CR3 register and enable Paging in CR0
    __asm__ __volatile__(
        "mov %0, %%cr3\n"
        "mov %%cr0, %%eax\n"
        "or $0x80000000, %%eax\n" // Set the Paging bit (bit 31)
        "mov %%eax, %%cr0\n"
        :
        : "r"(page_directory)
        : "eax"
    );
}

#endif