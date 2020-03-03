//
// Created by Affy Zhang on 2020/3/2.
//


#include <jni.h>
#include <base.h>

#define JAVA_CLASS "com/affy/nativetest/JniDynamicLoad"

jstring getNativeString(JNIEnv *env, jobject jobj) {
    return env->NewStringUTF("this is jni test");
}

jint sum(JNIEnv *env, jobject jobj, int x, int y) {
    return x + y;
}

static JNINativeMethod gMethods[] = {
        {"getNativeString", "()Ljava/lang/String;", (void *) getNativeString},
        {"sum",             "(II)I",               (void *) sum}
};

int registerNativeMethods(JNIEnv *env, const char *name, const JNINativeMethod *methods,
                          jint nMethods) {
    jclass jcls;
    jcls = env->FindClass(name);
    if (jcls == nullptr) {
        return JNI_FALSE;
    }
    if (env->RegisterNatives(jcls, methods, nMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_FALSE;
    }
    registerNativeMethods(env, JAVA_CLASS, gMethods, sizeof(gMethods)/ sizeof(gMethods[0]));
    LOGD("jni onload call");
    return JNI_VERSION_1_6;
}

