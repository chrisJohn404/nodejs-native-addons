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

void RunCallback(const FunctionCallbackInfo<Value>& args) {
  // Not sure...
  Isolate* isolate = args.GetIsolate();

  // Create a local definition of the callback function
  Local<Function> cb = Local<Function>::Cast(args[0]);

  // Create a JavaScript something...
  const unsigned argc = 1;
  Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "hello world") };

  // Execute the callback function.
  cb->Call(Null(isolate), argc, argv);
}

// This is the implementation of the "add" method where you
// get the result with a callback function.
void Add(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  // Check the number of arguments passed.
  if (args.Length() != 3) {
    // Throw an Error that is passed back to JavaScript
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  // Check the argument types
  // IsFunction Reference: http://bespin.cz/~ondras/html/classv8_1_1Value.html
  if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsFunction()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  }

  // Create a local definition of the callback function
  Local<Function> cb = Local<Function>::Cast(args[2]);

  // Parse the input arguments.
  double valueA = args[0]->NumberValue();
  double valueB = args[1]->NumberValue();

  // Perform the operation
  double value = valueA + valueB;

  
  Local<Number> num = Number::New(isolate, value);

  // Create a Javascript "number" object that can be returned as
  // the first argument of the callback function.
  const unsigned argc = 1;
  Local<Value> argv[argc] = { Number::New(isolate, value) };

  // Execute the callback function.
  cb->Call(Null(isolate), argc, argv);
}

void Init(Local<Object> exports, Local<Object> module) {
  // For some reason you can't have both of these enabled.
  // NODE_SET_METHOD(module, "exports", RunCallback);
  NODE_SET_METHOD(exports, "add", Add);
}

NODE_MODULE(addon, Init)

}  // namespace demo