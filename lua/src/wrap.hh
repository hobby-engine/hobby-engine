#ifndef _HOBBY_LUA_WRAP_H
#define _HOBBY_LUA_WRAP_H

#include "luajit/lua.hpp"
#include "hobby.hh"

struct WindowWrapper {
  Hobby::Window* window;
};

struct TextureWrapper {
  Hobby::Texture* texture;
};

#define LIB_NAME "Hobby"
#define TEXTURE_NAME "Texture"
#define WINDOW_NAME "Window"
#define DRAW_NAME "Draw"
#define TIME_NAME "Time"

#define OPT_BOOL(L, i, d) \
  lua_isboolean(L, i) ? lua_toboolean(L, i) : (d)

void RegisterModule(lua_State* L, const char* name, const luaL_Reg *functions);
void RegisterFunctions(lua_State* L, const luaL_Reg* funcs);

int WrapTexture(lua_State* L);
int WrapWindow(lua_State* L);
int WrapGraphics(lua_State* L);
int WrapTime(lua_State* L);

#endif // _HOBBY_LUA_WRAP_H
