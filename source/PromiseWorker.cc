#include "PromiseWorker.h"
//
PromiseWorker::PromiseWorker(Nan::Persistent<v8::Promise::Resolver>* persistent, AddonData* data, double number)
:Nan::AsyncWorker(NULL) {
    (*this).persistent = persistent;
    (*this).data = data;
    (*this).number = number;
    (*this).state = true;
}
PromiseWorker::PromiseWorker(Nan::Persistent<v8::Promise::Resolver>* persistent, AddonData* data, std::exception* error)
:Nan::AsyncWorker(NULL) {
    (*this).persistent = persistent;
    (*this).data = data;
    (*this).error = error;
    (*this).state = false;
}
PromiseWorker::PromiseWorker(Nan::Persistent<v8::Promise::Resolver>* persistent, AddonData* data)
:Nan::AsyncWorker(NULL) {
    (*this).persistent = persistent;
    (*this).data = data;
    (*this).state = false;
}
PromiseWorker::~PromiseWorker() {
    delete (*this).error;
}
void PromiseWorker::Execute() {
    // Провести подсчеты синхронно
    if(!!(*this).state) {
        AddonData* data = (*this).data;
        (*this).result = (*data).count += (*this).number;
    }
}
void PromiseWorker::HandleOKCallback() {
    // Выдать результаты после выполнения функции ::Execute()
    Nan::HandleScope scope;
    auto resolver = Nan::New(*(*this).persistent);
    if(!!(*this).state) {
        //resolver->Resolve(Nan::GetCurrentContext(), Nan::New((*this).result)/*.ToLocalChecked()*/);
        resolver->Resolve(Nan::New<v8::Context>(), Nan::New((*this).result)/*.ToLocalChecked()*/);
    }
    else {
        if((*this).error != 0)
            resolver->Reject(Nan::GetCurrentContext(), Nan::New<v8::String>((*(*this).error).what()).ToLocalChecked());
        else
            resolver->Reject(Nan::New<v8::Context>(), Nan::New<v8::String>("Arguments error").ToLocalChecked());
    }
    //v8::Isolate::GetCurrent()->RunMicrotasks();
}
