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

  int getWidth() const override;
  int getHeight() const override;
  int getChannelCount() const override;
  void bind() const override;

  unsigned int handle;

private:
  FilterMode _min = FilterMode::Linear, _mag = FilterMode::Linear;
  WrapMode _wrap = WrapMode::None;
  int _width, _height;
  int _channelCount;
};

#endif // _HOBBY_OPENGL_TEXTURE_HH
