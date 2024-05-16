#include "wrapper.hh"

static int wrap_getTitle(lua_State* L)
{
  LuaWrapper* wrapper = getLuaWrapper(L);
  lua_pushstring(L, wrapper->engine.window->getTitle());
  return 1;
}

static int wrap_setTitle(lua_State* L)
{
  LuaWrapper* wrapper = getLuaWrapper(L);
  const char* title = luaL_checkstring(L, 1);
  wrapper->engine.window->setTitle(title);
  return 0;
}

static int wrap_getSize(lua_State* L)
{
  LuaWrapper* wrapper = getLuaWrapper(L);
  int w, h;
  wrapper->engine.window->getSize(w, h);
  lua_pushnumber(L, w);
  lua_pushnumber(L, h);
  return 2;
}

static int wrap_setSize(lua_State* L)
{
  LuaWrapper* wrapper = getLuaWrapper(L);
  int w = luaL_checknumber(L, 1);
  int h = luaL_checknumber(L, 2);
  if (w <= 0 || h <= 0) {
    luaL_error(L, "Width and height must be above 0.");
  }
  wrapper->engine.window->setSize(w, h);
  return 0;
}

luaL_Reg window[] = {
  {"getWindowTitle", wrap_getTitle},
  {"setWindowTitle", wrap_setTitle},
  {"getWindowSize",  wrap_getSize },
  {"setWindowSize",  wrap_setSize },
  {nullptr,          nullptr      },
};

void wrapWindow(lua_State* L)
{
  lua_getglobal(L, LUA_LIB_NAME);
  registerFunctions(L, window);
}
