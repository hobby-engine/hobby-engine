#ifndef _HOBBY_LUA_WRAP_LUA_WRAPPER_H
#define _HOBBY_LUA_WRAP_LUA_WRAPPER_H

#include "engine.h"
#include "luaheaders.h"
#include "texture.h"

#define LUA_LIB_NAME "hobby"
#define LUA_RENDERER_NAME "renderer"
#define LUA_TIME_NAME "time"
#define LUA_TEXTURE_NAME "texture"

enum hb_LuaDataType {
  hb_LUA_DATA_TYPE_TEXTURE,
  hb_LUA_DATA_TYPE_SPRITE,
};

struct hb_LuaData {
  enum hb_LuaDataType type;
  void* data;
};

struct hb_LuaWrapper {
  struct hb_Engine* engine;
  lua_State* L;
  s32 errorHandlerIndex;
};

struct hb_LuaWrapper* hb_createLuaWrapper(struct hb_Engine* engine);

void hb_destroyLuaWrapper(struct hb_LuaWrapper* wrapper);
void hb_callLuaCallback(struct hb_LuaWrapper* wrapper, const char* fnName);
void hb_registerFunctions(lua_State* L, const luaL_Reg* funcs);
void hb_registerModule(lua_State* L, const char* name, const luaL_Reg* functions);
const char* hb_getLuaTypeName(enum hb_LuaDataType type);
struct hb_LuaData* hb_pushLuaData(
  lua_State* L, void* data, enum hb_LuaDataType, const char* metatable);
void hb_ensureUserdataIsOfType(
    lua_State* L, struct hb_LuaData* data, enum hb_LuaDataType type, s32 argn);

void hb_luaWrapRenderer(lua_State* L);
void hb_luaWrapTime(lua_State* L);
void hb_luaWrapTexture(lua_State* L);

#endif // _HOBBY_LUA_WRAP_LUA_WRAPPER_H
