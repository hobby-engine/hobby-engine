#version 330

layout (location = 0) in vec2 ipos;

uniform mat4 projection, transform;

void main() {
  gl_Position = projection * transform * vec4(ipos, 0., 1.);
}
