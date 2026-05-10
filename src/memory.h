#ifndef MEMORY_H
#define MEMORY_H

// Safe memory address jahan se hum apps ko RAM dena shuru karenge (2 MB mark)
unsigned int free_memory_address = 0x200000;

// Kernel Memory Allocator (kmalloc)
void* kmalloc(unsigned int size) {
    // Current free address ko save karo
    void* allocated_memory = (void*)free_memory_address;
    
    // Pointer ko aage badha do jitni memory maangi gayi hai
    free_memory_address += size; 
    
    return allocated_memory;
}

// OS kitni dynamically memory use kar raha hai?
unsigned int get_used_memory() {
    return free_memory_address - 0x200000;
}

#endif