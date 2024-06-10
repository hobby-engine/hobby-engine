#include "window.hh"
#include "wrapper.hh"

static int wrap_getmainwindow(lua_State* L)
{
  LuaWrapper* wrapper = getwrapper(L);
  LuaData* ld =
    createluadata(L, wrapper->engine.mainwin, LuaDataType::Window, "windowmt");
  ld->owned = false;
  return 1;
}

static int wrap_window(lua_State* L)
{
  WindowOptions winopt;
  if (!lua_istable(L, 1)) {
    return luaL_error(L, "Expected a table.");
  }

  lua_getfield(L, 1, "title");
  winopt.title = luaL_optstring(L, -1, "HB Popup");
  lua_getfield(L, 1, "canresize");
  winopt.canresize = lua_toboolean(L, -1);
  lua_getfield(L, 1, "width");
  winopt.width = luaL_optinteger(L, -1, 300);
  lua_getfield(L, 1, "height");
  winopt.height = luaL_optinteger(L, -1, 300);
  lua_getfield(L, 1, "x");
  winopt.x = luaL_optinteger(L, -1, -1);
  lua_getfield(L, 1, "y");
  winopt.y = luaL_optinteger(L, -1, -1);

  LuaWrapper* wrapper = getwrapper(L);

  Window* window = Window::create(wrapper->engine, winopt);
  createluadata(L, window, LuaDataType::Window, "windowmt");

  return 1;
}

static int wrap_gettitle(lua_State* L)
{
  Window* window = getuserdata<Window>(L, 1, LuaDataType::Window);
  lua_pushstring(L, window->gettitle());
  return 1;
}

static int wrap_settitle(lua_State* L)
{
  Window* window = getuserdata<Window>(L, 1, LuaDataType::Window);
  const char* title = luaL_checkstring(L, 2);
  window->settitle(title);
  return 0;
}

static int wrap_getsize(lua_State* L)
{
  Window* window = getuserdata<Window>(L, 1, LuaDataType::Window);
  int w = 0;
  int h = 0;
  window->getsize(w, h);
  lua_pushnumber(L, w);
  lua_pushnumber(L, h);
  return 2;
}

static int wrap_setsize(lua_State* L)
{
  Window* window = getuserdata<Window>(L, 1, LuaDataType::Window);
  int w = luaL_checknumber(L, 1);
  int h = luaL_checknumber(L, 2);
  if (w <= 0 || h <= 0) {
    luaL_error(L, "Width and height must be above 0.");
  }
  window->setsize(w, h);
  return 0;
}

static int wrap_makecurrent(lua_State* L)
{
  Window* window = getuserdata<Window>(L, 1, LuaDataType::Window);
  window->makecurrent();
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
  Window* window = getuserdata<Window>(L, 1, LuaDataType::Window);
  if (!window->isclosed()) {
    window->close();
  }
  delete window;
  return 0;
}

luaL_Reg window[] = {
  {"getmainwindow", wrap_getmainwindow},
  {"window",        wrap_window       },
  {nullptr,         nullptr           },
};

luaL_Reg windowmt[] = {
  {"gettitle",    wrap_gettitle   },
  {"settitle",    wrap_settitle   },
  {"getsize",     wrap_getsize    },
  {"setsize",     wrap_setsize    },
  {"makecurrent", wrap_makecurrent},
  {"__gc",        window__gc      },
  {"__index",     window__index   },
  {nullptr,       nullptr         },
};

void wrapwindow(lua_State* L)
{
  lua_getglobal(L, LUA_LIB_NAME);
  registerfuncs(L, window);

  luaL_newmetatable(L, "windowmt");
  registerfuncs(L, windowmt);
  lua_pop(L, 1); // windowmt
}
