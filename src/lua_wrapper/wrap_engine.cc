#include "wrapper.hh"

#include "GLFW/glfw3.h"

#include "common.hh"

static int wrap_getengine(lua_State* L)
{
  LuaWrapper* wrapper = getwrapper(L);

  createluadata(L, &wrapper->engine, LuaDataType::Engine, "enginemt");
  return 1;
}

static int wrap_pollevents(UNUSED lua_State* L)
{
  glfwWaitEvents();
  return 0;
}

luaL_Reg engine[] = {
  {"pollevents", wrap_pollevents},
  {"getengine",  wrap_getengine },
  {nullptr,      nullptr        },
};

static int wrap_isrunning(lua_State* L)
{
  Engine* engine = getuserdata<Engine>(L, 1, LuaDataType::Engine);
  lua_pushboolean(L, engine->isrunning());
  return 1;
}

static int wrap_update(lua_State* L)
{
  Engine* engine = getuserdata<Engine>(L, 1, LuaDataType::Engine);
  engine->update();

  lua_getglobal(L, LUA_LIB_NAME);
  lua_pushnumber(L, engine->time->getdt());
  lua_setfield(L, -2, "dt");

  lua_pushnumber(L, engine->time->getfps());
  lua_setfield(L, -2, "fps");

  lua_pushnumber(L, engine->time->gettotal());
  lua_setfield(L, -2, "time");

  lua_pushnumber(L, engine->renderer->getdrawcalls());
  lua_setfield(L, -2, "drawcalls");

  return 0;
}

static int engine__index(lua_State* L)
{
  luaL_getmetatable(L, "enginemt");
  lua_getfield(L, -1, luaL_checkstring(L, 2));
  return 1;
}

luaL_Reg enginemt[] = {
  {"__index",   engine__index },
  {"update",    wrap_update   },
  {"isrunning", wrap_isrunning},
  {nullptr,     nullptr       },
};

void wrapengine(lua_State* L)
{
  lua_getglobal(L, LUA_LIB_NAME);
  registerfuncs(L, engine);

  luaL_newmetatable(L, "enginemt");
  registerfuncs(L, enginemt);
  lua_pop(L, 1); // enginemt
}
