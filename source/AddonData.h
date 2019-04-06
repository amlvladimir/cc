#ifndef AddonData_H
#define AddonData_H
#include <nan.h>
//
class AddonData {
public:
    double count;
    AddonData(v8::Isolate* isolate, v8::Local<v8::Object> exports);
    ~AddonData();
private:
    v8::Persistent<v8::Object> exports;
    static void DeleteMe(const v8::WeakCallbackInfo<AddonData>& info);
};
#endif  // AddonData_H
