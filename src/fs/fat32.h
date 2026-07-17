// ==============================================================
// DAY 175: BULLETPROOF FAT32 ENGINE (DELETE & SAFE PADDING)
// ==============================================================
#ifndef FAT32_H
#define FAT32_H

#include "../drivers/ata.h"

extern void hd_print(char* text);
extern void hd_itoa(int n, char* buf);

unsigned int fat_bytes_per_sector = 0;
unsigned int fat_sectors_per_cluster = 0;
unsigned int fat_reserved_sectors = 0;
unsigned int fat_num_fats = 0;        
unsigned int fat_sectors_per_fat = 0;
unsigned int fat_root_cluster = 0;
unsigned int first_data_sector = 0;   

void init_fat32() {
    unsigned char boot_sector[512];
    ata_read_sector(0, boot_sector);
    if (boot_sector[510] != 0x55 || boot_sector[511] != 0xAA) return;
    fat_bytes_per_sector    = boot_sector[11] | (boot_sector[12] << 8);
    fat_sectors_per_cluster = boot_sector[13];
    fat_reserved_sectors    = boot_sector[14] | (boot_sector[15] << 8);
    fat_num_fats            = boot_sector[16]; 
    fat_sectors_per_fat = boot_sector[36] | (boot_sector[37] << 8) | (boot_sector[38] << 16) | (boot_sector[39] << 24);
    fat_root_cluster    = boot_sector[44] | (boot_sector[45] << 8) | (boot_sector[46] << 16) | (boot_sector[47] << 24);
    first_data_sector = fat_reserved_sectors + (fat_num_fats * fat_sectors_per_fat);
    hd_print("[FAT32] BPB Parsed! File System Connected.");
}

void fat32_list_root() {
    unsigned char sec_buf[512]; 
    unsigned int root_lba = first_data_sector + ((fat_root_cluster - 2) * fat_sectors_per_cluster);
    ata_read_sector(root_lba, sec_buf);
    hd_print("[FAT32] Root Directory (C:\\) Contents:");
    int found = 0;
    for (int i = 0; i < 16; i++) {
        int off = i * 32;
        if (sec_buf[off] == 0x00) break;
        if (sec_buf[off] == 0xE5 || sec_buf[off + 11] == 0x0F) continue;
        char print_buf[20] = " -> "; int p = 4;
        for (int j = 0; j < 11; j++) {
            if (sec_buf[off + j] != ' ') {
                if (j == 8) print_buf[p++] = '.';
                print_buf[p++] = sec_buf[off + j];
            }
        }
        print_buf[p] = '\0'; hd_print(print_buf); found++;
    }
    if (found == 0) hd_print(" -> (Empty)");
}

// HELPER: Auto-Padding logic (Ab space dene ki tension khatam)
void format_fat_name(char* name, char* ext, char* formatted) {
    for(int i=0; i<11; i++) formatted[i] = ' '; // Fill spaces
    for(int i=0; i<8; i++) { if(name[i] == '\0') break; formatted[i] = name[i]; }
    for(int i=0; i<3; i++) { if(ext[i] == '\0') break; formatted[8+i] = ext[i]; }
}

