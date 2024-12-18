//
// Created by Zongcheng Chu on 7/21/24.
//

#ifndef OPENGLES_GLBASE_H
#define OPENGLES_GLBASE_H

#include <GLES3/gl3.h>
#include "FormatDef.h"

#define SAMPLE_TRIANGLE             0
#define SAMPLE_LOAD_TEXTURE         1
#define SAMPLE_VAO_VBO              2
#define SAMPLE_FBO                  3
#define SAMPLE_TRANSFORMATION       4

class GLBase {
public:
    GLBase() {}
    virtual ~GLBase() {}

    virtual void loadImage(NativeImage* image) {};
    virtual void updateTransformationMatrix(float rotationX, float rotationY, float scaleX, float scaleY) {};

    // must implement in samples
    virtual void init() = 0;
    virtual void draw(int width, int height) = 0;
    virtual void destroy() = 0;

    constexpr static const float PI = 3.1415926;

protected:
    GLuint mVertexShader;
    GLuint mFragmentShader;
    GLuint mShaderProgram;
    int mSurfaceWidth;
    int mSurfaceHeight;
};

#endif //OPENGLES_GLBASE_H
