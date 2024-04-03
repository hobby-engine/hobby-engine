#include "vertex_array.h"
#include "vertex_buffer.h"

struct VertexArray createVertexArray() {
  struct VertexArray array;
  glGenVertexArrays(1, &array.glId);
  return array;
}

void bindVertexArray(struct VertexArray* array) {
  glBindVertexArray(array->glId);
}

void setVertexArrayAttribute(
    struct VertexArray* array,
    struct VertexBuffer* buffer,
    u32 index, s32 count, 
    GLenum type,
    size_t stride, size_t offset) {
  bindVertexArray(array);
  bindVertexBuffer(buffer);

  glVertexAttribPointer(index, count, type, GL_FALSE, stride, (void*)offset);
  glEnableVertexAttribArray(index);
}

void destroyVertexArray(struct VertexArray* array) {
  glDeleteVertexArrays(1, &array->glId);
}
