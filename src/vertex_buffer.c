#include "vertex_buffer.h"

#include "glad/glad.h"

#include "log.h"

static u32 getGlBufferType(enum hb_BufferType type) {
  switch (type) {
    case hb_BUFFER_TYPE_ARRAY_BUFFER: return GL_ARRAY_BUFFER;
    case hb_BUFFER_TYPE_INDEX_BUFFER: return GL_ELEMENT_ARRAY_BUFFER;
    default:
      hb_error("Invalid buffer type.");
      return -1;
  }
}

struct hb_VertexBuffer hb_createVertexBuffer(
    enum hb_BufferType type, bool isStatic) {
  struct hb_VertexBuffer buffer;

  glGenBuffers(1, &buffer.glId);

  buffer.type = type;
  buffer.isStatic = isStatic;

  return buffer;
}

void hb_destroyVertexBuffer(struct hb_VertexBuffer* buffer) {
  glDeleteBuffers(1, &buffer->glId);
}

void hb_bindVertexBuffer(struct hb_VertexBuffer* buffer) {
  glBindBuffer(getGlBufferType(buffer->type), buffer->glId);
}

void hb_setVertexBufferData(
    struct hb_VertexBuffer* buffer, size_t size, void* data) {
  hb_bindVertexBuffer(buffer);
  glBufferData(
      getGlBufferType(buffer->type),
      size, data,
      buffer->isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}
