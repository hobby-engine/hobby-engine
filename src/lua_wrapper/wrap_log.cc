#include "wrapper.hh"

#include "log.hh"

static int wrap_log(lua_State* L)
{
  const char* msg = lua_tostring(L, 1);
  hlog(msg);
  return 0;
}

static int wrap_warn(lua_State* L)
{
  const char* msg = lua_tostring(L, 1);
  warn(msg);
  return 0;
}

static int wrap_error(lua_State* L)
{
  const char* msg = lua_tostring(L, 1);
  error(msg);
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
  assert(cond, msg);
  return 0;
}

static int wrap_fatalAssert(lua_State* L)
{
  bool cond = lua_toboolean(L, 1);
  const char* msg = lua_tostring(L, 2);
  if (!cond) {
    luaL_error(L, msg);
  }
  return 0;
}

luaL_Reg logfn[] = {
  {"log",         wrap_log        },
  {"warn",        wrap_warn       },
  {"error",       wrap_error      },
  {"fatal",       wrap_fatal      },
  {"assert",      wrap_assert     },
  {"fatalassert", wrap_fatalAssert},
  {nullptr,       nullptr         },
};

void wrapLog(lua_State* L)
{
  lua_getglobal(L, LUA_LIB_NAME);
  registerFunctions(L, logfn);
}
