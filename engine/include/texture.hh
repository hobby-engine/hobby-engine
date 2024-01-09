#ifndef _HOBBY_TEXTURE_H
#define _HOBBY_TEXTURE_H

#include <string>

#include "vec2.hh"
#include "window.hh"

struct SDL_Texture;
struct SDL_Renderer;

namespace Hobby {

class Texture {
public:
  Texture(const std::string& path);
  ~Texture();

  Vec2 GetSize() const;
  int GetWidth() const;
  int GetHeight() const;
  void Draw(Vec2 position, double rotation = 0, Vec2 scale = Vec2(), Vec2 offset = Vec2()) const;

  static void Initialize(const Window& window);

private:
  static SDL_Renderer* Renderer;

  SDL_Texture* _texture;
};

} // namespace Hobby

#endif // _HOBBY_TEXTURE_H
