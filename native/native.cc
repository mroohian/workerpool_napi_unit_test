#include <assert.h>
#include <node_api.h>

napi_value normalMethod(napi_env env, napi_callback_info info) {
  napi_status status;

  napi_value world;
  status = napi_create_string_utf8(env, "world", 5, &world);
  assert(status == napi_ok);

  return world;
}

napi_value crashMethod(napi_env env, napi_callback_info info) {
  asm("ud2");

  return nullptr;
}

#define DECLARE_NAPI_METHOD(name, func)                                        \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;

  napi_property_descriptor normalMethodDesc = DECLARE_NAPI_METHOD("normalMethod", normalMethod);
  status = napi_define_properties(env, exports, 1, &normalMethodDesc);
  assert(status == napi_ok);

  napi_property_descriptor crashMethodDesc = DECLARE_NAPI_METHOD("crashMethod", crashMethod);
  status = napi_define_properties(env, exports, 1, &crashMethodDesc);
  assert(status == napi_ok);

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)