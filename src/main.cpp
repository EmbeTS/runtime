#include "../lib/duktape/duktape.h"

#include "bridge/bridge.h"
#include "fs/fs.h"
#include "kernel/kernel.h"

TaskHandle_t LoopTask;

void app_loop(void* parameter) {
  while (true) {
    bridge_process();

    delay(1);
  }
}

void setup() {
  bridge_init();

  fs_init();

  kernel_init();

  xTaskCreatePinnedToCore(app_loop, "LoopTask", 10000, NULL, 1, &LoopTask, 1);

  kernel_boot("/boot/ekrnl.txt");

  /*duk_context *ctx = duk_create_heap_default();
  duk_push_c_function(ctx, native_println, 1);
  duk_put_global_string(ctx, "print");

  duk_push_string(ctx, fs_read("/boot/kernel.js").c_str());
  duk_int_t returnCode = duk_peval(ctx);

  if (returnCode != 0) {
    duk_safe_to_stacktrace(ctx, -1);

    Serial.println(duk_safe_to_string(ctx, -1));
  }

  duk_pop(ctx);*/
}

void loop() {}