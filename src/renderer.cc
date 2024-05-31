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
  _drawcalls = _currentdrawcallcount;
  _currentdrawcallcount = 0;
}

void Renderer::present()
{
  if (_state != nullptr) {
    _flushdrawqueue();
  }

  _window->present();
}

void Renderer::_flushdrawqueue()
{
  if (_state->mesh.isindexed()) {
    drawindexed();
  } else {
    draw();
  }
  _currentdrawcallcount++;

  delete _state;
  _state = nullptr;
}

BatchState& Renderer::_requestbatchstate(const BatchRequest& req)
{
  bool newstate = false;
  bool flush = false;

  // If there is no command before this one, make one.
  if (_state == nullptr) {
    newstate = true;
  } else {
    bool canbatch = _state->texture == req.texture &&
                    _state->mesh.getformat() == req.vertexformat &&
                    _state->indexmode == req.indexmode &&
                    _state->mesh.isindexed();
    if (!canbatch) {
      // We can't batch anything more past this point, so we draw everything
      // we've collected so far.
      flush = true;
    }
  }

  if (flush) {
    _flushdrawqueue();
  }

  if (newstate || flush) {
    BatchState* state = new BatchState(req);
    _state = state;
    return *state;
  }

  _currentbatchedcalls++;
  return *_state;
}

void Renderer::drawellipse(float x, float y, float rx, float ry)
{
  BatchRequest req{VertexFormat::XYUC, IndexMode::Triangles, nullptr};
  req.isindexed = true;
  BatchState& state = _requestbatchstate(req);
  Mesh& mesh = state.mesh;

  int start = mesh.topindex();
  int circleres = fmax(2 * M_PI * sqrt((rx + ry) / 2), 8);

  for (float i = 0; i < circleres; i++) {
    float angle = (i / circleres) * M_PI * 2;
    float c = cosf(angle), s = sinf(angle);
    float px = x + c * rx;
    float py = y + s * ry;

    if (i > 2) {
      mesh.addindex(start, 0);
      mesh.addindex(start, i - 1);
      mesh.addindex(start, i);
    }
    mesh.addvertex_xyuc(px, py, c * 0.5 + 0.5, s * 0.5 + 0.5, _currentcolor);
  }
}

void Renderer::drawrect(float x, float y, float w, float h)
{
  BatchRequest req{VertexFormat::XYUC, IndexMode::Triangles, nullptr};
  req.isindexed = true;
  BatchState& state = _requestbatchstate(req);
  Mesh& mesh = state.mesh;

  int start = mesh.topindex();
  // 03
  // 12
  mesh.addindex(start, 1);
  mesh.addindex(start, 2);
  mesh.addindex(start, 3);
  mesh.addindex(start, 3);
  mesh.addindex(start, 1);
  mesh.addindex(start, 0);

  mesh.addvertex_xyuc(x, y, 0, 0, _currentcolor);
  mesh.addvertex_xyuc(x, y + h, 0, 1, _currentcolor);
  mesh.addvertex_xyuc(x + w, y + h, 1, 1, _currentcolor);
  mesh.addvertex_xyuc(x + w, y, 1, 0, _currentcolor);
}

void Renderer::drawtexture(
  const Texture2D& texture, float x, float y, float r, float sx, float sy,
  float ox, float oy, float skx, float sky)
{
  BatchRequest req{VertexFormat::XYUC, IndexMode::Triangles, &texture};
  req.isindexed = true;
  BatchState& state = _requestbatchstate(req);
  Mesh& mesh = state.mesh;

  int start = mesh.topindex();
  // 03
  // 12
  mesh.addindex(start, 1);
  mesh.addindex(start, 2);
  mesh.addindex(start, 3);
  mesh.addindex(start, 3);
  mesh.addindex(start, 1);
  mesh.addindex(start, 0);

  Mat4 transform;
  transform.setrotation(r);
  transform.scale(sx, sy);
  transform.skew(skx, sky);
  transform.translate(x, y);

  int w = texture.getwidth(), h = texture.getheight();

  float tlx = ox, tly = oy;
  transform.applytransform(&tlx, &tly);
  float blx = ox, bly = oy + h;
  transform.applytransform(&blx, &bly);
  float brx = ox + w, bry = oy + h;
  transform.applytransform(&brx, &bry);
  float trx = ox + w, _try = oy;
  transform.applytransform(&trx, &_try);

  mesh.addvertex_xyuc(tlx, tly, 0, 0, _currentcolor);
  mesh.addvertex_xyuc(blx, bly, 0, 1, _currentcolor);
  mesh.addvertex_xyuc(brx, bry, 1, 1, _currentcolor);
  mesh.addvertex_xyuc(trx, _try, 1, 0, _currentcolor);
}
