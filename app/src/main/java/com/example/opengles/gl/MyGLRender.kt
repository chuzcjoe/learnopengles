package com.example.opengles.gl

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyGLRender : GLSurfaceView.Renderer {
    private val mNativeRender: MyNativeRender = MyNativeRender()

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        mNativeRender.native_SurfaceCreated()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        mNativeRender.native_SurfaceChanged(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        mNativeRender.native_DrawFrame()
    }

    fun initRenderContext() {
        mNativeRender.native_init()
    }

    fun setImageData(pixelFormat: Int, width: Int, height: Int, bytes: ByteArray) {
        mNativeRender.native_setImageData(pixelFormat, width, height, bytes);
    }

    fun setSample(sample: Int) {
        mNativeRender.native_setSample(sample)
    }
}