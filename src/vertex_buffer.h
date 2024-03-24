#ifndef _HOBBY_VERTEX_BUFFER_H
#define _HOBBY_VERTEX_BUFFER_H

#include <stdbool.h>
#include <stdlib.h>

#include "typedefs.h"

enum hb_BufferType {
  hb_BUFFER_TYPE_ARRAY_BUFFER,
  hb_BUFFER_TYPE_INDEX_BUFFER,
};

struct hb_VertexBuffer {
  u32 glId;
  enum hb_BufferType type;
  bool isStatic;
};

struct hb_VertexBuffer hb_createVertexBuffer(enum hb_BufferType type, bool isStatic);
void hb_destroyVertexBuffer(struct hb_VertexBuffer* buffer);
void hb_setVertexBufferData(struct hb_VertexBuffer* buffer, size_t size, void* data);
void hb_bindVertexBuffer(struct hb_VertexBuffer* buffer);

#endif // _HOBBY_VERTEX_BUFFER_H
