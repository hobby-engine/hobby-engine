#version 330

layout (location = 0) in vec2 ipos;
layout (location = 1) in vec3 icolor;
layout (location = 2) in vec2 iuv;

out vec4 color;
out vec2 uv;

uniform mat4 projection, transform;

void main() {
  gl_Position = projection * transform * vec4(ipos, 0., 1.);
  color = vec4(icolor, 1.);
  uv = iuv;
}
