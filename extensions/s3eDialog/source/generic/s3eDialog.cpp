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
Generic implementation of the s3eDialog extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "s3eDialog_internal.h"
#include "s3eEdk.h"

s3eResult s3eDialogInit()
{
    //Add any generic initialisation code here
    return s3eDialogInit_platform();
}

s3eResult s3eDialogRegister(s3eDialogCallback cid, s3eCallback fn, void* userData)
{
    return (s3eResult)s3eEdkCallbacksRegister(S3E_EXT_DIALOG_HASH, S3E_DIALOG_CALLBACK_MAX, cid, fn, userData, S3E_FALSE);
}

s3eResult s3eDialogUnRegister(s3eDialogCallback cbid, s3eCallback fn)
{
    return (s3eResult)s3eEdkCallbacksUnRegister(S3E_EXT_DIALOG_HASH, S3E_DIALOG_CALLBACK_MAX, cbid, fn);
}

void s3eDialogTerminate()
{
    //Add any generic termination code here
    s3eDialogTerminate_platform();
}

s3eResult s3eDialogAlertBox(s3eDialogAlertInfo* info)
{
    return s3eDialogAlertBox_platform(info);
}
