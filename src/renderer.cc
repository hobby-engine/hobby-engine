#include "renderer.hh"

#include "mesh.hh"
#include <cmath>

Renderer::Renderer(Window* window) : m_window(window)
{
}

Renderer::~Renderer()
{
  delete m_state;
}

void Renderer::update()
{
  m_drawcalls = m_currentdrawcallcount;
  m_currentdrawcallcount = 0;
}

void Renderer::present()
{
  if (m_state != nullptr) {
    m_flushdrawqueue();
  }

  m_window->present();
}

void Renderer::m_flushdrawqueue()
{
  if (m_state->mesh.isindexed()) {
    drawindexed();
  } else {
    draw();
  }
  m_currentdrawcallcount++;

  delete m_state;
  m_state = nullptr;
}

BatchState& Renderer::m_requestbatchstate(const BatchRequest& req)
{
  bool newstate = false;
  bool flush = false;

  // If there is no command before this one, make one.
  if (m_state == nullptr) {
    newstate = true;
  } else {
    bool canbatch = m_state->texture == req.texture &&
                    m_state->mesh.getformat() == req.vertexformat &&
                    m_state->indexmode == req.indexmode &&
                    m_state->mesh.isindexed();
    if (!canbatch) {
      // We can't batch anything more past this point, so we draw everything
      // we've collected so far.
      flush = true;
    }
  }

  if (flush) {
    m_flushdrawqueue();
  }

  if (newstate || flush) {
    BatchState* state = new BatchState(req);
    m_state = state;
    return *state;
  }

  m_currentbatchedcalls++;
  return *m_state;
}

void Renderer::drawellipse(float x, float y, float rx, float ry)
{
  BatchRequest req{VertexFormat::XYUC, IndexMode::Triangles, nullptr};
  req.isindexed = true;
  BatchState& state = m_requestbatchstate(req);
  Mesh& mesh = state.mesh;

  int start = mesh.topindex();
  int circleres = fmax(2 * M_PI * sqrt((rx + ry) / 2), 8);

  for (float i = 0; i < circleres; i++) {
    float angle = (i / circleres) * M_PI * 2;
    float c = cosf(angle);
    float s = sinf(angle);
    float px = x + c * rx;
    float py = y + s * ry;

    if (i > 2) {
      mesh.addindex(start, 0);
      mesh.addindex(start, i - 1);
      mesh.addindex(start, i);
    }
    mesh.addvertex_xyuc(px, py, c * 0.5 + 0.5, s * 0.5 + 0.5, m_currentcolor);
  }
}

void Renderer::drawrect(float x, float y, float w, float h)
{
  BatchRequest req{VertexFormat::XYUC, IndexMode::Triangles, nullptr};
  req.isindexed = true;
  BatchState& state = m_requestbatchstate(req);
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

  mesh.addvertex_xyuc(x, y, 0, 0, m_currentcolor);
  mesh.addvertex_xyuc(x, y + h, 0, 1, m_currentcolor);
  mesh.addvertex_xyuc(x + w, y + h, 1, 1, m_currentcolor);
  mesh.addvertex_xyuc(x + w, y, 1, 0, m_currentcolor);
}

void Renderer::drawtexture(
  const Texture2D& texture, float x, float y, float r, float sx, float sy,
  float ox, float oy, float skx, float sky)
{
  BatchRequest req{VertexFormat::XYUC, IndexMode::Triangles, &texture};
  req.isindexed = true;
  BatchState& state = m_requestbatchstate(req);
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

  int w = texture.getwidth();
  int h = texture.getheight();

  float tlx = ox;
  float tly = oy;
  transform.applytransform(&tlx, &tly);
  float blx = ox;
  float bly = oy + h;
  transform.applytransform(&blx, &bly);
  float brx = ox + w;
  float bry = oy + h;
  transform.applytransform(&brx, &bry);
  float trx = ox + w;
  float _try = oy;
  transform.applytransform(&trx, &_try);

  mesh.addvertex_xyuc(tlx, tly, 0, 0, m_currentcolor);
  mesh.addvertex_xyuc(blx, bly, 0, 1, m_currentcolor);
  mesh.addvertex_xyuc(brx, bry, 1, 1, m_currentcolor);
  mesh.addvertex_xyuc(trx, _try, 1, 0, m_currentcolor);
}