// ==============================================================
// GENERIC GUI FILE READER (BUFFER OVERFLOW PROTECTED)
// ==============================================================
int fat32_read_file(char* filename, char* ext, char* out_buffer, int* out_length) {
    unsigned char sec_buf[512]; 
    unsigned int root_lba = first_data_sector + ((fat_root_cluster - 2) * fat_sectors_per_cluster);
    ata_read_sector(root_lba, sec_buf);
    
    char target[11]; format_fat_name(filename, ext, target);

    for (int i = 0; i < 16; i++) {
        int off = i * 32;
        if (sec_buf[off] == 0x00) break;
        if (sec_buf[off] == 0xE5 || sec_buf[off + 11] == 0x0F) continue;

        int match = 1;
        for(int j=0; j<11; j++) { if (sec_buf[off+j] != target[j]) match = 0; }

        if (match) {
            unsigned int cluster_high = (sec_buf[off + 21] << 8) | sec_buf[off + 20];
            unsigned int cluster_low  = (sec_buf[off + 27] << 8) | sec_buf[off + 26];
            unsigned int file_cluster = (cluster_high << 16) | cluster_low;
            
            // File size nikalna
            int size = sec_buf[off+28] | (sec_buf[off+29]<<8) | (sec_buf[off+30]<<16) | (sec_buf[off+31]<<24);
            
            // Limit the size taaki out_buffer na fate!
            if (size > 512) size = 512; 
            *out_length = size;

            unsigned int file_lba = first_data_sector + ((file_cluster - 2) * fat_sectors_per_cluster);
            
            // BUG FIX MAGIC: Pehle RAM ke Safe Buffer mein 512 bytes read karo...
            unsigned char safe_data_buf[512];
            ata_read_sector(file_lba, safe_data_buf);
            
            // ...Aur phir sirf jitni file ki length hai, utna hi out_buffer mein daalo!
            for(int k = 0; k < size; k++) {
                out_buffer[k] = safe_data_buf[k];
            }
            
            return 1; 
        }
    }
    return 0; 
}
// NAYA: DELETE FILE FUNCTION (Overwrite se pehle purani udao)
void fat32_delete_file(char* filename, char* ext) {
    unsigned char sec_buf[512]; 
    unsigned int root_lba = first_data_sector + ((fat_root_cluster - 2) * fat_sectors_per_cluster);
    ata_read_sector(root_lba, sec_buf);
    
    char target[11]; format_fat_name(filename, ext, target);

    for (int i = 0; i < 16; i++) {
        int off = i * 32;
        if (sec_buf[off] == 0x00) break;
        if (sec_buf[off] == 0xE5 || sec_buf[off + 11] == 0x0F) continue;

        int match = 1;
        for(int j=0; j<11; j++) { if (sec_buf[off+j] != target[j]) match = 0; }

        if (match) {
            sec_buf[off] = 0xE5; // Mark as deleted!
            ata_write_sector(root_lba, sec_buf);
            return;
        }
    }
}
// 3. MULTI-SECTOR WRITE ENGINE (LARGE FILES & BMP SUPPORT)
void fat32_write_file(char* filename, char* ext, unsigned char* data, int data_size) {
    fat32_delete_file(filename, ext); 
    
    int clusters_needed = (data_size + 511) / 512; 
    unsigned int first_cluster = 0, prev_cluster = 0;
    unsigned char fat_buf[512] = {0}; // MEMORY CORRUPTION FIX
    unsigned int current_fat_sec = 0xFFFFFFFF;
    int data_offset = 0;
    
    // Allocate and Link Clusters!
    for (int i = 0; i < clusters_needed; i++) {
        unsigned int free_cluster = 0;
        for (unsigned int c = 2; c < 65536; c++) { 
            unsigned int sec = fat_reserved_sectors + ((c * 4) / 512);
            unsigned int off = c % 128;
            if (sec != current_fat_sec) {
                if (current_fat_sec != 0xFFFFFFFF) ata_write_sector(current_fat_sec, fat_buf);
                ata_read_sector(sec, fat_buf); current_fat_sec = sec;
            }
            if (((unsigned int*)fat_buf)[off] == 0x00000000) {
                free_cluster = c;
                ((unsigned int*)fat_buf)[off] = 0x0FFFFFFF; 
                break;
            }
        }
        if (free_cluster == 0) return; // Disk Full
        if (first_cluster == 0) first_cluster = free_cluster;
        
        if (prev_cluster != 0) {
            unsigned int p_sec = fat_reserved_sectors + ((prev_cluster * 4) / 512);
            unsigned int p_off = prev_cluster % 128;
            if (p_sec != current_fat_sec) {
                ata_write_sector(current_fat_sec, fat_buf); 
                ata_read_sector(p_sec, fat_buf); current_fat_sec = p_sec;
            }
            ((unsigned int*)fat_buf)[p_off] = free_cluster;
        }
        prev_cluster = free_cluster;
        
        // Write Sector Chunk
        unsigned int data_lba = first_data_sector + ((free_cluster - 2) * fat_sectors_per_cluster);
        unsigned char data_sec[512] = {0};
        int bytes_to_copy = data_size - data_offset;
        if (bytes_to_copy > 512) bytes_to_copy = 512;
        
        for(int b=0; b<bytes_to_copy; b++) data_sec[b] = data[data_offset++];
        ata_write_sector(data_lba, data_sec);
    }
    if (current_fat_sec != 0xFFFFFFFF) ata_write_sector(current_fat_sec, fat_buf);
    
    // Root Directory Entry setup
    unsigned char root_buf[512] = {0}; // MEMORY CORRUPTION FIX
    unsigned int root_lba = first_data_sector + ((fat_root_cluster - 2) * fat_sectors_per_cluster);
    ata_read_sector(root_lba, root_buf);
    int entry_offset = -1;
    for (int i = 0; i < 16; i++) {
        int off = i * 32;
        if (root_buf[off] == 0x00 || root_buf[off] == 0xE5) { entry_offset = off; break; }
    }
    if (entry_offset == -1) return;
    char target[11]; format_fat_name(filename, ext, target);
    for(int i=0; i<11; i++) root_buf[entry_offset + i] = target[i];
    
    root_buf[entry_offset + 11] = 0x20; 
    root_buf[entry_offset + 20] = (first_cluster >> 16) & 0xFF; 
    root_buf[entry_offset + 21] = (first_cluster >> 24) & 0xFF;
    root_buf[entry_offset + 26] = first_cluster & 0xFF;         
    root_buf[entry_offset + 27] = (first_cluster >> 8) & 0xFF;
    root_buf[entry_offset + 28] = data_size & 0xFF;
    root_buf[entry_offset + 29] = (data_size >> 8) & 0xFF;
    root_buf[entry_offset + 30] = (data_size >> 16) & 0xFF;
    root_buf[entry_offset + 31] = (data_size >> 24) & 0xFF;
    ata_write_sector(root_lba, root_buf);
}
// ==============================================================
// NAYA: VFS BRIDGE (HARD DRIVE KO 'MY PC' SE JODNE KE LIYE)
// ==============================================================
extern void create_file(char* name, char* content);
extern int file_count;

