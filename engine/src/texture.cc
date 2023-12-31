#include "texture.hh"

#include <iostream>

#include "stb/stb_image.h"
#include "glad/glad.h"

#include "builtin_shaders.hh"

namespace Hobby {

Texture::Texture(std::string path)
    : _quad(Quad(-0.5, -0.5, 1, 1)),
      _shader(Shader(vertexSource, fragmentSource)) {
  glGenTextures(1, &_glTexture);

  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(
    path.c_str(),
    &_width, &_height, &_nrChannels, 0);
  if (data == nullptr) {
    std::cout << "Failed to load texture." << stbi_failure_reason() << std::endl;
    exit(1);
  }

  GLenum format = _nrChannels == 3 ? GL_RGB : GL_RGBA;

  glBindTexture(GL_TEXTURE_2D, _glTexture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(
    GL_TEXTURE_2D,
    0, format,
    _width, _height,
    0, format, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}

void Texture::Draw(Vec2 position) {
  _shader.Apply();
  glBindTexture(GL_TEXTURE_2D, _glTexture);
  _quad.Draw();
  glUseProgram(0);
}

Texture::~Texture() {
}

}
