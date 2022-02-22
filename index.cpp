#include <napi.h>

#include <vector>

struct Obj {
  int member = 5;
};

struct NativeObj : public Napi::ObjectWrap<NativeObj> {
  Obj* data;
  NativeObj(const Napi::CallbackInfo& info) : Napi::ObjectWrap<NativeObj>(info) {
    if (info.Length() != 1) throw Napi::TypeError::New(info.Env(), "requires an argument of external Obj");
    this->data = info[0].As<Napi::External<Obj>>().Data();
  }
  Napi::Value fWithData(const Napi::CallbackInfo& info) {
    return Napi::Number::From(info.Env(), data->member++);
  }
  static Napi::FunctionReference& Constructor() {
    static Napi::FunctionReference Constructor;
    return Constructor;
  }
  static void Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    auto&& t = DefineClass(env, "NativeObj", {
      InstanceMethod<&NativeObj::fWithData>(
        "fWithData",
        static_cast<napi_property_attributes>(napi_writable|napi_configurable)
      ),
    });
    exports["NativeObj"] = t;
    Constructor() = Napi::Persistent(t);
    Constructor().SuppressDestruct();
  }
  static Napi::Object New(const Napi::Env& env, Obj& obj) {
    return Constructor().New({
      Napi::External<Obj>::New(env, &obj)
    });
  }
};

static std::vector<Obj> objs {
  Obj{},
  Obj{},
};

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  //exports["NativeObj"] = NativeObj::Init(env);
  NativeObj::Init(env, exports);
  // should be a member in "Value" class...
  exports["getInfo"] = Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
      return NativeObj::New(info.Env(), objs[0]);
  });

  return exports;
}

NODE_API_MODULE(native_test, Init)

