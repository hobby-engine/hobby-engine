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
  bool isIndexed = true;
  VertexFormat vertexFormat;
  IndexMode indexMode;
  const Texture2D* texture = nullptr;

  BatchRequest(
    VertexFormat vertexFormat, IndexMode indexMode, const Texture2D* texture)
      : vertexFormat(vertexFormat), indexMode(indexMode), texture(texture)
  {
  }
};

// Stores data about what's being drawn.
struct BatchState
{
  Mesh mesh;
  IndexMode indexMode;
  const Texture2D* texture = nullptr;

  BatchState(const BatchRequest& req)
      : mesh(Mesh(req.vertexFormat, req.isIndexed)), indexMode(req.indexMode),
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

  inline int getDrawCalls() const
  {
    return _drawCalls;
  }

  inline void setColor(Color color)
  {
    _currentColor = color;
  }

  inline Color getColor()
  {
    return _currentColor;
  }

  virtual void clear(Color color) = 0;
  virtual void draw() = 0;
  virtual void drawIndexed() = 0;
  virtual void resizeWindow(Window* window) = 0;

  void update();
  void present();
  void drawRect(float x, float y, float w, float h);
  void drawEllipse(float x, float y, float rx, float ry);
  void drawTexture(
    const Texture2D& texture, float x, float y, float r, float sx, float sy,
    float ox, float oy, float skx, float sky);

private:
  void _flushDrawQueue();
  // Checks if the current command matches up with what we want to draw enough
  // that we can use the current command, or if we need to use a new one.
  BatchState& _requestBatchState(const BatchRequest& req);

protected:
  Window* _window;
  BatchState* _state = nullptr;

  Color _currentColor = {1, 1, 1, 1};

  // Draw call counting has a 1 frame latency. This is so that you can query it
  // anywhere and always have a full count.
  int _drawCalls = 0;            // Prev frame draw calls.
  int _currentDrawCallCount = 0; // Current frame's count.

  // Same with the batched calls.
  int _batchedCalls = 0;             // Prev frame batched calls.
  int _currentBatchedCallsCount = 0; // Current frame's count.
};

#endif // _HOBBY_RENDERER_HH
