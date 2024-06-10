#ifndef _HOBBY_RENDERER_HH
#define _HOBBY_RENDERER_HH

#include "mat4.hh"
#include "texture.hh"
#include "color.hh"
#include "mesh.hh"
#include "window.hh"

enum class IndexMode
{
  Triangles,
  TriangleFan,
  TriangleStripe,
};

// Tells the renderer what we want to draw, so that it can automatically batch
// similar, consecutive draw calls.
struct BatchRequest
{
  bool isindexed = true;
  VertexFormat vertexformat;
  IndexMode indexmode;
  const Texture2D* texture = nullptr;

  BatchRequest(
    VertexFormat vertexformat, IndexMode indexmode, const Texture2D* texture)
      : vertexformat(vertexformat), indexmode(indexmode), texture(texture)
  {
  }
};

// Stores data about what's being drawn.
struct BatchState
{
  Mesh mesh;
  IndexMode indexmode;
  const Texture2D* texture = nullptr;

  BatchState(const BatchRequest& req)
      : mesh(Mesh(req.vertexformat, req.isindexed)), indexmode(req.indexmode),
        texture(req.texture)
  {
  }
};

// Holds and manages the graphics state and rendering.
class Renderer
{
public:
  Renderer(Window* window);
  virtual ~Renderer();

  inline int getdrawcalls() const
  {
    return m_drawcalls;
  }

  inline void setcolor(Color color)
  {
    m_currentcolor = color;
  }

  inline Color getcolor()
  {
    return m_currentcolor;
  }

  virtual void clear(Color color) = 0;
  virtual void draw() = 0;
  virtual void drawindexed() = 0;
  virtual void resizewindow(Window* window) = 0;

  void update();
  void present();
  void drawrect(float x, float y, float w, float h);
  void drawellipse(float x, float y, float rx, float ry);
  void drawtexture(
    const Texture2D& texture, float x, float y, float r, float sx, float sy,
    float ox, float oy, float skx, float sky);

private:
  void m_flushdrawqueue();
  // Checks if the current command matches up with what we want to draw enough
  // that we can use the current command, or if we need to use a new one.
  BatchState& m_requestbatchstate(const BatchRequest& req);

protected:
  Window* m_window;
  BatchState* m_state = nullptr;

  Color m_currentcolor = {1, 1, 1, 1};

  // Draw call counting has a 1 frame latency. This is so that you can query it
  // anywhere and always have a full count.
  int m_drawcalls = 0;            // Prev frame draw calls.
  int m_currentdrawcallcount = 0; // Current frame's count.

  // Same with the batched calls.
  int m_batchedcalls = 0;        // Prev frame batched calls.
  int m_currentbatchedcalls = 0; // Current frame's count.
};

#endif // _HOBBY_RENDERER_HH
