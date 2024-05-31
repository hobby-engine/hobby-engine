#ifndef _HOBBY_WRAPPER_HH
#define _HOBBY_WRAPPER_HH

#include "engine.hh"
#include "luajit/lua.hpp"

#define LUA_LIB_NAME "hobby"

enum class LuaType
{
  Nil = 0,
  Number,
  Int,
  Boolean,
  String,
};

struct LuaWrapper
{
  Engine& engine;
  lua_State* L;
  int errorhandlerindex;

  LuaWrapper(Engine& engine);
  ~LuaWrapper();

  void callfunction(const char* name, int argc, ...);
};

enum class LuaDataType
{
  Engine,
  Window,
  Texture2D,
};

struct LuaData
{
  LuaDataType type;
  bool owned = true;
  // Can't use generics because I need to be able to check the type somehow
  // (stupid C++ not having reflection)
  void* data;
};

void registerfuncs(lua_State* L, const luaL_Reg* funcs);
LuaWrapper* getwrapper(lua_State* L);

void wrapengine(lua_State* L);
void wraprenderer(lua_State* L);
void wrapinput(lua_State* L);
void wraplog(lua_State* L);
void wraptexture(lua_State* L);
void wrapwindow(lua_State* L);

template <typename T>
LuaData* createluadata(lua_State* L, T* data, LuaDataType type, const char* mt)
{
  LuaData* luadata = (LuaData*)lua_newuserdata(L, sizeof(LuaData));
  luadata->type = type;
  luadata->owned = true;
  luadata->data = data;

  luaL_getmetatable(L, mt);
  lua_setmetatable(L, -2);

  return luadata;
}

template <typename T>
T* getuserdata(lua_State* L, int index, LuaDataType type)
{
  LuaData* v = (LuaData*)lua_touserdata(L, index);
  if (v->type != type) {
    luaL_error(L, "Incorrect userdata type.");
  }
  return (T*)v->data;
}

#endif // _HOBBY_WRAPPER_HH
