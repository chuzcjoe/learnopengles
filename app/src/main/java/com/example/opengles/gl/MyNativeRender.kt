package com.example.opengles.gl

class MyNativeRender {
    companion object {
      init {
         System.loadLibrary("opengles")
      }
    }

    external fun native_init()

    external fun native_initSample()

    external fun native_uninit()

    external fun native_SurfaceCreated()

    external fun native_SurfaceChanged(width: Int, height: Int)

    external fun native_DrawFrame()

    external fun native_setSample(sample: Int)

    external fun native_setImageData(pixelFormat: Int, width: Int, height: Int, bytes: ByteArray)
}