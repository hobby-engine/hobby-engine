#include "renderer.hh"

#include "mesh.hh"
#include <cmath>

Renderer::Renderer(Window* window) : _window(window)
{
}

Renderer::~Renderer()
{
  delete _state;
}

void Renderer::update()
{
  _drawCalls = _currentDrawCallCount;
  _currentDrawCallCount = 0;
}

void Renderer::present()
{
  if (_state != nullptr) {
    _flushDrawQueue();
  }

  _window->present();
}

void Renderer::_flushDrawQueue()
{
  if (_state->mesh.isIndexed()) {
    drawIndexed();
  } else {
    draw();
  }
  _currentDrawCallCount++;

  delete _state;
  _state = nullptr;
}

BatchState& Renderer::_requestBatchState(const BatchRequest& req)
{
  bool newState = false;
  bool flush = false;

  // If there is no command before this one, make one.
  if (_state == nullptr) {
    newState = true;
  } else {
    bool canBatch = _state->texture == req.texture &&
                    _state->mesh.getFormat() == req.vertexFormat &&
                    _state->indexMode == req.indexMode &&
                    _state->mesh.isIndexed();
    if (!canBatch) {
      // We can't batch anything more past this point, so we draw everything
      // we've collected so far.
      flush = true;
    }
  }

  if (flush) {
    _flushDrawQueue();
  }

  if (newState || flush) {
    BatchState* state = new BatchState(req);
    _state = state;
    return *state;
  }

  _currentBatchedCallsCount++;
  return *_state;
}

void Renderer::drawEllipse(float x, float y, float rx, float ry)
{
  BatchRequest req{VertexFormat::XYUC, IndexMode::Triangles, nullptr};
  req.isIndexed = true;
  BatchState& state = _requestBatchState(req);
  Mesh& mesh = state.mesh;

  int start = mesh.topIndex();
  int circleResolution = fmax(2 * M_PI * sqrt((rx + ry) / 2), 8);

  for (float i = 0; i < circleResolution; i++) {
    float angle = (i / circleResolution) * M_PI * 2;
    float c = cosf(angle), s = sinf(angle);
    float px = x + c * rx;
    float py = y + s * ry;

    if (i > 2) {
      mesh.addIndex(start, 0);
      mesh.addIndex(start, i - 1);
      mesh.addIndex(start, i);
    }
    mesh.addVertexXYUVC(px, py, c * 0.5 + 0.5, s * 0.5 + 0.5, _currentColor);
  }
}

void Renderer::drawRect(float x, float y, float w, float h)
{
  BatchRequest req{VertexFormat::XYUC, IndexMode::Triangles, nullptr};
  req.isIndexed = true;
  BatchState& state = _requestBatchState(req);
  Mesh& mesh = state.mesh;

  int start = mesh.topIndex();
  // 03
  // 12
  mesh.addIndex(start, 1);
  mesh.addIndex(start, 2);
  mesh.addIndex(start, 3);
  mesh.addIndex(start, 3);
  mesh.addIndex(start, 1);
  mesh.addIndex(start, 0);

  mesh.addVertexXYUVC(x, y, 0, 0, _currentColor);
  mesh.addVertexXYUVC(x, y + h, 0, 1, _currentColor);
  mesh.addVertexXYUVC(x + w, y + h, 1, 1, _currentColor);
  mesh.addVertexXYUVC(x + w, y, 1, 0, _currentColor);
}

void Renderer::drawTexture(
  const Texture2D& texture, float x, float y, float r, float sx, float sy,
  float ox, float oy, float skx, float sky)
{
  BatchRequest req{VertexFormat::XYUC, IndexMode::Triangles, &texture};
  req.isIndexed = true;
  BatchState& state = _requestBatchState(req);
  Mesh& mesh = state.mesh;

  int start = mesh.topIndex();
  // 03
  // 12
  mesh.addIndex(start, 1);
  mesh.addIndex(start, 2);
  mesh.addIndex(start, 3);
  mesh.addIndex(start, 3);
  mesh.addIndex(start, 1);
  mesh.addIndex(start, 0);

  Mat4 transform;
  transform.setRotation(r);
  transform.scale(sx, sy);
  transform.skew(skx, sky);
  transform.translate(x, y);

  int w = texture.getWidth(), h = texture.getHeight();

  float tlx = ox, tly = oy;
  transform.applyTransform(&tlx, &tly);
  float blx = ox, bly = oy + h;
  transform.applyTransform(&blx, &bly);
  float brx = ox + w, bry = oy + h;
  transform.applyTransform(&brx, &bry);
  float trx = ox + w, _try = oy;
  transform.applyTransform(&trx, &_try);

  mesh.addVertexXYUVC(tlx, tly, 0, 0, _currentColor);
  mesh.addVertexXYUVC(blx, bly, 0, 1, _currentColor);
  mesh.addVertexXYUVC(brx, bry, 1, 1, _currentColor);
  mesh.addVertexXYUVC(trx, _try, 1, 0, _currentColor);
}
