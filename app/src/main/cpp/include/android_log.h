#include <jni.h>
#include <android/log.h>

#ifndef _ANDROID_LOG_TAG
#define _ANDROID_LOG_TAG "ANDROID_JNI_TAG"
#define LOG_I(...)   __android_log_print(ANDROID_LOG_INFO,_ANDROID_LOG_TAG,__VA_ARGS__)
#endif





