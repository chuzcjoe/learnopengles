//
// Created by Zongcheng Chu on 7/21/24.
//

#include "GLShaderSources.h"

// Triangle Shader
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
         FragColor = vec4(0.0, 1.0, 0.0, 1.0);
     }
);

// Texture Load Shader
const char* TextureLoadVertexShader = VERTEX_SHADER(
      layout(location = 0) in vec4 aPosition;
      layout(location = 1) in vec2 aTexCoord;
      out vec2 vTexCoord;
      void main() {
          gl_Position = aPosition;
          vTexCoord = aTexCoord; // Corrected typo from vTexcoord to aTexCoord
      }
);

const char* TextureLoadFragmentShader = FRAGMENT_SHADER(
        precision mediump float;
        in vec2 vTexCoord;
        uniform sampler2D sTexture;
        out vec4 FragColor;
        void main() {
            FragColor = texture(sTexture, vTexCoord);
        }
);
