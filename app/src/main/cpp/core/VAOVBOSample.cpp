//
// Created by Zongcheng Chu on 7/25/24.
//

#include "VAOVBOSample.h"
#include "GLShaderSources.h"

VAOVBOSample::VAOVBOSample() {
    mVAO = GL_NONE;
    mEBO = GL_NONE;
    mVBO = GL_NONE;
}

VAOVBOSample::~VAOVBOSample() {}

void VAOVBOSample::init() {
    GLfloat vertices[4 * (3 + 4)] = {
            // Vertex positions followed by color attributes
            -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // v0, c0
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // v1, c1
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // v2, c2
            0.5f,  0.5f, 0.0f, 0.5f, 1.0f, 1.0f, 1.0f   // v3, c3
    };

    GLushort indices[6] = {0, 1, 2, 0, 2, 3};
    LOGD("VAOVBO sample creates shader.");

    mShaderProgram = GLUtils::CreateProgram(VAOVBOVertexShader, VAOVBOFragmentShader, mVertexShader, mFragmentShader);

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind the VAO (it's a good practice to unbind any VAO to prevent accidental modification)
    glBindVertexArray(GL_NONE);
}


void VAOVBOSample::draw(int width, int height) {
    if (mShaderProgram == GL_NONE) return;
    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    LOGD("VAOVBO draw");
    glUseProgram(mShaderProgram);
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)(0));
    glBindVertexArray(GL_NONE);
}

void VAOVBOSample::destroy() {
    if (mShaderProgram) {
        glDeleteProgram(mShaderProgram);
        glDeleteBuffers(1, &mVBO);
        glDeleteBuffers(1, &mEBO);
        glDeleteVertexArrays(1, &mVAO);
        mShaderProgram = GL_NONE;
    }
}