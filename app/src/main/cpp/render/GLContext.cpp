//
// Created by Zongcheng Chu on 7/21/24.
//

#include "GLContext.h"
#include "TriangleSample.h"
#include "TextureLoadSample.h"
#include "VAOVBOSample.h"
#include "FBOSample.h"
#include "TransformationSample.h"

GLContext* GLContext::mContext = nullptr;

GLContext::GLContext() {
    mSample = new TriangleSample();
}

GLContext::~GLContext() {
    delete mSample;
    mSample = nullptr;
}

GLContext *GLContext::getInstance() {
    if (mContext == nullptr) {
        mContext = new GLContext();
    }
    return mContext;
}

void GLContext::destroyInstance() {
    if (mContext) {
        delete mContext;
        mContext = nullptr;
    }
}

void GLContext::OnSurfaceCreated() {
    glClearColor(1., 1., 1., 1.);
}

void GLContext::OnSurfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
    mWidth = width;
    mHeight = height;
}

void GLContext::OnDrawFrame() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    if (mSample) {
        mSample->init();
        mSample->draw(mWidth, mHeight);
    }
}

void GLContext::setSample(int sample) {
    if (mSample) {
        mSample->destroy();
        delete mSample;
        mSample = nullptr;
    }
    switch (sample) {
        case SAMPLE_TRIANGLE:
            mSample = new TriangleSample();
            break;
        case SAMPLE_LOAD_TEXTURE:
            mSample = new TextureLoadSample();
            break;
        case SAMPLE_VAO_VBO:
            mSample = new VAOVBOSample();
            break;
        case SAMPLE_FBO:
            mSample = new FBOSample();
            break;
        case SAMPLE_TRANSFORMATION:
            mSample = new TransformationSample();
            break;
        default:
            break;
    }
}

void GLContext::setImageData(int pixelFormat, int width, int height, uint8_t *data) {
    NativeImage image;
    image.format = pixelFormat;
    image.width = width;
    image.height = height;
    image.planes[0] = data;

    switch (pixelFormat) {
        case IMAGE_FORMAT_RGBA:
            LOGD("Set image data for RGBA Format. Width: %d, Height: %d", width, height);
            break;
        default:
            break;
    }

    if (mSample) {
        mSample->loadImage(&image);
    }
}