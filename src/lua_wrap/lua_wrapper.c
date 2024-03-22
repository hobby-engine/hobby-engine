#include "lua_wrapper.h"

#include "lua.h"
#include "luaheaders.h"
#include "log.h"

static int errorHandler(lua_State* L) {
  const char* errorMessage = lua_tostring(L, -1);
  hb_fatal(errorMessage);

  return 0;
}

hb_LuaWrapper* hb_createLuaWrapper(hb_Engine* engine) {
  lua_State* L = luaL_newstate();

  hb_LuaWrapper* wrapper = lua_newuserdata(L, sizeof(hb_LuaWrapper));
  lua_setfield(L, LUA_REGISTRYINDEX, "wrapper");

  wrapper->engine = engine;
  wrapper->L = L;
  luaL_openlibs(L);

  lua_pushcfunction(L, errorHandler);
  wrapper->errorHandlerIndex = lua_gettop(L);

  lua_newtable(L);
  lua_setglobal(L, LUA_LIB_NAME);

  hb_luaWrapRenderer(L);
  hb_luaWrapTime(L);
  hb_luaWrapTexture(L);

  s32 res = luaL_dofile(L, "main.lua");
  if (res != LUA_OK) {
    lua_close(L);
    errorHandler(L);
  }

  return wrapper;
}

void hb_callLuaCallback(hb_LuaWrapper* wrapper, const char* fnName) {
  lua_State* L = wrapper->L;
  lua_getglobal(L, LUA_LIB_NAME);

  lua_getfield(L, -1, fnName);
  if (lua_isfunction(L, -1)) {
    lua_call(L, 0, 0);
  }
  lua_pop(L, 1);
}

void hb_destroyLuaWrapper(hb_LuaWrapper* wrapper) {
  lua_close(wrapper->L);
}

void hb_registerFunctions(lua_State* L, const luaL_Reg* funcs) {
  for (; funcs->name != NULL; funcs++) {
    lua_pushcfunction(L, funcs->func);
    lua_setfield(L, -2, funcs->name);
  }
}

void hb_registerModule(lua_State* L, const char* name, const luaL_Reg* functions) {
  lua_getglobal(L, LUA_LIB_NAME);

  lua_newtable(L); // module
  hb_registerFunctions(L, functions);
  lua_setfield(L, -2, name);

  lua_pop(L, 1); // lua lib
}
