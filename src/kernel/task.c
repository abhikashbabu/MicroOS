#include "task.h"
#include "../drivers/display.h"

#define MAX_TASKS 10

Task task_queue[MAX_TASKS];
Task* current_process = 0;
int task_count = 0;

void init_task_manager() {
    task_count = 0;
    
    current_process = &task_queue[0]; 
    current_process->id = 0; // process_id -> id
    current_process->state = 1; 
    current_process->is_active = 1;
    current_process->next_task = current_process; 
}
// NAYA FUNCTION: OS ke background threads chalane ke liye
int create_os_task(void (*entry_point)(), int pid) {
    if (task_count >= MAX_TASKS - 1) return -1; 
    task_count++;
    
    Task* new_task = &task_queue[task_count];
    new_task->id = pid; 
    new_task->state = 0; // READY
    new_task->is_active = 1;
    new_task->memory_used = 10; // dummy size
    
    new_task->regs.eip = (unsigned int)entry_point; // Function ka address set kiya
    new_task->regs.eflags = 0x202; 
    
    new_task->next_task = current_process->next_task;
    current_process->next_task = new_task;
    
    return new_task->id; 
}

int create_task(char* name, int size) {
    if (task_count >= MAX_TASKS - 1) return -1; 
    task_count++;
    
    Task* new_task = &task_queue[task_count];
    new_task->id = task_count; // process_id -> id
    new_task->state = 0; 
    new_task->is_active = 1;
    new_task->memory_used = size; // size -> memory_used
    
    int i = 0;
    while(name[i] != '\0' && i < 31) {
        new_task->name[i] = name[i];
        i++;
    }
    new_task->name[i] = '\0';
    
    new_task->regs.eip = 0;
    new_task->regs.eflags = 0x202; 
    
    new_task->next_task = current_process->next_task;
    current_process->next_task = new_task;
    
    return new_task->id; // process_id -> id
}

void end_task(int pid) {
    for (int i = 0; i <= task_count; i++) {
        if (task_queue[i].id == pid) { // process_id -> id
            task_queue[i].is_active = 0;
            task_queue[i].state = 2; // BLOCKED
        }
    }
}

void context_switch_handler() {
    if (task_count == 0) return; 
    
    current_process->state = 0; 
    current_process = current_process->next_task;
    current_process->state = 1; 
}