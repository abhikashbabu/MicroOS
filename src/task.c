#include "task.h"

task_t task_list[10];
int current_task_count = 0;

void init_task_manager() {
    task_list[0].id = 0;
    char kname[] = "MicroOS Kernel";
    for(int i=0; i<15; i++) task_list[0].name[i] = kname[i];
    task_list[0].memory_used = 1024;
    task_list[0].is_active = 1;
    
    task_list[1].id = 1;
    char sname[] = "CLI Shell";
    for(int i=0; i<10; i++) task_list[1].name[i] = sname[i];
    task_list[1].memory_used = 512;
    task_list[1].is_active = 1;

    current_task_count = 2;
}

// NAYA: Ab yeh function humein nayi PID wapas dega
int create_task(char* name, unsigned int mem) {
    if(current_task_count >= 10) return -1; // Limit reached
    
    int id = current_task_count;
    task_list[id].id = id;
    
    int i = 0;
    while(name[i] != '\0' && i < 31) {
        task_list[id].name[i] = name[i];
        i++;
    }
    task_list[id].name[i] = '\0';
    
    task_list[id].memory_used = mem;
    task_list[id].is_active = 1; // Task ON
    current_task_count++;
    
    return id; // PID return ki
}

// NAYA: Task ko memory se free karna
void end_task(int id) {
    if(id >= 0 && id < 10) {
        task_list[id].is_active = 0; // Task OFF
        task_list[id].memory_used = 0;
    }
}