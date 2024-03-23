#include "vertex_array.h"
#include "vertex_buffer.h"

struct hb_VertexArray hb_createVertexArray() {
  struct hb_VertexArray array;
  glGenVertexArrays(1, &array.glId);
  return array;
}

void hb_bindVertexArray(struct hb_VertexArray* array) {
  glBindVertexArray(array->glId);
}

void hb_setVertexArrayAttribute(
    struct hb_VertexArray* array,
    struct hb_VertexBuffer* buffer,
    u32 index, s32 count, 
    GLenum type,
    size_t stride, size_t offset) {
  hb_bindVertexArray(array);
  hb_bindVertexBuffer(buffer);

  glVertexAttribPointer(index, count, type, GL_FALSE, stride, (void*)offset);
  glEnableVertexAttribArray(index);
}

void hb_destroyVertexArray(struct hb_VertexArray* array) {
  glDeleteVertexArrays(1, &array->glId);
}
