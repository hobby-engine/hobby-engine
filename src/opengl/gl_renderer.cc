#include "gl_renderer.hh"

#include <cmath>

#include "glad/glad.h"

#include "mat4.hh"
#include "texture.hh"

OpenGlRenderer::OpenGlRenderer(OpenGlWindow* window)
  : _window(window),
    _vertexBuffer(VertexBuffer(VertexBufferType::Array, false)),
    _indexBuffer(VertexBuffer(VertexBufferType::Index, false)),
    _vertexArray(VertexArray()),
    _colorShader(OpenGlShader("res/color.vert", "res/color.frag")),
    _textureShader(OpenGlShader("res/texture.vert", "res/texture.frag")) {
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
}

void OpenGlRenderer::draw(
    const Texture2D& texture,
    float x, float y,
    float r,
    float sx, float sy,
    float ox, float oy) {

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

  int indices[] = {
    0, 1, 2, 0, 2, 3 
  };

  _indexBuffer.setData(6 * sizeof(unsigned int), indices);

  _vertexArray.setAttribute(
    _vertexBuffer, 0, 2, GL_FLOAT, sizeof(float) * 4, 0);
  _vertexArray.setAttribute(
    _vertexBuffer, 1, 2, GL_FLOAT, sizeof(float) * 4, 2 * sizeof(float));

  Mat4 transform;
  transform.setRotation(r);
  transform.scale(sx, sy);
  transform.translate(x, y);

  _textureShader.apply();
  _textureShader.sendMat4("proj", _projection);
  _textureShader.sendMat4("trans", transform);

  texture.bind();
  _indexBuffer.bind();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
