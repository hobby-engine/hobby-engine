#ifndef _HOBBY_TEXTURE_H
#define _HOBBY_TEXTURE_H

#include "basic_types.h"
#include "linmath.h"

enum hb_TextureFilter {
  hb_TEXTURE_FILTER_NEAREST,
  hb_TEXTURE_FILTER_LINEAR,
};

enum hb_TextureWrap {
  hb_TEXTURE_WRAP_NONE,
  hb_TEXTURE_WRAP_REPEAT,
  hb_TEXTURE_WRAP_MIRRORED_REPEAT,
  hb_TEXTURE_WRAP_CLAMP,
};

struct hb_Texture {
  u32 glId;
  s32 width, height;
  enum hb_TextureFilter min, mag;
  enum hb_TextureWrap wrap;
};

struct hb_Sprite {
  struct hb_Texture texture;
  f32 x, y;
  f32 rot;
  f32 scalex, scaley;
  f32 offsetx, offsety;
};

struct hb_Texture hb_createTexture(const char* path);
struct hb_Sprite hb_createSprite(const char* path);
void hb_setDefaultFilter(enum hb_TextureFilter min, enum hb_TextureFilter mag);
void hb_setDefaultWrap(enum hb_TextureWrap wrap);

#endif // _HOBBY_TEXTURE_H
