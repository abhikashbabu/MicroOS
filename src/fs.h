#ifndef FS_H
#define FS_H

// File ka structure
typedef struct {
    char name[32];
    char content[256];
    int size;
} File;

// Extern variables (Compiler ko batane ke liye ki memory kahin aur hai)
extern File file_system[10];
extern int file_count;

// Functions declare kar rahe hain
void init_fs();
int find_file(char* filename);

#endif