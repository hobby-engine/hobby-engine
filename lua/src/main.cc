#include <iostream>
#include <cmath>

#include "luajit/lua.hpp"

#include "wrap.hh"

void RegisterModule(lua_State* L, const char* name, const luaL_Reg* functions) {
  lua_getglobal(L, LIB_NAME);

  lua_newtable(L); // module
  RegisterFunctions(L, functions);

  lua_pushvalue(L, -1); // Copy

  lua_setfield(L, -3, name);
  lua_setfield(L, LUA_REGISTRYINDEX, name);
  lua_pop(L, 1); // point
}

void RegisterFunctions(lua_State* L, const luaL_Reg* funcs) {
  for (; funcs->name != nullptr; funcs++) {
    lua_pushcfunction(L, funcs->func);
    lua_setfield(L, -2, funcs->name);
  }
}

static int ErrorHandler(lua_State* L) {
  const char* errorMessage = lua_tostring(L, -1);
  std::cerr << "Error: " << errorMessage << std::endl;
  return 0;
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

  // Error handling
  lua_pushcfunction(L, ErrorHandler);
  int errorHandlerIndex = lua_gettop(L);

  lua_newtable(L);
  lua_setglobal(L, LIB_NAME);

  WrapApp(L);
  WrapTexture(L);
  WrapWindow(L);
  WrapGraphics(L);
  WrapTime(L);
  WrapInput(L);

  int loadRes = luaL_dofile(L, path.c_str());
  if (loadRes != LUA_OK) {
    ErrorHandler(L);
    lua_close(L);
    return 0;
  }

  lua_getglobal(L, LIB_NAME);
  lua_getfield(L, -1, "run");
  lua_pcall(L, 0, 0, errorHandlerIndex);
  lua_pop(L, 1); // point

  lua_close(L);
  return 0;
}
