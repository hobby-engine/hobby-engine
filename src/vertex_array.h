#ifndef _HOBBY_VERTEX_ARRAY_H
#define _HOBBY_VERTEX_ARRAY_H

#include <stdlib.h>

#include "glad/glad.h"

#include "basic_types.h"
#include "vertex_buffer.h"

typedef struct {
  u32 glId;
} hb_VertexArray;

hb_VertexArray hb_createVertexArray();
void hb_bindVertexArray(hb_VertexArray* array);
void hb_setVertexArrayAttribute(
  hb_VertexArray* array,
  hb_VertexBuffer* buffer,
  u32 index, s32 count, 
  GLenum type,
  size_t stride, size_t offset);
void hb_destroyVertexArray(hb_VertexArray* array);

#endif // _HOBBY_VERTEX_ARRAY_H