void fat32_sync_vfs() {
    file_count = 0; // 1. Purani RAM memory clear karo
    
    // 2. System App (Welcome App) wapas daalo taaki Start Menu na tute
    create_file("app.ind", "T:Welcome App;M:What is your name?;I:Enter Name;B:Submit;");

    // 3. Hard Drive ka Root Folder read karo
    unsigned char sec_buf[512] = {0}; 
    unsigned int root_lba = first_data_sector + ((fat_root_cluster - 2) * fat_sectors_per_cluster);
    ata_read_sector(root_lba, sec_buf);
    
    for (int i = 0; i < 16; i++) {
        int off = i * 32;
        if (sec_buf[off] == 0x00) break;
        if (sec_buf[off] == 0xE5 || sec_buf[off + 11] == 0x0F) continue;

        // 4. File ka naam nikalo (e.g., IMG.BMP)
        char fname[13]; int p = 0;
        for (int j = 0; j < 8; j++) { if (sec_buf[off + j] != ' ') fname[p++] = sec_buf[off + j]; }
        fname[p++] = '.';
        for (int j = 0; j < 3; j++) { if (sec_buf[off + 8 + j] != ' ') fname[p++] = sec_buf[off + 8 + j]; }
        fname[p] = '\0';

        // 5. 'My PC' App ko batane ke liye list mein add karo!
        if (fname[0] == 'N' && fname[1] == 'O' && fname[2] == 'T') {
            // Agar Note hai toh uska text bhi nikal lo (taaki double click pe khule!)
            char tmp[512] = {0}; int l = 0;
            fat32_read_file("NOTE", "TXT", ( char*)tmp, &l);
            tmp[l] = '\0';
            create_file(fname, tmp);
        } else {
            // Agar Image hai toh bas naam show karo
            create_file(fname, "<HDD BINARY FILE>");
        }
    }
}
#endif