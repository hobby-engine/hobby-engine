#include "wrap.hh"
#include <exception>

#define TEXTURE_MEMBERS "textureMembers"

static int w_CreateTexture(lua_State* L) {
  std::string path = luaL_checkstring(L, 1);

  Hobby::Texture* texture;
  try {
    texture = new Hobby::Texture(path);
  } catch (std::exception& e) {
    return luaL_error(L, e.what());
  }

  TextureWrapper* wrapper = static_cast<TextureWrapper*>(
    lua_newuserdata(L, sizeof(TextureWrapper)));
  wrapper->Texture = texture;
  luaL_getmetatable(L, "texturemt");
  lua_setmetatable(L, -2);

  return 1;
}

static int w_Draw(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected texture object.");
  }

  float x = luaL_checknumber(L, 2);
  float y = luaL_checknumber(L, 3);
  float rot = luaL_optnumber(L, 4, 0);
  float sx = luaL_optnumber(L, 5, 1);
  float sy = luaL_optnumber(L, 6, sx);
  float ox = luaL_optnumber(L, 7, 0);
  float oy = luaL_optnumber(L, 8, 0);

  TextureWrapper* wrapper = static_cast<TextureWrapper*>(lua_touserdata(L, 1));
  wrapper->Texture->Draw(
    Hobby::Vec2(x, y),
    rot,
    Hobby::Vec2(sx, sy),
    Hobby::Vec2(ox, oy));
  return 0;
};

static int w_GetSize(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected texture object.");
  }

  TextureWrapper* wrapper = static_cast<TextureWrapper*>(lua_touserdata(L, 1));
  Hobby::Vec2 size = wrapper->Texture->GetSize();
  lua_pushnumber(L, size.W);
  lua_pushnumber(L, size.H);
  return 2;
}

static int w_GetWidth(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected texture object.");
  }

  TextureWrapper* wrapper = static_cast<TextureWrapper*>(lua_touserdata(L, 1));
  lua_pushnumber(L, wrapper->Texture->GetWidth());
  return 1;
}

static int w_GetHeight(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected texture object.");
  }

  TextureWrapper* wrapper = static_cast<TextureWrapper*>(lua_touserdata(L, 1));
  lua_pushnumber(L, wrapper->Texture->GetHeight());
  return 1;
}

static int w_TextureGc(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected texture object.");
  }

  TextureWrapper* wrapper = static_cast<TextureWrapper*>(lua_touserdata(L, 1));
  delete wrapper->Texture;

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
  { "GetSize", w_GetSize },
  { "GetWidth", w_GetWidth },
  { "GetHeight", w_GetHeight },
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
