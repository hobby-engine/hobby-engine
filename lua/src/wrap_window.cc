#include "window.hh"

#include "wrap.hh"
#include <iostream>

int w_ShouldClose(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected window object.");
  }

  WindowWrapper* window = static_cast<WindowWrapper*>(lua_touserdata(L, 1));
  lua_pushboolean(L, window->window->ShouldClose());
  return 1;
}

int w_Update(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected window object.");
  }

  WindowWrapper* window = static_cast<WindowWrapper*>(lua_touserdata(L, 1));
  window->window->Update();
  return 0;
}

int w_CreateWindow(lua_State* L) {
  int argc = lua_gettop(L);

  point::WindowSettings settings;

  if (argc != 0) {
    if (!lua_istable(L, 1)) {
      lua_pushstring(L, "Must take a table.");
      lua_error(L);
    }
    lua_pushvalue(L, 1);

    lua_getfield(L, -1, "Title");
    const char* title = luaL_optstring(L, -1, settings.Title);
    lua_getfield(L, -1, "Width");
    int width = luaL_optinteger(L, -1, settings.Width);
    lua_getfield(L, -1, "Height");
    int height = luaL_optinteger(L, -1, settings.Height);
    lua_getfield(L, -1, "X");
    int x = luaL_optinteger(L, -1, settings.X);
    lua_getfield(L, -1, "Y");
    int y = luaL_optinteger(L, -1, settings.Y);
    lua_getfield(L, -1, "Resizable");
    bool resizable = settings.Resizable;
    if (!lua_isnil(L, -1)) {
      resizable = lua_toboolean(L, -1);
    }

    settings.Title = title;
    settings.Width = width;
    settings.Height = height;
    settings.X = x;
    settings.Y = y;
    settings.Resizable = resizable;
  }

  point::Window* window = new point::Window(settings);
  WindowWrapper* wrapper = static_cast<WindowWrapper*>(
    lua_newuserdata(L, sizeof(WindowWrapper)));
  wrapper->window = window;
  luaL_getmetatable(L, "windowmt");
  lua_setmetatable(L, -2);

  return 1;
}

static int w_WindowGc(lua_State* L) {
  if (!lua_isuserdata(L, -1)) {
    return luaL_error(L, "Expected window object.");
  }

  WindowWrapper* window = static_cast<WindowWrapper*>(lua_touserdata(L, -1));
  delete window->window;

  return 0;
}

luaL_Reg windowLib[] = {
  { "Create", w_CreateWindow },
  { "ShouldClose", w_ShouldClose },
  { "Update", w_Update },
  { nullptr, nullptr },
};

int WrapWindow(lua_State* L) {
  // Create window metatable
  luaL_newmetatable(L, "windowmt");
  lua_pushcfunction(L, w_WindowGc);
  lua_setfield(L, -2, "__gc");
  lua_pop(L, 1);

  RegisterModule(L, WINDOW_NAME, windowLib);
  return LUA_OK;
}
