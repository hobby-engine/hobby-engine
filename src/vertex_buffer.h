#ifndef _HOBBY_VERTEX_BUFFER_H
#define _HOBBY_VERTEX_BUFFER_H

#include <stdbool.h>
#include <stdlib.h>

#include "basic_types.h"

typedef enum {
  hb_BUFFER_TYPE_ARRAY_BUFFER,
} hb_BufferType;

typedef struct {
  u32 glId;
  hb_BufferType type;
  bool isStatic;
} hb_VertexBuffer;

hb_VertexBuffer hb_createVertexBuffer(hb_BufferType type, bool isStatic);
void hb_destroyVertexBuffer(hb_VertexBuffer* buffer);
void hb_setVertexBufferData(hb_VertexBuffer* buffer, size_t size, void* data);
void hb_bindVertexBuffer(hb_VertexBuffer* buffer);

#endif // _HOBBY_VERTEX_BUFFER_H
