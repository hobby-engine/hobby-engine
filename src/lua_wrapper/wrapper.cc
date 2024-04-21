#include "wrapper.hh"

#include <cstdlib>

#include "lua.hpp"

#include "log.hh"

static int errorHandler(lua_State* L) {
  const char* errorMessage = lua_tostring(L, -1);
  error("%s", errorMessage);
  lua_close(L);
  std::exit(1);
}

LuaWrapper::LuaWrapper(Engine& engine)
    : engine(engine) {

  L = luaL_newstate();
  luaL_openlibs(L);

  lua_pushlightuserdata(L, this);
  lua_setfield(L, LUA_REGISTRYINDEX, "wrapper");

  lua_pushcfunction(L, errorHandler);
  errorHandlerPos = lua_gettop(L);

  lua_newtable(L);
  lua_setglobal(L, LUA_LIB_NAME);

  wrapRenderer(L);
  wrapEngine(L);

  int res = luaL_dofile(L, "src/lua/run.lua");
  if (res != LUA_OK) {
    errorHandler(L);
  }

  res = luaL_dofile(L, "main.lua");
  if (res != LUA_OK) {
    errorHandler(L);
  }
}

LuaWrapper::~LuaWrapper() {
  lua_close(L);
}

void LuaWrapper::callFunction(const char* name) {
  lua_getglobal(L, LUA_LIB_NAME);

  lua_getfield(L, -1, name);
  if (lua_isfunction(L, -1)) {
    lua_pcall(L, 0, 0, errorHandlerPos);
  }
  lua_pop(L, 1);
}

void registerFunctions(lua_State* L, const luaL_Reg* funcs) {
  for (; funcs->name != NULL; funcs++) {
    lua_pushcfunction(L, funcs->func);
    lua_setfield(L, -2, funcs->name);
  }
}

LuaWrapper* getLuaWrapper(lua_State* L) {
  lua_getfield(L, LUA_REGISTRYINDEX, "wrapper");
  LuaWrapper* wrapper = (LuaWrapper*)lua_touserdata(L, -1);
  lua_pop(L, 1);
  return wrapper;
}
