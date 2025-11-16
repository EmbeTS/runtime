#include <Arduino.h>
#include "../lib/duktape/duktape.h"


duk_ret_t native_println(duk_context *ctx) {
    const char *str = duk_safe_to_string(ctx, 0);
    Serial.println(str);
    return 0; // no return value
}

void setup() {
  Serial.begin(9600);
  
  duk_context *ctx = duk_create_heap_default();
  duk_push_c_function(ctx, native_println, 1 /*nargs*/);
  duk_put_global_string(ctx, "print");
  duk_eval_string(ctx, "print('Hello from JS!');");
  Serial.println((int) duk_get_int(ctx, -1));
  duk_destroy_heap(ctx);
}

void loop() {
}
