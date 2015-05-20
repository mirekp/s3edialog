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
 * Internal header for the s3eDialog extension.
 *
 * This file should be used for any common function definitions etc that need to
 * be shared between the platform-dependent and platform-indepdendent parts of
 * this extension.
 */

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#ifndef S3EDIALOG_INTERNAL_H
#define S3EDIALOG_INTERNAL_H

#include "s3eTypes.h"
#include "s3eDialog.h"
#include "s3eDialog_autodefs.h"


/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult s3eDialogInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult s3eDialogInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void s3eDialogTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void s3eDialogTerminate_platform();

s3eResult s3eDialogAlertBox_platform(s3eDialogAlertInfo* info);


#endif /* !S3EDIALOG_INTERNAL_H */
