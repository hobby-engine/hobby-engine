#include "wrap_window.hh"

#include <iostream>

#include "wrap.hh"

#define WINDOW_MEMBERS "windowMembers"

int w_ShouldClose(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected window object.");
  }

  WindowWrapper* window = static_cast<WindowWrapper*>(lua_touserdata(L, 1));
  lua_pushboolean(L, window->Window->ShouldClose());
  return 1;
}

int w_Update(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected window object.");
  }

  WindowWrapper* window = static_cast<WindowWrapper*>(lua_touserdata(L, 1));
  window->Window->Update();
  return 0;
}

int w_Close(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected window object.");
  }

  WindowWrapper* window = static_cast<WindowWrapper*>(lua_touserdata(L, 1));
  window->Window->Update();
  return 0;
}

int w_SetTitle(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected window object.");
  }

  WindowWrapper* window = static_cast<WindowWrapper*>(lua_touserdata(L, 1));
  window->Window->SetTitle(luaL_checkstring(L, 2));
  return 0;
}

int w_GetTitle(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected window object.");
  }

  WindowWrapper* window = static_cast<WindowWrapper*>(lua_touserdata(L, 1));
  std::string title = window->Window->GetTitle();
  lua_pushstring(L, title.c_str());
  return 1;
}

int w_SetSize(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected window object.");
  }

  int x = luaL_checkinteger(L, 2);
  int y = luaL_checkinteger(L, 3);

  WindowWrapper* window = static_cast<WindowWrapper*>(lua_touserdata(L, 1));
  window->Window->SetSize(Hobby::Vec2(x, y));
  return 0;
}

int w_GetSize(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected window object.");
  }

  WindowWrapper* window = static_cast<WindowWrapper*>(lua_touserdata(L, 1));
  Hobby::Vec2 size = window->Window->GetSize();
  lua_pushinteger(L, size.W);
  lua_pushinteger(L, size.H);
  return 2;
}

int w_CreateWindow(lua_State* L) {
  int argc = lua_gettop(L);

  Hobby::WindowSettings settings;

  if (argc != 0) {
    if (!lua_istable(L, 1)) {
      lua_pushstring(L, "Must take a table.");
      lua_error(L);
      return 0;
    }

    lua_getfield(L, 1, "Title");
    const char* title = luaL_optstring(L, -1, settings.Title.c_str());
    lua_getfield(L, 1, "Width");
    int width = luaL_optint(L, -1, settings.Width);
    lua_getfield(L, 1, "Height");
    int height = luaL_optint(L, -1, settings.Height);
    lua_getfield(L, 1, "X");
    int x = luaL_optint(L, -1, settings.X);
    lua_getfield(L, 1, "Y");
    int y = luaL_optint(L, -1, settings.Y);
    lua_getfield(L, 1, "Resizable");
    bool resizable = OPT_BOOL(L, -1, settings.Resizable);
    lua_getfield(L, 1, "Borderless");
    bool borderless = OPT_BOOL(L, -1, settings.Borderless);
    lua_getfield(L, 1, "Visible");
    bool visible = OPT_BOOL(L, -1, settings.Visible);
    lua_getfield(L, 1, "Minimized");
    bool minimized = OPT_BOOL(L, -1, settings.Minimized);
    lua_getfield(L, 1, "Maximized");
    bool maximized = OPT_BOOL(L, -1, settings.Maximized);

    settings.Title = title;
    settings.Width = width;
    settings.Height = height;
    settings.X = x;
    settings.Y = y;
    settings.Resizable = resizable;
    settings.Borderless = borderless;
    settings.Visible = visible;
    settings.Minimized = minimized;
    settings.Maximized = maximized;
  }

  Hobby::Window* window;
  try {
    window = new Hobby::Window(settings);
  } catch (std::exception& e) {
    return luaL_error(L, e.what());
  }

  WindowWrapper* wrapper = static_cast<WindowWrapper*>(
    lua_newuserdata(L, sizeof(WindowWrapper)));
  wrapper->Window = window;
  wrapper->OwnsWindow = true;
  luaL_getmetatable(L, "windowmt");
  lua_setmetatable(L, -2);

  return 1;
}

void WindowUserdata(lua_State* L, Hobby::Window* window) {
  WindowWrapper* wrapper = static_cast<WindowWrapper*>(
    lua_newuserdata(L, sizeof(WindowWrapper)));
  wrapper->Window = window;
  wrapper->OwnsWindow = false;
  luaL_getmetatable(L, "windowmt");
  lua_setmetatable(L, -2);
}

static int w_WindowGc(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected window object.");
  }

  WindowWrapper* window = static_cast<WindowWrapper*>(lua_touserdata(L, 1));
  if (window->OwnsWindow) {
    delete window->Window;
  }

  return 0;
}

static int w_WindowIndex(lua_State* L) {
  // Ignore arg 1.
  const char* key = lua_tostring(L, 2);
  lua_getfield(L, LUA_REGISTRYINDEX, WINDOW_MEMBERS);
  lua_getfield(L, -1, key);

  // Clean up the stack
  lua_CFunction func = lua_tocfunction(L, -1);
  lua_pop(L, 2); 

  lua_pushcfunction(L, func);
  return 1;
}

luaL_Reg windowMt[] = {
  { "__gc", w_WindowGc },
  { "__index", w_WindowIndex },
  { nullptr, nullptr },
};

luaL_Reg windowMembers[] = {
  { "ShouldClose", w_ShouldClose },
  { "Close", w_Close },
  { "SetTitle", w_SetTitle },
  { "GetTitle", w_GetTitle },
  { "SetSize", w_SetSize },
  { "GetSize", w_GetSize },
  { "Update", w_Update },
  { nullptr, nullptr },
};

luaL_Reg windowLib[] = {
  { "Create", w_CreateWindow },
  { nullptr, nullptr },
};

int WrapWindow(lua_State* L) {
  // Create window metatable
  luaL_newmetatable(L, "windowmt");
  RegisterFunctions(L, windowMt);
  lua_pop(L, 1);

  lua_newtable(L);
  RegisterFunctions(L, windowMembers);
  lua_setfield(L, LUA_REGISTRYINDEX, WINDOW_MEMBERS);

  RegisterModule(L, WINDOW_NAME, windowLib);

  return LUA_OK;
}
