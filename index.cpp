#include <napi.h>

#include <vector>
#include <iostream>

struct NativeObj : public Napi::ObjectWrap<NativeObj> {
  NativeObj(const Napi::CallbackInfo& info) : Napi::ObjectWrap<NativeObj>(info) {}
  static Napi::FunctionReference& Constructor() {
    static Napi::FunctionReference Constructor;
    return Constructor;
  }
  static void Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    auto&& t = DefineClass(env, "NativeObj", {});
    exports["NativeObj"] = t;
    Constructor() = Napi::Persistent(t);
    Constructor().SuppressDestruct();
  }
  static Napi::Object New(const Napi::Env& env) {
    return Constructor().New({});
  }
};

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  NativeObj::Init(env, exports);
  exports["getInfo"] = Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
      return NativeObj::New(info.Env());
  });

  return exports;
}

NODE_API_MODULE(native_test, Init)

