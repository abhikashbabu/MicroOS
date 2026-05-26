#ifndef TASK_H
#define TASK_H

typedef struct {
    int id;
    char name[32];
    unsigned int memory_used;
    int is_active;
} task_t;

extern task_t task_list[10];
extern int current_task_count;

void init_task_manager();
int create_task(char* name, unsigned int mem); // NAYA: int return karega (PID)
void end_task(int id);                         // NAYA: Task band karne ke liye

#endif