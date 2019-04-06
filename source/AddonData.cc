#include "AddonData.h"
//
AddonData::AddonData(v8::Isolate* isolate, v8::Local<v8::Object> exports)
:count(0) {
    (*this).exports.Reset(isolate, exports);
    (*this).exports.SetWeak(this, DeleteMe, v8::WeakCallbackType::kParameter);
}
AddonData::~AddonData() {
    if(!(*this).exports.IsEmpty()) {
        (*this).exports.ClearWeak();
        (*this).exports.Reset();
    }
}
void AddonData::DeleteMe(const v8::WeakCallbackInfo<AddonData>& info) {
    delete info.GetParameter();
}
