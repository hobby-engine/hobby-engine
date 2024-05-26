#include "key.hh"
#include "wrapper.hh"

static int wrap_keydown(lua_State* L)
{
  LuaWrapper* wrapper = getLuaWrapper(L);
  bool pressed =
    wrapper->engine.input->isKeyPressed((Key)luaL_checknumber(L, 1));
  lua_pushboolean(L, pressed);
  return 1;
}

static int wrap_mousedown(lua_State* L)
{
  LuaWrapper* wrapper = getLuaWrapper(L);
  bool pressed =
    wrapper->engine.input->isMousePressed(luaL_checknumber(L, 1) - 1);
  lua_pushboolean(L, pressed);
  return 1;
}

luaL_Reg input[] = {
  {"keydown",   wrap_keydown  },
  {"mousedown", wrap_mousedown},
  {nullptr,     nullptr       },
};

void wrapInput(lua_State* L)
{
  lua_getglobal(L, LUA_LIB_NAME);
  lua_newtable(L);
  registerFunctions(L, input);
  lua_setfield(L, -2, "input");
}
