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
  unsigned int m_handle;
  FilterMode m_min = FilterMode::Linear, m_mag = FilterMode::Linear;
  WrapMode m_wrap = WrapMode::None;
  int m_width, m_height;
  int m_channels;
};

#endif // _HOBBY_OPENGL_TEXTURE_HH
