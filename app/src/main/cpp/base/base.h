//
// Created by Affy Zhang on 2020/3/2.
//

#ifndef NATIVEPROJECTTEST_BASE_H
#define NATIVEPROJECTTEST_BASE_H

#include <jni.h>
#include <android/log.h>

#define  LOGI(...) __android_log_print(ANDROID_LOG_INFO, "========= Info =========   ", __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, "========= Error =========   ", __VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_INFO, "========= Debug =========   ", __VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN, "========= Warn =========   ", __VA_ARGS__)

#endif //NATIVEPROJECTTEST_BASE_H
