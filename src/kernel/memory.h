#ifndef MEMORY_H
#define MEMORY_H

// Sirf bata rahe hain ki ye variables kahin aur bane hue hain (extern)
extern unsigned int heap_ptr;
extern unsigned int start_heap;

// Sirf functions ke naam
void* kmalloc(unsigned int size);
unsigned int get_used_memory();
void kfree(void* ptr);

#endif