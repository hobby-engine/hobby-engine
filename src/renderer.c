#include "renderer.h"

#include <math.h>
#include <stdio.h>

#include "linmath.h"

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "hbmath.h"


struct Renderer* createRenderer(struct Window* window) {
  struct Renderer* renderer = malloc(sizeof(struct Renderer));
  renderer->window = window;
  renderer->vertexBuffer = createVertexBuffer(BUFFER_TYPE_ARRAY_BUFFER, false);
  renderer->indexBuffer = createVertexBuffer(BUFFER_TYPE_INDEX_BUFFER, false);
  renderer->vertexArray = createVertexArray();
  renderer->currentColor = (struct Color){1., 1., 1., 1.};
  renderer->colorShader = loadShader("res/color.vert", "res/color.frag");
  renderer->textureShader = loadShader("res/texture.vert", "res/texture.frag");
  renderer->drawCalls = 0;
  renderer->circleResolution = -1;
  mat4x4_identity(renderer->projection);

  return renderer;
}

void rendererStep(struct Renderer* renderer) {
  renderer->drawCalls = renderer->currentFrameDrawCalls;
  renderer->currentFrameDrawCalls = 0;

  mat4x4_identity(renderer->projection);
  mat4x4_ortho(
      renderer->projection,
      0, renderer->window->width, renderer->window->height, 0, -1, 1);
}

