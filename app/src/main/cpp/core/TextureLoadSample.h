//
// Created by Zongcheng Chu on 7/21/24.
//

#ifndef OPENGLES_TEXTURELOADSAMPLE_H
#define OPENGLES_TEXTURELOADSAMPLE_H

#include <GLES3/gl3.h>
#include "GLBase.h"
#include "FormatDef.h"
#include "GLUtils.h"

class TextureLoadSample : public GLBase {
public:
    TextureLoadSample();
    virtual ~TextureLoadSample();
    void loadImage(NativeImage* image) override;

    // pure virtual functions
    virtual void init() override;
    virtual void draw(int width, int height) override;
    virtual void destroy() override;
private:
    GLuint mTextureID;
    GLint mSamplerLoc;
    NativeImage mImage;
};


#endif //OPENGLES_TEXTURELOADSAMPLE_H
