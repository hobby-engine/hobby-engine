#ifndef _POINT_ENGINE_TEXTURE_H
#define _POINT_ENGINE_TEXTURE_H

#include <string>

namespace point {

class Texture {
  public:
    Texture(std::string path);
    ~Texture();

    inline unsigned int GetId() const { return _glTexture; }

  private:
    int _width, _height, _nrChannels;
    unsigned int _glTexture;
};

} // namespace point

#endif // _POINT_ENGINE_TEXTURE_H
