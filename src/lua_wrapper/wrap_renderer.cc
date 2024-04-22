#include "wrapper.hh"

#include "lua.hpp"

int wrap_setDrawColor(lua_State* L) {
  float r = (float)luaL_checknumber(L, 1);
  float g = (float)luaL_checknumber(L, 2);
  float b = (float)luaL_checknumber(L, 3);
  float a = (float)luaL_optnumber(L, 4, 1);
  
  LuaWrapper* wrapper = getLuaWrapper(L);
  wrapper->engine.renderer->setColor({r, g, b, a});
  return 0;
}

int wrap_drawRect(lua_State* L) {
  float x = (float)luaL_checknumber(L, 1);
  float y = (float)luaL_checknumber(L, 2);
  float w = (float)luaL_checknumber(L, 3);
  float h = (float)luaL_checknumber(L, 4);
  
  LuaWrapper* wrapper = getLuaWrapper(L);
  wrapper->engine.renderer->drawRect(x, y, w, h);
  return 0;
}

int wrap_drawEllipse(lua_State* L) {
  float x  = (float)luaL_checknumber(L, 1);
  float y  = (float)luaL_checknumber(L, 2);
  float rx = (float)luaL_checknumber(L, 3);
  float ry = (float)luaL_optnumber(L, 4, rx);

  LuaWrapper* wrapper = getLuaWrapper(L);
  wrapper->engine.renderer->drawEllipse(x, y, rx, ry);
  return 0;
}

int wrap_clearScreen(lua_State* L) {
  float r = (float)luaL_checknumber(L, 1);
  float g = (float)luaL_checknumber(L, 2);
  float b = (float)luaL_checknumber(L, 3);
  float a = (float)luaL_optnumber(L, 4, 1);
  
  LuaWrapper* wrapper = getLuaWrapper(L);
  wrapper->engine.renderer->clear({r, g, b, a});
  return 0;
}

int wrap_presentScreen(lua_State* L) {
  LuaWrapper* wrapper = getLuaWrapper(L);
  wrapper->engine.window->present();
  return 0;
}

luaL_Reg renderer[] = {
  {"setColor", wrap_setDrawColor},
  {"drawRect", wrap_drawRect},
  {"drawEllipse", wrap_drawEllipse},
  {"clear", wrap_clearScreen},
  {"present", wrap_presentScreen},
  {nullptr, nullptr},
};

void wrapRenderer(lua_State* L) {
  lua_getglobal(L, LUA_LIB_NAME);
  lua_newtable(L);
  registerFunctions(L, renderer);
  lua_setfield(L, -2, "renderer");
}
