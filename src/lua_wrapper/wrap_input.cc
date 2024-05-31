#include "key.hh"
#include "wrapper.hh"

static int wrap_keydown(lua_State* L)
{
  LuaWrapper* wrapper = getwrapper(L);
  bool pressed = wrapper->engine.input->iskeydown((Key)luaL_checknumber(L, 1));
  lua_pushboolean(L, pressed);
  return 1;
}

static int wrap_mousedown(lua_State* L)
{
  LuaWrapper* wrapper = getwrapper(L);
  bool pressed = wrapper->engine.input->ismousedown(luaL_checknumber(L, 1) - 1);
  lua_pushboolean(L, pressed);
  return 1;
}

luaL_Reg input[] = {
  {"iskeydown",   wrap_keydown  },
  {"ismousedown", wrap_mousedown},
  {nullptr,       nullptr       },
};

void wrapinput(lua_State* L)
{
  lua_getglobal(L, LUA_LIB_NAME);
  lua_newtable(L);
  registerfuncs(L, input);
  lua_setfield(L, -2, "input");
}
