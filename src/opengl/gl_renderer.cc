#include "gl_renderer.hh"

#include "mesh.hh"
#include "opengl/vertex.hh"
#include "renderer.hh"

#include "glad/glad.h"

#include "common.hh"
#include "log.hh"

// COLOR SHADER

const char* colorVert = R"glsl(
#version 330 core

layout (location = 0) in vec2 ipos;
layout (location = 1) in vec4 icolor;

uniform mat4 proj, trans;

out vec4 color;

void main() {
  gl_Position = proj * trans * vec4(ipos, 0., 1.);
  color = icolor;
}
)glsl";

const char* colorFrag = R"glsl(
#version 330 core

in vec4 color;

out vec4 fragColor;

void main() {
  fragColor = color;
}
)glsl";

// TEXTURE SHADER

const char* textureVert = R"glsl(
#version 330 core

layout (location = 0) in vec2 ipos;
layout (location = 1) in vec2 iuv;

uniform mat4 proj, trans;

out vec2 uv;

void main() {
  gl_Position = proj * trans * vec4(ipos, 0., 1.);

  uv = iuv;
}
)glsl";

const char* textureFrag = R"glsl(
#version 330 core

out vec4 fragColor;

in vec2 uv;

uniform sampler2D tex;

void main() {
  fragColor = texture(tex, uv);
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
    : Renderer(window), _vbo(VertexBuffer(VertexBufferType::Array, false)),
      _ibo(VertexBuffer(VertexBufferType::Index, false)), _vao(VertexArray()),
      _colorShader(OpenGlShader::embedded(colorVert, colorFrag)),
      _textureShader(OpenGlShader::embedded(textureVert, textureFrag))
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#ifdef HB_DEBUG
  hlog("OpenGL debug enabled.");
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(openGlMessage, nullptr);
#endif
}

void OpenGlRenderer::clear(Color color)
{
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGlRenderer::_setAttributes()
{
  VertexFormat format = _state->mesh.getFormat();
  switch (format) {
    case VertexFormat::XY:
      _vao.setAttribute(_vbo, 0, 2, GL_FLOAT, getVertexFormatStride(format), 0);
      break;
    case VertexFormat::XYU:
      _vao.setAttribute(_vbo, 0, 2, GL_FLOAT, getVertexFormatStride(format), 0);
      _vao.setAttribute(
        _vbo, 1, 2, GL_FLOAT, getVertexFormatStride(format), 2 * sizeof(float));
      break;
    case VertexFormat::XYC:
      _vao.setAttribute(_vbo, 0, 2, GL_FLOAT, getVertexFormatStride(format), 0);
      _vao.setAttribute(
        _vbo, 1, 4, GL_FLOAT, getVertexFormatStride(format), 2 * sizeof(float));
      break;
    case VertexFormat::XYUC:
      _vao.setAttribute(_vbo, 0, 2, GL_FLOAT, getVertexFormatStride(format), 0);
      _vao.setAttribute(
        _vbo, 1, 2, GL_FLOAT, getVertexFormatStride(format), 2 * sizeof(float));
      _vao.setAttribute(
        _vbo, 2, 4, GL_FLOAT, getVertexFormatStride(format), 4 * sizeof(float));
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

void OpenGlRenderer::draw()
{
  float* vertices = _state->mesh.data();

  int vertexLength = getVertexFormatVertexLength(_state->mesh.getFormat());
  int meshSize = _state->mesh.vertexCount();

  _vbo.setData(meshSize * sizeof(float), vertices);
  _setAttributes();

  Mat4 transform;
  transform.setIdentity();

  _colorShader.apply();
  _colorShader.sendMat4("proj", _projection);
  _colorShader.sendMat4("trans", transform); // TODO: Get rid of this.

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

  _colorShader.apply();
  _colorShader.sendMat4("proj", _projection);
  _colorShader.sendMat4("trans", transform); // TODO: Get rid of this.

  _ibo.bind();

  hlog("=== INDICES ===");
  int l = getVertexFormatVertexLength(_state->mesh.getFormat());
  for (int i = 0; i < indexCount; i++) {
    int index = indices[i];
    float x = vertices[index * l];
    float y = vertices[index * l + 1];
    hlog("%d = %g, %g", index, x, y);
  }

  GLenum indexMode = _getGlIndexMode(_state->indexMode);
  glDrawElements(indexMode, indexCount, GL_UNSIGNED_INT, nullptr);
}
