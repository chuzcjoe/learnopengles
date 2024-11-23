//
// Created by Zongcheng Chu on 7/21/24.
//

#include "TextureLoadSample.h"
#include "GLShaderSources.h"

TextureLoadSample::TextureLoadSample() {
    mTextureID = 0;
}

TextureLoadSample::~TextureLoadSample() {
    NativeImageUtils::freeNativeImage(&mImage);
}

void TextureLoadSample::init() {
    // generate a texture
    glGenTextures(1, &mTextureID);
    // set the texture object as the current activate texture object
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    // set texture wrapping
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    mShaderProgram = GLUtils::CreateProgram(TextureLoadVertexShader, TextureLoadFragmentShader, mVertexShader, mFragmentShader);
    if (mShaderProgram) {
        mSamplerLoc = glGetUniformLocation(mShaderProgram, "sTexture");
    } else {
        LOGE("Couldn't find uniform variable sTexture.");
    }
}

void TextureLoadSample::draw(int width, int height) {
    LOGD("Draw Texture");
    if (mShaderProgram == GL_NONE || mTextureID == GL_NONE) return;

    GLfloat vertices[] = {
            -1.0f,  0.5f, 0.0f,  // Top left
            -1.0f, -0.5f, 0.0f,  // Bottom left
            1.0f, -0.5f, 0.0f,   // Bottom right
            1.0f,  0.5f, 0.0f,   // Top right
    };

    GLfloat textureCoords[] = {
            0.0f,  0.0f,        // top left
            0.0f,  1.0f,        // bottom left
            1.0f,  1.0f,        // bottom right
            1.0f,  0.0f         // top right
    };

    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

    glClearColor(1., 1., 1., 1.);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mImage.width, mImage.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, mImage.planes[0]);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    glUseProgram(mShaderProgram);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), vertices);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), textureCoords);
    glEnableVertexAttribArray(1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glUniform1i(mSamplerLoc, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void TextureLoadSample::loadImage(NativeImage *image) {
    if (image) {
        mImage.width = image->width;
        mImage.height = image->height;
        mImage.format = image->format;
        NativeImageUtils::copyImage(image, &mImage);
    }
}

void TextureLoadSample::destroy() {
    if (mShaderProgram) {
        glDeleteProgram(mShaderProgram);
        glDeleteTextures(1, &mTextureID);
        mShaderProgram = GL_NONE;
    }
    NativeImageUtils::freeNativeImage(&mImage);
}