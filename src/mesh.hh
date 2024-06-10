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

  void addvertex_xy(float x, float y);
  void addvertex_xyu(float x, float y, float uvx, float uvy);
  void addvertex_xyuc(float x, float y, float uvx, float uvy, Color color);
  void addvertex_xyc(float x, float y, Color color);
  void addindex(int start, int index);

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
  bool _indexed = false; // Do we use the index buffer to draw?
  int _topindex = 0;

  VertexFormat _vertexformat;

  DynArr<float> _vertices;
  // TODO: This sucks, ideally it should take up no space whatsoever if you
  // don't need it. Maybe make an `IndexMesh` class for indexed meshes?
  DynArr<uint32_t>* _indices = nullptr;
};

#endif // _HOBBY_MESH_HH
