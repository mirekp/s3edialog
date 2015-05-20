/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */
/*
 * android-specific implementation of the s3eDialog extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eDialog_internal.h"
#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"

static jobject g_Obj;
static jmethodID g_s3eDialogAlertBox;

void JNICALL Dialog_dialogCallback(JNIEnv* env, jobject obj, jint button, jint id)
{
    s3eDialogCallbackData data;
    data.m_Id = (int) id;
    data.m_ButtonPressed = (int) button;
    s3eEdkCallbacksEnqueue(S3E_EXT_DIALOG_HASH, S3E_DIALOG_FINISHED, (void*)&data, sizeof(s3eDialogAlertInfo));
}

s3eResult s3eDialogInit_platform()
{
    // Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();
    jobject obj = NULL;
    jmethodID cons = NULL;

    // Get the extension class
    jclass cls = s3eEdkAndroidFindClass("s3eDialog");
    if (!cls)
        goto fail;

    // Get its constructor
    cons = env->GetMethodID(cls, "<init>", "()V");
    if (!cons)
        goto fail;

    // Construct the java class
    obj = env->NewObject(cls, cons);
    if (!obj)
        goto fail;

    // Get all the extension methods
    g_s3eDialogAlertBox = env->GetMethodID(cls, "s3eDialogAlertBox", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)Z");
    if (!g_s3eDialogAlertBox)
        goto fail;

    static const JNINativeMethod methods[] =
    {
        {"native_dialogCallback","(II)V",(void*)&Dialog_dialogCallback}
    };

    // Register the native hooks
    if (env->RegisterNatives(cls, methods,sizeof(methods)/sizeof(methods[0])))
        goto fail;

    IwTrace(DIALOG, ("DIALOG init success"));
    g_Obj = env->NewGlobalRef(obj);
    env->DeleteLocalRef(obj);
    env->DeleteGlobalRef(cls);

    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;

fail:
    jthrowable exc = env->ExceptionOccurred();
    if (exc)
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
        IwTrace(s3eDialog, ("One or more java methods could not be found"));
    }
    return S3E_RESULT_ERROR;

}

void s3eDialogTerminate_platform()
{
    // Add any platform-specific termination code here
}

s3eResult s3eDialogAlertBox_platform(s3eDialogAlertInfo* info)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring message_jstr = env->NewStringUTF(info->m_Message);
    jstring title_jstr   = env->NewStringUTF(info->m_Title);
    jstring button1_jstr = env->NewStringUTF(info->m_Button[0]);
    jstring button2_jstr = env->NewStringUTF(info->m_Button[1]);
    jstring button3_jstr = env->NewStringUTF(info->m_Button[2]);
    jint id_jint         = (jint) info->m_Id;
    bool res = (bool)env->CallBooleanMethod(g_Obj, g_s3eDialogAlertBox, message_jstr, title_jstr,
                                            button1_jstr, button2_jstr, button3_jstr, id_jint);
    return res ? S3E_RESULT_SUCCESS : S3E_RESULT_ERROR;
}
