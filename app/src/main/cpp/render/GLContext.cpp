//
// Created by Zongcheng Chu on 7/21/24.
//

#include "GLContext.h"

GLContext* GLContext::mContext = nullptr;

GLContext::GLContext() {
    mSample = new TriangleSample();
}

GLContext::~GLContext() {}

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
        mSample->draw();
    }
}

void GLContext::setSample(int sample) {
    switch (sample) {
        case SAMPLE_TRIANGLE:
            mSample = new TriangleSample();
            break;
    }
}