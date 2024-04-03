#include "texture.h"

#include "glad/glad.h"
#include "log.h"
#include "stb/stb_image.h"

static enum TextureFilter defaultMin = hb_TEXTURE_FILTER_LINEAR;
static enum TextureFilter defaultMag = hb_TEXTURE_FILTER_LINEAR;
static enum TextureWrap defaultWrap = hb_TEXTURE_WRAP_NONE;

static u32 getGlFilter(enum TextureFilter filter) {
  switch (filter) {
    case hb_TEXTURE_FILTER_LINEAR:
      return GL_LINEAR;
    case hb_TEXTURE_FILTER_NEAREST:
      return GL_NEAREST;
    default:
      fatal("Invalid filter type. This should be unreachable.\n");
      return 0;
  }
}

static u32 getGlWrap(enum TextureWrap wrap) {
  switch (wrap) {
    case hb_TEXTURE_WRAP_NONE:
      return GL_CLAMP_TO_BORDER;
    case hb_TEXTURE_WRAP_REPEAT:
      return GL_REPEAT;
    case hb_TEXTURE_WRAP_MIRRORED_REPEAT:
      return GL_MIRRORED_REPEAT;
    case hb_TEXTURE_WRAP_CLAMP:
      return GL_CLAMP_TO_EDGE;
    default:
      fatal("Invalid filter type. This should be unreachable.\n");
      return 0;
  }
}

struct Texture* loadTexture(const char* path) {
  s32 width, height, channelCount;
  u8* data = stbi_load(path, &width, &height, &channelCount, 0);

  fatalAssert(data != NULL, "Failed to load image '%s'", path);

  u32 channels;
  
  switch (channelCount) {
    case 3: channels = GL_RGB; break;
    case 4: channels = GL_RGBA; break;
  }

  u32 glId;
  glGenTextures(1, &glId);
  glBindTexture(GL_TEXTURE_2D, glId);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, getGlWrap(defaultWrap));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, getGlWrap(defaultWrap));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, getGlFilter(defaultMin));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, getGlFilter(defaultMag));

  glTexImage2D(
    GL_TEXTURE_2D, 0,
    channels, width, height, 0,
    channels, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);

  struct Texture* texture = malloc(sizeof(struct Texture));
  texture->width = width;
  texture->height = height;
  texture->min = defaultMin;
  texture->mag = defaultMag;
  texture->wrap = defaultWrap;
  texture->glId = glId;

  return texture;
}

struct Sprite* loadSprite(const char* path) {
  struct Sprite* sprite = malloc(sizeof(struct Sprite));
  sprite->texture = loadTexture(path);
  sprite->x = sprite->y = 0;
  sprite->rot = 0;
  sprite->scalex = sprite->scaley = 1;
  sprite->offsetx = sprite->offsety = 0;
  return sprite;
}

void destroyTexture(struct Texture* texture) {
  free(texture);
}

void destroySprite(struct Sprite* sprite) {
  destroyTexture(sprite->texture);
  free(sprite);
}

void setDefaultFilter(enum TextureFilter min, enum TextureFilter mag) {
  defaultMin = min;
  defaultMag = mag;
}

void setDefaultWrap(enum TextureWrap wrap) {
  defaultWrap = wrap;
}
