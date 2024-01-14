#ifndef _HOBBY_LUA_WRAP_H
#define _HOBBY_LUA_WRAP_H

#include "luajit/lua.hpp"
#include "hobby.hh"
#include <iostream>
#include <stdexcept>

struct WindowWrapper {
  bool OwnsWindow;
  Hobby::Window* Window;
};

struct TextureWrapper {
  Hobby::Texture* Texture;
};

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

#define LIB_NAME "Hobby"
#define APP_NAME "App"
#define TEXTURE_NAME "Texture"
#define WINDOW_NAME "Window"
#define DRAW_NAME "Draw"
#define TIME_NAME "Time"

#define OPT_BOOL(L, i, d) \
  lua_isboolean(L, i) ? lua_toboolean(L, i) : (d)

void RegisterModule(lua_State* L, const char* name, const luaL_Reg *functions);
void RegisterFunctions(lua_State* L, const luaL_Reg* funcs);

int WrapApp(lua_State* L);
int WrapTexture(lua_State* L);
int WrapWindow(lua_State* L);
int WrapGraphics(lua_State* L);
int WrapTime(lua_State* L);

void WindowUserdata(lua_State* L, Hobby::Window* window);

#endif // _HOBBY_LUA_WRAP_H
