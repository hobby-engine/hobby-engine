#include "wrapper.hh"

#include "log.hh"

static int wrap_log(lua_State* L)
{
  const char* msg = lua_tostring(L, 1);
  Logger::instance()->log(msg);
  return 0;
}

static int wrap_warn(lua_State* L)
{
  const char* msg = lua_tostring(L, 1);
  Logger::instance()->warn(msg);
  return 0;
}

static int wrap_error(lua_State* L)
{
  const char* msg = lua_tostring(L, 1);
  Logger::instance()->error(msg);
  return 0;
}

static int wrap_fatal(lua_State* L)
{
  const char* msg = lua_tostring(L, 1);
  luaL_error(L, msg);
  return 0;
}

static int wrap_assert(lua_State* L)
{
  bool cond = lua_toboolean(L, 1);
  const char* msg = lua_tostring(L, 2);
  bool res = Logger::instance()->assert(cond, msg);
  lua_pushboolean(L, res);
  return 1;
}

static int wrap_fassert(lua_State* L)
{
  bool cond = lua_toboolean(L, 1);
  const char* msg = lua_tostring(L, 2);
  if (!cond) {
    luaL_error(L, msg);
  }
  return 0;
}

luaL_Reg logfn[] = {
  {"log",     wrap_log    },
  {"warn",    wrap_warn   },
  {"error",   wrap_error  },
  {"fatal",   wrap_fatal  },
  {"assert",  wrap_assert },
  {"fassert", wrap_fassert},
  {nullptr,   nullptr     },
};

void wraplog(lua_State* L)
{
  lua_getglobal(L, LUA_LIB_NAME);
  registerfuncs(L, logfn);
}
