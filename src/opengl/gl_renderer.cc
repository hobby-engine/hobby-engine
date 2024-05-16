#include "gl_renderer.hh"

#include <cmath>

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "log.hh"
#include "mat4.hh"
#include "texture.hh"
#include "common.hh"

// COLOR SHADER

const char* colorVert = R"glsl(
#version 330 core

layout (location = 0) in vec2 ipos;

uniform mat4 proj, trans;

void main() {
  gl_Position = proj * trans * vec4(ipos, 0., 1.);
}
)glsl";

const char* colorFrag = R"glsl(
#version 330 core

uniform vec4 color;

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
    UNUSED unsigned source,
    UNUSED unsigned type,
    UNUSED unsigned id,
    unsigned severity,
    UNUSED int length,
    const char* message,
    UNUSED const void* userParam) {
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

OpenGlRenderer::OpenGlRenderer(GlfwWindow* window)
  : _window(window),
    _vertexBuffer(VertexBuffer(VertexBufferType::Array, false)),
    _indexBuffer(VertexBuffer(VertexBufferType::Index, false)),
    _vertexArray(VertexArray()),
    _colorShader(OpenGlShader::embedded(colorVert, colorFrag)),
    _textureShader(OpenGlShader::embedded(textureVert, textureFrag)) {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#ifdef HB_DEBUG
  hlog("OpenGL debug enabled.");
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(openGlMessage, nullptr);
#endif
}

void OpenGlRenderer::update() {
  int w, h;
  _window->getSize(w, h);

  _projection.setIdentity();
  _projection.ortho(0, w, h, 0, -1, 1);

  _drawCalls = _currentDrawCallCount;
  _currentDrawCallCount = 0;
}

int OpenGlRenderer::getDrawCalls() const {
  return _drawCalls;
}

void OpenGlRenderer::setColor(Color color) {
  _currentColor = color;
}

void OpenGlRenderer::clear(Color color) {
  glClearColor(
    color.r,
    color.g,
    color.b,
    color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGlRenderer::drawRect(float x, float y, float w, float h) {
  float vertices[] = {
    0, 0,
    0, h,
    w, h,
    w, 0,
  };

  _vertexBuffer.setData(2 * 4 * sizeof(float), vertices);

  int indices[] = {
    0, 1, 2, 0, 2, 3 
  };

  _indexBuffer.setData(6 * sizeof(unsigned int), indices);

  _vertexArray.setAttribute(_vertexBuffer, 0, 2, GL_FLOAT, sizeof(float) * 2, 0);

  Mat4 transform;
  transform.setTranslation(x, y);

  _colorShader.apply();
  _colorShader.sendMat4("proj", _projection);
  _colorShader.sendMat4("trans", transform);
  _colorShader.sendColor("color", _currentColor);

  _indexBuffer.bind();
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

  _currentDrawCallCount++;
}

void OpenGlRenderer::drawEllipse(float x, float y, float rx, float ry) {
  int circleResolution = fmax(2 * M_PI * sqrt((rx + ry) / 2), 8);

  float points[circleResolution * 2];

  for (int i = 0; i < circleResolution; i++) {
    int index = i * 2;
    float angle = ((float)i / circleResolution) * M_PI * 2;
    points[index]   = cosf(angle) * rx;
    points[index+1] = sinf(angle) * ry;
  }

  _vertexBuffer.setData(2 * circleResolution * sizeof(float), points);
  _vertexArray.setAttribute(_vertexBuffer, 0, 2, GL_FLOAT, sizeof(float) * 2, 0);

  Mat4 transform;
  transform.setTranslation(x, y);

  _colorShader.apply();
  _colorShader.sendMat4("proj", _projection);
  _colorShader.sendMat4("trans", transform);
  _colorShader.sendColor("color", _currentColor);

  _vertexArray.bind();
  glDrawArrays(GL_TRIANGLE_FAN, 0, circleResolution);

  _currentDrawCallCount++;
}

void OpenGlRenderer::drawVertices(int count, float* vertices) {
  _vertexBuffer.setData(count * sizeof(float), vertices);

  _vertexArray.setAttribute(_vertexBuffer, 0, 2, GL_FLOAT, sizeof(float) * 2, 0);

  Mat4 transform;
  transform.setIdentity();

  _colorShader.apply();
  _colorShader.sendMat4("proj", _projection);
  _colorShader.sendMat4("trans", transform);
  _colorShader.sendColor("color", _currentColor);

  _vertexArray.bind();
  glDrawArrays(GL_TRIANGLES, 0, count);

  _currentDrawCallCount++;
}

void OpenGlRenderer::drawBoid(float x, float y, float b, float h, float r) {
  float vertices[] = {
    0, -b/2,
    0,  b/2,
    h,  0,
  };

  _vertexBuffer.setData(2 * 3 * sizeof(float), vertices);

  _vertexArray.setAttribute(_vertexBuffer, 0, 2, GL_FLOAT, sizeof(float) * 2, 0);

  Mat4 transform;
  transform.setRotation(r);
  // transform.setIdentity();
  transform.translate(x, y);

  _colorShader.apply();
  _colorShader.sendMat4("proj", _projection);
  _colorShader.sendMat4("trans", transform);
  _colorShader.sendColor("color", _currentColor);

  _vertexArray.bind();
  glDrawArrays(GL_TRIANGLES, 0, 3);

  _currentDrawCallCount++;
}

void OpenGlRenderer::drawTexture(
    const Texture2D& texture,
    float x, float y,
    float r,
    float sx, float sy,
    float ox, float oy,
    float skx, float sky) {

  float w = (float)texture.getWidth();
  float h = (float)texture.getHeight();
  float left = ox * sx, right = (w + ox) * sx;
  float top = oy * sy, bottom = (h + oy) * sy;

  float vertices[] = {
    left,  top,    0, 0,
    left,  bottom, 0, 1,
    right, bottom, 1, 1,
    right, top,    1, 0
  };

  _vertexBuffer.setData(4 * 4 * sizeof(float), vertices);

  _vertexArray.setAttribute(
    _vertexBuffer, 0, 2, GL_FLOAT, sizeof(float) * 4, 0);
  _vertexArray.setAttribute(
    _vertexBuffer, 1, 2, GL_FLOAT, sizeof(float) * 4, 2 * sizeof(float));

  Mat4 transform;
  transform.setRotation(r);
  transform.skew(skx, sky);
  transform.scale(sx, sy);
  transform.translate(x, y);

  _textureShader.apply();
  _textureShader.sendMat4("proj", _projection);
  _textureShader.sendMat4("trans", transform);

  texture.bind();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

  _currentDrawCallCount++;
}
