#pragma once
#include "jni/jni.h"

class class_loader {
public:
    explicit class_loader(JNIEnv* jni_env, jobject class_loader);
    ~class_loader();

    jclass find_class(const char* class_name) const;
private:
    JNIEnv* jni_env;
    jobject object;
    jmethodID find_class_method_id;
};
