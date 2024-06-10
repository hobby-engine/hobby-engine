#include "gl_texture.hh"

#include <cstdint>

#include "glad/glad.h"
#include "stb/stb_image.h"

#include "log.hh"
#include "texture.hh"

static int getglfilter(FilterMode filter)
{
  switch (filter) {
    case FilterMode::Linear:
      return GL_LINEAR;
    case FilterMode::Nearest:
      return GL_NEAREST;
    default:
      Logger::instance()->error(
        "Invalid filter type. This should be unreachable.\n");
      return 0;
  }
}

static int getglwrap(WrapMode mode)
{
  switch (mode) {
    case WrapMode::None:
      return GL_CLAMP_TO_BORDER;
    case WrapMode::Repeat:
      return GL_REPEAT;
    case WrapMode::MirroredRepeat:
      return GL_MIRRORED_REPEAT;
    case WrapMode::Clamp:
      return GL_CLAMP_TO_EDGE;
    default:
      Logger::instance()->error(
        "Invalid filter type. This should be unreachable.\n");
      return 0;
  }
}

OpenGlTexture2D::OpenGlTexture2D(const char* path)
{
  uint8_t* data = stbi_load(path, &m_width, &m_height, &m_channels, 0);

  if (!Logger::instance()->fassert(
        data != nullptr, "Failed to load image '%s'", path)) {
    std::exit(1);
  }

  int channels = -1;

  switch (m_channels) {
    case 3:
      channels = GL_RGB;
      break;
    case 4:
      channels = GL_RGBA;
      break;
    default:
      Logger::instance()->fatal("Unsupported channel format.");
      std::exit(1);
  }

  glGenTextures(1, &m_handle);
  glBindTexture(GL_TEXTURE_2D, m_handle);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, getglwrap(m_wrap));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, getglwrap(m_wrap));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, getglfilter(m_min));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, getglfilter(m_mag));

  glTexImage2D(
    GL_TEXTURE_2D, 0, channels, m_width, m_height, 0, channels,
    GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}

OpenGlTexture2D::OpenGlTexture2D(Color color)
{
  glGenTextures(1, &m_handle);
  glBindTexture(GL_TEXTURE_2D, m_handle);

  m_wrap = WrapMode::Repeat;

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, getglwrap(m_wrap));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, getglwrap(m_wrap));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, getglfilter(m_min));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, getglfilter(m_mag));

  uint8_t bcolor[4] = {
    (uint8_t)(color.r * UINT8_MAX), (uint8_t)(color.g * UINT8_MAX),
    (uint8_t)(color.b * UINT8_MAX), (uint8_t)(color.a * UINT8_MAX)};

  m_width = 1;
  m_height = 1;
  m_channels = 4;

  glTexImage2D(
    GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
    bcolor);
}

OpenGlTexture2D::~OpenGlTexture2D()
{
  glDeleteTextures(0, &m_handle);
}

int OpenGlTexture2D::getwidth() const
{
  return m_width;
}

int OpenGlTexture2D::getheight() const
{
  return m_height;
}

int OpenGlTexture2D::getchannels() const
{
  return m_channels;
}

void OpenGlTexture2D::bind() const
{
  glBindTexture(GL_TEXTURE_2D, m_handle);
}
