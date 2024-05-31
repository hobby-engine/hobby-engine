#include "gl_renderer.hh"

#include "glfw/glfw_window.hh"
#include "mesh.hh"
#include "opengl/vertex.hh"
#include "renderer.hh"

#include "glad/glad.h"

#include "common.hh"
#include "log.hh"

// TEXTURE SHADER

const char* defaultvert = R"glsl(
#version 330 core

in vec2 ipos;
in vec2 iuv;
in vec4 icolor;

uniform mat4 proj, trans;

out vec2 v_uv;
out vec4 v_color;

void main() {
  gl_Position = proj * trans * vec4(ipos, 0., 1.);

  v_uv = iuv;
  v_color = icolor;
}
)glsl";

const char* defaultfrag = R"glsl(
#version 330 core

out vec4 fragcolor;

in vec2 v_uv;
in vec4 v_color;

uniform sampler2D tex;

void main() {
  fragcolor = texture(tex, v_uv) * v_color;
}
)glsl";

void openGlMessage(
  UNUSED unsigned source, UNUSED unsigned type, UNUSED unsigned id,
  unsigned severity, UNUSED int length, const char* message,
  UNUSED const void* userParam)
{
  switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
    case GL_DEBUG_SEVERITY_MEDIUM:
      error("OpenGL: %s", message);
      return;
    case GL_DEBUG_SEVERITY_LOW:
      warn("OpenGL: %s", message);
      return;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      hlog("OpenGL: %s", message);
      return;
  }

  error("Unknown severity level!");
}

OpenGlRenderer::OpenGlRenderer(Window* window)
    : Renderer(window), _currentformat(VertexFormat::XY),
      _vbo(VertexBuffer(VertexBufferType::Array, false)),
      _ibo(VertexBuffer(VertexBufferType::Index, false)), _vao(VertexArray()),
      _defaultshader(OpenGlShader::embedded(defaultvert, defaultfrag))
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#ifdef HB_DEBUG
  hlog("OpenGL debug enabled.");
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(openGlMessage, nullptr);
#endif

  _defaultshader.apply();

  _coltex = new OpenGlTexture2D({1.0, 1.0, 1.0, 1.0});

  resizewindow(window);
}

OpenGlRenderer::~OpenGlRenderer()
{
  delete _coltex;
}

void OpenGlRenderer::initopengl()
{
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    fatal("Failed to initialize glad.");
  }
}

void OpenGlRenderer::resizewindow(Window* window)
{
  int w, h;
  window->getsize(w, h);

  _projection.setidentity();
  _projection.ortho(0, w, h, 0, -1, 1);

  window->makecurrent();
  glViewport(0, 0, w, h);
}

void OpenGlRenderer::clear(Color color)
{
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGlRenderer::_setattribs()
{
  VertexFormat format = _currentformat;
  if (_state) {
    format = _state->mesh.getformat();
    // Nothing changed, this is a waste of our time
    if (format == _currentformat) {
      return;
    }
  }

  size_t stride = getvertformatstride(format);

  switch (format) {
    case VertexFormat::XY:
      _vao.setattrib(_vbo, 0, 2, GL_FLOAT, stride, 0);
      break;
    case VertexFormat::XYU:
      _vao.setattrib(_vbo, 0, 2, GL_FLOAT, stride, 0);
      _vao.setattrib(_vbo, 1, 2, GL_FLOAT, stride, 2 * sizeof(float));
      break;
    case VertexFormat::XYC:
      _vao.setattrib(_vbo, 0, 2, GL_FLOAT, stride, 0);
      _vao.setattrib(_vbo, 1, 4, GL_FLOAT, stride, 2 * sizeof(float));
      break;
    case VertexFormat::XYUC:
      _vao.setattrib(_vbo, 0, 2, GL_FLOAT, stride, 0);
      _vao.setattrib(_vbo, 1, 2, GL_FLOAT, stride, 2 * sizeof(float));
      _vao.setattrib(_vbo, 2, 4, GL_FLOAT, stride, 4 * sizeof(float));
      break;
    default:
      return;
  }
}

GLenum OpenGlRenderer::_getglindexmode(IndexMode mode)
{
  switch (mode) {
    case IndexMode::Triangles:
      return GL_TRIANGLES;
    case IndexMode::TriangleFan:
      return GL_TRIANGLE_FAN;
    case IndexMode::TriangleStripe:
      return GL_TRIANGLE_STRIP;
  }

  // Unreachable.
  return GL_TRIANGLES;
}

void OpenGlRenderer::_setupshader(const Mat4& transform)
{
  glActiveTexture(GL_TEXTURE0);
  _coltex->bind();

  _defaultshader.apply();

  if (_state->texture) {
    _state->texture->bind();
  }
  _defaultshader.sendint("tex", 0);
  _defaultshader.sendmat4("proj", _projection);
  _defaultshader.sendmat4("trans", transform);
}

void OpenGlRenderer::draw()
{
  float* vertices = _state->mesh.data();

  int vertexlen = getverformatlen(_state->mesh.getformat());
  int meshlen = _state->mesh.vertexcount();

  _vbo.setdata(meshlen * sizeof(float), vertices);
  _setattribs();

  Mat4 transform;
  transform.setidentity();

  _setupshader(transform);

  _vao.bind();

  int elementc = meshlen / vertexlen;
  glDrawArrays(_getglindexmode(_state->indexmode), 0, elementc);
}

void OpenGlRenderer::drawindexed()
{
  float* vertices = _state->mesh.data();
  unsigned int* indices = _state->mesh.indices();

  int vertexcount = _state->mesh.vertexcount();
  int indexcount = _state->mesh.indexcount();

  _vbo.setdata(vertexcount * sizeof(float), vertices);
  _ibo.setdata(indexcount * sizeof(uint32_t), indices);
  _setattribs();

  Mat4 transform;
  transform.setidentity();

  _setupshader(transform);

  _ibo.bind();

  GLenum indexmode = _getglindexmode(_state->indexmode);
  glDrawElements(indexmode, indexcount, GL_UNSIGNED_INT, nullptr);
}
