//
// Created by Zongcheng Chu on 8/4/24.
//

#include "TransformationSample.h"
#include "GLShaderSources.h"
#include "gtc/matrix_transform.hpp"

TransformationSample::TransformationSample() {
    mTextureID = GL_NONE;
    mSampleLoc = 0;
    mMVPLoc = 0;
    mVAO = GL_NONE;
    mVBO = GL_NONE;
    mMVPMatrix = glm::mat4x4(0.0f);
    mAngleX = 0;
    mAngleY = 0;
    mScaleX = 1.0f;
    mScaleY = 1.0f;
}

TransformationSample::~TransformationSample() {
    NativeImageUtils::freeNativeImage(&mImage);
}

void TransformationSample::loadImage(NativeImage *image) {
    if (image) {
        mImage.width = image->width;
        mImage.height = image->height;
        mImage.format = image->format;
        NativeImageUtils::copyImage(image, &mImage);
        LOGD("Loaded image, width: %d, height: %d\n", mImage.width, mImage.height);
    }
}

void TransformationSample::init() {
    GLfloat vertices[] = {
            -1.0f,1.0f, 0.0f,0.0f,0.0f, // Position 0
            -1.0f,-1.0f, 0.0f,0.0f,1.0f,  // Position 1
            1.0f,-1.0f, 0.0f,1.0f,1.0f, // Position 2
            1.0f,1.0f, 0.0f,1.0f,0.0f // Position 3
    };

    GLushort indices[6] = {0, 1, 2, 0, 2, 3};

    mShaderProgram = GLUtils::CreateProgram(TransformationVertexShader, TransformationFragmentShader, mVertexShader, mFragmentShader);
    if (!mShaderProgram) {
        LOGE("create shader program error.");
        return;
    }
    mSampleLoc = glGetUniformLocation(mShaderProgram, "TextureMap");
    mMVPLoc = glGetUniformLocation(mShaderProgram, "MVPMatrix");

    // Generate VAO and define how data is stored
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    // Generate VBO and load data
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Generate EBO and load data
    glGenBuffers(1, &mEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Specify the layout of the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind the VAO (it's a good practice to unbind any VAO to prevent accidental modification)
    glBindVertexArray(GL_NONE);

    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mImage.width, mImage.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, mImage.planes[0]);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
}

void TransformationSample::updateMVP(glm::mat4 &mvp, int angleX, int angleY, float ratio) {
    angleX = angleX % 360;
    angleY = angleY % 360;

    //转化为弧度角
    float radiansX = static_cast<float>(PI / 180.0f * angleX);
    float radiansY = static_cast<float>(PI / 180.0f * angleY);


    // Projection matrix
    glm::mat4 Projection = glm::perspective(45.0f,ratio, 0.1f,100.f);

    // View matrix
    glm::mat4 View = glm::lookAt(
            glm::vec3(0, 0, 4), // Camera is at (0,0,1), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix
    glm::mat4 Model = glm::mat4(1.0f);
    Model = glm::scale(Model, glm::vec3(mScaleX, mScaleY, 1.0f));
    Model = glm::rotate(Model, radiansX, glm::vec3(1.0f, 0.0f, 0.0f));
    Model = glm::rotate(Model, radiansY, glm::vec3(0.0f, 1.0f, 0.0f));
    Model = glm::translate(Model, glm::vec3(0.0f, 0.0f, 0.0f));

    mvp = Projection * View * Model;
}

void TransformationSample::draw(int width, int height) {
    LOGD("draw transformation sample.");
    if (mShaderProgram == GL_NONE) return;

    mAngleX = (mAngleX + 1) % 360;
    mAngleY = (mAngleY + 1) % 360;

    updateMVP(mMVPMatrix, mAngleX, mAngleY, (float)(width) / (float)(height));
    glUseProgram(mShaderProgram);
    glBindVertexArray(mVAO);
    glUniformMatrix4fv(mMVPLoc, 1, GL_FALSE, &mMVPMatrix[0][0]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glUniform1i(mSampleLoc, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)(0));
}

void TransformationSample::destroy() {

}