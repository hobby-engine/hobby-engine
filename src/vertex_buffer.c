#include "vertex_buffer.h"

#include "glad/glad.h"

#include "log.h"

static u32 getGlBufferType(enum BufferType type) {
  switch (type) {
    case BUFFER_TYPE_ARRAY_BUFFER: return GL_ARRAY_BUFFER;
    case BUFFER_TYPE_INDEX_BUFFER: return GL_ELEMENT_ARRAY_BUFFER;
    default:
      error("Invalid buffer type.");
      return -1;
  }
}

struct VertexBuffer createVertexBuffer(
    enum BufferType type, bool isStatic) {
  struct VertexBuffer buffer;

  glGenBuffers(1, &buffer.glId);

  buffer.type = type;
  buffer.isStatic = isStatic;

  return buffer;
}

void destroyVertexBuffer(struct VertexBuffer* buffer) {
  glDeleteBuffers(1, &buffer->glId);
}

void bindVertexBuffer(struct VertexBuffer* buffer) {
  glBindBuffer(getGlBufferType(buffer->type), buffer->glId);
}

void setVertexBufferData(
    struct VertexBuffer* buffer, size_t size, void* data) {
  bindVertexBuffer(buffer);
  glBufferData(
      getGlBufferType(buffer->type),
      size, data,
      buffer->isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}
