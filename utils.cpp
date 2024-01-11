#include "utils.h"
#include <Windows.h>

typedef long(__stdcall* _JNI_GetCreatedJavaVMs)(JavaVM**, long, long*);

JavaVM* utils::get_jvm_instance()
{
    JavaVM* jvm;

    HMODULE jvm_handle = GetModuleHandleA("jvm.dll");
    _JNI_GetCreatedJavaVMs JNI_GetCreatedJavaVMs = reinterpret_cast<_JNI_GetCreatedJavaVMs>(GetProcAddress(jvm_handle, "JNI_GetCreatedJavaVMs"));
    JNI_GetCreatedJavaVMs(&jvm, 1, nullptr);

    return jvm;
}