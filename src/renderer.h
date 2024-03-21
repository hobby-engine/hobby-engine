#ifndef _HOBBY_RENDERER_H
#define _HOBBY_RENDERER_H

#include "shader.h"
#include "color.h"
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

  mat4x4 projection;

  hb_Color currentColor;
} hb_Renderer;

hb_Renderer* hb_createRenderer(hb_Window* window);
void hb_rendererStep(hb_Renderer* renderer);

f32* hb_colorToArray(hb_Color color);

void hb_drawClear(hb_Color color);
void hb_drawPresent();
void hb_drawSetColor(hb_Color color);
void hb_drawRectangleOutline(f32 x, f32 y, f32 width, f32 height);
void hb_drawRectangle(f32 x, f32 y, f32 width, f32 height);

#endif // _HOBBY_RENDERER_H
