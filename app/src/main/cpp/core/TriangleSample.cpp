//
// Created by Zongcheng Chu on 7/21/24.
//

#include "TriangleSample.h"
#include "GLShaderSources.h"

TriangleSample::TriangleSample() {}

TriangleSample::~TriangleSample() {}

void TriangleSample::init() {
    mShaderProgram = GLUtils::CreateProgram(TriangleVertexShader, TriangleFragmentShader, mVertexShader, mFragmentShader);
}

void TriangleSample::draw() {
    GLfloat vVertices[] = {
            0.0f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
    };

    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Use the program object
    glUseProgram (mShaderProgram);

    // Load the vertex data
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
    glEnableVertexAttribArray (0);

    glDrawArrays (GL_TRIANGLES, 0, 3);
    glUseProgram (GL_NONE);
}

void TriangleSample::destroy() {
    if (mShaderProgram) {
        glDeleteProgram(mShaderProgram);
        mShaderProgram = GL_NONE;
    }
}