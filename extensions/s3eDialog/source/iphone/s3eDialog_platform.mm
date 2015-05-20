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
 * iphone-specific implementation of the s3eDialog extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eDialog_internal.h"
#include "s3eEdk.h"
#import <UIKit/UIKit.h>
#include "IwDebug.h"

@interface MessageBoxDelegate : NSObject <UIAlertViewDelegate> {
@public int m_Id;
}
- (void) alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex;
@end

@implementation MessageBoxDelegate
- (void) alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    IwTrace(DIALOG_VERBOSE, ("sending callback with %d", static_cast<int>(buttonIndex)));

    s3eDialogCallbackData data;
    data.m_Id = m_Id;
    data.m_ButtonPressed = buttonIndex;
    s3eEdkCallbacksEnqueue(S3E_EXT_DIALOG_HASH, S3E_DIALOG_FINISHED, &data, sizeof(s3eDialogCallbackData));

    [self release];
}
@end


s3eResult s3eDialogInit_platform()
{
    return S3E_RESULT_SUCCESS;
}

void s3eDialogTerminate_platform()
{
}

s3eResult s3eDialogAlertBox_platform(s3eDialogAlertInfo* info)
{
    UIAlertView* alert = [[[UIAlertView alloc] init] autorelease];

    [alert setTitle: [NSString stringWithUTF8String: info->m_Title]];
    [alert setMessage: [NSString stringWithUTF8String: info->m_Message]];

    [alert addButtonWithTitle: [NSString stringWithUTF8String: info->m_Button[0]]];
    if (info->m_Button[1] != NULL)
        [alert addButtonWithTitle: [NSString stringWithUTF8String: info->m_Button[1]]];
    if (info->m_Button[1] != NULL && info->m_Button[2] != NULL)
        [alert addButtonWithTitle: [NSString stringWithUTF8String: info->m_Button[2]]];

    MessageBoxDelegate* delegate = [[MessageBoxDelegate alloc] init];
    delegate->m_Id = info->m_Id;

    [alert setDelegate:delegate];
    [alert show];

    return S3E_RESULT_SUCCESS;
}
