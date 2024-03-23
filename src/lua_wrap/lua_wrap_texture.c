#include "lua_wrapper.h"

static int wrap_createTexture(lua_State* L) {
  const char* path = lua_tostring(L, 1);

  struct hb_LuaTexture* wrapper = lua_newuserdata(L, sizeof(struct hb_LuaTexture));
  wrapper->texture = hb_createTexture(path);
  
  return 1;
}

static int wrap_createSprite(lua_State* L) {
  const char* path = lua_tostring(L, 1);

  struct hb_LuaSprite* wrapper = lua_newuserdata(L, sizeof(struct hb_LuaSprite));
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
