#include "wrapper.hh"

static int wrap_setcolor(lua_State* L)
{
  float r = (float)luaL_checknumber(L, 1);
  float g = (float)luaL_checknumber(L, 2);
  float b = (float)luaL_checknumber(L, 3);
  float a = (float)luaL_optnumber(L, 4, 1);

  LuaWrapper* wrapper = getLuaWrapper(L);
  wrapper->engine.renderer->setColor({r, g, b, a});
  return 0;
}

static int wrap_getcolor(lua_State* L)
{
  LuaWrapper* wrapper = getLuaWrapper(L);
  Color c = wrapper->engine.renderer->getColor();

  lua_pushnumber(L, c.r);
  lua_pushnumber(L, c.g);
  lua_pushnumber(L, c.b);
  lua_pushnumber(L, c.a);
  return 4;
}

static int wrap_rect(lua_State* L)
{
  float x = (float)luaL_checknumber(L, 1);
  float y = (float)luaL_checknumber(L, 2);
  float w = (float)luaL_checknumber(L, 3);
  float h = (float)luaL_checknumber(L, 4);

  LuaWrapper* wrapper = getLuaWrapper(L);
  wrapper->engine.renderer->drawRect(x, y, w, h);
  return 0;
}

static int wrap_ellipse(lua_State* L)
{
  float x = (float)luaL_checknumber(L, 1);
  float y = (float)luaL_checknumber(L, 2);
  float rx = (float)luaL_checknumber(L, 3);
  float ry = (float)luaL_optnumber(L, 4, rx);

  LuaWrapper* wrapper = getLuaWrapper(L);
  wrapper->engine.renderer->drawEllipse(x, y, rx, ry);
  return 0;
}

static int wrap_clear(lua_State* L)
{
  float r = (float)luaL_checknumber(L, 1);
  float g = (float)luaL_checknumber(L, 2);
  float b = (float)luaL_checknumber(L, 3);
  float a = (float)luaL_optnumber(L, 4, 1);

  LuaWrapper* wrapper = getLuaWrapper(L);
  wrapper->engine.renderer->clear({r, g, b, a});
  return 0;
}

static int wrap_swap(lua_State* L)
{
  LuaWrapper* wrapper = getLuaWrapper(L);
  wrapper->engine.renderer->present();
  return 0;
}

luaL_Reg renderer[] = {
  {"setcolor", wrap_setcolor},
  {"getcolor", wrap_getcolor},
  {"rect",     wrap_rect    },
  {"ellipse",  wrap_ellipse },
  {"clear",    wrap_clear   },
  {"swap",     wrap_swap    },
  {nullptr,    nullptr      },
};

void wrapRenderer(lua_State* L)
{
  lua_getglobal(L, LUA_LIB_NAME);
  lua_newtable(L);
  registerFunctions(L, renderer);
  lua_setfield(L, -2, "draw");
}
