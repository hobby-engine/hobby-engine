#ifndef _HOBBY_VERTEX_BUFFER_H
#define _HOBBY_VERTEX_BUFFER_H

#include <stdbool.h>
#include <stdlib.h>

#include "typedefs.h"

enum BufferType {
  BUFFER_TYPE_ARRAY_BUFFER,
  BUFFER_TYPE_INDEX_BUFFER,
};

struct VertexBuffer {
  u32 glId;
  enum BufferType type;
  bool isStatic;
};

struct VertexBuffer createVertexBuffer(enum BufferType type, bool isStatic);
void destroyVertexBuffer(struct VertexBuffer* buffer);
void setVertexBufferData(struct VertexBuffer* buffer, size_t size, void* data);
void bindVertexBuffer(struct VertexBuffer* buffer);

#endif // _HOBBY_VERTEX_BUFFER_H
