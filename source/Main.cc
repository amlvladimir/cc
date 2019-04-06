#include <node.h>
#include <exception>
#include "AddonData.h"
#include "PromiseWorker.h"
using namespace v8;
//
struct WrongArgumentsAmount: public std::exception {
	const char* what() const noexcept {
    	return "Wrong amount of arguments";
    }
};
//
static void Method(const v8::FunctionCallbackInfo<v8::Value>& info) {
    AddonData* data = reinterpret_cast<AddonData*>(info.Data().As<External>()->Value());
    auto context = Nan::GetCurrentContext();
    auto resolver = v8::Promise::Resolver::New(context).ToLocalChecked();
    Nan::Persistent<v8::Promise::Resolver> *persistent = new Nan::Persistent<v8::Promise::Resolver>(resolver);
    PromiseWorker* pw;
    //
    if(info.Length() == 1) {
        // TODO: проверить на Number
        v8::Local<v8::Object> obj = info[0].As<v8::Object>();
        Nan::Maybe<double> obj_number = Nan::To<double>(obj);
        double number = (!obj_number.IsNothing())?obj_number.FromJust():0;
        pw = new PromiseWorker(persistent, data, number);
    } else {
        WrongArgumentsAmount* error = new WrongArgumentsAmount();
        pw = new PromiseWorker(persistent, data, error);
    }

    Nan::AsyncQueueWorker(pw);
    info.GetReturnValue().Set(resolver->GetPromise());
}
//
extern "C" NODE_MODULE_EXPORT void
NODE_MODULE_INITIALIZER(
Local<Object> exports,
Local<Value> module,
Local<Context> context) {
    Isolate* isolate = context->GetIsolate();
    AddonData* data = new AddonData(isolate, exports);
    Local<External> external = External::New(isolate, data);
    exports->Set(context,
        String::NewFromUtf8(isolate, "add", NewStringType::kNormal).ToLocalChecked(),
        FunctionTemplate::New(isolate, Method, external)->GetFunction(context).ToLocalChecked()
    ).FromJust();
}
