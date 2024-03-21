#include <stdio.h>
#include <stdlib.h>

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "linmath.h"

#include "engine.h"
#include "basic_types.h"
#include "log.h"
#include "shader.h"
#include "time.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "window.h"

#define WIDTH 800
#define HEIGHT 600

s32 main() {
  hb_Window* window = hb_createWindow("Hobby", WIDTH, HEIGHT);
  hb_Engine engine = hb_createEngine(window);
  hb_Shader shaderProgram = hb_loadShader("res/color.vert", "res/color.frag");

  u32 varr;
  glGenVertexArrays(1, &varr);

  hb_VertexArray vertexArray = hb_createVertexArray();

  hb_VertexBuffer vertexBuffer = hb_createVertexBuffer(
      hb_BUFFER_TYPE_ARRAY_BUFFER, true);
  hb_setVertexBufferData(&vertexBuffer, 5 * 4 * sizeof(f32), (f32[]) {
    0,   0,     1, 1, 1,
    0,   100,   1, 1, 1,
    100, 100,   1, 1, 1,
    100, 0,     1, 1, 1,
  });
  hb_bindVertexBuffer(&vertexBuffer);

  size_t stride = 5 * sizeof(f32);
  hb_setVertexArrayAttribute(
    &vertexArray, &vertexBuffer, 0, 2, GL_FLOAT, stride, 0);
  hb_setVertexArrayAttribute(
    &vertexArray, &vertexBuffer, 1, 3, GL_FLOAT, stride, 2 * sizeof(f32));

  f32 rotation = 0;

  while (!glfwWindowShouldClose(window->glfwWindow)) {
    hb_engineStep(&engine);

    f32 dt = engine.time->deltaTime;

    glfwPollEvents();

    rotation += dt;

    char title[16];
    sprintf(title, "%.5f", engine.time->fps);
    hb_windowSetTitle(window, title);

    glClearColor(1, 0.3, 0.6, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    mat4x4 projection, transform;
    mat4x4_identity(projection);
    mat4x4_identity(transform);
    mat4x4_ortho(projection, 0, window->width, window->height, 0, -1, 1);
    mat4x4_translate(transform, 150, 150, 0);
    mat4x4_rotate_Z(transform, transform, rotation);

    hb_useShader(&shaderProgram);
    hb_setShaderMat4(&shaderProgram, "projection", projection);
    hb_setShaderMat4(&shaderProgram, "transform", transform);
    hb_bindVertexArray(&vertexArray);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glfwSwapBuffers(window->glfwWindow);
  }

  hb_destroyVertexBuffer(&vertexBuffer);
  hb_destroyVertexArray(&vertexArray);

  hb_destroyShader(&shaderProgram);
  hb_destroyEngine(&engine);
  return 0;
}
