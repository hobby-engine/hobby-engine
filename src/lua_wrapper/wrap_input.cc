#include "key.hh"
#include "wrapper.hh"

static int wrap_isKeyPressed(lua_State* L)
{
  LuaWrapper* wrapper = getLuaWrapper(L);
  bool pressed =
    wrapper->engine.input->isKeyPressed((Key)luaL_checknumber(L, 1));
  lua_pushboolean(L, pressed);
  return 1;
}

static int wrap_isMousePressed(lua_State* L)
{
  LuaWrapper* wrapper = getLuaWrapper(L);
  bool pressed =
    wrapper->engine.input->isMousePressed(luaL_checknumber(L, 1) - 1);
  lua_pushboolean(L, pressed);
  return 1;
}

luaL_Reg input[] = {
  {"isKeyPressed",   wrap_isKeyPressed  },
  {"isMousePressed", wrap_isMousePressed},
  {nullptr,          nullptr            },
};

void wrapInput(lua_State* L)
{
  lua_getglobal(L, LUA_LIB_NAME);
  registerFunctions(L, input);
}
