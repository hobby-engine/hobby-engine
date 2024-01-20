#ifndef _HOBBY_LUA_TEXTURE_H
#define _HOBBY_LUA_TEXTURE_H

#include "luajit/lua.hpp"
#include "texture.hh"

#define TEXTURE_NAME "Texture"

struct TextureWrapper {
  Hobby::Texture* Texture;
};

int WrapTexture(lua_State* L);

#endif
