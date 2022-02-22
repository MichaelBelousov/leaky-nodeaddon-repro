#include <napi.h>

struct NativeObj : public Napi::ObjectWrap<NativeObj> {
  NativeObj(const Napi::CallbackInfo& info) : Napi::ObjectWrap<NativeObj>(info) {}
  static void Init(Napi::Env env, Napi::Object exports) {
    Napi::Function wrappedCtor = DefineClass(env, "NativeObj", {
        StaticMethod<&NativeObj::Create>("create", static_cast<napi_property_attributes>(napi_writable|napi_configurable)),
    });
    exports["NativeObj"] = wrappedCtor;
    Napi::FunctionReference* constructorRef = new Napi::FunctionReference();
    *constructorRef = Napi::Persistent(wrappedCtor);
    env.SetInstanceData<Napi::FunctionReference>(constructorRef);
  }
  static Napi::Value Create(const Napi::CallbackInfo& info) {
    auto&& constructorRef = info.Env().GetInstanceData<Napi::FunctionReference>();
    return constructorRef->New({});
  }
};

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  NativeObj::Init(env, exports);
  return exports;
}

NODE_API_MODULE(native_test, Init)

