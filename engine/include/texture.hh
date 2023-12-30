#ifndef _POINT_ENGINE_TEXTURE_H
#define _POINT_ENGINE_TEXTURE_H

#include <string>

#include "SDL2/SDL.h"

#include "vec2.hh"
#include "graphics.hh"

namespace point {

/// TEXTURES AAAAAA
class Texture {
  public:
    /// @brief Load texture from path.
    Texture(std::string path);
    ~Texture();

    void Draw(Graphics* graphics, Vec2 position);

  private:
    int _width, _height, _nrChannels;
    unsigned int _glTexture;
};

} // namespace point

#endif // _POINT_ENGINE_TEXTURE_H
