#include <LittleFS.h>

void fs_create_structure() {
  const String dirs[] = {
      "/boot",
      "/data",
      "/tmp"};
  
  for (const String &dir : dirs) {
    if (!LittleFS.exists(dir)) {
      LittleFS.mkdir(dir);
    }
  }
}

void fs_init() {
  if (!LittleFS.begin((true)))
    return;

  fs_create_structure();
}

void fs_wipe() {
  LittleFS.format();
}

bool fs_write(String path, String content) {
  File file = LittleFS.open(path, "w");

  delay(100);

  if (!file || !file.print(content))
    return false;

  file.close();

  return true;
}

String fs_read(String path) {
  if (!LittleFS.exists(path))
    return "";

  File file = LittleFS.open(path, "r");
  String content = "";

  while (file.available()) {
    content += (char)file.read();
  }

  file.close();

  return content;
}