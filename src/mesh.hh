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
    return m_indexed;
  }

  inline int vertexcount()
  {
    return m_vertices.size();
  }

  inline int indexcount()
  {
    return m_indices->size();
  }

  inline int topindex()
  {
    return m_topindex;
  }

  inline float* data()
  {
    return m_vertices.data();
  }

  inline uint32_t* indices()
  {
    return m_indices->data();
  }

  inline VertexFormat getformat()
  {
    return m_vertexformat;
  }

private:
  bool m_indexed = false; // Do we use the index buffer to draw?
  int m_topindex = 0;

  VertexFormat m_vertexformat;

  DynArr<float> m_vertices;
  // TODO: This sucks, ideally it should take up no space whatsoever if you
  // don't need it. Maybe make an `IndexMesh` class for indexed meshes?
  DynArr<uint32_t>* m_indices = nullptr;
};

#endif // _HOBBY_MESH_HH
