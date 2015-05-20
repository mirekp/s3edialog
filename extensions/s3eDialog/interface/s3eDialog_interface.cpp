/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */

#include "s3eExt.h"
#include "IwDebug.h"
#include "s3eDevice.h"


#include "s3eDialog.h"


// Define S3E_EXT_SKIP_LOADER_CALL_LOCK on the user-side to skip LoaderCallStart/LoaderCallDone()-entry.
// e.g. in s3eNUI this is used for generic user-side IwUI-based implementation.
#ifndef S3E_EXT_SKIP_LOADER_CALL_LOCK
#if defined I3D_ARCH_MIPS || defined S3E_ANDROID_X86 || (defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)) || defined I3D_ARCH_NACLX86_64
// For platforms missing stack-switching (MIPS, WP8, Android-x86, NaCl, etc.) make loader-entry via LoaderCallStart/LoaderCallDone() on the user-side.
#define LOADER_CALL_LOCK
#endif
#endif

/**
 * Definitions for functions types passed to/from s3eExt interface
 */
typedef const char*(*s3eDialogGetErrorString_t)();
typedef s3eDialogError(*s3eDialogGetError_t)();
typedef  s3eResult(*s3eDialogRegister_t)(s3eDialogCallback cid, s3eCallback fn, void* userData);
typedef  s3eResult(*s3eDialogUnRegister_t)(s3eDialogCallback cbid, s3eCallback fn);
typedef  s3eResult(*s3eDialogAlertBox_t)(s3eDialogAlertInfo* info);

/**
 * struct that gets filled in by s3eDialogRegister
 */
typedef struct s3eDialogFuncs
{
    s3eDialogGetErrorString_t m_s3eDialogGetErrorString;
    s3eDialogGetError_t m_s3eDialogGetError;
    s3eDialogRegister_t m_s3eDialogRegister;
    s3eDialogUnRegister_t m_s3eDialogUnRegister;
    s3eDialogAlertBox_t m_s3eDialogAlertBox;
} s3eDialogFuncs;

static s3eDialogFuncs g_Ext;
static bool g_GotExt = false;
static bool g_TriedExt = false;
static bool g_TriedNoMsgExt = false;

static bool _extLoad()
{
    if (!g_GotExt && !g_TriedExt)
    {
        s3eResult res = s3eExtGetHash(0xa6c1a5c0, &g_Ext, sizeof(g_Ext));
        if (res == S3E_RESULT_SUCCESS)
            g_GotExt = true;
        else
            s3eDebugAssertShow(S3E_MESSAGE_CONTINUE_STOP_IGNORE,                 "error loading extension: s3eDialog");

        g_TriedExt = true;
        g_TriedNoMsgExt = true;
    }

    return g_GotExt;
}

static bool _extLoadNoMsg()
{
    if (!g_GotExt && !g_TriedNoMsgExt)
    {
        s3eResult res = s3eExtGetHash(0xa6c1a5c0, &g_Ext, sizeof(g_Ext));
        if (res == S3E_RESULT_SUCCESS)
            g_GotExt = true;
        g_TriedNoMsgExt = true;
        if (g_TriedExt)
            g_TriedExt = true;
    }

    return g_GotExt;
}

s3eBool s3eDialogAvailable()
{
    _extLoadNoMsg();
    return g_GotExt ? S3E_TRUE : S3E_FALSE;
}

const char* s3eDialogGetErrorString()
{
    IwTrace(DIALOG_VERBOSE, ("calling s3eDialog[0] func: s3eDialogGetErrorString"));

    if (!_extLoad())
        return NULL;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_s3eDialogGetErrorString);
#endif

    const char* ret = g_Ext.m_s3eDialogGetErrorString();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_s3eDialogGetErrorString);
#endif

    return ret;
}

s3eDialogError s3eDialogGetError()
{
    IwTrace(DIALOG_VERBOSE, ("calling s3eDialog[1] func: s3eDialogGetError"));

    if (!_extLoad())
        return (s3eDialogError)0;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_s3eDialogGetError);
#endif

    s3eDialogError ret = g_Ext.m_s3eDialogGetError();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_s3eDialogGetError);
#endif

    return ret;
}

s3eResult s3eDialogRegister(s3eDialogCallback cid, s3eCallback fn, void* userData)
{
    IwTrace(DIALOG_VERBOSE, ("calling s3eDialog[2] func: s3eDialogRegister"));

    if (!_extLoad())
        return S3E_RESULT_ERROR;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_s3eDialogRegister);
#endif

    s3eResult ret = g_Ext.m_s3eDialogRegister(cid, fn, userData);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_s3eDialogRegister);
#endif

    return ret;
}

s3eResult s3eDialogUnRegister(s3eDialogCallback cbid, s3eCallback fn)
{
    IwTrace(DIALOG_VERBOSE, ("calling s3eDialog[3] func: s3eDialogUnRegister"));

    if (!_extLoad())
        return S3E_RESULT_ERROR;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_s3eDialogUnRegister);
#endif

    s3eResult ret = g_Ext.m_s3eDialogUnRegister(cbid, fn);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_s3eDialogUnRegister);
#endif

    return ret;
}

s3eResult s3eDialogAlertBox(s3eDialogAlertInfo* info)
{
    IwTrace(DIALOG_VERBOSE, ("calling s3eDialog[4] func: s3eDialogAlertBox"));

    if (!_extLoad())
        return S3E_RESULT_SUCCESS;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_s3eDialogAlertBox);
#endif

    s3eResult ret = g_Ext.m_s3eDialogAlertBox(info);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_s3eDialogAlertBox);
#endif

    return ret;
}