//
// Created by Zongcheng Chu on 7/21/24.
//

#pragma once

#define VERTEX_SHADER(...) "#version 300 es\n" #__VA_ARGS__
#define FRAGMENT_SHADER(...) "#version 300 es\n" #__VA_ARGS__

const char* TriangleVertexShader = VERTEX_SHADER(
       layout(location = 0) in vec4 vPosition;
       void main() {
           gl_Position = vPosition;
       }
);

const char* TriangleFragmentShader = FRAGMENT_SHADER(
         precision mediump float;
         out vec4 FragColor;
         void main() {
             FragColor = vec4 (0.0, 1.0, 0.0, 1.0);
         }
 );
