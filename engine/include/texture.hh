#ifndef _HOBBY_ENGINE_TEXTURE_H
#define _HOBBY_ENGINE_TEXTURE_H

#include <string>

#include "SDL2/SDL.h"

#include "quad.hh"
#include "vec2.hh"
#include "shader.hh"
#include "graphics.hh"

namespace Hobby {

/// TEXTURES AAAAAA
class Texture {
  public:
    /// @brief Load texture from path.
    Texture(std::string path);
    ~Texture();

    /// @brief Draw the texture.
    void Draw(Vec2 position);
    /// @brief Set a new quad.
    void SetQuad(Quad quad);

  private:
    int _width, _height, _nrChannels;
    Quad _quad;
    Shader _shader;
    unsigned int _glTexture;
};

} // namespace Hobby

#endif // _HOBBY_ENGINE_TEXTURE_H
