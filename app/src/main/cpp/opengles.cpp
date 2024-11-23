#include <jni.h>
#include "GLContext.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opengles_gl_MyNativeRender_native_1init(JNIEnv *env, jobject thiz) {
    GLContext::getInstance();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_opengles_gl_MyNativeRender_native_1uninit(JNIEnv *env, jobject thiz) {
    GLContext::destroyInstance();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_opengles_gl_MyNativeRender_native_1SurfaceCreated(JNIEnv *env, jobject thiz) {
    GLContext::getInstance()->OnSurfaceCreated();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_opengles_gl_MyNativeRender_native_1SurfaceChanged(JNIEnv *env, jobject thiz, int width, int height) {
    GLContext::getInstance()->OnSurfaceChanged(width, height);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_opengles_gl_MyNativeRender_native_1DrawFrame(JNIEnv *env, jobject thiz) {
    GLContext::getInstance()->OnDrawFrame();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opengles_gl_MyNativeRender_native_1setSample(JNIEnv *env, jobject thiz, jint sample) {
    GLContext::getInstance()->setSample(sample);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_opengles_gl_MyNativeRender_native_1setImageData(JNIEnv *env, jobject thiz, jint pixel_format, jint width, jint height, jbyteArray bytes) {
    jsize length = env->GetArrayLength(bytes);
    uint8_t* buffer = new uint8_t[length];
    env->GetByteArrayRegion(bytes, 0, length, reinterpret_cast<jbyte*>(buffer));
    GLContext::getInstance()->setImageData(pixel_format, width, height, buffer);
    delete[] buffer;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_opengles_gl_MyNativeRender_native_1initSample(JNIEnv *env, jobject thiz) {
    GLContext::getInstance()->initSample();
}