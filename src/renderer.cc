#include "renderer.hh"

#include "mat4.hh"
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
  int w, h;
  _window->getSize(w, h);

  _projection.setIdentity();
  _projection.ortho(0, w, h, 0, -1, 1);

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
  BatchRequest req{VertexFormat::XYC, IndexMode::Triangles, nullptr};
  BatchState& state = _requestBatchState(req);
  Mesh& mesh = state.mesh;

  int start = mesh.topIndex();
  int circleResolution = fmax(2 * M_PI * sqrt((rx + ry) / 2), 8);

  for (float i = 0; i < circleResolution; i++) {
    float angle = (i / circleResolution) * M_PI * 2;
    float px = x + cosf(angle) * rx;
    float py = y + sinf(angle) * ry;

    if (i > 2) {
      mesh.addIndex(start, 0);
      mesh.addIndex(start, i - 1);
      mesh.addIndex(start, i);
    }
    mesh.addVertexXYC(px, py, _currentColor);
  }
}

void Renderer::drawRect(float x, float y, float w, float h)
{
  BatchRequest req{VertexFormat::XYC, IndexMode::Triangles, nullptr};
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

  mesh.addVertexXYC(x, y, _currentColor);
  mesh.addVertexXYC(x, y + h, _currentColor);
  mesh.addVertexXYC(x + w, y + h, _currentColor);
  mesh.addVertexXYC(x + w, y, _currentColor);
}
