#include "task.h"

// Variables yahan permanently banenge
task_t task_list[10];
int current_task_count = 0;

// OS boot hote hi default tasks register karna
void init_task_manager() {
    // Task 0: Kernel
    task_list[0].id = 0;
    char kname[] = "MicroOS Kernel";
    for(int i=0; i<15; i++) task_list[0].name[i] = kname[i];
    task_list[0].memory_used = 1024;
    task_list[0].is_active = 1;
    
    // Task 1: Shell
    task_list[1].id = 1;
    char sname[] = "CLI Shell";
    for(int i=0; i<10; i++) task_list[1].name[i] = sname[i];
    task_list[1].memory_used = 512;
    task_list[1].is_active = 1;

    current_task_count = 2;
}

// Naya task start karne ka function
void create_task(char* name, unsigned int mem) {
    if(current_task_count >= 10) return; // Limit check
    
    int id = current_task_count;
    task_list[id].id = id;
    
    // Name copy karna
    int i = 0;
    while(name[i] != '\0' && i < 31) {
        task_list[id].name[i] = name[i];
        i++;
    }
    task_list[id].name[i] = '\0';
    
    task_list[id].memory_used = mem;
    task_list[id].is_active = 1;
    current_task_count++;
}