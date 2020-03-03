#include <jni.h>
#include <string>
#include "test/People.h"
#include <base.h>
#include <pthread.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_affy_nativetest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    People people;
    return env->NewStringUTF(people.getString().c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_affy_nativetest_MainActivity_callNativeStr(JNIEnv *env, jobject thiz, jstring str) {
    //convert java style string to c style string
    const char *jnistr = env->GetStringUTFChars(str, 0);
    LOGD("this is java style string %s", jnistr);
    //release alloc memory space
    env->ReleaseStringUTFChars(str, jnistr);
    return env->NewStringUTF("return c style string");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_affy_nativetest_MainActivity_stringMethod(JNIEnv *env, jobject thiz, jstring str) {
    const char *jnistr = env->GetStringUTFChars(str, 0);
    int length = env->GetStringLength(str);
    LOGD("java string length %d", length);

    char buffer[128];
    env->GetStringUTFRegion(str, 0, length - 1, buffer);
    LOGD("get java string region %s", buffer);
    env->ReleaseStringUTFChars(str, jnistr);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_affy_nativetest_MainActivity_callNativeStrArray(JNIEnv *env, jobject thiz,
                                                         jobjectArray str_array) {
    int length = env->GetArrayLength(str_array);
    LOGD("str_array len %d", length);
    jstring element = static_cast<jstring>(env->GetObjectArrayElement(str_array, 0));
    const char *firstChar = env->GetStringUTFChars(element, 0);
    LOGD("the first string is %s", firstChar);
    env->ReleaseStringUTFChars(element, firstChar);
//    return env->NewStringUTF(chars);
    return element;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_affy_nativetest_MainActivity_accessInstanceField(JNIEnv *env, jobject thiz) {
    jclass clz = env->GetObjectClass(thiz);
    jfieldID fieldId = env->GetFieldID(clz, "name", "Ljava/lang/String;");
    env->SetObjectField(thiz, fieldId, env->NewStringUTF("shit"));
}

extern "C"
JNIEXPORT void JNICALL
Java_com_affy_nativetest_MainActivity_accessStaticField(JNIEnv *env, jobject thiz) {
    jclass clz = env->GetObjectClass(thiz);
    jfieldID fieldId = env->GetStaticFieldID(clz, "num", "I");
    int num = env->GetStaticIntField(clz, fieldId);
    env->SetStaticIntField(clz, fieldId, ++num);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_affy_nativetest_MainActivity_accessInstanceMethod(JNIEnv *env, jobject thiz) {
    jclass clazz = env->GetObjectClass(thiz);
    jmethodID methodId = env->GetMethodID(clazz, "callInstanceMethod", "(I)V");
    env->CallVoidMethod(thiz, methodId, 2);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_affy_nativetest_MainActivity_accessStaticMethod(JNIEnv *env, jobject thiz) {
    jclass clazz = env->GetObjectClass(thiz);
    jmethodID methodId = env->GetStaticMethodID(clazz, "callStaticMethod",
                                                "(Ljava/lang/String;I)V");
    env->CallStaticVoidMethod(clazz, methodId, env->NewStringUTF("jni string"), 2);

    jmethodID mid = env->GetStaticMethodID(clazz, "callStaticMethod", "([Ljava/lang/String;)V");
    jobjectArray strArray = env->NewObjectArray(2, env->FindClass("java/lang/String"), nullptr);
    for (int i = 0; i < 2; ++i) {
        env->SetObjectArrayElement(strArray, i, env->NewStringUTF("string in native "));
    }
    env->CallStaticVoidMethod(clazz, mid, strArray);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_affy_nativetest_MainActivity_invokeConstructors(JNIEnv *env, jobject thiz) {
    jclass clazz = env->FindClass("com/affy/nativetest/bean/Animal");
    jmethodID methodId = env->GetMethodID(clazz, "<init>", "(Ljava/lang/String;)V");
    return env->NewObject(clazz, methodId, env->NewStringUTF("this is animal a"));
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_affy_nativetest_MainActivity_allocConstructors(JNIEnv *env, jobject thiz) {
    jclass clazz = env->FindClass("com/affy/nativetest/bean/Animal");
    jmethodID methodId = env->GetMethodID(clazz, "<init>", "(Ljava/lang/String;)V");
    jobject animal = env->AllocObject(clazz);
    env->CallNonvirtualVoidMethod(animal, clazz, methodId, env->NewStringUTF("this is animal b"));
    return animal;
}