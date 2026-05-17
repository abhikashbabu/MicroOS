#ifndef PCI_H
#define PCI_H

#include "io.h"
#include "display.h"

unsigned int pci_read_word(unsigned short bus, unsigned short slot, unsigned short func, unsigned char offset) {
    unsigned int address;
    unsigned int lbus  = (unsigned int)bus;
    unsigned int lslot = (unsigned int)slot;
    unsigned int lfunc = (unsigned int)func;

    address = (unsigned int)((lbus << 16) | (lslot << 11) |
              (lfunc << 8) | (offset & 0xFC) | ((unsigned int)0x80000000));
    outl(0xCF8, address);
    return (inl(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF;
}

void scan_pci_bus() {
    print_string("Scanning PCI Hardware Bus...\n");
    print_string("----------------------------------\n");
    
    int count = 0;
    for(int bus = 0; bus < 256; bus++) {
        for(int slot = 0; slot < 32; slot++) {
            unsigned short vendor = pci_read_word(bus, slot, 0, 0);
            if(vendor != 0xFFFF) { // 0xFFFF ka matlab slot khali hai
                unsigned short device = pci_read_word(bus, slot, 0, 2);
                
                print_string("[+] Device Found -> Vendor ID: 0x");
                // Simple hex display trick using custom routine logic
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

#endif