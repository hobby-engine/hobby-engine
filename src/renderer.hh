#ifndef _HOBBY_RENDERER_HH
#define _HOBBY_RENDERER_HH

struct Color {
  double r, g, b, a;
};

class Renderer {
  public:
    virtual ~Renderer() {}

    virtual void update() = 0;
    virtual void setColor(Color color) = 0;
    virtual void clear(Color color) = 0;
    virtual void drawRect(float x, float y, float w, float h) = 0;
    virtual void drawEllipse(float x, float y, float rx, float ry) = 0;
  protected:
    Color _currentColor;
};

#endif // _HOBBY_RENDERER_HH
