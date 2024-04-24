#include "opengl/gl_texture.hh"
#include "wrapper.hh"

int wrap_texture2d(lua_State* L) {
  const char* path = luaL_checkstring(L, 1);

  auto texture2d = new OpenGlTexture2D(path);
  createLuaData(L, texture2d, LuaDataType::Texture2D, "texture2dmt");
  return 1;
}

luaL_Reg texture[] = {
  {"texture2d", wrap_texture2d},
  {nullptr, nullptr},
};

int texture2d__index(lua_State* L) {
  luaL_getmetatable(L, "texture2dmt");
  lua_getfield(L, -1, luaL_checkstring(L, 2));
  return 1;
}

int texture2d__gc(lua_State* L) {
  Texture2D* texture2d = getUserdata<Texture2D>(L, 1, LuaDataType::Texture2D);
  delete texture2d;
  return 0;
}

int wrap_draw(lua_State* L) {
  Texture2D* texture2d = getUserdata<Texture2D>(L, 1, LuaDataType::Texture2D);
  float x = luaL_checknumber(L, 2);
  float y = luaL_checknumber(L, 3);
  float r = luaL_optnumber(L, 4, 0);
  float sx = luaL_optnumber(L, 5, 1);
  float sy = luaL_optnumber(L, 6, sx);
  float ox = luaL_optnumber(L, 7, 0);
  float oy = luaL_optnumber(L, 8, 0);
  LuaWrapper* wrapper = getLuaWrapper(L);

  wrapper->engine.renderer->draw(
    *texture2d,
    x, y, r, sx, sy, ox, oy);
  return 0;
}

int wrap_getWidth(lua_State* L) {
  Texture2D* texture2d = getUserdata<Texture2D>(L, 1, LuaDataType::Texture2D);
  lua_pushnumber(L, texture2d->getWidth());
  return 1;
}

int wrap_getHeight(lua_State* L) {
  Texture2D* texture2d = getUserdata<Texture2D>(L, 1, LuaDataType::Texture2D);
  lua_pushnumber(L, texture2d->getHeight());
  return 1;
}

int wrap_getSize(lua_State* L) {
  Texture2D* texture2d = getUserdata<Texture2D>(L, 1, LuaDataType::Texture2D);
  lua_pushnumber(L, texture2d->getWidth());
  lua_pushnumber(L, texture2d->getHeight());
  return 2;
}

luaL_Reg texture2dmt[] = {
  {"__index", texture2d__index},
  {"__gc", texture2d__gc},
  {"draw", wrap_draw},
  {"getWidth", wrap_getWidth},
  {"getHeight", wrap_getHeight},
  {"getSize", wrap_getSize},
  {nullptr, nullptr},
};

void wrapTexture(lua_State *L) {
  lua_getglobal(L, LUA_LIB_NAME);
  registerFunctions(L, texture);

  luaL_newmetatable(L, "texture2dmt");
  registerFunctions(L, texture2dmt);
  lua_pop(L, 1); // texture2dmt
}
