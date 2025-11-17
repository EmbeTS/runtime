#include "bridge.h"
#include "packet.h"

#include <Arduino.h>

uint8_t bridge_init_seq[6] = {0x23, 0x23, 0x23, 0x1a, 0x1d, 0xff};

String bridge_buffer = "";

void bridge_wseq(uint8_t *seq, size_t size) {
  Serial.write(seq, size / sizeof(uint8_t));
}

void bridge_init() {
  Serial.begin(115200);

  delay(1);

  bridge_wseq(bridge_init_seq, sizeof(bridge_init_seq));
}

void bridge_process() {
  if (!Serial.available())
    return;

  bridge_buffer += (char)Serial.read();

  if (is_pckt(bridge_buffer)) {
    pckt_process(get_pckt(bridge_buffer));

    bridge_buffer = rem_pckt(bridge_buffer);
  }
}