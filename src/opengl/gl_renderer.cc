#include "gl_renderer.hh"

#include "glad/glad.h"
#include "mat4.hh"
#include <cmath>

OpenGlRenderer::OpenGlRenderer(OpenGlWindow* window)
  : _window(window),
    _vertexBuffer(VertexBuffer(VertexBufferType::Array, false)),
    _indexBuffer(VertexBuffer(VertexBufferType::Index, false)),
    _vertexArray(VertexArray()),
    _colorShader(OpenGlShader("res/color.vert", "res/color.frag")) {
}

void OpenGlRenderer::update() {

  int w, h;
  _window->getSize(w, h);

  _projection.setIdentity();
  _projection.ortho(0, w, h, 0, -1, 1);
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
}
