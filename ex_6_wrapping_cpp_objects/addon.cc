// addon.cc
/*
It is also possible to wrap C++ objects/classes in 
a way that allows new instances to be created using 
the JavaScript new operator.
*/
#include <node.h>
#include "myobject.h"

namespace demo {

using v8::Exception;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Null;
using v8::Object;
using v8::String;
using v8::Value;

void InitAll(Local<Object> exports) {
  MyObject::Init(exports);
}

NODE_MODULE(addon, InitAll)

}  // namespace demo

