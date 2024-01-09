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

void Texture::Draw(Vec2 position) const {
  int width, height;
  SDL_QueryTexture(_texture, nullptr, nullptr, &width, &height);

  SDL_Rect dest = {
    static_cast<int>(position.X),
    static_cast<int>(position.Y),
    width, height
  };
  
  SDL_RenderCopy(
    Renderer, 
    _texture,
    nullptr, &dest);
}

} // namespace Hobby
