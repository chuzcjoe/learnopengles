//
// Created by Zongcheng Chu on 7/21/24.
//

#ifndef OPENGLES_GLCONTEXT_H
#define OPENGLES_GLCONTEXT_H

#include <GLES3/gl3.h>
#include "GLBase.h"
#include "TriangleSample.h"

// Singleton class
class GLContext {
private:
    GLContext();
    ~GLContext();
public:
    void OnSurfaceCreated();
    void OnSurfaceChanged(int width, int height);
    void OnDrawFrame();

    void setSample(int sample);

    static GLContext* getInstance();
    static void destroyInstance();

private:
    static GLContext* mContext;
    GLBase* mSample = nullptr;
    int mWidth;
    int mHeight;
};


#endif //OPENGLES_GLCONTEXT_H
