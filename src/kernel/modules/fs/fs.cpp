#include "../../../../lib/duktape/duktape.h"
#include "../../../fs/fs.h"

duk_ret_t native_kmod_fs_read(duk_context *ctx) {
  const char *path = duk_safe_to_string(ctx, 0);

  String content = fs_read(String(path));

  duk_push_string(ctx, content.c_str());

  return 1;
}

void kmod_fs_init(duk_context *ctx, duk_idx_t parent_idx) {
  duk_idx_t i = duk_push_object(ctx);

  duk_push_c_function(ctx, native_kmod_fs_read, 1);
  duk_put_prop_string(ctx, i, "read");

  duk_put_prop_string(ctx, parent_idx, "fs");
}