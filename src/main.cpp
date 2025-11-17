#include "../lib/duktape/duktape.h"

#include "bridge/bridge.h"
#include "fs/fs.h"

TaskHandle_t LoopTask;

duk_ret_t native_println(duk_context *ctx) {
    const char *str = duk_safe_to_string(ctx, 0);
    Serial.println(str);
    return 0; // no return value
}

void app_loop(void* parameter) {
  while (true) {
    bridge_process();

    delay(1);
  }
}

void setup() {
  bridge_init();

  fs_init();

  //Serial.println(fs_read("/boot/index.js"));

  xTaskCreatePinnedToCore(app_loop, "LoopTask", 10000, NULL, 1, &LoopTask, 1);

  duk_context *ctx = duk_create_heap_default();
  duk_push_c_function(ctx, native_println, 1);
  duk_put_global_string(ctx, "print");

  duk_push_string(ctx, fs_read("/boot/index.js").c_str());
  duk_int_t returnCode = duk_peval(ctx);

  if (returnCode != 0) {
    duk_safe_to_stacktrace(ctx, -1);

    Serial.println(duk_safe_to_string(ctx, -1));
  }

  duk_pop(ctx);
  //duk_destroy_heap(ctx);
}

void loop() {}