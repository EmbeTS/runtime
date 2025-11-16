#include "bridge.h"
#include "packet.h"

#include <Arduino.h>

char bridge_buffer[] = {};

void bridge_init() {
  Serial.begin(115200);
}

void bridge_process() {
  if (!Serial.available())
    return;

  char incoming = Serial.read();
  
  // Append incoming byte to buffer
  size_t len = strlen(bridge_buffer);
  bridge_buffer[len] = incoming;
  bridge_buffer[len + 1] = '\0'; // Null-terminate the string

  // Check for packet start pattern
  size_t bufferLen = strlen(bridge_buffer);
  size_t patternLen = get_packet_start_pattern_length();

  if (bufferLen >= patternLen) {
    bool patternFound = true;
    for (size_t i = 0; i < patternLen; i++) {
      if (bridge_buffer[i] != getPacketStartPattern(i)) {
        patternFound = false;
        break;
      }
    }

    if (patternFound) {
      // Packet pattern detected
      Serial.println("Packet start pattern found!");
      // Clear buffer after detection
      bridge_buffer[0] = '\0';
    } else {
      // Shift buffer left by one to make room for new byte
      memmove(bridge_buffer, bridge_buffer + 1, bufferLen);
      bridge_buffer[bufferLen - 1] = '\0'; // Null-terminate the string
    }
  }
}