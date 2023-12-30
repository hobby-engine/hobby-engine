#ifndef _POINT_LUA_WRAP_H
#define _POINT_LUA_WRAP_H

#include "luajit/lua.hpp"
#include "hobby.hh"

struct WindowWrapper {
  Hobby::Window* window;
};

#define LIB_NAME "Hobby"
#define WINDOW_NAME "Window"
#define GRAPHICS_NAME "Graphics"

void RegisterModule(lua_State* L, const char* name, const luaL_Reg *functions);
void RegisterFunctions(lua_State* L, const luaL_Reg* funcs);

int WrapWindow(lua_State* L);
int WrapGraphics(lua_State* L);

#endif // _POINT_LUA_WRAP_H
