#include "renderer.h"
#include "linmath.h"
#include "vertex_array.h"
#include "vertex_buffer.h"

static hb_Renderer* singleton;

hb_Renderer* hb_createRenderer(hb_Window* window) {
  hb_Renderer* renderer = (hb_Renderer*)malloc(sizeof(hb_Renderer));
  renderer->window = window;

  renderer->vertexBuffer = hb_createVertexBuffer(hb_BUFFER_TYPE_ARRAY_BUFFER, false);
  renderer->vertexArray = hb_createVertexArray();
  renderer->currentColor = (hb_Color){1., 1., 1., 1.};

  renderer->colorShader = hb_loadShader("res/color.vert", "res/color.frag");

  mat4x4_identity(renderer->projection);

  singleton = renderer;

  return renderer;
}

void hb_rendererStep(hb_Renderer* renderer) {
  mat4x4_identity(renderer->projection);
  mat4x4_ortho(
      renderer->projection,
      0, singleton->window->width, singleton->window->height, 0, -1, 1);
}

static void drawRectangle(u32 mode, f32 x, f32 y, f32 width, f32 height) {
  hb_setVertexBufferData(&singleton->vertexBuffer, 2 * 4 * sizeof(f32), (f32[]){
    0, 0,
    0, height,
    width, height,
    width, 0,
  });

  hb_setVertexArrayAttribute(
    &singleton->vertexArray, &singleton->vertexBuffer,
    0, 2, GL_FLOAT, sizeof(f32) * 2, 0);

  mat4x4 transform;
  mat4x4_identity(transform);
  mat4x4_translate(transform, x, y, 0);

  hb_useShader(&singleton->colorShader);
  hb_setShaderMat4(&singleton->colorShader, "projection", singleton->projection);
  hb_setShaderMat4(&singleton->colorShader, "transform", transform);
  hb_setShaderColor(&singleton->colorShader, "color", singleton->currentColor);
  hb_bindVertexArray(&singleton->vertexArray);
  glDrawArrays(mode, 0, 4);
}

void hb_drawRectangleOutline(f32 x, f32 y, f32 width, f32 height) {
  drawRectangle(GL_LINE_LOOP, x, y, width, height);
}

void hb_drawRectangle(f32 x, f32 y, f32 width, f32 height) {
  drawRectangle(GL_TRIANGLE_FAN, x, y, width, height);
}

void hb_drawClear(hb_Color color) {
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void hb_drawPresent() {
  glfwSwapBuffers(singleton->window->glfwWindow);
}

void hb_drawSetColor(hb_Color color) {
  singleton->currentColor = color;
}
