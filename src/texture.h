#ifndef _HOBBY_TEXTURE_H
#define _HOBBY_TEXTURE_H

#include "typedefs.h"
#include "linmath.h"

enum TextureFilter {
  hb_TEXTURE_FILTER_NEAREST,
  hb_TEXTURE_FILTER_LINEAR,
};

enum TextureWrap {
  hb_TEXTURE_WRAP_NONE,
  hb_TEXTURE_WRAP_REPEAT,
  hb_TEXTURE_WRAP_MIRRORED_REPEAT,
  hb_TEXTURE_WRAP_CLAMP,
};

struct Texture {
  u32 glId;
  s32 width, height;
  enum TextureFilter min, mag;
  enum TextureWrap wrap;
};

struct Sprite {
  struct Texture* texture;
  f32 x, y;
  f32 rot;
  f32 scalex, scaley;
  f32 offsetx, offsety;
};

struct Texture* loadTexture(const char* path);
struct Sprite* loadSprite(const char* path);
void destroyTexture(struct Texture* texture);
void destroySprite(struct Sprite* sprite);

void setDefaultFilter(enum TextureFilter min, enum TextureFilter mag);
void setDefaultWrap(enum TextureWrap wrap);

#endif // _HOBBY_TEXTURE_H
