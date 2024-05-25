#include "wrapper.hh"

#include "GLFW/glfw3.h"

#include "common.hh"

static int wrap_getEngine(lua_State* L)
{
  LuaWrapper* wrapper = getLuaWrapper(L);

  createLuaData(L, &wrapper->engine, LuaDataType::Engine, "enginemt");
  return 1;
}

static int wrap_pollEvents(UNUSED lua_State* L)
{
  glfwWaitEvents();
  return 0;
}

luaL_Reg engine[] = {
  {"pollEvents", wrap_pollEvents},
  {"getEngine",  wrap_getEngine },
  {nullptr,      nullptr        },
};

static int wrap_isRunning(lua_State* L)
{
  Engine* engine = getUserdata<Engine>(L, 1, LuaDataType::Engine);
  lua_pushboolean(L, engine->isRunning());
  return 1;
}

static int wrap_update(lua_State* L)
{
  Engine* engine = getUserdata<Engine>(L, 1, LuaDataType::Engine);
  engine->update();

  lua_getglobal(L, LUA_LIB_NAME);
  lua_pushnumber(L, engine->time->dt);
  lua_setfield(L, -2, "dt");

  lua_pushnumber(L, engine->time->fps);
  lua_setfield(L, -2, "fps");

  lua_pushnumber(L, engine->time->totalTime);
  lua_setfield(L, -2, "time");

  lua_pushnumber(L, engine->renderer->getDrawCalls());
  lua_setfield(L, -2, "drawCalls");

  return 0;
}

static int engine__index(lua_State* L)
{
  luaL_getmetatable(L, "enginemt");
  lua_getfield(L, -1, luaL_checkstring(L, 2));
  return 1;
}

luaL_Reg engineMethods[] = {
  {"__index",   engine__index },
  {"update",    wrap_update   },
  {"isRunning", wrap_isRunning},
  {nullptr,     nullptr       },
};

void wrapEngine(lua_State* L)
{
  lua_getglobal(L, LUA_LIB_NAME);
  registerFunctions(L, engine);

  luaL_newmetatable(L, "enginemt");
  registerFunctions(L, engineMethods);
  lua_pop(L, 1); // enginemt
}
