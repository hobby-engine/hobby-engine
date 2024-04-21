#ifndef _HOBBY_WRAPPER_HH
#define _HOBBY_WRAPPER_HH

#include "engine.hh"
#include "lua.hpp"

#define LUA_LIB_NAME "hobby"

struct LuaWrapper {
  Engine& engine;
  lua_State* L;
  int errorHandlerPos;

  LuaWrapper(Engine& engine);
  ~LuaWrapper();

  void callFunction(const char* name);
};

enum class LuaDataType {
  Engine,
};

struct LuaData {
  LuaDataType type;
  // Can't use generics because I need to be able to check the type somehow
  // (stupid C++ not having reflection)
  void* data;
};

void registerFunctions(lua_State* L, const luaL_Reg* funcs);
LuaWrapper* getLuaWrapper(lua_State* L);

void wrapEngine(lua_State* L);
void wrapRenderer(lua_State* L);

template <typename T>
void createLuaData(lua_State* L, T* data, LuaDataType type, const char* mt) {
  LuaData* luaData = (LuaData*)lua_newuserdata(L, sizeof(LuaData));
  luaData->type = type;
  luaData->data = data;

  luaL_getmetatable(L, mt);
  lua_setmetatable(L, -2);
}

template <typename T>
T* getUserdata(lua_State* L, int index, LuaDataType type) {
  LuaData* v = (LuaData*)lua_touserdata(L, index);
  if (v->type != type) {
    luaL_error(L, "Incorrect userdata type.");
  }
  return (T*)v->data;
}

#endif // _HOBBY_WRAPPER_HH
