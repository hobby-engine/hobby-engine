#include "wrap.hh"

int w_TimeGetDelta(lua_State* L) {
  lua_pushnumber(L, Hobby::Time::GetDelta());
  return 1;
}

int w_TimeStep(lua_State* L) {
  (void)L;
  Hobby::Time::Step();
  return 0;
}

luaL_Reg timeLib[] = {
  { "Step", w_TimeStep },
  { "GetDelta", w_TimeGetDelta },
  { nullptr, nullptr },
};

int WrapTime(lua_State *L) {
  RegisterModule(L, TIME_NAME, timeLib);
  return LUA_OK;
}
