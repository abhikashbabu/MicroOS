#ifndef TASK_H
#define TASK_H

// TCB (Task Control Block) - Saves CPU state for Context Switching
typedef struct {
    unsigned int eax, ebx, ecx, edx, esi, edi, esp, ebp;
    unsigned int eip;     // Instruction Pointer
    unsigned int eflags;  // Flags
    unsigned int cr3;     // Page Directory
} CPU_Registers;

typedef struct Task {
    int id;               // process_id ko wapas 'id' kar diya
    int state;            // 0: READY, 1: RUNNING, 2: BLOCKED
    int is_active;        // Shell compatibility
    char name[32];        // IND Runner compatibility
    int memory_used;      // size ko wapas 'memory_used' kar diya
    CPU_Registers regs;
    struct Task* next_task; 
} Task;

extern Task task_queue[];
extern int task_count;

// Backwards compatibility for shell.c
#define task_list task_queue
#define current_task_count task_count

void init_task_manager();
int create_task(char* name, int size); // IND App signature
int create_os_task(void (*entry_point)(), int pid); // NAYA: OS Background threads ke liye
void end_task(int pid); // Added for IND App closing
void context_switch_handler(); 

#endif