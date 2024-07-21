//
// Created by Zongcheng Chu on 7/21/24.
//

#ifndef OPENGLES_GLLOG_H
#define OPENGLES_GLLOG_H

#include <android/log.h>

#define LOG_TAG "OPENGLES3"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#endif //OPENGLES_GLLOG_H
