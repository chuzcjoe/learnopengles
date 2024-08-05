//
// Created by Zongcheng Chu on 7/26/24.
//

#include "FBOSample.h"
#include "GLShaderSources.h"

FBOSample::FBOSample() {
    mShaderProgram = GL_NONE;
    mFBOProgram = GL_NONE;
}

FBOSample::~FBOSample() {}

void FBOSample::loadImage(NativeImage *image) {
    if (image) {
        mImage.width = image->width;
        mImage.height = image->height;
        mImage.format = image->format;
        NativeImageUtils::copyImage(image, &mImage);
        LOGD("Loaded image, width: %d, height: %d\n", mImage.width, mImage.height);
    }
}

void FBOSample::init() {
    GLfloat vertices[] = {
            -1.0f,  1.0f, 0.0f,  // Top left
            -1.0f, -1.0f, 0.0f,  // Bottom left
            1.0f, -1.0f, 0.0f,   // Bottom right
            1.0f,  1.0f, 0.0f,   // Top right
    };

    GLfloat onScreenTexCoords[] = {
            0.0f,  0.0f,        // top left
            0.0f,  1.0f,        // bottom left
            1.0f,  1.0f,        // bottom right
            1.0f,  0.0f         // top right
    };

    GLfloat offScreenTexCoords[] = {
            0.0f,  1.0f,        // top left
            0.0f,  0.0f,        // bottom left
            1.0f,  0.0f,        // bottom right
            1.0f,  1.0f         // top right
    };

    GLushort indices[] = {0, 1, 2, 0, 2, 3 };

    // on screen rendering
    mShaderProgram = GLUtils::CreateProgram(FBOONScreenVertexShader, FBOONScreenFragmentShader, mVertexShader, mFragmentShader);
    // off screen FrameBuffer rendering
    mFBOProgram = GLUtils::CreateProgram(FBOOFFScreenVertexShader, FBOOFFScreenFragmentShader, mFBOVertexShader, mFBOFragmentShader);

    if (mShaderProgram == GL_NONE) {
        LOGD("FBO sample creates mShaderProgram error.");
    }

    if (mFBOProgram == GL_NONE) {
        LOGD("FBO sample creates mFBOProgram error.");
    }

    mOnScreenSamplerLoc = glGetUniformLocation(mShaderProgram, "onScreenTexture");
    mOffScreenSamplerLoc = glGetUniformLocation(mFBOProgram, "offScreenTexture");

    glGenVertexArrays(2, mVAO);

    // bind first VAO for offscreen rendering
    glBindVertexArray(mVAO[0]);
    glGenBuffers(3, mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(offScreenTexCoords), offScreenTexCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(2);
    glGenBuffers(1, &mEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // end of first VAO

    // bind second VAO for onscreen rendering
    glBindVertexArray(mVAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(onScreenTexCoords), onScreenTexCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBindVertexArray(GL_NONE);
    // end of second VAO

    // image texture
    glGenTextures(1, &mOffScreenTextureID);
    glBindTexture(GL_TEXTURE_2D, mOffScreenTextureID);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mImage.width, mImage.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, mImage.planes[0]);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    // FrameBuffer
    glGenFramebuffers(1, &mFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
    glGenTextures(1, &mOnScreenTextureID);
    glBindTexture(GL_TEXTURE_2D, mOnScreenTextureID);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mImage.width, mImage.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mOnScreenTextureID, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER)!= GL_FRAMEBUFFER_COMPLETE) {
        LOGE("FBOSample::CreateFrameBufferObj glCheckFramebufferStatus status != GL_FRAMEBUFFER_COMPLETE");
        return;
    }
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
}

void FBOSample::draw(int width, int height) {
    LOGD("Draw FBO sample");
    glViewport(0, 0, mImage.width, mImage.height);

    // Off-screen rendering
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(mFBOProgram);
    glBindVertexArray(mVAO[0]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mOffScreenTextureID);
    glUniform1i(mOffScreenSamplerLoc, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)(0));
    glBindVertexArray(GL_NONE);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        LOGE("OpenGL error after off-screen rendering: %d", error);
    }

    // On-screen rendering
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, width, height);
    glUseProgram(mShaderProgram);
    glBindVertexArray(mVAO[1]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mOnScreenTextureID);
    glUniform1i(mOnScreenSamplerLoc, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)(0));
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
    glBindVertexArray(GL_NONE);

    error = glGetError();
    if (error != GL_NO_ERROR) {
        LOGE("OpenGL error after on-screen rendering: %d", error);
    }
}

void FBOSample::destroy() {
    glDeleteProgram(mFBOProgram);
    glDeleteProgram(mShaderProgram);
    glDeleteTextures(1, &mOnScreenTextureID);
    glDeleteTextures(1, &mOffScreenTextureID);
    glDeleteBuffers(3, mVBO);
    glDeleteVertexArrays(2, mVAO);
    glDeleteFramebuffers(1, &mFBO);
    NativeImageUtils::freeNativeImage(&mImage);
}