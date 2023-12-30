#include "builtin_shaders.hh"

const char* vertexSource = R"glsl(
#version 330

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aUv;

out vec2 uv;

void main() {
  gl_Position = vec4(aPosition, 1.0);
  uv = aUv;
}
)glsl";

const char* fragmentSource = R"glsl(
#version 330

in vec2 uv;

out vec4 FragColor;

uniform sampler2D texture1;

void main() {
  FragColor = texture(texture1, uv);
}
)glsl";
