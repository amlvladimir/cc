#ifndef PromiseWorker_H
#define PromiseWorker_H
#include <nan.h>
#include <exception>
#include "AddonData.h"
//
class PromiseWorker: public Nan::AsyncWorker {
public:
    //PromiseWorker(Nan::Persistent<v8::Promise::Resolver> *persistent, AddonData* data, v8::Local<v8::Object> &whatObj);
    PromiseWorker(Nan::Persistent<v8::Promise::Resolver> *persistent, AddonData* data, double number);
    PromiseWorker(Nan::Persistent<v8::Promise::Resolver> *persistent, AddonData* data, std::exception* error);
    PromiseWorker(Nan::Persistent<v8::Promise::Resolver> *persistent, AddonData* data);
    ~PromiseWorker();
    virtual void Execute();
    virtual void HandleOKCallback();
private:
    AddonData* data = 0;
    std::exception* error = 0;
    Nan::Persistent<v8::Promise::Resolver>* persistent = 0;
    double number = 0;
    double result = 0;
    bool state = false;
};
#endif  // PromiseWorker_H
