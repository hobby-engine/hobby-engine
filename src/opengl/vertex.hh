#ifndef _HOBBY_OPENGL_VERTEX_BUFFER_HH
#define _HOBBY_OPENGL_VERTEX_BUFFER_HH

#include <cstdlib>

#include "glad/glad.h"

enum class VertexBufferType {
  Array,
  Index,
};

struct VertexBuffer {
  unsigned int handle;
  VertexBufferType type;
  bool isStatic;

  VertexBuffer(VertexBufferType type, bool isStatic);
  ~VertexBuffer();

  void bind() const;
  void setData(size_t size, void* data);
};

struct VertexArray {
  unsigned int handle;

  VertexArray();
  ~VertexArray();

  void bind() const;
  void setAttribute(
    const VertexBuffer& buffer,
    unsigned int index, int count,
    GLenum type,
    size_t stride, size_t offset);
};

#endif // _HOBBY_OPENGL_VERTEX_BUFFER_HH
