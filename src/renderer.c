#include "renderer.h"

#include <math.h>
#include <stdio.h>

#include "linmath.h"

#include "vertex_array.h"
#include "vertex_buffer.h"

#define PI 3.14159265358979323846
#define TAU (PI * 2)

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
  renderer->circleResolution = 24;
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

void hb_drawSetCircleResolution(u32 resolution) {
  singleton->circleResolution = resolution;
}

static void drawTexture(hb_Texture* texture, f32 x, f32 y, f32 rot, f32 sx, f32 sy, f32 ox, f32 oy) {
  s32 width = texture->width, height = texture->height;
  s32 left = -ox * sx, right = (width - ox) * sx;
  s32 top = -oy * sy, bottom = (height - oy) * sy;
  hb_setVertexBufferData(&singleton->vertexBuffer, 4 * 4 * sizeof(f32), (f32[]){
    left, top,     0, 0,
    left,  bottom, 0, 1,
    right, bottom, 1, 1,
    right, top,    1, 0
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
  mat4x4_rotate_Z(transform, transform, rot);

  hb_useShader(&singleton->textureShader);
  hb_setShaderMat4(&singleton->textureShader, "projection", singleton->projection);
  hb_setShaderMat4(&singleton->textureShader, "transform", transform);

  glBindTexture(GL_TEXTURE_2D, texture->glId);
  hb_bindVertexBuffer(&singleton->indexBuffer);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  singleton->currentFrameDrawCalls++;
}

void hb_drawSprite(hb_Sprite* sprite) {
  drawTexture(
      &sprite->texture,
      sprite->x, sprite->y,
      sprite->rot,
      sprite->scalex, sprite->scaley,
      sprite->offsetx, sprite->offsety);
}

void hb_drawTexture(hb_Texture *texture, f32 x, f32 y) {
  drawTexture(texture, x, y, 0, 1, 1, 0, 0);
}

void hb_drawTextureOffset(hb_Texture *texture, f32 x, f32 y, f32 ox, f32 oy) {
  drawTexture(texture, x, y, 0, 1, 1, ox, oy);
}

void hb_drawTextureExt(hb_Texture *texture, f32 x, f32 y, f32 rot, f32 sx, f32 sy, f32 ox, f32 oy) {
  drawTexture(texture, x, y, rot, sx, sy, ox, oy);
}

static void drawRectangle(f32 x, f32 y, f32 width, f32 height) {
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
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  singleton->currentFrameDrawCalls++;
}

void hb_drawRectangleOutline(f32 x, f32 y, f32 width, f32 height) {
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  drawRectangle(x, y, width, height);
}

void hb_drawRectangle(f32 x, f32 y, f32 width, f32 height) {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  drawRectangle(x, y, width, height);
}

static void drawEllipse(u32 mode, f32 x, f32 y, f32 rx, f32 ry) {
  const u32 circleResolution = singleton->circleResolution;

  f32 points[circleResolution * 2];

  for (u32 i = 0; i < circleResolution; i++) {
    u32 index = i * 2;
    f32 angle = ((f32)i / circleResolution) * TAU;
    points[index]   = cos(angle) * rx;
    points[index+1] = sin(angle) * ry;
  }

  hb_setVertexBufferData(&singleton->vertexBuffer, 2 * circleResolution * sizeof(f32), points);

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
  glDrawArrays(mode, 0, circleResolution);

  singleton->currentFrameDrawCalls++;
}

void hb_drawEllipseOutline(f32 x, f32 y, f32 rx, f32 ry) {
  drawEllipse(GL_LINE_LOOP, x, y, rx, ry);
}

void hb_drawEllipse(f32 x, f32 y, f32 rx, f32 ry) {
  drawEllipse(GL_TRIANGLE_FAN, x, y, rx, ry);
}

void hb_drawCircleOutline(f32 x, f32 y, f32 radius) {
  drawEllipse(GL_LINE_LOOP, x, y, radius, radius);
}

void hb_drawCircle(f32 x, f32 y, f32 radius) {
  drawEllipse(GL_TRIANGLE_FAN, x, y, radius, radius);
}
