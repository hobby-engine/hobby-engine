#ifndef _HOBBY_LUA_WRAP_LUA_WRAPPER_H
#define _HOBBY_LUA_WRAP_LUA_WRAPPER_H

#include "engine.h"
#include "luaheaders.h"
#include "texture.h"

#define LUA_LIB_NAME "hobby"
#define LUA_RENDERER_NAME "renderer"
#define LUA_TIME_NAME "time"
#define LUA_TEXTURE_NAME "texture"

enum LuaDataType {
  LUA_DATA_TYPE_TEXTURE,
  LUA_DATA_TYPE_SPRITE,
};

struct LuaData {
  enum LuaDataType type;
  void* data;
};

struct LuaWrapper {
  struct Engine* engine;
  lua_State* L;
  s32 errorHandlerIndex;
};

struct LuaWrapper* createLuaWrapper(struct Engine* engine);

void destroyLuaWrapper(struct LuaWrapper* wrapper);
void callLuaCallback(struct LuaWrapper* wrapper, const char* fnName);
void registerFunctions(lua_State* L, const luaL_Reg* funcs);
void registerModule(lua_State* L, const char* name, const luaL_Reg* functions);
const char* getLuaTypeName(enum LuaDataType type);
struct LuaData* pushLuaData(
  lua_State* L, void* data, enum LuaDataType, const char* metatable);
void ensureUserdataIsOfType(
    lua_State* L, struct LuaData* data, enum LuaDataType type, s32 argn);
struct LuaWrapper* getLuaWrapper(lua_State* L);

void luaWrapRenderer(lua_State* L);
void luaWrapTime(lua_State* L);
void luaWrapTexture(lua_State* L);

#endif // _HOBBY_LUA_WRAP_LUA_WRAPPER_H
