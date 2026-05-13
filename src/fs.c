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
void create_file(char* name, char* content) {
    if (file_count >= 10) return; // Maximum 10 files allowed in memory
    
    int i = 0;
    // File ka naam copy karna
    while(name[i] != '\0' && i < 31) { 
        file_system[file_count].name[i] = name[i]; 
        i++; 
    }
    file_system[file_count].name[i] = '\0';

    i = 0;
    // File ka content (code) copy karna
    while(content[i] != '\0' && i < 255) { 
        file_system[file_count].content[i] = content[i]; 
        i++; 
    }
    file_system[file_count].content[i] = '\0';
    
    file_system[file_count].size = i;
    file_count++; // Total files ka number badha do
}
// NAYA: File delete karne ka function
void delete_file(char* filename) {
    int idx = find_file(filename);
    if (idx == -1) return;
    
    // Baaki files ko left shift kar do (Pichli file ko overwrite kardo)
    for (int i = idx; i < file_count - 1; i++) {
        file_system[i] = file_system[i + 1];
    }
    file_count--; // Total count kam kar do
}

// NAYA: Existing file mein naya code add karne ka function
void append_file(char* filename, char* extra) {
    int idx = find_file(filename);
    if (idx == -1) return;
    
    int curr_len = file_system[idx].size;
    int i = 0;
    
    // Puraane content ke aage naya text copy karo
    while(extra[i] != '\0' && (curr_len + i) < 254) {
        file_system[idx].content[curr_len + i] = extra[i];
        i++;
    }
    file_system[idx].content[curr_len + i] = '\0';
    file_system[idx].size = curr_len + i;
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