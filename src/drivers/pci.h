#ifndef PCI_H
#define PCI_H

#include "../kernel/io.h"
#include "../drivers/display.h"

#define RTL8139_VENDOR_ID 0x10EC
#define RTL8139_DEVICE_ID 0x8139

// Purana 16-bit reader
unsigned int pci_read_word(unsigned short bus, unsigned short slot, unsigned short func, unsigned char offset) {
    unsigned int address;
    unsigned int lbus  = (unsigned int)bus;
    unsigned int lslot = (unsigned int)slot;
    unsigned int lfunc = (unsigned int)func;

    address = (unsigned int)((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xFC) | ((unsigned int)0x80000000));
    outl(0xCF8, address);
    return (inl(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF;
}

// NAYA: 32-bit Data Reader (BAR0 padhne ke liye zaroori hai)
unsigned int pci_read_dword(unsigned short bus, unsigned short slot, unsigned short func, unsigned char offset) {
    unsigned int address = (unsigned int)((bus << 16) | (slot << 11) | (func << 8) | (offset & 0xFC) | 0x80000000);
    outl(0xCF8, address);
    return inl(0xCFC);
}

// Tumhara hardware scanner (As it is)
void scan_pci_bus() {
    print_string("Scanning PCI Hardware Bus...\n");
    print_string("----------------------------------\n");
    int count = 0;
    for(int bus = 0; bus < 256; bus++) {
        for(int slot = 0; slot < 32; slot++) {
            unsigned short vendor = pci_read_word(bus, slot, 0, 0);
            if(vendor != 0xFFFF) { 
                unsigned short device = pci_read_word(bus, slot, 0, 2);
                print_string("[+] Device Found -> Vendor ID: 0x");
                char buf[10]; itoa(vendor, buf); print_string(buf);
                print_string(" | Device ID: 0x");
                itoa(device, buf); print_string(buf);
                print_string("\n");
                count++;
            }
        }
    }
    print_string("----------------------------------\n");
    print_string("Total Hardware Devices Detected: ");
    char c_buf[5]; itoa(count, c_buf); print_string(c_buf);
    print_string("\n");
}

// ==============================================================
// NAYA: RTL8139 MAC ADDRESS EXTRACTOR
// ==============================================================
int pci_get_rtl8139_mac(unsigned char* mac_out) {
    for (int bus = 0; bus < 256; bus++) {
        for (int slot = 0; slot < 32; slot++) {
            unsigned short vendor = pci_read_word(bus, slot, 0, 0);
            if (vendor == RTL8139_VENDOR_ID) {
                unsigned short device = pci_read_word(bus, slot, 0, 2);
                if (device == RTL8139_DEVICE_ID) {
                    
                    // 1. Hardware mil gaya! Ab Offset 0x10 se BAR0 (Base Address) read karo
                    unsigned int bar0 = pci_read_dword(bus, slot, 0, 0x10);
                    
                    // 2. Aakhiri 2 bits (Type flags) ko ignore karke I/O Port Address nikalo
                    unsigned int io_base = bar0 & 0xFFFFFFFC; 
                    
                    // 3. I/O Port se 6 Bytes (MAC Address) nikal lo!
                    for(int i = 0; i < 6; i++) {
                        mac_out[i] = inb(io_base + i);
                    }
                    return 1; // Success
                }
            }
        }
    }
    return 0; // Card nahi mila
}

#endif