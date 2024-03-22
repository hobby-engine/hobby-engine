#include "lua_wrapper.h"

static int wrap_createTexture(lua_State* L) {
  const char* path = lua_tostring(L, 1);

  hb_LuaTexture* wrapper = (hb_LuaTexture*)lua_newuserdata(L, sizeof(hb_LuaTexture));
  wrapper->texture = hb_createTexture(path);
  
  return 1;
}

luaL_Reg texture[] ={
  {"create", wrap_createTexture},
  {NULL, NULL},
};

void hb_luaWrapTexture(lua_State* L) {
  hb_registerModule(L, LUA_TEXTURE_NAME, texture);
}
