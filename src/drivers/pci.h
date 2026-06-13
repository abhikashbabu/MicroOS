#ifndef PCI_H
#define PCI_H

#include "../kernel/io.h"
#include "../drivers/display.h"

#define RTL8139_VENDOR_ID 0x10EC
#define RTL8139_DEVICE_ID 0x8139

__attribute__((weak)) unsigned int rtl_io_base = 0;
__attribute__((weak)) unsigned char rtl_mac[6];

static unsigned int pci_read_word(unsigned short bus, unsigned short slot, unsigned short func, unsigned char offset) {
    unsigned int address = (unsigned int)((bus << 16) | (slot << 11) | (func << 8) | (offset & 0xFC) | 0x80000000);
    outl(0xCF8, address);
    return (inl(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF;
}

static unsigned int pci_read_dword(unsigned short bus, unsigned short slot, unsigned short func, unsigned char offset) {
    unsigned int address = (unsigned int)((bus << 16) | (slot << 11) | (func << 8) | (offset & 0xFC) | 0x80000000);
    outl(0xCF8, address);
    return inl(0xCFC);
}

// NAYA MAGIC: PCI Command bhejne ke liye Write Function
static void pci_write_dword(unsigned short bus, unsigned short slot, unsigned short func, unsigned char offset, unsigned int data) {
    unsigned int address = (unsigned int)((bus << 16) | (slot << 11) | (func << 8) | (offset & 0xFC) | 0x80000000);
    outl(0xCF8, address);
    outl(0xCFC, data);
}

static void scan_pci_bus() {
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

static int pci_get_rtl8139_mac() {
    for (int bus = 0; bus < 256; bus++) {
        for (int slot = 0; slot < 32; slot++) {
            unsigned short vendor = pci_read_word(bus, slot, 0, 0);
            if (vendor == RTL8139_VENDOR_ID) {
                unsigned short device = pci_read_word(bus, slot, 0, 2);
                if (device == RTL8139_DEVICE_ID) {
                    
                    // ========================================================
                    // 1. DMA HANDBRAKE RELEASE (ENABLE PCI BUS MASTERING)
                    // ========================================================
                    unsigned int pci_cmd = pci_read_dword(bus, slot, 0, 0x04);
                    pci_cmd |= 0x0004; // Bit 2 ON karte hi Handbrake khul gaya!
                    pci_write_dword(bus, slot, 0, 0x04, pci_cmd);

                    // 2. Base Address Read karo
                    unsigned int bar0 = pci_read_dword(bus, slot, 0, 0x10);
                    rtl_io_base = bar0 & 0xFFFFFFFC; 
                    
                    // 3. MAC Address nikalo
                    for(int i = 0; i < 6; i++) {
                        rtl_mac[i] = inb(rtl_io_base + i);
                    }
                    return 1; 
                }
            }
        }
    }
    return 0; 
}

#endif