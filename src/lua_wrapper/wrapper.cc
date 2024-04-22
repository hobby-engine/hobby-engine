#include "wrapper.hh"

#include <cstdlib>

#include "lua.h"
#include "lua.hpp"

#include "log.hh"

static int errorHandler(lua_State* L) {
  lua_getglobal(L, "debug");
  if (!lua_istable(L, -1)) {
    fatal(
      "%s\nDebug library has been removed. Cannot provide stack trace.",
      lua_tostring(L, 1));
  }
  lua_getfield(L, -1, "traceback");
  if (!lua_iscfunction(L, -1)) {
    fatal(
      "%s\n'debug.traceback' has been removed. Cannot provide stack trace.",
      lua_tostring(L, 1));
  }

  lua_pushvalue(L, 1);
  lua_pushinteger(L, 2);
  lua_call(L, 2, 1);
  fatal("%s\n", lua_tostring(L, -1));

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
  wrapInput(L);
  wrapLog(L);

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

void LuaWrapper::callFunction(const char* name, int argCount, ...) {
  lua_getglobal(L, LUA_LIB_NAME);
  lua_getfield(L, -1, name);
  if (!lua_isfunction(L, -1)) {
    lua_pop(L, 2);
    return;
  }

  va_list args;
  va_start(args, argCount);
  for (int i = 0; i < argCount; i++) {
    int type = va_arg(args, int);
    switch (type) {
      case LUA_TNIL: {
        lua_pushnil(L);
        break;
      }
      case LUA_TNUMBER: {
        double d = va_arg(args, double);
        lua_pushnumber(L, d);
        break;
      }
      case LUA_TBOOLEAN: {
        bool b = (bool)va_arg(args, int);
        lua_pushboolean(L, b);
        break;
      }
    }
  }
  va_end(args);

  lua_pcall(L, argCount, 0, errorHandlerPos);
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
