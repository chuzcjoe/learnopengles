//
// Created by Zongcheng Chu on 7/21/24.
//

#ifndef OPENGLES_FORMATDEF_H
#define OPENGLES_FORMATDEF_H

#include "stdint.h"
#include <algorithm>

#define IMAGE_FORMAT_RGBA       0

struct NativeImage {
    int width;
    int height;
    int format;
    uint8_t* planes[3];

    NativeImage() {
        width = 0;
        height = 0;
        format = 0;
        planes[0] = nullptr;
        planes[1] = nullptr;
        planes[2] = nullptr;
    }
};

class NativeImageUtils {
public:
    static void copyImage(NativeImage* src, NativeImage* dst) {
        if (src == nullptr || src->planes[0] == nullptr ||
            src->width != dst->width || src->height != dst->height ||
            src->format != dst->format) {
                return;
        }

        if (dst->planes[0] == nullptr) allocateMemoryForImage(dst);

        switch (src->format) {
            case IMAGE_FORMAT_RGBA:
                std::copy(src->planes[0],src->planes[0] + (src->width * src->height * 4),dst->planes[0]);
                break;
            default:
                break;
        }
    }

    static void allocateMemoryForImage(NativeImage* image) {
        if (image->width == 0 || image->height == 0) return;

        switch (image->format) {
            case IMAGE_FORMAT_RGBA:
                image->planes[0] = new uint8_t[image->width * image->height * 4];
                break;
            default:
                break;
        }
    }
};


#endif //OPENGLES_FORMATDEF_H
