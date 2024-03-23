#include "lua_wrapper.h"

static int wrap_createTexture(lua_State* L) {
  const char* path = lua_tostring(L, 1);

  struct hb_LuaData* wrapper = lua_newuserdata(L, sizeof(struct hb_LuaData));
  wrapper->data = hb_createTexture(path);
  wrapper->type = hb_LUA_DATA_TYPE_TEXTURE;

  luaL_getmetatable(L, "texturemt");
  lua_setmetatable(L, -2);
  
  return 1;
}

static int wrap_createSprite(lua_State* L) {
  const char* path = lua_tostring(L, 1);

  struct hb_LuaData* wrapper = lua_newuserdata(L, sizeof(struct hb_LuaData));
  wrapper->data = hb_createSprite(path);
  wrapper->type = hb_LUA_DATA_TYPE_SPRITE;

  luaL_getmetatable(L, "spritemt");
  lua_setmetatable(L, -2);

  return 1;
}

static int textureGc(lua_State* L) {
  struct hb_LuaData* wrapper = lua_touserdata(L, 1);
  if (wrapper->type != hb_LUA_DATA_TYPE_TEXTURE) {
    lua_pushstring(L, "Expected type of Texture.");
    return lua_error(L);
  }

  struct hb_Texture* texture = wrapper->data;
  hb_destroyTexture(texture);

  return 0;
}

static int spriteGc(lua_State* L) {
  struct hb_LuaData* wrapper = lua_touserdata(L, 1);
  if (wrapper->type != hb_LUA_DATA_TYPE_SPRITE) {
    lua_pushstring(L, "Expected type of Sprite.");
    return lua_error(L);
  }

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
  {"create", wrap_createTexture},
  {"createSprite", wrap_createSprite},
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
