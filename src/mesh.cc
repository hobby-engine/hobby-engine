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
    : _indexed(indexed), _vertexformat(format)
{
  _vertices.reserve(count * getverformatlen(format));

  if (indexed) {
    _indices = new DynArr<uint32_t>();
    _indices->reserve(count);
  }
}

Mesh::~Mesh()
{
  if (_indices != nullptr) {
    delete _indices;
  }
}

void Mesh::addvertex_xy(float x, float y)
{
  _vertices.pushback(x);
  _vertices.pushback(y);
}

void Mesh::addvertex_xyu(float x, float y, float uvx, float uvy)
{
  _vertices.pushback(x);
  _vertices.pushback(y);
  _vertices.pushback(uvx);
  _vertices.pushback(uvy);
}

void Mesh::addvertex_xyuc(float x, float y, float uvx, float uvy, Color color)
{
  _vertices.pushback(x);
  _vertices.pushback(y);
  _vertices.pushback(uvx);
  _vertices.pushback(uvy);
  _vertices.pushback(color.r);
  _vertices.pushback(color.g);
  _vertices.pushback(color.b);
  _vertices.pushback(color.a);
}

void Mesh::addvertex_xyc(float x, float y, Color color)
{
  _vertices.pushback(x);
  _vertices.pushback(y);
  _vertices.pushback(color.r);
  _vertices.pushback(color.g);
  _vertices.pushback(color.b);
  _vertices.pushback(color.a);
}

void Mesh::addindex(int start, int index)
{
  if (start + index > _topindex) {
    _topindex = start + index + 1;
  }
  _indices->pushback(start + index);
}
