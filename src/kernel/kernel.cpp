#include "kernel.h"

#include <Arduino.h>
#include "../fs/fs.h"
#include "../../lib/duktape/duktape.h"

#include "modules/fs/fs.h"

duk_context *kernel_ctx;

duk_ret_t native_println(duk_context *ctx) {
  const char *str = duk_safe_to_string(ctx, 0);

  Serial.println(str);

  return 0; // no return value
}

void kmod_init() {

  duk_push_c_function(kernel_ctx, native_println, 1);
  duk_put_global_string(kernel_ctx, "print");

  duk_idx_t idx = duk_push_object(kernel_ctx);

  kmod_fs_init(kernel_ctx, idx);

  duk_put_global_string(kernel_ctx, "___$kmod");
} 

void kernel_init() {
  kernel_ctx = duk_create_heap_default();

  kmod_init();
}

void kernel_boot(const char *path) {
  String kpath = fs_read(path);

  duk_push_string(kernel_ctx, fs_read(kpath).c_str());
  duk_int_t returnCode = duk_peval(kernel_ctx);

  if (returnCode != 0) {
    duk_safe_to_stacktrace(kernel_ctx, -1);

    Serial.println(duk_safe_to_string(kernel_ctx, -1));
  }

  duk_pop(kernel_ctx);
}