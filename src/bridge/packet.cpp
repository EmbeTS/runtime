#include <Arduino.h> 

#include "packet.h"
#include "../os/os.h"

String pckt_start_seq = "\x21\x21\x21\x1a\x1d\xff";
String pckt_end_seq = "\xff\x1d\x1a\x22\x22\x22";

bool is_pckt(String buffer) {
  return buffer.indexOf(pckt_start_seq) != -1 
      && buffer.indexOf(pckt_end_seq) != -1;
}

String get_pckt(String buffer) {
  int start_idx = buffer.indexOf(pckt_start_seq);
  int end_idx = buffer.indexOf(pckt_end_seq);
    
  if (start_idx == -1 || end_idx == -1) {
    return "";
  }
    
  int content_start = start_idx + pckt_start_seq.length();
  return buffer.substring(content_start, end_idx);
}

String rem_pckt(String buffer) {
  int end_idx = buffer.indexOf(pckt_end_seq);
    
  if (end_idx == -1) {
    return buffer;
  }
    
  int content_end = end_idx + pckt_end_seq.length();
  return buffer.substring(content_end);
}

void pckt_process(String data) {
  switch (data[0]) {
    case '\x32':
      os_restart();
      break;
    }
}