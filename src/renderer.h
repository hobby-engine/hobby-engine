#ifndef _HOBBY_RENDERER_H
#define _HOBBY_RENDERER_H

#include "shader.h"
#include "color.h"
#include "texture.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "window.h"
#include "linmath.h"

typedef struct {
  hb_Window* window;

  hb_VertexBuffer vertexBuffer;
  hb_VertexBuffer indexBuffer;
  hb_VertexArray vertexArray;

  hb_Shader colorShader;
  hb_Shader textureShader;

  mat4x4 projection;

  hb_Color currentColor;

  u32 drawCalls, currentFrameDrawCalls;
  s32 circleResolution;
} hb_Renderer;

hb_Renderer* hb_createRenderer(hb_Window* window);
void hb_rendererStep(hb_Renderer* renderer);

void hb_drawClear(hb_Color color);
void hb_drawPresent();
void hb_drawSetColor(hb_Color color);
void hb_drawSetCircleResolution(u32 resolution);
void hb_drawSprite(hb_Sprite* sprite);
void hb_drawTexture(hb_Texture* texture, f32 x, f32 y);
void hb_drawTextureOffset(hb_Texture* texture, f32 x, f32 y, f32 ox, f32 oy);
void hb_drawTextureExt(hb_Texture* texture, f32 x, f32 y, f32 rot, f32 sx, f32 sy, f32 ox, f32 oy);
void hb_drawRectangleOutline(f32 x, f32 y, f32 width, f32 height);
void hb_drawRectangle(f32 x, f32 y, f32 width, f32 height);
void hb_drawEllipseOutline(f32 x, f32 y, f32 rx, f32 ry);
void hb_drawEllipse(f32 x, f32 y, f32 rx, f32 ey);
void hb_drawCircleOutline(f32 x, f32 y, f32 radius);
void hb_drawCircle(f32 x, f32 y, f32 radius);

#endif // _HOBBY_RENDERER_H
