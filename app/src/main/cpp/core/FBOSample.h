//
// Created by Zongcheng Chu on 7/26/24.
//

#ifndef OPENGLES_FBOSAMPLE_H
#define OPENGLES_FBOSAMPLE_H

#include "GLBase.h"
#include "GLUtils.h"
#include "FormatDef.h"

class FBOSample : public GLBase {
public:
    FBOSample();
    virtual ~FBOSample();

    virtual void loadImage(NativeImage* image) override;

    virtual void init() override;
    virtual void draw(int width, int height) override;
    virtual void destroy() override;

private:
    NativeImage mImage;

    GLuint mVAO[2];
    GLuint mVBO[3];
    GLuint mEBO;

    GLuint mOffScreenTextureID;
    GLuint mOnScreenTextureID;

    GLint mOnScreenSamplerLoc;

    // FrameBuffer related
    GLuint mFBO;
    GLuint mFBOProgram;
    GLuint mFBOVertexShader;
    GLuint mFBOFragmentShader;
    GLint mOffScreenSamplerLoc;

    GLfloat  mRatio;
};


#endif //OPENGLES_FBOSAMPLE_H
