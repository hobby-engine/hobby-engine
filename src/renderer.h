#ifndef _HOBBY_RENDERER_H
#define _HOBBY_RENDERER_H

#include "shader.h"
#include "color.h"
#include "texture.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "window.h"
#include "linmath.h"

struct hb_Renderer {
  struct hb_Window* window;

  struct hb_VertexBuffer vertexBuffer;
  struct hb_VertexBuffer indexBuffer;
  struct hb_VertexArray vertexArray;

  struct hb_Shader colorShader;
  struct hb_Shader textureShader;

  mat4x4 projection;

  struct hb_Color currentColor;

  u32 drawCalls, currentFrameDrawCalls;
  s32 circleResolution;
};

struct hb_Renderer* hb_createRenderer(struct hb_Window* window);
void hb_rendererStep(struct hb_Renderer* renderer);

void hb_drawClear(struct hb_Color color);
void hb_drawPresent(struct hb_Renderer* renderer);
void hb_drawSetColor(struct hb_Renderer* renderer, struct hb_Color color);
void hb_drawSetCircleResolution(struct hb_Renderer* renderer, u32 resolution);
void hb_drawSprite(struct hb_Renderer* renderer, struct hb_Sprite* sprite);
void hb_drawTexture(
    struct hb_Renderer* renderer, struct hb_Texture* texture, f32 x, f32 y);
void hb_drawTextureOffset(
    struct hb_Renderer* renderer, struct hb_Texture* texture,
    f32 x, f32 y, f32 ox, f32 oy);
void hb_drawTextureExt(
  struct hb_Renderer* renderer, 
  struct hb_Texture* texture,
  f32 x, f32 y, f32 rot, f32 sx, f32 sy, f32 ox, f32 oy);
void hb_drawRectangleOutline(
  struct hb_Renderer* renderer, f32 x, f32 y, f32 width, f32 height);
void hb_drawRectangle(
  struct hb_Renderer* renderer, f32 x, f32 y, f32 width, f32 height);
void hb_drawEllipseOutline(
  struct hb_Renderer* renderer, f32 x, f32 y, f32 rx, f32 ry);
void hb_drawEllipse(struct hb_Renderer* renderer, f32 x, f32 y, f32 rx, f32 ey);
void hb_drawCircleOutline(
  struct hb_Renderer* renderer, f32 x, f32 y, f32 radius);
void hb_drawCircle(struct hb_Renderer* renderer, f32 x, f32 y, f32 radius);
void hb_drawPolygon(struct hb_Renderer* renderer, f32* vertices, u32 count);

#endif // _HOBBY_RENDERER_H
