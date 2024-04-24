#version 330

layout (location = 0) in vec2 ipos;
layout (location = 1) in vec2 iuv;

uniform mat4 proj, trans;

out vec2 uv;

void main() {
  gl_Position = proj * trans * vec4(ipos, 0., 1.);

  uv = iuv;
}
