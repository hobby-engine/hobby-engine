#include "lua_wrapper.h"

#include "engine.h"
#include "lua.h"
#include "luaheaders.h"
#include "log.h"

static int errorHandler(lua_State* L) {
  const char* errorMessage = lua_tostring(L, -1);
  error("%s", errorMessage);
  lua_close(L);
  exit(1);
}

struct LuaWrapper* createLuaWrapper(struct Engine* engine) {
  lua_State* L = luaL_newstate();

  struct LuaWrapper* wrapper = malloc(sizeof(struct LuaWrapper));
  lua_pushlightuserdata(L, wrapper);
  lua_setfield(L, LUA_REGISTRYINDEX, "wrapper");

  wrapper->engine = engine;
  wrapper->L = L;
  luaL_openlibs(L);

  lua_pushcfunction(L, errorHandler);
  wrapper->errorHandlerIndex = lua_gettop(L);

  lua_newtable(L);
  lua_setglobal(L, LUA_LIB_NAME);

  luaWrapRenderer(L);
  luaWrapTime(L);
  luaWrapTexture(L);

  s32 res = luaL_dofile(L, "main.lua");
  if (res != LUA_OK) {
    errorHandler(L);
    lua_close(L);
  }

  return wrapper;
}

void destroyLuaWrapper(struct LuaWrapper* wrapper) {
  lua_close(wrapper->L);
  destroyEngine(wrapper->engine);
  free(wrapper);
}

void callLuaCallback(struct LuaWrapper* wrapper, const char* fnName) {
  lua_State* L = wrapper->L;
  lua_getglobal(L, LUA_LIB_NAME);

  lua_getfield(L, -1, fnName);
  if (lua_isfunction(L, -1)) {
    lua_pcall(L, 0, 0, wrapper->errorHandlerIndex);
  }
  lua_pop(L, 1);
}

void registerFunctions(lua_State* L, const luaL_Reg* funcs) {
  for (; funcs->name != NULL; funcs++) {
    lua_pushcfunction(L, funcs->func);
    lua_setfield(L, -2, funcs->name);
  }
}

void registerModule(lua_State* L, const char* name, const luaL_Reg* functions) {
  lua_getglobal(L, LUA_LIB_NAME);

  lua_newtable(L); // module
  registerFunctions(L, functions);
  lua_setfield(L, -2, name);

  lua_pop(L, 1); // lua lib
}

const char* getLuaTypeName(enum LuaDataType type) {
  switch (type) {
    case LUA_DATA_TYPE_TEXTURE: return "Texture";
    case LUA_DATA_TYPE_SPRITE: return "Sprite";
    default:
      error("Invalid Lua data type. This should be unreachable.\n");
      return NULL;
  }
}

void ensureUserdataIsOfType(
    lua_State* L, struct LuaData* data, enum LuaDataType type, s32 argn) {
  if (data->type != type) {
    luaL_error(L, "Function expected type %s for arg %d, got %s",
      getLuaTypeName(type), argn, getLuaTypeName(data->type));
  }
}

struct LuaWrapper* getLuaWrapper(lua_State* L) {
  lua_getfield(L, LUA_REGISTRYINDEX, "wrapper");
  struct LuaWrapper* wrapper = lua_touserdata(L, -1);
  lua_pop(L, 1);
  return wrapper;
}

struct LuaData* pushLuaData(
    lua_State* L, void* data, enum LuaDataType type, const char* metatable) {

  struct LuaData* wrapper = lua_newuserdata(L, sizeof(struct LuaData));
  wrapper->data = data;
  wrapper->type = type;

  luaL_getmetatable(L, metatable);
  lua_setmetatable(L, -2);

  return wrapper;
}
