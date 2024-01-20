#include "wrap_app.hh"

#include <iostream>

#include "window.hh"
#include "wrap.hh"

#define APP_MEMBERS "appMembers"

int LuaApp::Current = LUA_REFNIL;

void AppCallback(lua_State* L, const char* name) {
  lua_getglobal(L, LIB_NAME);
  lua_getfield(L, -1, APP_NAME);
  lua_getfield(L, -1, name);

  if (lua_isfunction(L, -1)) {
    lua_call(L, 0, 0);
  }

  lua_pop(L, 2);
}

void LuaApp::Ready() {
  AppCallback(L, "Ready");
}

void LuaApp::Step() {
  AppCallback(L, "Step");
}

void LuaApp::Draw() {
  AppCallback(L, "Draw");
}

static int w_CreateApp(lua_State* L) {
  Hobby::WindowSettings windowSettings;
  LuaApp* app;
  try {
    app = new LuaApp(L, windowSettings);
  } catch (std::exception& e) {
    return luaL_error(L, e.what());
  }

  AppWrapper* wrapper = static_cast<AppWrapper*>(
    lua_newuserdata(L, sizeof(AppWrapper)));
  wrapper->App = app;
  luaL_getmetatable(L, "appmt");
  lua_setmetatable(L, -2);

  app->Ref = luaL_ref(L, LUA_REGISTRYINDEX);
  LuaApp::Current = app->Ref;

  return 0;
}

static LuaApp* GetApp(lua_State* L) {
  lua_rawgeti(L, LUA_REGISTRYINDEX, LuaApp::Current);
  if (!lua_isuserdata(L, -1)) {
    luaL_error(L, "Expected app object.");
  }

  AppWrapper* wrapper = static_cast<AppWrapper*>(lua_touserdata(L, -1));
  return wrapper->App;
}

static int w_Run(lua_State* L) {
  LuaApp* app = GetApp(L);
  app->Run();
  return 0;
}

static int w_GetWindow(lua_State* L) {
  LuaApp* app = GetApp(L);
  WindowUserdata(L, &app->GetWindow());
  return 1;
}

static int w_AppGc(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected app object.");
  }

  AppWrapper* wrapper = static_cast<AppWrapper*>(lua_touserdata(L, 1));
  delete wrapper->App;

  return 0;
}

luaL_Reg appLib[] = {
  { "Create", w_CreateApp },
  { "GetWindow", w_GetWindow },
  { "Run", w_Run },
  { nullptr, nullptr },
};

luaL_Reg appMt[] = {
  { "__gc", w_AppGc },
  { nullptr, nullptr },
};

int WrapApp(lua_State *L) {
  luaL_newmetatable(L, "appmt");
  RegisterFunctions(L, appMt);
  lua_pop(L, 1);

  RegisterModule(L, APP_NAME, appLib);

  return LUA_OK;
}
