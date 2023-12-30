#include <iostream>
#include <cmath>

#include "luajit/lua.hpp"

#include "wrap.hh"

void RegisterModule(lua_State* L, const char* name, luaL_Reg functions[]) {
  lua_getglobal(L, LIB_NAME);

  lua_newtable(L); // module

  luaL_Reg func;
  for (int i = 0; (func = functions[i]).func != nullptr; i++) {
    lua_pushcfunction(L, func.func);
    lua_setfield(L, -2, func.name);
  }

  lua_setfield(L, -2, name);
  lua_pop(L, 1); // point
}

int main(int argc, char* args[]) {
  std::string path = "./main.lua";
  if (argc == 2) {
    path = args[1];
    if (path.back() == '/') {
      path += "main.lua";
    } else {
      path += "/main.lua";
    }
  } else if (argc != 1) {
    std::cerr << "Usage: " << args[0] << " [path]" << std::endl;
    return 1;
  }

  lua_State* L = luaL_newstate();
  luaL_openlibs(L);

  lua_newtable(L);
  lua_setglobal(L, LIB_NAME);

  WrapWindow(L);
  WrapGraphics(L);

  int res = luaL_dofile(L, path.c_str());
  if (res != LUA_OK) {
    std::cerr << "Error: " << lua_tostring(L, -1) << std::endl;
    lua_close(L);
    return 1;
  }

  lua_getglobal(L, LIB_NAME);
  lua_getfield(L, -1, "run");
  lua_call(L, 0, -1);
  lua_pop(L, 1); // point

  lua_close(L);
  return 0;
}
