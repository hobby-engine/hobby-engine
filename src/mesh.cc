#include "mesh.hh"

size_t getVertexFormatStride(VertexFormat format)
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

int getVertexFormatVertexLength(VertexFormat format)
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

Mesh::Mesh(VertexFormat format, bool isIndexed, int count)
    : _isIndexed(isIndexed), _vertexFormat(format)
{
  _vertices.reserve(count * getVertexFormatVertexLength(format));

  if (isIndexed) {
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

void Mesh::addIndex(int start, int index)
{
  if (index > _topIndex) {
    _topIndex = index + 1;
  }
  _indices->pushBack(start + index);
}

void Mesh::addVertexXY(float x, float y)
{
  _vertices.pushBack(x);
  _vertices.pushBack(y);
}

void Mesh::addVertexXYUV(float x, float y, float uvx, float uvy)
{
  _vertices.pushBack(x);
  _vertices.pushBack(y);
  _vertices.pushBack(uvx);
  _vertices.pushBack(uvy);
}

void Mesh::addVertexXYC(float x, float y, Color color)
{
  _vertices.pushBack(x);
  _vertices.pushBack(y);
  _vertices.pushBack(color.r);
  _vertices.pushBack(color.g);
  _vertices.pushBack(color.b);
  _vertices.pushBack(color.a);
}

void Mesh::addVertexXYUVC(float x, float y, float uvx, float uvy, Color color)
{
  _vertices.pushBack(x);
  _vertices.pushBack(y);
  _vertices.pushBack(uvx);
  _vertices.pushBack(uvy);
  _vertices.pushBack(color.r);
  _vertices.pushBack(color.g);
  _vertices.pushBack(color.b);
  _vertices.pushBack(color.a);
}
