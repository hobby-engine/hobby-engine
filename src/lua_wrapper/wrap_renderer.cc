#include "wrapper.hh"

#include "lua.hpp"

int wrap_setDrawColor(lua_State* L) {
  float r = lua_tonumber(L, 1);
  float g = lua_tonumber(L, 2);
  float b = lua_tonumber(L, 3);
  float a = luaL_optnumber(L, 4, 1);
  
  LuaWrapper* wrapper = getLuaWrapper(L);
  wrapper->engine.renderer->setColor({r, g, b, a});
  return 0;
}

int wrap_drawRect(lua_State* L) {
  float x = lua_tonumber(L, 1);
  float y = lua_tonumber(L, 2);
  float w = lua_tonumber(L, 3);
  float h = lua_tonumber(L, 4);
  
  LuaWrapper* wrapper = getLuaWrapper(L);
  wrapper->engine.renderer->drawRect(x, y, w, h);
  return 0;
}

int wrap_drawEllipse(lua_State* L) {
  float x = lua_tonumber(L, 1);
  float y = lua_tonumber(L, 2);
  float rx = lua_tonumber(L, 3);
  float ry = luaL_optnumber(L, 4, rx);

  LuaWrapper* wrapper = getLuaWrapper(L);
  wrapper->engine.renderer->drawEllipse(x, y, rx, ry);
  return 0;
}

int wrap_clearScreen(lua_State* L) {
  float r = lua_tonumber(L, 1);
  float g = lua_tonumber(L, 2);
  float b = lua_tonumber(L, 3);
  float a = luaL_optnumber(L, 4, 1);
  
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
