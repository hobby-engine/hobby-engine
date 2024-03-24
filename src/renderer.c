#include "renderer.h"

#include <math.h>
#include <stdio.h>

#include "linmath.h"

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "hbmath.h"


struct hb_Renderer* hb_createRenderer(struct hb_Window* window) {
  struct hb_Renderer* renderer = malloc(sizeof(struct hb_Renderer));
  renderer->window = window;
  renderer->vertexBuffer = hb_createVertexBuffer(hb_BUFFER_TYPE_ARRAY_BUFFER, false);
  renderer->indexBuffer = hb_createVertexBuffer(hb_BUFFER_TYPE_INDEX_BUFFER, false);
  renderer->vertexArray = hb_createVertexArray();
  renderer->currentColor = (struct hb_Color){1., 1., 1., 1.};
  renderer->colorShader = hb_loadShader("res/color.vert", "res/color.frag");
  renderer->textureShader = hb_loadShader("res/texture.vert", "res/texture.frag");
  renderer->drawCalls = 0;
  renderer->circleResolution = -1;
  mat4x4_identity(renderer->projection);

  return renderer;
}

void hb_rendererStep(struct hb_Renderer* renderer) {
  renderer->drawCalls = renderer->currentFrameDrawCalls;
  renderer->currentFrameDrawCalls = 0;

  mat4x4_identity(renderer->projection);
  mat4x4_ortho(
      renderer->projection,
      0, renderer->window->width, renderer->window->height, 0, -1, 1);
}

