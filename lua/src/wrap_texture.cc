#include "wrap.hh"

#define TEXTURE_MEMBERS "textureMembers"

static int w_CreateTexture(lua_State* L) {
  const char* path = luaL_checkstring(L, 1);

  Hobby::Texture* texture = new Hobby::Texture(path);
  TextureWrapper* wrapper = static_cast<TextureWrapper*>(
    lua_newuserdata(L, sizeof(TextureWrapper)));
  wrapper->texture = texture;
  luaL_getmetatable(L, "texturemt");
  lua_setmetatable(L, -2);

  return 1;
}

static int w_Draw(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected texture object.");
  }

  TextureWrapper* wrapper = static_cast<TextureWrapper*>(lua_touserdata(L, 1));
  wrapper->texture->Draw(Hobby::Vec2(0, 0));
  return 0;
};

static int w_TextureGc(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected texture object.");
  }

  TextureWrapper* wrapper = static_cast<TextureWrapper*>(lua_touserdata(L, 1));
  delete wrapper->texture;

  return 0;
}

static int w_TextureIndex(lua_State* L) {
  // Ignore arg 1.
  const char* key = lua_tostring(L, 2);
  lua_getfield(L, LUA_REGISTRYINDEX, TEXTURE_MEMBERS);
  lua_getfield(L, -1, key);

  // Clean up the stack
  lua_CFunction func = lua_tocfunction(L, -1);
  lua_pop(L, 2); 

  lua_pushcfunction(L, func);
  return 1;
}

luaL_Reg textureMt[] = {
  { "__gc", w_TextureGc },
  { "__index", w_TextureIndex },
  { nullptr, nullptr },
};

luaL_Reg textureMembers[] = {
  { "Draw", w_Draw },
  { nullptr, nullptr },
};

luaL_Reg textureLib[] = {
  { "Create", w_CreateTexture },
  { nullptr, nullptr },
};

int WrapTexture(lua_State* L) {
  luaL_newmetatable(L, "texturemt");
  RegisterFunctions(L, textureMt);
  lua_pop(L, 1);

  lua_newtable(L);
  RegisterFunctions(L, textureMembers);
  lua_setfield(L, LUA_REGISTRYINDEX, TEXTURE_MEMBERS);

  RegisterModule(L, TEXTURE_NAME, textureLib);
  return LUA_OK;
}
