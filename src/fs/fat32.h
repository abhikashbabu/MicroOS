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

void fat32_write_file(char* filename, char* ext, char* data, int data_size) {
    fat32_delete_file(filename, ext); // Puraani file udao agar hai toh!
    
    unsigned char sec_buf[512];
    unsigned int fat_lba = fat_reserved_sectors;
    unsigned int free_cluster = 0;

    ata_read_sector(fat_lba, sec_buf);
    unsigned int* fat_table = (unsigned int*)sec_buf;
    for(int i = 2; i < 128; i++) { 
        if (fat_table[i] == 0x00000000) { free_cluster = i; fat_table[i] = 0x0FFFFFFF; break; }
    }
    if (free_cluster == 0) return;
    ata_write_sector(fat_lba, sec_buf);

    unsigned int root_lba = first_data_sector + ((fat_root_cluster - 2) * fat_sectors_per_cluster);
    ata_read_sector(root_lba, sec_buf);
    
    int entry_offset = -1;
    for (int i = 0; i < 16; i++) {
        int off = i * 32;
        if (sec_buf[off] == 0x00 || sec_buf[off] == 0xE5) { entry_offset = off; break; }
    }
    if (entry_offset == -1) return;

    char target[11]; format_fat_name(filename, ext, target);
    for(int i=0; i<11; i++) sec_buf[entry_offset + i] = target[i];
    
    sec_buf[entry_offset + 11] = 0x20; 
    sec_buf[entry_offset + 20] = (free_cluster >> 16) & 0xFF; 
    sec_buf[entry_offset + 21] = (free_cluster >> 24) & 0xFF;
    sec_buf[entry_offset + 26] = free_cluster & 0xFF;         
    sec_buf[entry_offset + 27] = (free_cluster >> 8) & 0xFF;
    sec_buf[entry_offset + 28] = data_size & 0xFF;
    sec_buf[entry_offset + 29] = (data_size >> 8) & 0xFF;
    sec_buf[entry_offset + 30] = (data_size >> 16) & 0xFF;
    sec_buf[entry_offset + 31] = (data_size >> 24) & 0xFF;

    ata_write_sector(root_lba, sec_buf);

    unsigned int data_lba = first_data_sector + ((free_cluster - 2) * fat_sectors_per_cluster);
    unsigned char data_sec[512] = {0}; 
    for(int i=0; i < data_size && i < 512; i++) data_sec[i] = data[i];
    ata_write_sector(data_lba, data_sec);
}
#endif