#include "gl_texture.hh"

#include <cstdint>

#include "glad/glad.h"
#include "stb/stb_image.h"

#include "log.hh"
#include "texture.hh"

static int hobbyFilterToOpenGl(FilterMode filter)
{
  switch (filter) {
    case FilterMode::Linear:
      return GL_LINEAR;
    case FilterMode::Nearest:
      return GL_NEAREST;
    default:
      error("Invalid filter type. This should be unreachable.\n");
      return 0;
  }
}

static int hobbyWrapToOpenGl(WrapMode mode)
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
      error("Invalid filter type. This should be unreachable.\n");
      return 0;
  }
}

OpenGlTexture2D::OpenGlTexture2D(const char* path)
{
  uint8_t* data = stbi_load(path, &_width, &_height, &_channelCount, 0);

  fatalAssert(data != nullptr, "Failed to load image '%s'", path);

  int channels = -1;

  switch (_channelCount) {
    case 3:
      channels = GL_RGB;
      break;
    case 4:
      channels = GL_RGBA;
      break;
    default:
      fatal("Unsupported channel format.");
  }

  glGenTextures(1, &handle);
  glBindTexture(GL_TEXTURE_2D, handle);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, hobbyWrapToOpenGl(_wrap));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, hobbyWrapToOpenGl(_wrap));
  glTexParameteri(
    GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, hobbyFilterToOpenGl(_min));
  glTexParameteri(
    GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, hobbyFilterToOpenGl(_mag));

  glTexImage2D(
    GL_TEXTURE_2D, 0, channels, _width, _height, 0, channels, GL_UNSIGNED_BYTE,
    data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}

OpenGlTexture2D::OpenGlTexture2D(Color color)
{
  glGenTextures(1, &handle);
  glBindTexture(GL_TEXTURE_2D, handle);

  _wrap = WrapMode::Repeat;

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, hobbyWrapToOpenGl(_wrap));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, hobbyWrapToOpenGl(_wrap));
  glTexParameteri(
    GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, hobbyFilterToOpenGl(_min));
  glTexParameteri(
    GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, hobbyFilterToOpenGl(_mag));

  uint8_t bColor[4] = {
    (uint8_t)(color.r * UINT8_MAX), (uint8_t)(color.g * UINT8_MAX),
    (uint8_t)(color.b * UINT8_MAX), (uint8_t)(color.a * UINT8_MAX)};

  _width = 1;
  _height = 1;
  _channelCount = 4;

  glTexImage2D(
    GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
    bColor);
}

OpenGlTexture2D::~OpenGlTexture2D()
{
  glDeleteTextures(0, &handle);
}

int OpenGlTexture2D::getWidth() const
{
  return _width;
}

int OpenGlTexture2D::getHeight() const
{
  return _height;
}

int OpenGlTexture2D::getChannelCount() const
{
  return _channelCount;
}

void OpenGlTexture2D::bind() const
{
  glBindTexture(GL_TEXTURE_2D, handle);
}