void hb_drawClear(struct hb_Color color) {
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void hb_drawPresent(struct hb_Renderer* renderer) {
  glfwSwapBuffers(renderer->window->glfwWindow);
}

void hb_drawSetColor(struct hb_Renderer* renderer, struct hb_Color color) {
  renderer->currentColor = color;
}

void hb_drawSetCircleResolution(struct hb_Renderer* renderer, u32 resolution) {
  renderer->circleResolution = resolution;
}

static void drawTexture(
    struct hb_Renderer* renderer, 
    struct hb_Texture* texture,
    f32 x, f32 y, f32 rot, f32 sx, f32 sy, f32 ox, f32 oy) {
  s32 width = texture->width, height = texture->height;
  s32 left = -ox * sx, right = (width - ox) * sx;
  s32 top = -oy * sy, bottom = (height - oy) * sy;
  hb_setVertexBufferData(&renderer->vertexBuffer, 4 * 4 * sizeof(f32), (f32[]){
    left, top,     0, 0,
    left,  bottom, 0, 1,
    right, bottom, 1, 1,
    right, top,    1, 0
  });
  //0 __3
  // |/|
  // --
  //1  2
  hb_setVertexBufferData(&renderer->indexBuffer, 6 * sizeof(u32), (u32[]){
    0, 1, 2, 0, 2, 3 
  });

  hb_setVertexArrayAttribute(
    &renderer->vertexArray, &renderer->vertexBuffer,
    0, 2, GL_FLOAT, sizeof(f32) * 4, 0);
  hb_setVertexArrayAttribute(
    &renderer->vertexArray, &renderer->vertexBuffer,
    1, 2, GL_FLOAT, sizeof(f32) * 4, 2 * sizeof(f32));

  mat4x4 transform;
  mat4x4_identity(transform);
  mat4x4_translate(transform, x, y, 0);
  mat4x4_rotate_Z(transform, transform, rot);

  hb_useShader(&renderer->textureShader);
  hb_setShaderMat4(&renderer->textureShader, "projection", renderer->projection);
  hb_setShaderMat4(&renderer->textureShader, "transform", transform);

  glBindTexture(GL_TEXTURE_2D, texture->glId);
  hb_bindVertexBuffer(&renderer->indexBuffer);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  renderer->currentFrameDrawCalls++;
}

void hb_drawSprite(struct hb_Renderer* renderer, struct hb_Sprite* sprite) {
  drawTexture(
      renderer,
      sprite->texture,
      sprite->x, sprite->y,
      sprite->rot,
      sprite->scalex, sprite->scaley,
      sprite->offsetx, sprite->offsety);
}

void hb_drawTexture(
    struct hb_Renderer* renderer, 
    struct hb_Texture *texture,
    f32 x, f32 y, f32 rot, f32 sx, f32 sy, f32 ox, f32 oy) {
  drawTexture(renderer, texture, x, y, rot, sx, sy, ox, oy);
}

static void drawRectangle(
    struct hb_Renderer* renderer, f32 x, f32 y, f32 width, f32 height) {
  hb_setVertexBufferData(&renderer->vertexBuffer, 2 * 4 * sizeof(f32), (f32[]){
    0, 0,
    0, height,
    width, height,
    width, 0,
  });
  hb_setVertexBufferData(&renderer->indexBuffer, 6 * sizeof(u32), (u32[]){
    0, 1, 2, 0, 2, 3 
  });

  hb_setVertexArrayAttribute(
    &renderer->vertexArray, &renderer->vertexBuffer,
    0, 2, GL_FLOAT, sizeof(f32) * 2, 0);

  mat4x4 transform;
  mat4x4_identity(transform);
  mat4x4_translate(transform, x, y, 0);

  hb_useShader(&renderer->colorShader);
  hb_setShaderMat4(&renderer->colorShader, "projection", renderer->projection);
  hb_setShaderMat4(&renderer->colorShader, "transform", transform);
  hb_setShaderColor(&renderer->colorShader, "color", renderer->currentColor);

  hb_bindVertexBuffer(&renderer->indexBuffer);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  renderer->currentFrameDrawCalls++;
}

void hb_drawRectangleOutline(
    struct hb_Renderer* renderer, f32 x, f32 y, f32 width, f32 height) {
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  drawRectangle(renderer, x, y, width, height);
}

void hb_drawRectangle(
    struct hb_Renderer* renderer, f32 x, f32 y, f32 width, f32 height) {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  drawRectangle(renderer, x, y, width, height);
}

static void drawEllipse(
    struct hb_Renderer* renderer, u32 mode, f32 x, f32 y, f32 rx, f32 ry) {
  s32 circleResolution = renderer->circleResolution;
  // Manually figure something out
  if (circleResolution == -1) {
    circleResolution = fmax(2 * hb_PI * sqrt((rx + ry) / 2), 8);
  }

  f32 points[circleResolution * 2];

  for (s32 i = 0; i < circleResolution; i++) {
    s32 index = i * 2;
    f32 angle = ((f32)i / circleResolution) * hb_TAU;
    points[index]   = cos(angle) * rx;
    points[index+1] = sin(angle) * ry;
  }

  hb_setVertexBufferData(&renderer->vertexBuffer, 2 * circleResolution * sizeof(f32), points);

  hb_setVertexArrayAttribute(
    &renderer->vertexArray, &renderer->vertexBuffer,
    0, 2, GL_FLOAT, sizeof(f32) * 2, 0);

  mat4x4 transform;
  mat4x4_identity(transform);
  mat4x4_translate(transform, x, y, 0);

  hb_useShader(&renderer->colorShader);
  hb_setShaderMat4(&renderer->colorShader, "projection", renderer->projection);
  hb_setShaderMat4(&renderer->colorShader, "transform", transform);
  hb_setShaderColor(&renderer->colorShader, "color", renderer->currentColor);

  hb_bindVertexArray(&renderer->vertexArray);
  glDrawArrays(mode, 0, circleResolution);

  renderer->currentFrameDrawCalls++;
}

void hb_drawEllipseOutline(
    struct hb_Renderer* renderer, f32 x, f32 y, f32 rx, f32 ry) {
  drawEllipse(renderer, GL_LINE_LOOP, x, y, rx, ry);
}

void hb_drawEllipse(
    struct hb_Renderer* renderer, f32 x, f32 y, f32 rx, f32 ry) {
  drawEllipse(renderer, GL_TRIANGLE_FAN, x, y, rx, ry);
}

void hb_drawCircleOutline(
    struct hb_Renderer* renderer, f32 x, f32 y, f32 radius) {
  drawEllipse(renderer, GL_LINE_LOOP, x, y, radius, radius);
}

void hb_drawCircle(struct hb_Renderer* renderer, f32 x, f32 y, f32 radius) {
  drawEllipse(renderer, GL_TRIANGLE_FAN, x, y, radius, radius);
}

void hb_drawPolygon(struct hb_Renderer* renderer, f32* vertices, u32 count) {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  hb_setVertexBufferData(&renderer->vertexBuffer, count * sizeof(f32), vertices);

  hb_setVertexArrayAttribute(
    &renderer->vertexArray, &renderer->vertexBuffer,
    0, 2, GL_FLOAT, sizeof(f32) * 2, 0);

  mat4x4 transform;
  mat4x4_identity(transform);

  hb_useShader(&renderer->colorShader);
  hb_setShaderMat4(&renderer->colorShader, "projection", renderer->projection);
  hb_setShaderMat4(&renderer->colorShader, "transform", transform);
  hb_setShaderColor(&renderer->colorShader, "color", renderer->currentColor);

  hb_bindVertexArray(&renderer->vertexArray);
  glDrawArrays(GL_TRIANGLES, 0, count);

  renderer->currentFrameDrawCalls++;
}
