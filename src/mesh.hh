#ifndef _HOBBY_MESH_HH
#define _HOBBY_MESH_HH

#include "dynarr.hh"
#include "color.hh"
#include <cstdint>

enum class VertexFormat
{
  XY,
  XYZ,

  XYU,
  XYZU,

  XYC,
  XYZC,

  XYUC,
  XYZUC,
};

size_t getVertexFormatStride(VertexFormat format);
int getVertexFormatVertexLength(VertexFormat format);

class Mesh
{
public:
  Mesh(VertexFormat format, bool isIndexed, int count = 0);
  ~Mesh();

  void clear();

  inline void addVertexXY(float x, float y)
  {
    _vertices.pushBack(x);
    _vertices.pushBack(y);
  }

  inline void addVertexXYUV(float x, float y, float uvx, float uvy)
  {
    _vertices.pushBack(x);
    _vertices.pushBack(y);
    _vertices.pushBack(uvx);
    _vertices.pushBack(uvy);
  }

  inline void
  addVertexXYUVC(float x, float y, float uvx, float uvy, Color color)
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

  inline void addVertexXYC(float x, float y, Color color)
  {
    _vertices.pushBack(x);
    _vertices.pushBack(y);
    _vertices.pushBack(color.r);
    _vertices.pushBack(color.g);
    _vertices.pushBack(color.b);
    _vertices.pushBack(color.a);
  }

  inline void addIndex(int start, int index)
  {
    if (start + index > _topIndex) {
      _topIndex = start + index + 1;
    }
    _indices->pushBack(start + index);
  }

  inline int isIndexed()
  {
    return _isIndexed;
  }

  inline int vertexCount()
  {
    return _vertices.size();
  }

  inline int indexCount()
  {
    return _indices->size();
  }

  inline int topIndex()
  {
    return _topIndex;
  }

  inline float* data()
  {
    return _vertices.data();
  }

  inline uint32_t* indices()
  {
    return _indices->data();
  }

  inline VertexFormat getFormat()
  {
    return _vertexFormat;
  }

private:
  // Do we use the index buffer to draw?
  bool _isIndexed = false;
  int _topIndex = 0;

  VertexFormat _vertexFormat;
  DynArr<float> _vertices;
  DynArr<uint32_t>* _indices = nullptr;
};

#endif // _HOBBY_MESH_HH
