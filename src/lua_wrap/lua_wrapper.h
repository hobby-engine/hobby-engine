#ifndef _HOBBY_LUA_WRAP_LUA_WRAPPER_H
#define _HOBBY_LUA_WRAP_LUA_WRAPPER_H

#include "engine.h"
#include "luaheaders.h"
#include "texture.h"

#define LUA_LIB_NAME "hobby"
#define LUA_RENDERER_NAME "renderer"
#define LUA_TIME_NAME "time"
#define LUA_TEXTURE_NAME "texture"

struct hb_LuaWrapper {
  struct hb_Engine* engine;
  struct lua_State* L;
  s32 errorHandlerIndex;
};

struct hb_LuaTexture {
  struct hb_Texture texture;
};

struct hb_LuaSprite {
  struct hb_Sprite sprite;
};

struct hb_LuaWrapper* hb_createLuaWrapper(struct hb_Engine* engine);

void hb_destroyLuaWrapper(struct hb_LuaWrapper* wrapper);
void hb_callLuaCallback(struct hb_LuaWrapper* wrapper, const char* fnName);
void hb_registerFunctions(lua_State* L, const luaL_Reg* funcs);
void hb_registerModule(lua_State* L, const char* name, const luaL_Reg* functions);

void hb_luaWrapRenderer(lua_State* L);
void hb_luaWrapTime(lua_State* L);
void hb_luaWrapTexture(lua_State* L);

#endif // _HOBBY_LUA_WRAP_LUA_WRAPPER_H
