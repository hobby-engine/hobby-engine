#include "texture.hh"

#include <iostream>
#include <stdexcept>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_render.h"

namespace Hobby {

SDL_Renderer* Texture::Renderer = nullptr;

void Texture::Initialize(const Window& window) {
  if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP) < 0) {
    throw std::runtime_error(IMG_GetError());
  }

  Renderer = window._renderer;
}

Texture::Texture(const std::string& path) {
  _texture = IMG_LoadTexture(Renderer, path.c_str());
  if (_texture == nullptr) {
    throw std::runtime_error(IMG_GetError());
  }
}

Texture::~Texture() {
  SDL_DestroyTexture(_texture);
}

Vec2 Texture::GetSize() const {
  int width, height;
  SDL_QueryTexture(_texture, nullptr, nullptr, &width, &height);
  return Vec2(width, height);
}

int Texture::GetWidth() const {
  int width;
  SDL_QueryTexture(_texture, nullptr, nullptr, &width, nullptr);
  return width;
}

int Texture::GetHeight() const {
  int height;
  SDL_QueryTexture(_texture, nullptr, nullptr, nullptr, &height);
  return height;
}

void Texture::Draw(Vec2 position, double rotation, Vec2 scale, Vec2 offset) const {
  int width, height;
  SDL_QueryTexture(_texture, nullptr, nullptr, &width, &height);

  float scaleX = scale.X, scaleY = scale.Y;

  int flip = 0;
  if (scaleX < 0) {
    flip |= SDL_FLIP_HORIZONTAL;
    scaleX *= -1;
  }
  if (scaleY < 0) {
    flip |= SDL_FLIP_VERTICAL;
    scaleY *= -1;
  }

  SDL_Point center = {
    static_cast<int>(offset.X), static_cast<int>(offset.Y),
  };

  SDL_Rect dest = {
    static_cast<int>(position.X),
    static_cast<int>(position.Y),
    static_cast<int>(width * scaleX),
    static_cast<int>(height * scaleY),
  };
  
  SDL_RenderCopyEx(
    Renderer, _texture,
    nullptr, &dest,
    rotation, &center,
    static_cast<SDL_RendererFlip>(flip)
  );
}

} // namespace Hobby
