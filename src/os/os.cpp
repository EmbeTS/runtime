#include <Arduino.h>

#include "os.h"

void os_restart() {
  ESP.restart();
}