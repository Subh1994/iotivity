/******************************************************************
 *
 * Copyright 2016 Samsung Electronics All Rights Reserved.
 *
 *
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************/

/**
  * @file   JniJvm.h
  *
  * @brief  This file contains the essential declarations and functions required
  *            for JNI implementation
  */

#ifndef __JNI_ES_JVM_H
#define __JNI_ES_JVM_H

#include <jni.h>
#include<string>
#include <android/log.h>

#define ESTAG "ES-JNI"
#define JNI_CURRENT_VERSION JNI_VERSION_1_6

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, ESTAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, ESTAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, ESTAG, __VA_ARGS__)

extern JavaVM *g_jvm;

extern jclass g_cls_RemoteEnrollee;
extern jclass g_cls_ESException;

extern jmethodID g_mid_RemoteEnrollee_ctor ;
extern jmethodID g_mid_ESException_ctor;

typedef void(*RemoveListenerCallback)(JNIEnv *env, jobject jListener);

/**
 * @brief Get the native handle field
 */
static jfieldID ESGetHandleField(JNIEnv *env, jobject jobj)
{
    jclass cls = env->GetObjectClass(jobj);
    return env->GetFieldID(cls, "m_nativeHandle", "J");
}

/**
 * @brief Get the native handle
 */
template <typename T>
static T *ESGetHandle(JNIEnv *env, jobject jobj)
{
    jlong handle = env->GetLongField(jobj, ESGetHandleField(env, jobj));
    return reinterpret_cast<T *>(handle);
}

/**
 * @brief Set the native handle
 */
template <typename T>
static void ESSetHandle(JNIEnv *env, jobject jobj, T *type)
{
    jlong handle = reinterpret_cast<jlong>(type);

    env->SetLongField(jobj, ESGetHandleField(env, jobj), handle);
}

/**
 * @brief Get the JNI Environment
 */
static JNIEnv *GetESJNIEnv(jint &ret)
{
    JNIEnv *env = NULL;

    ret = g_jvm->GetEnv((void **)&env, JNI_CURRENT_VERSION);
    switch (ret)
    {
        case JNI_OK:
            return env;
        case JNI_EDETACHED:
            if (g_jvm->AttachCurrentThread(&env, NULL) < 0)
            {
                LOGE("Failed to get the environment");
                return nullptr;
            }
            else
            {
                return env;
            }

        case JNI_EVERSION:
            LOGE("JNI version not supported");
        default:
            LOGE("Failed to get the environment");
            return nullptr;
    }
}
#endif // __JNI_ES_JVM_H
