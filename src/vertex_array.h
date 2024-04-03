#ifndef _HOBBY_VERTEX_ARRAY_H
#define _HOBBY_VERTEX_ARRAY_H

#include <stdlib.h>

#include "glad/glad.h"

#include "typedefs.h"
#include "vertex_buffer.h"

struct VertexArray {
  u32 glId;
};

struct VertexArray createVertexArray();
void bindVertexArray(struct VertexArray* array);
void setVertexArrayAttribute(
  struct VertexArray* array,
  struct VertexBuffer* buffer,
  u32 index, s32 count, 
  GLenum type,
  size_t stride, size_t offset);
void destroyVertexArray(struct VertexArray* array);

#endif // _HOBBY_VERTEX_ARRAY_H
