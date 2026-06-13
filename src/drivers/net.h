// ==============================================================
// DAY 172: THE MICRO OS NETWORK STACK (ARP & ICMP PING)
// ==============================================================
#ifndef NET_H
#define NET_H

#include "rtl8139.h"
#include "../drivers/display.h"

unsigned char my_ip[4] = {10, 0, 2, 15};      
unsigned char router_ip[4] = {10, 0, 2, 2};   
unsigned char router_mac[6] = {0}; 
int network_ready = 0;             

void net_send_arp_request() {
    unsigned char packet[64] = {0}; 
    
    for(int i = 0; i < 6; i++) packet[i] = 0xFF;
    for(int i = 0; i < 6; i++) packet[6 + i] = rtl_mac[i];
    packet[12] = 0x08; packet[13] = 0x06;

    packet[14] = 0x00; packet[15] = 0x01;
    packet[16] = 0x08; packet[17] = 0x00;
    packet[18] = 0x06; packet[19] = 0x04;
    packet[20] = 0x00; packet[21] = 0x01;

    for(int i = 0; i < 6; i++) packet[22 + i] = rtl_mac[i];
    for(int i = 0; i < 4; i++) packet[28 + i] = my_ip[i];
    for(int i = 0; i < 6; i++) packet[32 + i] = 0x00;
    for(int i = 0; i < 4; i++) packet[38 + i] = router_ip[i];

    rtl8139_send_packet(packet, 64);
    hd_print("[NET] ARP Request sent to 10.0.2.2!");
    hd_print("[NET] Waiting for Router's reply...");
}

// NAYA MAGIC: Google (8.8.8.8) ko PING karne ka Function
void net_ping_google() {
    if (!network_ready) return;

    unsigned char packet[74] = {0}; 
    unsigned char target_ip[4] = {8, 8, 8, 8}; // Google Public DNS

    // 1. ETHERNET HEADER (Destination MAC humesha Local Router hota hai)
    for(int i=0; i<6; i++) packet[i] = router_mac[i];
    for(int i=0; i<6; i++) packet[6+i] = rtl_mac[i];
    packet[12] = 0x08; packet[13] = 0x00; // IPv4 Protocol

    // 2. IPv4 HEADER (20 bytes)
    packet[14] = 0x45; // Version 4
    packet[15] = 0x00; 
    packet[16] = 0x00; packet[17] = 0x3C; // Total Length (60 bytes)
    packet[18] = 0xAB; packet[19] = 0xCD; // ID
    packet[20] = 0x40; packet[21] = 0x00; // Flags (Don't fragment)
    packet[22] = 0x40; // TTL (64)
    packet[23] = 0x01; // Protocol (1 = ICMP Ping)
    
    packet[24] = 0x00; packet[25] = 0x00; // Header Checksum init
    for(int i=0; i<4; i++) packet[26+i] = my_ip[i];
    for(int i=0; i<4; i++) packet[30+i] = target_ip[i];

    // IP Checksum Calculation
    unsigned int ip_sum = 0;
    for(int i=14; i<34; i+=2) ip_sum += (packet[i] << 8) | packet[i+1];
    while(ip_sum >> 16) ip_sum = (ip_sum & 0xFFFF) + (ip_sum >> 16);
    unsigned short ip_chk = ~ip_sum;
    packet[24] = (ip_chk >> 8) & 0xFF;
    packet[25] = ip_chk & 0xFF;

    // 3. ICMP HEADER (Type 8 = Echo Request)
    packet[34] = 0x08; // Type
    packet[35] = 0x00; // Code
    packet[36] = 0x00; packet[37] = 0x00; // ICMP Checksum init
    packet[38] = 0x00; packet[39] = 0x01; // ID
    packet[40] = 0x00; packet[41] = 0x01; // Sequence
    
    char* msg = "MICRO OS PINGS YOU"; // 18 bytes Payload
    for(int i=0; i<18; i++) packet[42+i] = msg[i];

    // ICMP Checksum Calculation
    unsigned int icmp_sum = 0;
    for(int i=34; i<60; i+=2) icmp_sum += (packet[i] << 8) | packet[i+1];
    while(icmp_sum >> 16) icmp_sum = (icmp_sum & 0xFFFF) + (icmp_sum >> 16);
    unsigned short icmp_chk = ~icmp_sum;
    packet[36] = (icmp_chk >> 8) & 0xFF;
    packet[37] = icmp_chk & 0xFF;

    rtl8139_send_packet(packet, 60);
    hd_print("[NET] Pinging 8.8.8.8 (Google DNS) with 18 bytes...");
}

void net_poll_rx() {
    unsigned char packet[1500];
    int length;
    
    if (rtl8139_receive_packet(packet, &length)) {
        
        // ARP Reply Parser
        if (packet[12] == 0x08 && packet[13] == 0x06) {
            if (packet[20] == 0x00 && packet[21] == 0x02) {
                for(int i = 0; i < 6; i++) router_mac[i] = packet[22 + i];
                network_ready = 1; 
                hd_print("[NET] ARP Reply Received! Network Ready.");
            }
        }
        // NAYA MAGIC: ICMP (Ping) Reply Parser
        else if (packet[12] == 0x08 && packet[13] == 0x00) { // IPv4 Packet
            if (packet[23] == 0x01) { // Protocol is ICMP
                if (packet[34] == 0x00) { // Type 0 = Echo Reply!
                    hd_print("Reply from 8.8.8.8: time < 1ms TTL=64");
                }
            }
        }
    }
}
#endif