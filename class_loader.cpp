#include "class_loader.h"

class_loader::class_loader(JNIEnv* jni_env, jobject object) {
    this->jni_env = jni_env;
    this->object = object;

    jclass class_loader_klass = jni_env->FindClass("java/lang/ClassLoader");
    this->find_class_method_id = jni_env->GetMethodID(class_loader_klass, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");

    jni_env->DeleteLocalRef(class_loader_klass);
}

class_loader::~class_loader() {
    this->jni_env->DeleteLocalRef(object);
}

jclass class_loader::find_class(const char* class_name) const {
    jstring class_name_jstring = jni_env->NewStringUTF(class_name);

    jclass klass = reinterpret_cast<jclass>(jni_env->CallObjectMethod(this->object, find_class_method_id, class_name_jstring));
    jni_env->DeleteLocalRef(class_name_jstring);

    return klass;
}
