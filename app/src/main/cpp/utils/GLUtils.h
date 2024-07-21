//
// Created by Zongcheng Chu on 7/21/24.
//

#ifndef OPENGLES_GLUTILS_H
#define OPENGLES_GLUTILS_H

#include <GLES3/gl3.h>
#include <stdlib.h>
#include "GLLog.h"

class GLUtils {
public:
    static GLuint LoadShader(GLenum shaderType, const char *pSource);
    static GLuint CreateProgram(const char *vertexShaderSource, const char* fragShaderSource, GLuint& vertexShaderHandle, GLuint& fragShaderHandle);
    static void CheckGLError(const char *pGLOperation);
};


#endif //OPENGLES_GLUTILS_H
