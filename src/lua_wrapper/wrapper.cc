#include "wrapper.hh"

#include <cstdlib>

#include "lua.h"
#include "lua.hpp"

#include "log.hh"

#include "lua/auxiliary.hh"
#include "lua/class.hh"
#include "lua/event.hh"
#include "lua/input.hh"
#include "lua/math.hh"
#include "lua/run.hh"
#include "lua/set.hh"
#include "lua/shader.hh"
#include "lua/thing.hh"

static int errorHandler(lua_State* L)
{
  const char* msg = lua_tostring(L, -1);

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

  lua_call(L, 0, 1);

  if (lua_isstring(L, -1)) {
    const char* trace = lua_tostring(L, -1);
    fatal("%s\n%s", msg, trace);
  } else {
    fatal("%s", msg);
  }
  return 0;
}

LuaWrapper::LuaWrapper(Engine& engine) : engine(engine)
{

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
  wrapTexture(L);
  wrapWindow(L);

  // Initialize scripts
  // clang-format off
  const char* scripts[] = {
    scriptAuxLua,   
    scriptClassLua, 
    scriptEventLua,
    scriptInputLua,
    scriptMathLua,
    scriptSetLua,
    scriptThingLua,
    scriptRunLua,
    nullptr
  };
  // clang-format on
  for (int i = 0; scripts[i] != nullptr; i++) {
    if (luaL_dostring(L, scripts[i]) != LUA_OK) {
      errorHandler(L);
    }
  }

  if (luaL_dofile(L, "main.lua") != LUA_OK) {
    errorHandler(L);
  }
}

LuaWrapper::~LuaWrapper()
{
  lua_close(L);
}

void LuaWrapper::callFunction(const char* name, int argCount, ...)
{
  lua_getglobal(L, LUA_LIB_NAME);
  lua_getfield(L, -1, name);
  if (!lua_isfunction(L, -1)) {
    fatal("Cannot call non-function value '%s'.", name);
  }

  va_list args;
  va_start(args, argCount);
  for (int i = 0; i < argCount; i++) {
    LuaType type = (LuaType)va_arg(args, int);
    switch (type) {
      case LuaType::Nil: {
        lua_pushnil(L);
        break;
      }
      case LuaType::Int: {
        int i = va_arg(args, int);
        lua_pushinteger(L, i);
        break;
      }
      case LuaType::Number: {
        double d = va_arg(args, double);
        lua_pushnumber(L, d);
        break;
      }
      case LuaType::Boolean: {
        lua_pushboolean(L, va_arg(args, int));
        break;
      }
      default:
        fatal("Unsupported value '%d'.", type);
        break;
    }
  }
  va_end(args);

  lua_pcall(L, argCount, 0, errorHandlerPos);
  lua_pop(L, 1);
}

void registerFunctions(lua_State* L, const luaL_Reg* funcs)
{
  for (; funcs->name != NULL; funcs++) {
    lua_pushcfunction(L, funcs->func);
    lua_setfield(L, -2, funcs->name);
  }
}

LuaWrapper* getLuaWrapper(lua_State* L)
{
  lua_getfield(L, LUA_REGISTRYINDEX, "wrapper");
  LuaWrapper* wrapper = (LuaWrapper*)lua_touserdata(L, -1);
  lua_pop(L, 1);
  return wrapper;
}
