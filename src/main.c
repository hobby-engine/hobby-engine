#include <stdio.h>
#include <stdlib.h>

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "linmath.h"

#include "basic_types.h"
#include "shader.h"
#include "time.h"

#define WIDTH 800
#define HEIGHT 600

#define TEXTURE_SHADER_VERT "res/texture.vs"
#define TEXTURE_SHADER_FRAG "res/texture.fs"

f32 vertices[] = {
// Pos        Color      Uv
  0,   0,     1, 1, 1,   0, 0,
  0,   100,   1, 1, 1,   0, 1,
  100, 100,   1, 1, 1,   1, 1,
  100, 0,     1, 1, 1,   1, 0,
};

s32 window_width, window_height;

void onFramebufferSizeChanged(GLFWwindow* window, s32 width, s32 height) {
  glViewport(0, 0, width, height);
  window_width = width;
  window_height = height;
}

int main() {
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW.\n");
    exit(1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GLFW window", NULL, NULL);
  if (!window) {
    fprintf(stderr, "Failed to create window.\n");
    glfwTerminate();
    exit(1);
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD.\n");
    exit(1);
  }

  glfwSetFramebufferSizeCallback(window, onFramebufferSizeChanged);

  hb_ShaderProgram shaderProgram = hb_loadShaderProgram(
      "res/texture.vert", "res/texture.frag");

  u32 varr;
  glGenVertexArrays(1, &varr);

  u32 vbuf;
  glGenBuffers(1, &vbuf);
  glBindVertexArray(varr);
  glBindBuffer(GL_ARRAY_BUFFER, vbuf);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  size_t stride = 7 * sizeof(f32);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(f32)));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(5 * sizeof(f32)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  hb_Time time = hb_createTime();
  f32 rotation = 0;

  while (!glfwWindowShouldClose(window)) {
    hb_step(&time);

    f32 dt = time.deltaTime;

    glfwPollEvents();

    rotation += dt;

    glClearColor(1, 0.3, 0.6, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    mat4x4 projection, transform;
    mat4x4_identity(projection);
    mat4x4_identity(transform);
    mat4x4_ortho(projection, 0, window_width, window_height, 0, -1, 1);
    mat4x4_translate(transform, 150, 150, 0);
    mat4x4_rotate_Z(transform, transform, rotation);

    hb_useShaderProgram(&shaderProgram);
    hb_setShaderProgramMat4(&shaderProgram, "projection", projection);
    hb_setShaderProgramMat4(&shaderProgram, "transform", transform);
    glBindVertexArray(varr);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glfwSwapBuffers(window);
  }

  hb_destroyShaderProgram(&shaderProgram);

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
