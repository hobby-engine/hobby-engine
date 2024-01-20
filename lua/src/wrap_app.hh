#ifndef _HOBBY_LUA_WRAP_APP_H
#define _HOBBY_LUA_WRAP_APP_H

#include "hobby.hh"
#include "luajit/lua.hpp"

#define APP_NAME "App"

class LuaApp final : public Hobby::App {
public:
  LuaApp(lua_State* L, const Hobby::WindowSettings& windowSettings)
    : Hobby::App(windowSettings),
      L(L) {
  }

  ~LuaApp() {
    luaL_unref(L, LUA_REGISTRYINDEX, Ref);
  }

  void Ready() override;
  void Step() override;
  void Draw() override;

  lua_State* L;

  int Ref;
  static int Current;
};

struct AppWrapper {
  LuaApp* App;
};
int WrapApp(lua_State* L);

#endif
