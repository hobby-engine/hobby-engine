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

int wrap_drawVertices(lua_State* L) {
  if (!lua_istable(L, 1)) {
    return luaL_error(L, "Expected a table.");
  }

  int length = lua_objlen(L, 1);
  if (length % 2 != 0) {
    return luaL_error(L, "Invalid vertices (Odd number of elements.)");
  }
  int count = length + 2;

  float vertices[count];

  lua_pushvalue(L, 1);
  lua_pushnil(L);
  while (lua_next(L, -2)) {
    if (lua_isnumber(L, -2) && lua_isnumber(L, -1)) {
      int index = lua_tointeger(L, -2) - 1;
      float number = lua_tonumber(L, -1);
      vertices[index] = number;
    } else {
      return luaL_error(L, "Expected a table of indices with number values.");
    }

    lua_pop(L, 1);
  }

  // Close
  vertices[count - 2] = vertices[0];
  vertices[count - 1] = vertices[1];

  LuaWrapper* wrapper = getLuaWrapper(L);
  wrapper->engine.renderer->drawVertices(count, vertices);
  return 0;
}

int wrap_drawBoid(lua_State* L) {
  float x = (float)luaL_checknumber(L, 1);
  float y = (float)luaL_checknumber(L, 2);
  float b = (float)luaL_checknumber(L, 3);
  float h = (float)luaL_checknumber(L, 4);
  float r = (float)luaL_checknumber(L, 5);

  LuaWrapper* wrapper = getLuaWrapper(L);
  wrapper->engine.renderer->drawBoid(x, y, b, h, r);
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
  {"setDrawColor", wrap_setDrawColor},
  {"drawRect", wrap_drawRect},
  {"drawEllipse", wrap_drawEllipse},
  {"drawVertices", wrap_drawVertices},
  {"drawBoid", wrap_drawBoid},
  {"wipe", wrap_clearScreen},
  {"swapDrawBuffers", wrap_presentScreen},
  {nullptr, nullptr},
};

void wrapRenderer(lua_State* L) {
  lua_getglobal(L, LUA_LIB_NAME);
  registerFunctions(L, renderer);
}
