#include "vertex.hh"

#include "log.hh"

static unsigned int getGlBufferType(VertexBufferType type)
{
  switch (type) {
    case VertexBufferType::Array:
      return GL_ARRAY_BUFFER;
    case VertexBufferType::Index:
      return GL_ELEMENT_ARRAY_BUFFER;
    default:
      error("Invalid buffer type.");
      return -1;
  }
}

VertexBuffer::VertexBuffer(VertexBufferType type, bool isStatic)
    : type(type), isStatic(isStatic)
{
  glGenBuffers(1, &handle);
}

VertexBuffer::~VertexBuffer()
{
  glDeleteBuffers(1, &handle);
}

void VertexBuffer::bind() const
{
  glBindBuffer(getGlBufferType(type), handle);
}

void VertexBuffer::setData(size_t size, void* data)
{
  bind();
  glBufferData(
    getGlBufferType(type), size, data,
    isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}

VertexArray::VertexArray()
{
  glGenVertexArrays(1, &handle);
}

VertexArray::~VertexArray()
{
  glDeleteVertexArrays(1, &handle);
}

void VertexArray::bind() const
{
  glBindVertexArray(handle);
}

void VertexArray::setAttribute(
  const VertexBuffer& buffer, unsigned int index, int count, GLenum type,
  size_t stride, size_t offset)
{
  bind();
  buffer.bind();

  glVertexAttribPointer(index, count, type, GL_FALSE, stride, (void*)offset);
  glEnableVertexAttribArray(index);
}
