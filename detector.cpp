#include "detector.h"
#include "utils.h"
#include "jni/jvmti.h"
#include "class_loader.h"

#include <vector>
#include <algorithm>
#include <ranges>


std::vector<jobject> get_class_loaders(jvmtiEnv* jvmti_env) {
    std::vector<jobject> class_loaders;
    jthread* threads;
    jint thread_count;

    jvmti_env->GetAllThreads(&thread_count, &threads);

    for(int i = 0; i < thread_count; ++i) {
        jthread thread = threads[i];
        jvmtiThreadInfo thread_info;

        jvmti_env->GetThreadInfo(thread, &thread_info);
        if(!thread_info.context_class_loader) {
            continue;
        }

        class_loaders.push_back(thread_info.context_class_loader);
    }

    return class_loaders;
}

bool check_for_vape_v4(JNIEnv* jni_env, jvmtiEnv* jvmti_env) {
    const std::vector<jobject> class_loaders = get_class_loaders(jvmti_env);

    return std::ranges::any_of(class_loaders.begin(), class_loaders.end(), [jni_env](jobject cl_object) {
        const auto cl = class_loader(jni_env, cl_object);
        jclass klass = cl.find_class("a.A");
        jni_env->DeleteLocalRef(klass);

        return klass;
    });
}

void detector::main(HMODULE hmodule) {
    JavaVM* java_vm = utils::get_jvm_instance();

    if(!java_vm) {
        MessageBoxA(nullptr, "could not find jvm handle", "vape v4 detector", MB_SYSTEMMODAL | MB_ICONERROR);
        FreeLibraryAndExitThread(hmodule, 1);
    }

    JNIEnv* jni_env;
    jvmtiEnv* jvmti_env;

    java_vm->AttachCurrentThread(reinterpret_cast<void**>(&jni_env), nullptr);
    java_vm->GetEnv(reinterpret_cast<void**>(&jni_env), JNI_VERSION_1_8);
    java_vm->GetEnv(reinterpret_cast<void**>(&jvmti_env), JVMTI_VERSION_1_2);

    MessageBoxA(nullptr, "checking for vape v4", "vape v4 detector", MB_ICONINFORMATION | MB_SYSTEMMODAL);

    if(check_for_vape_v4(jni_env, jvmti_env)) {
        MessageBoxA(nullptr, "using vape v4", "vape v4 detector", MB_ICONWARNING | MB_SYSTEMMODAL);
    }

    java_vm->DetachCurrentThread();
    FreeLibraryAndExitThread(hmodule, 0);
}
