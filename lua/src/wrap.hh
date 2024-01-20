#ifndef _HOBBY_LUA_WRAP_H
#define _HOBBY_LUA_WRAP_H

#include <iostream>
#include <stdexcept>

#include "luajit/lua.hpp"
#include "hobby.hh"

#include "wrap_app.hh"
#include "wrap_draw.hh"
#include "wrap_texture.hh"
#include "wrap_time.hh"
#include "wrap_window.hh"
#include "wrap_input.hh"

#define LIB_NAME "Hobby"

#define OPT_BOOL(L, i, d) \
  lua_isboolean(L, i) ? lua_toboolean(L, i) : (d)

void RegisterModule(lua_State* L, const char* name, const luaL_Reg *functions);
void RegisterFunctions(lua_State* L, const luaL_Reg* funcs);

#endif // _HOBBY_LUA_WRAP_H
