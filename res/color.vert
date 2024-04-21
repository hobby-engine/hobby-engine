#version 330

layout (location = 0) in vec2 ipos;

uniform mat4 proj, trans;

void main() {
  gl_Position = proj * trans * vec4(ipos, 0., 1.);
}
