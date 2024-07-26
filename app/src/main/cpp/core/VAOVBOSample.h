//
// Created by Zongcheng Chu on 7/25/24.
//

#ifndef OPENGLES_VAOVBOSAMPLE_H
#define OPENGLES_VAOVBOSAMPLE_H

#include "GLBase.h"
#include "GLUtils.h"

class VAOVBOSample : public GLBase {
public:
    VAOVBOSample();
    virtual ~VAOVBOSample();

    virtual void init() override;
    virtual void draw() override;
    virtual void destroy() override;

private:
    GLuint mVAO;
    GLuint mVBO;
    GLuint mEBO;
};


#endif //OPENGLES_VAOVBOSAMPLE_H
