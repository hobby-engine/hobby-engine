#ifndef _HOBBY_VERTEX_ARRAY_H
#define _HOBBY_VERTEX_ARRAY_H

#include <stdlib.h>

#include "glad/glad.h"

#include "typedefs.h"
#include "vertex_buffer.h"

struct hb_VertexArray {
  u32 glId;
};

struct hb_VertexArray hb_createVertexArray();
void hb_bindVertexArray(struct hb_VertexArray* array);
void hb_setVertexArrayAttribute(
  struct hb_VertexArray* array,
  struct hb_VertexBuffer* buffer,
  u32 index, s32 count, 
  GLenum type,
  size_t stride, size_t offset);
void hb_destroyVertexArray(struct hb_VertexArray* array);

#endif // _HOBBY_VERTEX_ARRAY_H
