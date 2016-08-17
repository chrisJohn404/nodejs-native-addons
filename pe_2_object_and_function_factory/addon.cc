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
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Null;
using v8::Object;
using v8::String;
using v8::Value;

void MyFunction(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "You executed 'myFunction'!!"));
}
void MyFunctionCB(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() != 1) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }
    // Check the argument types
    // IsFunction Reference: http://bespin.cz/~ondras/html/classv8_1_1Value.html
    if (!args[0]->IsFunction()) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    // Create a local definition of the callback function
    Local<Function> cb = Local<Function>::Cast(args[0]);
    
    // Define a string to be returned
    Local<String> str = String::NewFromUtf8(isolate, "You executed 'MyFunctionCB'!!");

    // Define the return arguments.
    const unsigned argc = 1;
    Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "You executed 'MyFunctionCB'!!") };

    // Execute the callback function
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

void CreateFunction(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, MyFunction);
    Local<Function> fn = tpl->GetFunction();

    // omit this to make it anonymous
    fn->SetName(String::NewFromUtf8(isolate, "theFunction"));

    args.GetReturnValue().Set(fn);
}


void CreateObject(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // Create a JavaScript object.
    Local<Object> obj = Object::New(isolate);

    // 1. Define a function, 2. give it a name, and 3. save it to the object.
    Local<FunctionTemplate> myFuncTPL = FunctionTemplate::New(isolate, MyFunction);
    Local<Function> myFunc = myFuncTPL->GetFunction();
    myFunc->SetName(String::NewFromUtf8(isolate, "myFunction"));
    obj->Set(String::NewFromUtf8(isolate, "myFunction"), myFunc);

    // Define a second function.
    Local<FunctionTemplate> myFuncCBTPL = FunctionTemplate::New(isolate, MyFunctionCB);
    Local<Function> myFuncCB = myFuncCBTPL->GetFunction();
    myFuncCB->SetName(String::NewFromUtf8(isolate, "myFunctionCB"));
    obj->Set(String::NewFromUtf8(isolate, "myFunctionCB"), myFuncCB);

    // Define the "add" function.
    Local<FunctionTemplate> addTPL = FunctionTemplate::New(isolate, Add);
    Local<Function> add = addTPL->GetFunction();
    add->SetName(String::NewFromUtf8(isolate, "add"));
    obj->Set(String::NewFromUtf8(isolate, "add"), add);


    args.GetReturnValue().Set(obj);
}

void Init(Local<Object> exports, Local<Object> module) {
    NODE_SET_METHOD(module, "exports", CreateObject);
}


NODE_MODULE(addon, Init)

}  // namespace demo