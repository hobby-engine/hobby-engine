#include "quad.hh"

#include "glad/glad.h"

namespace Hobby {

Quad::Quad(float x, float y, float w, float h)
    : X(x), Y(y), W(w), H(h) {
  const float vertices[] = {
  //Pos                UV
    X,     Y,     0,   0, 0, // Top left
    X + W, Y,     0,   1, 0, // Top right
    X,     Y + H, 0,   0, 1, // Bottom left
    X + W, Y + H, 0,   1, 1, // Bottom right
  };

  const int indices[] = {
    0, 1, 2,
    2, 1, 3,
  };

  glGenVertexArrays(1, &_vao);
  glGenBuffers(1, &_vbo);
  glGenBuffers(1, &_ebo);

  glBindVertexArray(_vao);

  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
}

Quad::~Quad() {
  glDeleteVertexArrays(1, &_vao);
  glDeleteBuffers(1, &_vbo);
  glDeleteBuffers(1, &_ebo);
}

void Quad::Draw() {
  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

} // namespace Hobby
