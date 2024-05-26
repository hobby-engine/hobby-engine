#include "gl_renderer.hh"

#include "glfw/glfw_window.hh"
#include "mesh.hh"
#include "opengl/vertex.hh"
#include "renderer.hh"

#include "glad/glad.h"

#include "common.hh"
#include "log.hh"

// TEXTURE SHADER

const char* textureVert = R"glsl(
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

const char* textureFrag = R"glsl(
#version 330 core

out vec4 fragColor;

in vec2 v_uv;
in vec4 v_color;

uniform sampler2D tex;

void main() {
  fragColor = texture(tex, v_uv) * v_color;
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
    : Renderer(window), _currentFormat(VertexFormat::XY),
      _vbo(VertexBuffer(VertexBufferType::Array, false)),
      _ibo(VertexBuffer(VertexBufferType::Index, false)), _vao(VertexArray()),
      _defaultShader(OpenGlShader::embedded(textureVert, textureFrag))
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#ifdef HB_DEBUG
  hlog("OpenGL debug enabled.");
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(openGlMessage, nullptr);
#endif

  _defaultShader.apply();

  _colorTexture = new OpenGlTexture2D({1.0, 1.0, 1.0, 1.0});

  resizeWindow(window);
}

OpenGlRenderer::~OpenGlRenderer()
{
  delete _colorTexture;
}

void OpenGlRenderer::resizeWindow(Window* window)
{
  hlog("test");
  int w, h;
  window->getSize(w, h);

  _projection.setIdentity();
  _projection.ortho(0, w, h, 0, -1, 1);

  window->setCurrent();
  glViewport(0, 0, w, h);
}

void OpenGlRenderer::clear(Color color)
{
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGlRenderer::_setAttributes()
{
  VertexFormat format = _currentFormat;
  if (_state) {
    format = _state->mesh.getFormat();
    // Nothing changed, this is a waste of our time
    if (format == _currentFormat) {
      return;
    }
  }

  size_t stride = getVertexFormatStride(format);

  switch (format) {
    case VertexFormat::XY:
      _vao.setAttribute(_vbo, 0, 2, GL_FLOAT, stride, 0);
      break;
    case VertexFormat::XYU:
      _vao.setAttribute(_vbo, 0, 2, GL_FLOAT, stride, 0);
      _vao.setAttribute(_vbo, 1, 2, GL_FLOAT, stride, 2 * sizeof(float));
      break;
    case VertexFormat::XYC:
      _vao.setAttribute(_vbo, 0, 2, GL_FLOAT, stride, 0);
      _vao.setAttribute(_vbo, 1, 4, GL_FLOAT, stride, 2 * sizeof(float));
      break;
    case VertexFormat::XYUC:
      _vao.setAttribute(_vbo, 0, 2, GL_FLOAT, stride, 0);
      _vao.setAttribute(_vbo, 1, 2, GL_FLOAT, stride, 2 * sizeof(float));
      _vao.setAttribute(_vbo, 2, 4, GL_FLOAT, stride, 4 * sizeof(float));
      break;
    default:
      return;
  }
}

GLenum OpenGlRenderer::_getGlIndexMode(IndexMode mode)
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

void OpenGlRenderer::_setupShaderForDraw(const Mat4& transform)
{
  glActiveTexture(GL_TEXTURE0);
  _colorTexture->bind();

  _defaultShader.apply();
  _defaultShader.sendInt("tex", 0);
  _defaultShader.sendMat4("proj", _projection);
  _defaultShader.sendMat4("trans", transform);
}

void OpenGlRenderer::draw()
{
  float* vertices = _state->mesh.data();

  int vertexLength = getVertexFormatVertexLength(_state->mesh.getFormat());
  int meshSize = _state->mesh.vertexCount();

  _vbo.setData(meshSize * sizeof(float), vertices);
  _setAttributes();

  Mat4 transform;
  transform.setIdentity();

  _setupShaderForDraw(transform);

  _vao.bind();

  int elementCount = meshSize / vertexLength;
  glDrawArrays(_getGlIndexMode(_state->indexMode), 0, elementCount);
}

void OpenGlRenderer::drawIndexed()
{
  float* vertices = _state->mesh.data();
  unsigned int* indices = _state->mesh.indices();

  int vertexCount = _state->mesh.vertexCount();
  int indexCount = _state->mesh.indexCount();

  _vbo.setData(vertexCount * sizeof(float), vertices);
  _ibo.setData(indexCount * sizeof(uint32_t), indices);
  _setAttributes();

  Mat4 transform;
  transform.setIdentity();

  _setupShaderForDraw(transform);

  _ibo.bind();

  GLenum indexMode = _getGlIndexMode(_state->indexMode);
  glDrawElements(indexMode, indexCount, GL_UNSIGNED_INT, nullptr);
}
