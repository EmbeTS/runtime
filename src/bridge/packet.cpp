#include <Arduino.h> 

#include "packet.h"

const char packetStartPattern[] = {0x21, 0x21, 0x21, 0x1a, 0x1d, 0xff};

size_t get_packet_start_pattern_length() {
  return sizeof(packetStartPattern);
}

char getPacketStartPattern(size_t index) {
  if (index >= sizeof(packetStartPattern))
    return -1;
    
  return packetStartPattern[index];
}