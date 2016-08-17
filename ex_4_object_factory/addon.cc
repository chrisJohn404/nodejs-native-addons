// addon.cc
/*
It is common practice within Addons to pass JavaScript 
functions to a C++ function and execute them from there. 
The following example illustrates how to invoke such callbacks.

Note that this example uses a two-argument form of Init() 
that receives the full module object as the second argument. 
This allows the Addon to completely overwrite exports with a 
single function instead of adding the function as a property 
of exports.

Note that, in this example, the callback function is invoked 
synchronously.
*/
#include <node.h>

namespace demo {

using v8::Exception;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Null;
using v8::Object;
using v8::String;
using v8::Value;

void CreateObject(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  Local<Object> obj = Object::New(isolate);
  obj->Set(String::NewFromUtf8(isolate, "msg"), args[0]->ToString());

  args.GetReturnValue().Set(obj);
}

void Init(Local<Object> exports, Local<Object> module) {
  NODE_SET_METHOD(module, "exports", CreateObject);
}

NODE_MODULE(addon, Init)

}  // namespace demo