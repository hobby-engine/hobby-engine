#ifndef _HOBBY_QUAD_H
#define _HOBBY_QUAD_H

namespace Hobby {

class Quad {
public:
  float X, Y, W, H;

  Quad(float x, float y, float w, float h);
  ~Quad();

  void Draw(unsigned int textureId);
private:
  unsigned int _ebo, _vao, _vbo;
};

} // namespace Hobby

#endif
