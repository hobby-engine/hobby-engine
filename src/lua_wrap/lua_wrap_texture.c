#include "lua_wrapper.h"

static int wrap_createTexture(lua_State* L) {
  const char* path = lua_tostring(L, 1);
  pushLuaData(L, loadTexture(path), LUA_DATA_TYPE_TEXTURE, "texturemt");
  return 1;
}

static int wrap_createSprite(lua_State* L) {
  const char* path = lua_tostring(L, 1);
  pushLuaData(L, loadSprite(path), LUA_DATA_TYPE_SPRITE, "spritemt");
  return 1;
}

static int textureGc(lua_State* L) {
  struct LuaData* wrapper = lua_touserdata(L, 1);
  ensureUserdataIsOfType(L, wrapper, LUA_DATA_TYPE_TEXTURE, 1);

  struct Texture* texture = wrapper->data;
  destroyTexture(texture);

  return 0;
}

static int spriteGc(lua_State* L) {
  struct LuaData* wrapper = lua_touserdata(L, 1);
  ensureUserdataIsOfType(L, wrapper, LUA_DATA_TYPE_SPRITE, 1);

  struct Sprite* sprite = wrapper->data;
  destroySprite(sprite);

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

void luaWrapTexture(lua_State* L) {
  luaL_newmetatable(L, "texturemt");
  registerFunctions(L, textureMt);
  lua_pop(L, 1);

  luaL_newmetatable(L, "spritemt");
  registerFunctions(L, spriteMt);
  lua_pop(L, 1);

  registerModule(L, LUA_TEXTURE_NAME, texture);
}
