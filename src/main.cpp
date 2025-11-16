#include "../lib/duktape/duktape.h"

#include "bridge/bridge.h"

/*duk_ret_t native_println(duk_context *ctx) {
    const char *str = duk_safe_to_string(ctx, 0);
    Serial.println(str);
    return 0; // no return value
}*/

void setup() {
  bridge_init();

  /*duk_context *ctx = duk_create_heap_default();
  duk_push_c_function(ctx, native_println, 1);
  duk_put_global_string(ctx, "print");
  duk_eval_string(ctx, "print('Hello from JS!');");
  Serial.println((int) duk_get_int(ctx, -1));
  duk_destroy_heap(ctx);*/
}

void loop() {
  bridge_process();

  /*if (Serial.available()) {
    // Write into buffer
    size_t len = Serial.readBytesUntil('\n', buffer, sizeof(buffer) - 1);
    buffer[len] = '\0'; // Null-terminate the string
  }

  // Check if buffer contains the packet start pattern
  bool patternFound = false;
  size_t bufferLen = strlen(buffer);
  size_t patternLen = sizeof(pcktStartPattern);

  if (bufferLen >= patternLen) {
    for (size_t i = 0; i <= bufferLen - patternLen; i++) {
      if (memcmp(&buffer[i], pcktStartPattern, patternLen) == 0) {
        patternFound = true;
        // Remove everything before the pattern, including the pattern itself
        memmove(buffer, &buffer[i + patternLen], bufferLen - (i + patternLen) + 1);
        break;
      }
    }
  }

  if (patternFound) {
    // Packet pattern detected
    Serial.println("Packet start pattern found!");
    Serial.print("Buffer after pattern removal: ");
    Serial.println(buffer);
    patternFound = false;
  }*/
}