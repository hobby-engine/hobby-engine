#include "lua_wrapper.h"
#include "renderer.h"

static int wrap_drawClear(lua_State* L) {
  f64 r = lua_tonumber(L, 1);
  f64 g = lua_tonumber(L, 2);
  f64 b = lua_tonumber(L, 3);
  f64 a = luaL_optnumber(L, 4, 1);
  hb_drawClear((hb_Color){r, g, b, a});

  return 0;
}

static int wrap_drawPresent(lua_State* L) {
  hb_drawPresent();

  return 0;
}

static int wrap_drawSetColor(lua_State* L) {
  f64 r = lua_tonumber(L, 1);
  f64 g = lua_tonumber(L, 2);
  f64 b = lua_tonumber(L, 3);
  f64 a = luaL_optnumber(L, 4, 1);
  hb_drawSetColor((hb_Color){r, g, b, a});

  return 0;
}

static int wrap_drawSetCircleResolution(lua_State* L) {
  f64 res = lua_tonumber(L, 1);
  hb_drawSetCircleResolution(res);

  return 0;
}

static int wrap_drawRectangle(lua_State* L) {
  f64 x = lua_tonumber(L, 1);
  f64 y = lua_tonumber(L, 2);
  f64 w = lua_tonumber(L, 3);
  f64 h = lua_tonumber(L, 4);

  hb_drawRectangle(x, y, w, h);
  return 0;
}

static int wrap_drawCircle(lua_State* L) {
  f64 x = lua_tonumber(L, 1);
  f64 y = lua_tonumber(L, 2);
  f64 r = lua_tonumber(L, 3);

  hb_drawCircle(x, y, r);
  return 0;
}

luaL_Reg renderer[] = {
  {"clear", wrap_drawClear},
  {"present", wrap_drawPresent},
  {"setColor", wrap_drawSetColor},
  {"setCircleResolution", wrap_drawSetCircleResolution},
  {"rectangle", wrap_drawRectangle},
  {"circle", wrap_drawCircle},
  {NULL, NULL}
};

void hb_luaWrapRenderer(lua_State *L) {
  hb_registerModule(L, LUA_RENDERER_NAME, renderer);
}
