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

size_t getvertformatstride(VertexFormat format);
int getverformatlen(VertexFormat format);

class Mesh
{
public:
  Mesh(VertexFormat format, bool indexed, int count = 0);
  ~Mesh();

  void clear();

  inline void addvertex_xy(float x, float y)
  {
    _vertices.pushback(x);
    _vertices.pushback(y);
  }

  inline void addvertex_xyu(float x, float y, float uvx, float uvy)
  {
    _vertices.pushback(x);
    _vertices.pushback(y);
    _vertices.pushback(uvx);
    _vertices.pushback(uvy);
  }

  inline void
  addvertex_xyuc(float x, float y, float uvx, float uvy, Color color)
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

  inline void addvertex_xyc(float x, float y, Color color)
  {
    _vertices.pushback(x);
    _vertices.pushback(y);
    _vertices.pushback(color.r);
    _vertices.pushback(color.g);
    _vertices.pushback(color.b);
    _vertices.pushback(color.a);
  }

  inline void addindex(int start, int index)
  {
    if (start + index > _topindex) {
      _topindex = start + index + 1;
    }
    _indices->pushback(start + index);
  }

  inline int isindexed()
  {
    return _indexed;
  }

  inline int vertexcount()
  {
    return _vertices.size();
  }

  inline int indexcount()
  {
    return _indices->size();
  }

  inline int topindex()
  {
    return _topindex;
  }

  inline float* data()
  {
    return _vertices.data();
  }

  inline uint32_t* indices()
  {
    return _indices->data();
  }

  inline VertexFormat getformat()
  {
    return _vertexformat;
  }

private:
  // Do we use the index buffer to draw?
  bool _indexed = false;
  int _topindex = 0;

  VertexFormat _vertexformat;
  DynArr<float> _vertices;
  DynArr<uint32_t>* _indices = nullptr;
};

#endif // _HOBBY_MESH_HH
