//
// Created by Zongcheng Chu on 7/21/24.
//

#ifndef OPENGLES_TRIANGLESAMPLE_H
#define OPENGLES_TRIANGLESAMPLE_H

#include "GLBase.h"
#include "GLUtils.h"

class TriangleSample : public GLBase{
public:
    TriangleSample();
    virtual ~TriangleSample();

    virtual void init() override;
    virtual void draw(int width, int height) override;
    virtual void destroy() override;
};


#endif //OPENGLES_TRIANGLESAMPLE_H
