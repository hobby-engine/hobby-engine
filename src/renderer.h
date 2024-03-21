#ifndef _HOBBY_RENDERER_H
#define _HOBBY_RENDERER_H

#include "shader.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "window.h"

typedef struct {
  float r, g, b, a;
} hb_Color;

typedef struct {
  hb_Window* window;

  hb_VertexBuffer vertexBuffer;
  hb_VertexBuffer indexBuffer;
  hb_VertexArray vertexArray;

  hb_Shader colorShader;

  hb_Color currentColor;
} hb_Renderer;

hb_Renderer* hb_createRenderer(hb_Window* window);
void hb_drawClear(hb_Color color);
void hb_drawPresent();
void hb_drawSetColor(hb_Color color);
void hb_drawRectangleOutline(f32 x, f32 y, f32 width, f32 height);
void hb_drawRectangle(f32 x, f32 y, f32 width, f32 height);

#endif // _HOBBY_RENDERER_H
