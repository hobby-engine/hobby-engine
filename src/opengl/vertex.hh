#ifndef _HOBBY_OPENGL_VERTEX_BUFFER_HH
#define _HOBBY_OPENGL_VERTEX_BUFFER_HH

#include <cstdlib>

#include "glad/glad.h"

enum class VertexBufferType
{
  Array,
  Index,
};

struct VertexBuffer
{
  unsigned int handle;
  VertexBufferType type;
  bool isstatic;

  VertexBuffer(VertexBufferType type, bool isstatic);
  ~VertexBuffer();

  void bind() const;
  void setdata(size_t size, void* data);
};

struct VertexArray
{
  unsigned int handle;

  VertexArray();
  ~VertexArray();

  void bind() const;
  void setattrib(
    const VertexBuffer& buffer, unsigned int index, int count, GLenum type,
    size_t stride, size_t offset);
};

#endif // _HOBBY_OPENGL_VERTEX_BUFFER_HH
