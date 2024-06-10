#include "mesh.hh"

size_t getvertformatstride(VertexFormat format)
{
  switch (format) {
    case VertexFormat::XY:
      return sizeof(float) * 2;
    case VertexFormat::XYZ:
      return sizeof(float) * 3;
    case VertexFormat::XYU:
      return sizeof(float) * 4;
    case VertexFormat::XYZU:
      return sizeof(float) * 5;
    case VertexFormat::XYC:
      return sizeof(float) * 6;
    case VertexFormat::XYZC:
      return sizeof(float) * 7;
    case VertexFormat::XYUC:
      return sizeof(float) * 8;
    case VertexFormat::XYZUC:
      return sizeof(float) * 9;
  }

  // Unreachable.
  return 0;
}

int getverformatlen(VertexFormat format)
{
  switch (format) {
    case VertexFormat::XY:
      return 2;
    case VertexFormat::XYZ:
      return 3;
    case VertexFormat::XYU:
      return 4;
    case VertexFormat::XYZU:
      return 5;
    case VertexFormat::XYC:
      return 6;
    case VertexFormat::XYZC:
      return 7;
    case VertexFormat::XYUC:
      return 8;
    case VertexFormat::XYZUC:
      return 9;
  }
  return 0;
}

Mesh::Mesh(VertexFormat format, bool indexed, int count)
    : m_indexed(indexed), m_vertexformat(format)
{
  m_vertices.reserve(count * getverformatlen(format));

  if (indexed) {
    m_indices = new DynArr<uint32_t>();
    m_indices->reserve(count);
  }
}

Mesh::~Mesh()
{
  if (m_indices != nullptr) {
    delete m_indices;
  }
}

void Mesh::addvertex_xy(float x, float y)
{
  m_vertices.pushback(x);
  m_vertices.pushback(y);
}

void Mesh::addvertex_xyu(float x, float y, float uvx, float uvy)
{
  m_vertices.pushback(x);
  m_vertices.pushback(y);
  m_vertices.pushback(uvx);
  m_vertices.pushback(uvy);
}

void Mesh::addvertex_xyuc(float x, float y, float uvx, float uvy, Color color)
{
  m_vertices.pushback(x);
  m_vertices.pushback(y);
  m_vertices.pushback(uvx);
  m_vertices.pushback(uvy);
  m_vertices.pushback(color.r);
  m_vertices.pushback(color.g);
  m_vertices.pushback(color.b);
  m_vertices.pushback(color.a);
}

void Mesh::addvertex_xyc(float x, float y, Color color)
{
  m_vertices.pushback(x);
  m_vertices.pushback(y);
  m_vertices.pushback(color.r);
  m_vertices.pushback(color.g);
  m_vertices.pushback(color.b);
  m_vertices.pushback(color.a);
}

void Mesh::addindex(int start, int index)
{
  if (start + index > m_topindex) {
    m_topindex = start + index + 1;
  }
  m_indices->pushback(start + index);
}
