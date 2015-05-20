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
 * osx-specific implementation of the s3eDialog extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eDialog_internal.h"
#include "s3eEdk.h"
#import <AppKit/AppKit.h>
#include "IwDebug.h"

s3eResult s3eDialogInit_platform()
{
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void s3eDialogTerminate_platform()
{
    // Add any platform-specific termination code here
}

s3eResult s3eDialogRegister_platform(s3eDialogCallback cid, s3eCallback fn, void* userData)
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eDialogUnRegister_platform(s3eDialogCallback cbid, s3eCallback fn)
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eDialogAlertBox_platform(s3eDialogAlertInfo* info)
{
    NSAlert* alert = [[[NSAlert alloc] init] autorelease];

    [alert setMessageText: [NSString stringWithUTF8String: info->m_Title]];
    [alert setInformativeText: [NSString stringWithUTF8String: info->m_Message]];

    int buttons[3] = { 0,0,0 };

    if (info->m_Button[1] != NULL && info->m_Button[2] != NULL)
    {
        [alert addButtonWithTitle: [NSString stringWithUTF8String: info->m_Button[2]]];
        [alert addButtonWithTitle: [NSString stringWithUTF8String: info->m_Button[1]]];
        [alert addButtonWithTitle: [NSString stringWithUTF8String: info->m_Button[0]]];
        buttons[0] = NSAlertThirdButtonReturn;
        buttons[1] = NSAlertSecondButtonReturn;
        buttons[2] = NSAlertFirstButtonReturn;
    }
    else if (info->m_Button[1] != NULL)
    {
        [alert addButtonWithTitle: [NSString stringWithUTF8String: info->m_Button[1]]];
        [alert addButtonWithTitle: [NSString stringWithUTF8String: info->m_Button[0]]];
        buttons[0] = NSAlertSecondButtonReturn;
        buttons[1] = NSAlertFirstButtonReturn;
    }
    else
    {
        [alert addButtonWithTitle: [NSString stringWithUTF8String: info->m_Button[0]]];
        buttons[0] = NSAlertFirstButtonReturn;
    }

    int result = [alert runModal];

    s3eDialogCallbackData data;
    data.m_Id = info->m_Id;

    for (int i=0; i<3; i++)
        if (buttons[i] == result)
            data.m_ButtonPressed = i;

    s3eEdkCallbacksEnqueue(S3E_EXT_DIALOG_HASH, S3E_DIALOG_FINISHED, &data, sizeof(s3eDialogCallbackData));

    return S3E_RESULT_SUCCESS;
}
