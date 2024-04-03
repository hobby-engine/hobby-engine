#ifndef _HOBBY_RENDERER_H
#define _HOBBY_RENDERER_H

#include "shader.h"
#include "color.h"
#include "texture.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "window.h"
#include "linmath.h"

struct Renderer {
  struct Window* window;

  struct VertexBuffer vertexBuffer;
  struct VertexBuffer indexBuffer;
  struct VertexArray vertexArray;

  struct Shader colorShader;
  struct Shader textureShader;

  mat4x4 projection;

  struct Color currentColor;

  u32 drawCalls, currentFrameDrawCalls;
  s32 circleResolution;
};

struct Renderer* createRenderer(struct Window* window);
void rendererStep(struct Renderer* renderer);

void drawClear(struct Color color);
void drawPresent(struct Renderer* renderer);
void drawSetColor(struct Renderer* renderer, struct Color color);
void drawSetCircleResolution(struct Renderer* renderer, u32 resolution);
void drawSprite(struct Renderer* renderer, struct Sprite* sprite);
void drawTexture(
  struct Renderer* renderer, 
  struct Texture* texture,
  f32 x, f32 y, f32 rot, f32 sx, f32 sy, f32 ox, f32 oy);
void drawRectangleOutline(
  struct Renderer* renderer, f32 x, f32 y, f32 width, f32 height);
void drawRectangle(
  struct Renderer* renderer, f32 x, f32 y, f32 width, f32 height);
void drawEllipseOutline(
  struct Renderer* renderer, f32 x, f32 y, f32 rx, f32 ry);
void drawEllipse(struct Renderer* renderer, f32 x, f32 y, f32 rx, f32 ey);
void drawCircleOutline(
  struct Renderer* renderer, f32 x, f32 y, f32 radius);
void drawCircle(struct Renderer* renderer, f32 x, f32 y, f32 radius);
void drawPolygon(struct Renderer* renderer, f32* vertices, u32 count);

#endif // _HOBBY_RENDERER_H
