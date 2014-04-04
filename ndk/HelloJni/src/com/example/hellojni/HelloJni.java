/*
 * Copyright (C) 2009 The Android Open Source Project
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
 */
package com.example.hellojni;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;


public class HelloJni extends Activity
{
	private GLSurfaceView mGLView;
	private boolean rendererSet=true;
	
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        
        String msg = stringFromJNI();
        Log.d("", msg);
        
        mGLView = new GLSurfaceView(this);
        mGLView.setEGLContextClientVersion(2);
        mGLView.setEGLConfigChooser(8,8,8,8,16,0);
         
        mGLView.setRenderer(new DemoRenderer());
        setContentView(mGLView);
    }
    
    @Override
    protected void onPause() {
        super.onPause();
     
        if (rendererSet) {
        	mGLView.onPause();
        }
    }
     
    @Override
    protected void onResume() {
        super.onResume();
     
        if (rendererSet) {
        	mGLView.onResume();
        }
    }
    
    private static native String stringFromJNI();
    static {
        System.loadLibrary("hello-jni");
    }
}

class DemoRenderer implements GLSurfaceView.Renderer{
    private static native void nativeInit();
    private static native void nativeRender();
    private static native void nativeDone();

    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        nativeInit();
    }

    public void onSurfaceChanged(GL10 gl, int w, int h) {

        //nativeResize(w, h);
    }

    public void onDrawFrame(GL10 gl) {
       nativeRender();
    }
}
