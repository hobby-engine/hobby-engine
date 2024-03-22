#include "lua_wrapper.h"

static int wrap_createTexture(lua_State* L) {
  const char* path = lua_tostring(L, 1);

  hb_LuaTexture* wrapper = (hb_LuaTexture*)lua_newuserdata(L, sizeof(hb_LuaTexture));
  wrapper->texture = hb_createTexture(path);
  
  return 1;
}

static int wrap_createSprite(lua_State* L) {
  const char* path = lua_tostring(L, 1);

  hb_LuaSprite* wrapper = (hb_LuaSprite*)lua_newuserdata(L, sizeof(hb_LuaSprite));
  wrapper->sprite = hb_createSprite(path);
  
  return 1;
}

luaL_Reg texture[] ={
  {"create", wrap_createTexture},
  {"createSprite", wrap_createSprite},
  {NULL, NULL},
};

void hb_luaWrapTexture(lua_State* L) {
  hb_registerModule(L, LUA_TEXTURE_NAME, texture);
}
