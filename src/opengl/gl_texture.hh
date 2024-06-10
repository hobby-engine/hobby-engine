#ifndef _HOBBY_OPENGL_TEXTURE_HH
#define _HOBBY_OPENGL_TEXTURE_HH

#include "color.hh"
#include "texture.hh"

class OpenGlTexture2D final : public Texture2D
{
public:
  OpenGlTexture2D(const char* path);
  OpenGlTexture2D(Color color);
  ~OpenGlTexture2D();

  int getwidth() const override;
  int getheight() const override;
  int getchannels() const override;
  void bind() const override;

private:
  unsigned int _handle;
  FilterMode _min = FilterMode::Linear, _mag = FilterMode::Linear;
  WrapMode _wrap = WrapMode::None;
  int _width, _height;
  int _channels;
};

#endif // _HOBBY_OPENGL_TEXTURE_HH
