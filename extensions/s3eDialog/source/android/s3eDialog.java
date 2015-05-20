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
java implementation of the s3eDialog extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
import com.ideaworks3d.marmalade.LoaderAPI;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.DialogInterface.*;
import android.view.KeyEvent;



class s3eDialog
{
    
    private static native void native_dialogCallback(int button, int id);
    public int m_Id = -1;
    int button = -1;
    
    class s3eDialogListener implements AlertDialog.OnClickListener,DialogInterface.OnKeyListener
    {
        public int m_numButtons = 1;
        

        public void onClick(DialogInterface dialog, int which)
        {
            
            switch(which)
            {
                case DialogInterface.BUTTON1: button = 0; break; // OK
                case DialogInterface.BUTTON2: button = 1; break; // NEUTRAL
                case DialogInterface.BUTTON3: button = 2; break; // CANCEL
            }

            // Neutral is always in the centre so cancel becomes the 3rd button
            if (m_numButtons == 3)
            {
                if (which == DialogInterface.BUTTON3)
                    button = 1;
                if (which == DialogInterface.BUTTON2)
                    button = 2;
            }

            native_dialogCallback(button, m_Id);
        }
        public boolean onKey(DialogInterface dialog, int keyCode, KeyEvent event)
        {  
           
          
          if( keyCode == KeyEvent.KEYCODE_BACK)
           {      
             button = -1;
             native_dialogCallback(button, m_Id);
          
            
            dialog.dismiss();

            return true;
           
           }
            
          return false;
        }
    }

    public boolean s3eDialogAlertBox(String message, String title, String button1, String button2, String button3, int id)
    {
        s3eDialogListener listener  = new s3eDialogListener();
        m_Id = id;

        AlertDialog.Builder builder = new AlertDialog.Builder(LoaderAPI.getActivity());

        builder.setTitle(title)
               .setMessage(message)
               .setCancelable(false)
               .setPositiveButton(button1,listener)
               .setOnKeyListener(listener);

        // The button asisngment depends on the number of buttons we need
        if (button2 != null && button3 == null)
        {
            builder.setNegativeButton(button2,listener);
            listener.m_numButtons = 2;
        }
        else if (button2 != null && button3 != null)
        {
            builder.setNeutralButton(button2,listener);
            builder.setNegativeButton(button3,listener);
            listener.m_numButtons = 3;
        }

        builder.create();
        builder.show();

        return true;
    }
}
