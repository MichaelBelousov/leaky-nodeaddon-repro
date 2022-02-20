#include <napi.h>

#include <string>
#include <exception>

struct NativeObj : public Napi::ObjectWrap<NativeObj> {
  void* data;
  NativeObj(const Napi::CallbackInfo& info) : Napi::ObjectWrap<NativeObj>(info) {
    this->data = Napi::External<void>::New(info.Env(), this->data);
  }
  void fWithData(const Napi::CallbackInfo& info) {
  }
  static Napi::Object Init(Napi::Env env) {
    return DefineClass(env, "NativeObj", {
      InstanceMethod<&NativeObj::fWithData>(
        "fWithData",
        static_cast<napi_property_attributes>(napi_writable|napi_configurable)
      ),
    });
  }
};

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports["NativeObj"] = NativeObj::Init(env);

  return exports;
}

NODE_API_MODULE(native_test, Init)
