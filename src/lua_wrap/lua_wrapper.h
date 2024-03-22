#ifndef _HOBBY_LUA_WRAP_LUA_WRAPPER_H
#define _HOBBY_LUA_WRAP_LUA_WRAPPER_H

#include "engine.h"
#include "luaheaders.h"
#include "texture.h"

#define LUA_LIB_NAME "hobby"
#define LUA_RENDERER_NAME "renderer"
#define LUA_TIME_NAME "time"
#define LUA_TEXTURE_NAME "texture"

typedef struct {
  hb_Engine* engine;
  lua_State* L;
  s32 errorHandlerIndex;
} hb_LuaWrapper;

typedef struct {
  hb_Texture texture;
} hb_LuaTexture;

hb_LuaWrapper* hb_createLuaWrapper(hb_Engine* engine);

void hb_destroyLuaWrapper(hb_LuaWrapper* wrapper);
void hb_callLuaCallback(hb_LuaWrapper* wrapper, const char* fnName);
void hb_registerFunctions(lua_State* L, const luaL_Reg* funcs);
void hb_registerModule(lua_State* L, const char* name, const luaL_Reg* functions);

void hb_luaWrapRenderer(lua_State* L);
void hb_luaWrapTime(lua_State* L);
void hb_luaWrapTexture(lua_State* L);

#endif // _HOBBY_LUA_WRAP_LUA_WRAPPER_H
