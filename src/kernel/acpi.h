#ifndef ACPI_H
#define ACPI_H

#include "../drivers/display.h"

int battery_percentage = 100; // OS wide battery state

// ACPI (Advanced Configuration and Power Interface) Initialization
void init_acpi() {
    // BIOS memory space (0x000E0000 se 0x000FFFFF) scan karna
    unsigned char* mem = (unsigned char*) 0x000E0000;
    int rsdp_found = 0;
    
    // Asli OS hardware mein "RSD PTR " signature dhundhta hai
    while ((unsigned int)mem < 0x000FFFFF) {
        if (mem[0] == 'R' && mem[1] == 'S' && mem[2] == 'D' && mem[3] == ' ' &&
            mem[4] == 'P' && mem[5] == 'T' && mem[6] == 'R' && mem[7] == ' ') {
            rsdp_found = 1;
            break;
        }
        mem += 16;
    }

    if (rsdp_found) {
        battery_percentage = 95; // ACPI mil gaya, fetching initial power state
    }
}

// OS Uptime ke hisaab se battery drain calculate karna
void process_power_drain(int uptime_sec) {
    // Demo ke liye: Har 10 second mein 1% battery kam hogi
    if (uptime_sec > 0 && uptime_sec % 10 == 0) {
        if (battery_percentage > 2) {
            battery_percentage--;
        }
    }
}

#endif