void drawClear(struct Color color) {
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void drawPresent(struct Renderer* renderer) {
  glfwSwapBuffers(renderer->window->glfwWindow);
}

void drawSetColor(struct Renderer* renderer, struct Color color) {
  renderer->currentColor = color;
}

void drawSetCircleResolution(struct Renderer* renderer, u32 resolution) {
  renderer->circleResolution = resolution;
}

static void drawTextureExt(
    struct Renderer* renderer, 
    struct Texture* texture,
    f32 x, f32 y, f32 rot, f32 sx, f32 sy, f32 ox, f32 oy) {
  s32 width = texture->width, height = texture->height;
  s32 left = -ox * sx, right = (width - ox) * sx;
  s32 top = -oy * sy, bottom = (height - oy) * sy;
  setVertexBufferData(&renderer->vertexBuffer, 4 * 4 * sizeof(f32), (f32[]){
    left, top,     0, 0,
    left,  bottom, 0, 1,
    right, bottom, 1, 1,
    right, top,    1, 0
  });
  //0 __3
  // |/|
  // --
  //1  2
  setVertexBufferData(&renderer->indexBuffer, 6 * sizeof(u32), (u32[]){
    0, 1, 2, 0, 2, 3 
  });

  setVertexArrayAttribute(
    &renderer->vertexArray, &renderer->vertexBuffer,
    0, 2, GL_FLOAT, sizeof(f32) * 4, 0);
  setVertexArrayAttribute(
    &renderer->vertexArray, &renderer->vertexBuffer,
    1, 2, GL_FLOAT, sizeof(f32) * 4, 2 * sizeof(f32));

  mat4x4 transform;
  mat4x4_identity(transform);
  mat4x4_translate(transform, x, y, 0);
  mat4x4_rotate_Z(transform, transform, rot);

  useShader(&renderer->textureShader);
  setShaderMat4(&renderer->textureShader, "projection", renderer->projection);
  setShaderMat4(&renderer->textureShader, "transform", transform);

  glBindTexture(GL_TEXTURE_2D, texture->glId);
  bindVertexBuffer(&renderer->indexBuffer);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  renderer->currentFrameDrawCalls++;
}

void drawSprite(struct Renderer* renderer, struct Sprite* sprite) {
  drawTextureExt(
      renderer,
      sprite->texture,
      sprite->x, sprite->y,
      sprite->rot,
      sprite->scalex, sprite->scaley,
      sprite->offsetx, sprite->offsety);
}

void drawTexture(
    struct Renderer* renderer, 
    struct Texture *texture,
    f32 x, f32 y, f32 rot, f32 sx, f32 sy, f32 ox, f32 oy) {
  drawTextureExt(renderer, texture, x, y, rot, sx, sy, ox, oy);
}

static void drawRectangleExt(
    struct Renderer* renderer, f32 x, f32 y, f32 width, f32 height) {
  setVertexBufferData(&renderer->vertexBuffer, 2 * 4 * sizeof(f32), (f32[]){
    0, 0,
    0, height,
    width, height,
    width, 0,
  });
  setVertexBufferData(&renderer->indexBuffer, 6 * sizeof(u32), (u32[]){
    0, 1, 2, 0, 2, 3 
  });

  setVertexArrayAttribute(
    &renderer->vertexArray, &renderer->vertexBuffer,
    0, 2, GL_FLOAT, sizeof(f32) * 2, 0);

  mat4x4 transform;
  mat4x4_identity(transform);
  mat4x4_translate(transform, x, y, 0);

  useShader(&renderer->colorShader);
  setShaderMat4(&renderer->colorShader, "projection", renderer->projection);
  setShaderMat4(&renderer->colorShader, "transform", transform);
  setShaderColor(&renderer->colorShader, "color", renderer->currentColor);

  bindVertexBuffer(&renderer->indexBuffer);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  renderer->currentFrameDrawCalls++;
}

void drawRectangleOutline(
    struct Renderer* renderer, f32 x, f32 y, f32 width, f32 height) {
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  drawRectangleExt(renderer, x, y, width, height);
}

void drawRectangle(
    struct Renderer* renderer, f32 x, f32 y, f32 width, f32 height) {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  drawRectangleExt(renderer, x, y, width, height);
}

static void drawEllipseExt(
    struct Renderer* renderer, u32 mode, f32 x, f32 y, f32 rx, f32 ry) {
  s32 circleResolution = renderer->circleResolution;
  // Manually figure something out
  if (circleResolution == -1) {
    circleResolution = fmax(2 * PI * sqrt((rx + ry) / 2), 8);
  }

  f32 points[circleResolution * 2];

  for (s32 i = 0; i < circleResolution; i++) {
    s32 index = i * 2;
    f32 angle = ((f32)i / circleResolution) * TAU;
    points[index]   = cos(angle) * rx;
    points[index+1] = sin(angle) * ry;
  }

  setVertexBufferData(&renderer->vertexBuffer, 2 * circleResolution * sizeof(f32), points);

  setVertexArrayAttribute(
    &renderer->vertexArray, &renderer->vertexBuffer,
    0, 2, GL_FLOAT, sizeof(f32) * 2, 0);

  mat4x4 transform;
  mat4x4_identity(transform);
  mat4x4_translate(transform, x, y, 0);

  useShader(&renderer->colorShader);
  setShaderMat4(&renderer->colorShader, "projection", renderer->projection);
  setShaderMat4(&renderer->colorShader, "transform", transform);
  setShaderColor(&renderer->colorShader, "color", renderer->currentColor);

  bindVertexArray(&renderer->vertexArray);
  glDrawArrays(mode, 0, circleResolution);

  renderer->currentFrameDrawCalls++;
}

void drawEllipseOutline(
    struct Renderer* renderer, f32 x, f32 y, f32 rx, f32 ry) {
  drawEllipseExt(renderer, GL_LINE_LOOP, x, y, rx, ry);
}

void drawEllipse(
    struct Renderer* renderer, f32 x, f32 y, f32 rx, f32 ry) {
  drawEllipseExt(renderer, GL_TRIANGLE_FAN, x, y, rx, ry);
}

void drawCircleOutline(
    struct Renderer* renderer, f32 x, f32 y, f32 radius) {
  drawEllipseExt(renderer, GL_LINE_LOOP, x, y, radius, radius);
}

void drawCircle(struct Renderer* renderer, f32 x, f32 y, f32 radius) {
  drawEllipseExt(renderer, GL_TRIANGLE_FAN, x, y, radius, radius);
}

void drawPolygon(struct Renderer* renderer, f32* vertices, u32 count) {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  setVertexBufferData(&renderer->vertexBuffer, count * sizeof(f32), vertices);

  setVertexArrayAttribute(
    &renderer->vertexArray, &renderer->vertexBuffer,
    0, 2, GL_FLOAT, sizeof(f32) * 2, 0);

  mat4x4 transform;
  mat4x4_identity(transform);

  useShader(&renderer->colorShader);
  setShaderMat4(&renderer->colorShader, "projection", renderer->projection);
  setShaderMat4(&renderer->colorShader, "transform", transform);
  setShaderColor(&renderer->colorShader, "color", renderer->currentColor);

  bindVertexArray(&renderer->vertexArray);
  glDrawArrays(GL_TRIANGLES, 0, count);

  renderer->currentFrameDrawCalls++;
}
