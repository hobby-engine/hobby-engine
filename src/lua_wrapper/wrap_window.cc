#include "window.hh"
#include "wrapper.hh"

static int wrap_mainwindow(lua_State* L)
{
  LuaWrapper* wrapper = getLuaWrapper(L);
  LuaData* ld = createLuaData(
    L, wrapper->engine.mainWindow, LuaDataType::Window, "windowmt");
  ld->owned = false;
  return 1;
}

static int wrap_window(lua_State* L)
{
  WindowSettings settings;
  if (!lua_istable(L, 1)) {
    return luaL_error(L, "Expected a table.");
  }

  lua_getfield(L, 1, "title");
  settings.title = luaL_optstring(L, -1, "HB Popup");
  lua_getfield(L, 1, "canResize");
  settings.canResize = lua_toboolean(L, -1);
  lua_getfield(L, 1, "width");
  settings.width = luaL_optinteger(L, -1, 300);
  lua_getfield(L, 1, "height");
  settings.height = luaL_optinteger(L, -1, 300);
  lua_getfield(L, 1, "x");
  settings.x = luaL_optinteger(L, -1, -1);
  lua_getfield(L, 1, "y");
  settings.y = luaL_optinteger(L, -1, -1);

  LuaWrapper* wrapper = getLuaWrapper(L);

  Window* window = Window::create(wrapper->engine, settings);
  createLuaData(L, window, LuaDataType::Window, "windowmt");

  return 1;
}

static int wrap_gettitle(lua_State* L)
{
  Window* window = getUserdata<Window>(L, 1, LuaDataType::Window);
  lua_pushstring(L, window->getTitle());
  return 1;
}

static int wrap_settitle(lua_State* L)
{
  Window* window = getUserdata<Window>(L, 1, LuaDataType::Window);
  const char* title = luaL_checkstring(L, 2);
  window->setTitle(title);
  return 0;
}

static int wrap_getsize(lua_State* L)
{
  Window* window = getUserdata<Window>(L, 1, LuaDataType::Window);
  int w = 0, h = 0;
  window->getSize(w, h);
  lua_pushnumber(L, w);
  lua_pushnumber(L, h);
  return 2;
}

static int wrap_setsize(lua_State* L)
{
  Window* window = getUserdata<Window>(L, 1, LuaDataType::Window);
  int w = luaL_checknumber(L, 1);
  int h = luaL_checknumber(L, 2);
  if (w <= 0 || h <= 0) {
    luaL_error(L, "Width and height must be above 0.");
  }
  window->setSize(w, h);
  return 0;
}

static int wrap_setcurrent(lua_State* L)
{
  Window* window = getUserdata<Window>(L, 1, LuaDataType::Window);
  window->setCurrent();
  return 0;
}

static int window__index(lua_State* L)
{
  luaL_getmetatable(L, "windowmt");
  lua_getfield(L, -1, luaL_checkstring(L, 2));
  return 1;
}

static int window__gc(lua_State* L)
{
  LuaData* v = (LuaData*)lua_touserdata(L, 1);
  if (!v->owned) {
    return 0;
  }
  Window* window = getUserdata<Window>(L, 1, LuaDataType::Window);
  if (!window->isClosed()) {
    window->close();
  }
  delete window;
  return 0;
}

luaL_Reg window[] = {
  {"mainwindow", wrap_mainwindow},
  {"window",     wrap_window    },
  {nullptr,      nullptr        },
};

luaL_Reg windowmt[] = {
  {"gettitle",   wrap_gettitle  },
  {"settitle",   wrap_settitle  },
  {"getsize",    wrap_getsize   },
  {"setsize",    wrap_setsize   },
  {"setcurrent", wrap_setcurrent},
  {"__gc",       window__gc     },
  {"__index",    window__index  },
  {nullptr,      nullptr        },
};

void wrapWindow(lua_State* L)
{
  lua_getglobal(L, LUA_LIB_NAME);
  registerFunctions(L, window);

  luaL_newmetatable(L, "windowmt");
  registerFunctions(L, windowmt);
  lua_pop(L, 1); // windowmt
}
