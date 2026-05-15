#ifndef CMOS_H
#define CMOS_H

#include "io.h"

// CMOS Ports
#define CMOS_ADDRESS 0x70
#define CMOS_DATA    0x71

// Motherboard time "BCD" format mein deta hai, usko normal number mein badalna
unsigned char bcd_to_bin(unsigned char bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

// CMOS ke specific register se time read karna
unsigned char get_rtc_register(int reg) {
    outb(CMOS_ADDRESS, reg);
    return inb(CMOS_DATA);
}

// Time fetch karne ka main function
void get_time(int* hours, int* minutes, int* seconds) {
    // 0x04 = Hours, 0x02 = Minutes, 0x00 = Seconds
    *hours = bcd_to_bin(get_rtc_register(0x04));
    *minutes = bcd_to_bin(get_rtc_register(0x02));
    *seconds = bcd_to_bin(get_rtc_register(0x00));
}
// CMOS se current Date read karna (Day, Month, Year)
void get_date(int* day, int* month, int* year) {
    // 0x07 = Day, 0x08 = Month, 0x09 = Year
    *day = bcd_to_bin(get_rtc_register(0x07));
    *month = bcd_to_bin(get_rtc_register(0x08));
    *year = bcd_to_bin(get_rtc_register(0x09));
}

#endif