#ifndef _HOBBY_RENDERER_HH
#define _HOBBY_RENDERER_HH

#include "texture.hh"

struct Color {
  double r, g, b, a;
};

class Renderer {
  public:
    virtual ~Renderer() {}

    virtual void update() = 0;
    virtual int getDrawCalls() const = 0;
    virtual void setColor(Color color) = 0;
    virtual void clear(Color color) = 0;
    virtual void drawRect(float x, float y, float w, float h) = 0;
    virtual void drawEllipse(float x, float y, float rx, float ry) = 0;
    virtual void drawVertices(int count, float* vertices) = 0;
    virtual void drawBoid(float x, float y, float b, float h, float r) = 0;
    virtual void drawTexture(
        const Texture2D& texture,
        float x, float y,
        float r,
        float sx, float sy,
        float ox, float oy,
        float skx, float sky) = 0;
  protected:
    Color _currentColor;
};

#endif // _HOBBY_RENDERER_HH
