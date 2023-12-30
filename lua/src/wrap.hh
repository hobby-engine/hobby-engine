#ifndef _POINT_LUA_WRAP_H
#define _POINT_LUA_WRAP_H

#include "luajit/lua.hpp"
#include "point.hh"

struct WindowWrapper {
  point::Window* window;
};

#define LIB_NAME "point"
#define WINDOW_NAME "window"
#define GRAPHICS_NAME "graphics"

void RegisterModule(lua_State* L, const char* name, luaL_Reg functions[]);

int WrapWindow(lua_State* L);
int WrapGraphics(lua_State* L);

#endif // _POINT_LUA_WRAP_H
