#include "lua_wrapper.h"

static int wrap_getFps(lua_State* L) {
  lua_getfield(L, LUA_REGISTRYINDEX, "wrapper");
  struct LuaWrapper* wrapper = lua_touserdata(L, -1);

  lua_pushnumber(L, wrapper->engine->time->fps);
  return 1;
}

static int wrap_getDeltaTime(lua_State* L) {
  lua_getfield(L, LUA_REGISTRYINDEX, "wrapper");
  struct LuaWrapper* wrapper = lua_touserdata(L, -1);
  
  lua_pushnumber(L, wrapper->engine->time->deltaTime);
  return 1;
}

luaL_Reg time[] = {
  {"getFps", wrap_getFps},
  {"getDeltaTime", wrap_getDeltaTime},
  {NULL, NULL},
};

void luaWrapTime(lua_State* L) {
  registerModule(L, LUA_TIME_NAME, time);
}
