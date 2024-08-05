//
// Created by Zongcheng Chu on 8/4/24.
//

#ifndef OPENGLES_TRANSFORMATIONSAMPLE_H
#define OPENGLES_TRANSFORMATIONSAMPLE_H

#include "GLBase.h"
#include "GLUtils.h"
#include "FormatDef.h"
#include "detail/type_mat2x2.hpp"
#include "detail//type_mat4x4.hpp"

class TransformationSample : public GLBase {
public:
    TransformationSample();
    virtual ~TransformationSample();

    virtual void loadImage(NativeImage* image) override;
    virtual void init() override;
    virtual void draw(int width, int height) override;
    virtual void destroy() override;

    void updateMVP(glm::mat4& mvp, int angleX, int angleY, float ratio);

private:
    NativeImage mImage;

    GLuint mTextureID;
    GLint mSampleLoc;
    GLint mMVPLoc;
    GLuint mVAO;
    GLuint mVBO;
    GLuint mEBO;
    glm::mat4 mMVPMatrix;

    int mAngleX;
    int mAngleY;
    float mScaleX;
    float mScaleY;
};


#endif //OPENGLES_TRANSFORMATIONSAMPLE_H
