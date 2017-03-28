#include "Master.hpp"
#include <platform/android/jni/JniHelper.h>
#include <cocos2d.h>
#include <android/log.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

void cocos_android_app_init (JNIEnv * env)
{
    Master * master = new Master();
}
