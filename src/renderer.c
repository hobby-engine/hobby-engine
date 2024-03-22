#include "renderer.h"
#include "linmath.h"
#include "vertex_array.h"
#include "vertex_buffer.h"

static hb_Renderer* singleton;

hb_Renderer* hb_createRenderer(hb_Window* window) {
  hb_Renderer* renderer = (hb_Renderer*)malloc(sizeof(hb_Renderer));
  renderer->window = window;
  renderer->vertexBuffer = hb_createVertexBuffer(hb_BUFFER_TYPE_ARRAY_BUFFER, false);
  renderer->indexBuffer = hb_createVertexBuffer(hb_BUFFER_TYPE_INDEX_BUFFER, false);
  renderer->vertexArray = hb_createVertexArray();
  renderer->currentColor = (hb_Color){1., 1., 1., 1.};
  renderer->colorShader = hb_loadShader("res/color.vert", "res/color.frag");
  renderer->textureShader = hb_loadShader("res/texture.vert", "res/texture.frag");
  renderer->drawCalls = 0;
  mat4x4_identity(renderer->projection);

  singleton = renderer;

  return renderer;
}

void hb_rendererStep(hb_Renderer* renderer) {
  renderer->drawCalls = renderer->currentFrameDrawCalls;
  renderer->currentFrameDrawCalls = 0;

  mat4x4_identity(renderer->projection);
  mat4x4_ortho(
      renderer->projection,
      0, singleton->window->width, singleton->window->height, 0, -1, 1);
}

void hb_drawTexture(hb_Texture* texture, f32 x, f32 y) {
  hb_setVertexBufferData(&singleton->vertexBuffer, 4 * 4 * sizeof(f32), (f32[]){
    0, 0,                            0, 0,
    0, texture->height,              0, 1,
    texture->width, texture->height, 1, 1,
    texture->width, 0,               1, 0
  });
  //0 __3
  // |/|
  // --
  //1  2
  hb_setVertexBufferData(&singleton->indexBuffer, 6 * sizeof(u32), (u32[]){
    0, 1, 2, 0, 2, 3 
  });

  hb_setVertexArrayAttribute(
    &singleton->vertexArray, &singleton->vertexBuffer,
    0, 2, GL_FLOAT, sizeof(f32) * 4, 0);
  hb_setVertexArrayAttribute(
    &singleton->vertexArray, &singleton->vertexBuffer,
    1, 2, GL_FLOAT, sizeof(f32) * 4, 2 * sizeof(f32));

  mat4x4 transform;
  mat4x4_identity(transform);
  mat4x4_translate(transform, x, y, 0);

  hb_useShader(&singleton->textureShader);
  hb_setShaderMat4(&singleton->textureShader, "projection", singleton->projection);
  hb_setShaderMat4(&singleton->textureShader, "transform", transform);

  glBindTexture(GL_TEXTURE_2D, texture->glId);
  hb_bindVertexBuffer(&singleton->indexBuffer);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  singleton->currentFrameDrawCalls++;
}

static void drawRectangle(u32 mode, f32 x, f32 y, f32 width, f32 height) {
  hb_setVertexBufferData(&singleton->vertexBuffer, 2 * 4 * sizeof(f32), (f32[]){
    0, 0,
    0, height,
    width, height,
    width, 0,
  });
  hb_setVertexBufferData(&singleton->indexBuffer, 6 * sizeof(u32), (u32[]){
    0, 1, 2, 0, 2, 3 
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

  hb_bindVertexBuffer(&singleton->indexBuffer);
  glDrawElements(mode, 6, GL_UNSIGNED_INT, 0);

  singleton->currentFrameDrawCalls++;
}

void hb_drawRectangleOutline(f32 x, f32 y, f32 width, f32 height) {
  drawRectangle(GL_LINE_LOOP, x, y, width, height);
}

void hb_drawRectangle(f32 x, f32 y, f32 width, f32 height) {
  drawRectangle(GL_TRIANGLES, x, y, width, height);
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
