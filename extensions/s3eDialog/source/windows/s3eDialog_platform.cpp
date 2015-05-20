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
 * windows-specific implementation of the s3eDialog extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eDialog_internal.h"
#include "s3eEdk.h"
#include <windows.h>

s3eResult s3eDialogInit_platform()
{
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void s3eDialogTerminate_platform()
{
    // Add any platform-specific termination code here
}

static HHOOK s_DialogHook = NULL;
static s3eDialogAlertInfo* s_Info = NULL;

LRESULT CALLBACK DialogHookFunction(INT nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HCBT_ACTIVATE)
    {
        HWND child = (HWND)wParam;

        if (GetDlgItem(child, IDOK) != NULL)
            SetDlgItemText(child, IDOK, s_Info->m_Button[0]);
        if (GetDlgItem(child, IDABORT) != NULL)
            SetDlgItemText(child, IDABORT, s_Info->m_Button[0]);
        if (GetDlgItem(child, IDYES) != NULL)
            SetDlgItemText(child, IDYES, s_Info->m_Button[0]);

        if (GetDlgItem(child, IDRETRY) != NULL)
            SetDlgItemText(child, IDRETRY, s_Info->m_Button[1]);
        if (GetDlgItem(child, IDNO) != NULL)
            SetDlgItemText(child, IDNO, s_Info->m_Button[1]);

        if (GetDlgItem(child, IDIGNORE) != NULL)
            SetDlgItemText(child, IDIGNORE, s_Info->m_Button[2]);

        UnhookWindowsHookEx(s_DialogHook);
    }
    else
        CallNextHookEx(s_DialogHook, nCode, wParam, lParam);
    return 0;
}

s3eResult s3eDialogAlertBox_platform(s3eDialogAlertInfo* info)
{
    int code = MB_OK;
    if (info->m_Button[2] != NULL && info->m_Button[1] != NULL)
        code = MB_ABORTRETRYIGNORE;
    else if (info->m_Button[1] != NULL)
        code = MB_YESNO;

    s_Info = info;
    s_DialogHook = SetWindowsHookEx(WH_CBT, DialogHookFunction, NULL, GetCurrentThreadId());

    int result = MessageBox(0, info->m_Message, info->m_Title, code);

    s3eDialogCallbackData data;
    data.m_Id = info->m_Id;

    switch(result)
    {
        case IDOK:
        case IDABORT:
        case IDYES:
            data.m_ButtonPressed = 0;
            break;
        case IDRETRY:
        case IDNO:
            data.m_ButtonPressed = 1;
            break;
        case IDIGNORE:
            data.m_ButtonPressed = 2;
            break;
    }

    s3eEdkCallbacksEnqueue(S3E_EXT_DIALOG_HASH, S3E_DIALOG_FINISHED, &data, sizeof(s3eDialogCallbackData));

    // Don't want to persist this pointer value
    s_Info = NULL;

    return S3E_RESULT_SUCCESS;
}
