//
// Created by Zongcheng Chu on 7/21/24.
//

#ifndef OPENGLES_GLBASE_H
#define OPENGLES_GLBASE_H

#include <GLES3/gl3.h>

#define SAMPLE_TRIANGLE             0
#define SAMPLE_LOAD_TEXTURE         1

class GLBase {
public:
    GLBase() {}
    virtual ~GLBase() {}

    // must implement in samples
    virtual void init() = 0;
    virtual void draw() = 0;
    virtual void destroy() = 0;

protected:
    GLuint mVertexShader;
    GLuint mFragmentShader;
    GLuint mShaderProgram;
    int mSurfaceWidth;
    int mSurfaceHeight;
};

#endif //OPENGLES_GLBASE_H
