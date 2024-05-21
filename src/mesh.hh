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
  void addVertexXY(float x, float y);
  void addVertexXYUV(float x, float y, float uvx, float uvy);
  void addVertexXYC(float x, float y, Color color);
  void addVertexXYUVC(float x, float y, float uvx, float uvy, Color color);
  void addIndex(int start, int index);

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
