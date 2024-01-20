#ifndef _HOBBY_LUA_WINDOW_H
#define _HOBBY_LUA_WINDOW_H

#include "hobby.hh"
#include "luajit/lua.hpp"

#define WINDOW_NAME "Window"

struct WindowWrapper {
  bool OwnsWindow;
  Hobby::Window* Window;
};

int WrapWindow(lua_State* L);
void WindowUserdata(lua_State* L, Hobby::Window* window);

#endif
