#include "texture.hh"

#include <iostream>

#include "stb/stb_image.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace point {

Texture::Texture(std::string path) {
  glGenTextures(1, &_glTexture);
  glBindTexture(GL_TEXTURE_2D, _glTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(
    path.c_str(),
    &_width, &_height, &_nrChannels, 0);
  if (!data) {
    std::cout << "Failed to load texture." << std::endl;
    exit(1);
  }

  glTexImage2D(
    GL_TEXTURE_2D,
    0, GL_RGB,
    _width, _height,
    0,
    GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}

void Texture::Draw(Graphics* graphics, Vec2 position) {
}

Texture::~Texture() {
}

}
