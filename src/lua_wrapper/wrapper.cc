#include "wrapper.hh"

#include <cstdlib>
#include <cstring>

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

static int errorhandler(lua_State* L)
{
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

  lua_pushvalue(L, -3);
  lua_pushnumber(L, 0);
  lua_call(L, 2, 1);

  if (lua_isstring(L, -1)) {
    error("%s", lua_tostring(L, -1));
  } else {
    error("%s", lua_tostring(L, -3));
  }

  lua_close(L);
  exit(1);
}

LuaWrapper::LuaWrapper(Engine& engine) : engine(engine)
{

  L = luaL_newstate();
  luaL_openlibs(L);

  lua_pushlightuserdata(L, this);
  lua_setfield(L, LUA_REGISTRYINDEX, "wrapper");

  lua_pushcfunction(L, errorhandler);
  errorhandlerindex = lua_gettop(L);

  lua_newtable(L);
  lua_setglobal(L, LUA_LIB_NAME);

  wraprenderer(L);
  wrapengine(L);
  wrapinput(L);
  wraplog(L);
  wraptexture(L);
  wrapwindow(L);

  // Initialize scripts
  // clang-format off
  const char* scripts[] = {
    scriptauxlua,   
    scriptclasslua, 
    scripteventlua,
    scriptinputlua,
    scriptmathlua,
    scriptsetlua,
    scriptthinglua,
    scriptrunlua,
    nullptr
  };
  // clang-format on
  for (int i = 0; scripts[i] != nullptr; i++) {
    if (luaL_dostring(L, scripts[i]) != LUA_OK) {
      errorhandler(L);
    }
  }

  if (luaL_dofile(L, "main.lua") != LUA_OK) {
    errorhandler(L);
  }
}

LuaWrapper::~LuaWrapper()
{
  lua_close(L);
}

void LuaWrapper::callfunction(const char* name, int argc, ...)
{
  lua_getglobal(L, LUA_LIB_NAME);
  lua_getfield(L, -1, name);
  if (!lua_isfunction(L, -1)) {
    fatal("Cannot call non-function value '%s'.", name);
  }

  va_list args;
  va_start(args, argc);
  for (int i = 0; i < argc; i++) {
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

  lua_pcall(L, argc, 0, errorhandlerindex);
  lua_pop(L, 1);
}

void registerfuncs(lua_State* L, const luaL_Reg* funcs)
{
  for (; funcs->name != NULL; funcs++) {
    lua_pushcfunction(L, funcs->func);
    lua_setfield(L, -2, funcs->name);
  }
}

LuaWrapper* getwrapper(lua_State* L)
{
  lua_getfield(L, LUA_REGISTRYINDEX, "wrapper");
  LuaWrapper* wrapper = (LuaWrapper*)lua_touserdata(L, -1);
  lua_pop(L, 1);
  return wrapper;
}
