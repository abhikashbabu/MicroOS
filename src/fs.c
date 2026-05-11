#include "fs.h"

// Yahan actual memory ban rahi hai
File file_system[10];
int file_count = 0;

void init_fs() {
    // 1. Ek simple Text file
    char* name1 = "readme.txt";
    char* content1 = "Micro OS is an experimental x86 OS!";
    int i = 0; while(name1[i]) { file_system[0].name[i] = name1[i]; i++; } file_system[0].name[i] = '\0';
    i = 0; while(content1[i]) { file_system[0].content[i] = content1[i]; i++; } file_system[0].content[i] = '\0';
    file_system[0].size = 35;

    // 2. Tumhari .ind app
    char* name2 = "hello.ind";
    char* content2 = "print:Hello from IND App!;";
    i = 0; while(name2[i]) { file_system[1].name[i] = name2[i]; i++; } file_system[1].name[i] = '\0';
    i = 0; while(content2[i]) { file_system[1].content[i] = content2[i]; i++; } file_system[1].content[i] = '\0';
    file_system[1].size = 26;

    file_count = 2;
}

int find_file(char* filename) {
    for (int i = 0; i < file_count; i++) {
        int j = 0;
        int match = 1;
        while (filename[j] != '\0' || file_system[i].name[j] != '\0') {
            if (filename[j] != file_system[i].name[j]) {
                match = 0;
                break;
            }
            j++;
        }
        if (match) return i; 
    }
    return -1; 
}