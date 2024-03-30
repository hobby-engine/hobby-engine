#include "lua_wrapper.h"

static int wrap_createTexture(lua_State* L) {
  const char* path = lua_tostring(L, 1);
  hb_pushLuaData(L, hb_loadTexture(path), hb_LUA_DATA_TYPE_TEXTURE, "texturemt");
  return 1;
}

static int wrap_createSprite(lua_State* L) {
  const char* path = lua_tostring(L, 1);
  hb_pushLuaData(L, hb_loadSprite(path), hb_LUA_DATA_TYPE_SPRITE, "spritemt");
  return 1;
}

static int textureGc(lua_State* L) {
  struct hb_LuaData* wrapper = lua_touserdata(L, 1);
  hb_ensureUserdataIsOfType(L, wrapper, hb_LUA_DATA_TYPE_TEXTURE, 1);

  struct hb_Texture* texture = wrapper->data;
  hb_destroyTexture(texture);

  return 0;
}

static int spriteGc(lua_State* L) {
  struct hb_LuaData* wrapper = lua_touserdata(L, 1);
  hb_ensureUserdataIsOfType(L, wrapper, hb_LUA_DATA_TYPE_SPRITE, 1);

  struct hb_Sprite* sprite = wrapper->data;
  hb_destroySprite(sprite);

  return 0;
}

luaL_Reg textureMt[] = {
  {"__gc", textureGc},
  {NULL, NULL},
};

luaL_Reg spriteMt[] = {
  {"__gc", spriteGc},
  {NULL, NULL},
};

luaL_Reg texture[] ={
  {"load", wrap_createTexture},
  {"loadSprite", wrap_createSprite},
  {NULL, NULL},
};

void hb_luaWrapTexture(lua_State* L) {
  luaL_newmetatable(L, "texturemt");
  hb_registerFunctions(L, textureMt);
  lua_pop(L, 1);

  luaL_newmetatable(L, "spritemt");
  hb_registerFunctions(L, spriteMt);
  lua_pop(L, 1);

  hb_registerModule(L, LUA_TEXTURE_NAME, texture);
}
