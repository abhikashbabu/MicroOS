#include "memory.h"

// Variables yahan actually create honge
unsigned int heap_ptr = 0x200000; 
unsigned int start_heap = 0x200000;

void* kmalloc(unsigned int size) {
    if(size == 0) return 0;
    
    void* mem = (void*)heap_ptr;
    heap_ptr += size; 
    
    return mem;
}

unsigned int get_used_memory() {
    return heap_ptr - start_heap;
}

void kfree(void* ptr) {
    (void)ptr; // NAYA: Compiler ki "unused parameter" warning chup karane ke liye
}