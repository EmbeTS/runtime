#include <Arduino.h>

void fs_init();
void fs_wipe();
bool fs_write(String, String);
String fs_read(String);