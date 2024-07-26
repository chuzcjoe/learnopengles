//
// Created by Zongcheng Chu on 7/21/24.
//

#pragma once

#define VERTEX_SHADER(...) "#version 300 es\n" #__VA_ARGS__
#define FRAGMENT_SHADER(...) "#version 300 es\n" #__VA_ARGS__

// Triangle Shader
extern const char* TriangleVertexShader;
extern const char* TriangleFragmentShader;

// Texture Load Shader
extern const char* TextureLoadVertexShader;
extern const char* TextureLoadFragmentShader;

// VAO VBO Shader
extern const char* VAOVBOVertexShader;
extern const char* VAOVBOFragmentShader;