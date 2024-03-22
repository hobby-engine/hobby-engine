#ifndef _HOBBY_TEXTURE_H
#define _HOBBY_TEXTURE_H

#include "basic_types.h"

typedef enum {
  hb_TEXTURE_FILTER_NEAREST,
  hb_TEXTURE_FILTER_LINEAR,
} hb_TextureFilter;

typedef enum {
  hb_TEXTURE_WRAP_NONE,
  hb_TEXTURE_WRAP_REPEAT,
  hb_TEXTURE_WRAP_MIRRORED_REPEAT,
  hb_TEXTURE_WRAP_CLAMP,
} hb_TextureWrap;

typedef struct {
  u32 glId;
  s32 width, height;
  hb_TextureFilter min, mag;
  hb_TextureWrap wrap;
} hb_Texture;

hb_Texture hb_createTexture(const char* path);
void hb_setDefaultFilter(hb_TextureFilter min, hb_TextureFilter mag);
void hb_setDefaultWrap(hb_TextureWrap wrap);

#endif // _HOBBY_TEXTURE_H
