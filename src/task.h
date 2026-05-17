#ifndef TASK_H
#define TASK_H

// PCB Structure wahi rahega
typedef struct {
    int id;
    char name[32];
    unsigned int memory_used;
    int is_active;
} task_t;

// Sirf bata rahe hain ki ye variables kahin aur bane hain (extern)
extern task_t task_list[10];
extern int current_task_count;

// Sirf functions ke naam
void init_task_manager();
void create_task(char* name, unsigned int mem);

#endif