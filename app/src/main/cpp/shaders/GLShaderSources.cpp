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
      layout(location = 0) in vec3 aPosition;
      layout(location = 1) in vec2 aTexCoord;
      out vec2 vTexCoord;
      void main() {
          gl_Position = vec4(aPosition, 1.);
          vTexCoord = aTexCoord;
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


// VAO VBO Shader
const char* VAOVBOVertexShader = VERTEX_SHADER(
      layout(location = 0) in vec3 aPosition;
      layout(location = 1) in vec4 aColor;
      out vec4 vColor;
      void main() {
          gl_Position = vec4(aPosition, 1.0);
          vColor = aColor;
      }
);

const char* VAOVBOFragmentShader = FRAGMENT_SHADER(
        precision mediump float;
        in vec4 vColor;
        out vec4 FragColor;
        void main() {
            FragColor = vColor;
        }
);




// FrameBuffer Shader
const char* FBOOFFScreenVertexShader = VERTEX_SHADER(
       layout(location = 0) in vec3 aPosition;
       layout(location = 2) in vec2 aTexCoord;
       out vec2 vTexCoord;
       void main() {
           gl_Position = vec4(aPosition, 1.);
           vTexCoord = aTexCoord;
       }
);

const char* FBOOFFScreenFragmentShader = FRAGMENT_SHADER(
     precision mediump float;
     in vec2 vTexCoord;
     uniform sampler2D offScreenTexture;
     out vec4 FragColor;
     void main() {
         vec4 color = texture(offScreenTexture, vTexCoord);
         float gray = color.r * 0.299 + color.g * 0.587 + color.b * 0.114;
         FragColor = vec4(vec3(gray), 1.0);
     }
);

const char* FBOOFFScreenSharpenFragmentShader = FRAGMENT_SHADER(
     precision mediump float;
     in vec2 vTexCoord;
     uniform sampler2D offScreenTexture;
     out vec4 FragColor;

     void main() {
         vec2 texelSize = 1.0 / vec2(textureSize(offScreenTexture, 0));
         vec3 color = vec3(0.0);

         mat3 kernel = mat3(
                 0.0, -1.0, 0.0,
                 -1.0,  5.0, -1.0,
                 0.0, -1.0, 0.0
         );

         for (int i = -1; i <= 1; i++) {
             for (int j = -1; j <= 1; j++) {
                 vec2 offset = vec2(float(i), float(j)) * texelSize;
                 color += texture(offScreenTexture, vTexCoord + offset).rgb * kernel[i + 1][j + 1];
             }
         }

         FragColor = vec4(color, 1.0);
     }
);

const char* FBOONScreenVertexShader = VERTEX_SHADER(
       layout(location = 0) in vec3 aPosition;
       layout(location = 1) in vec2 aTexCoord;
       out vec2 vTexCoord;
       void main() {
           gl_Position = vec4(aPosition, 1.);
           vTexCoord = aTexCoord;
       }
);

const char* FBOONScreenFragmentShader = FRAGMENT_SHADER(
        precision mediump float;
        in vec2 vTexCoord;
        uniform sampler2D onScreenTexture;
        out vec4 FragColor;
        void main() {
            FragColor = texture(onScreenTexture, vTexCoord);
            // FragColor = vec4(0.0, 1.0, 0.0, 1.0);
        }
);