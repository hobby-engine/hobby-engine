#include "lua_wrapper.h"
#include "renderer.h"

static int wrap_drawClear(lua_State* L) {
  f64 r = lua_tonumber(L, 1);
  f64 g = lua_tonumber(L, 2);
  f64 b = lua_tonumber(L, 3);
  f64 a = luaL_optnumber(L, 4, 1);
  hb_drawClear((struct hb_Color){r, g, b, a});

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
  hb_drawSetColor((struct hb_Color){r, g, b, a});

  return 0;
}

static int wrap_drawSetCircleResolution(lua_State* L) {
  f64 res = lua_tonumber(L, 1);
  hb_drawSetCircleResolution(res);

  return 0;
}

static int wrap_drawTexture(lua_State* L) {
  struct hb_LuaData* wrapper = lua_touserdata(L, 1);
  hb_ensureUserdataIsOfType(L, wrapper, hb_LUA_DATA_TYPE_TEXTURE, 1);

  f64 x = lua_tonumber(L, 2);
  f64 y = lua_tonumber(L, 3);
  f64 rot = luaL_optnumber(L, 4, 0);
  f64 scalex = luaL_optnumber(L, 5, 1);
  f64 scaley = luaL_optnumber(L, 6, scalex);
  f64 offsetx = luaL_optnumber(L, 7, 0);
  f64 offsety = luaL_optnumber(L, 8, 0);

  hb_drawTextureExt(wrapper->data, x, y, rot, scalex, scaley, offsetx, offsety);

  return 0;
}

static int wrap_drawSprite(lua_State* L) {
  struct hb_LuaData* wrapper = lua_touserdata(L, 1);
  hb_ensureUserdataIsOfType(L, wrapper, hb_LUA_DATA_TYPE_SPRITE, 1);

  hb_drawSprite(wrapper->data);

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

static int wrap_drawRectangleOutline(lua_State* L) {
  f64 x = lua_tonumber(L, 1);
  f64 y = lua_tonumber(L, 2);
  f64 w = lua_tonumber(L, 3);
  f64 h = lua_tonumber(L, 4);

  hb_drawRectangleOutline(x, y, w, h);
  return 0;
}

static int wrap_drawEllipse(lua_State* L) {
  f64 x = lua_tonumber(L, 1);
  f64 y = lua_tonumber(L, 2);
  f64 rx = lua_tonumber(L, 3);
  f64 ry = lua_tonumber(L, 4);

  hb_drawEllipse(x, y, rx, ry);

  return 0;
}

static int wrap_drawEllipseOutline(lua_State* L) {
  f64 x = lua_tonumber(L, 1);
  f64 y = lua_tonumber(L, 2);
  f64 rx = lua_tonumber(L, 3);
  f64 ry = lua_tonumber(L, 4);

  hb_drawEllipseOutline(x, y, rx, ry);

  return 0;
}

static int wrap_drawCircle(lua_State* L) {
  f64 x = lua_tonumber(L, 1);
  f64 y = lua_tonumber(L, 2);
  f64 r = lua_tonumber(L, 3);

  hb_drawCircle(x, y, r);
  return 0;
}

static int wrap_drawCircleOutline(lua_State* L) {
  f64 x = lua_tonumber(L, 1);
  f64 y = lua_tonumber(L, 2);
  f64 r = lua_tonumber(L, 3);

  hb_drawCircleOutline(x, y, r);
  return 0;
}

static int wrap_getDrawCalls(lua_State* L) {
  lua_getfield(L, LUA_REGISTRYINDEX, "wrapper");
  struct hb_LuaWrapper* wrapper = lua_touserdata(L, -1);

  lua_pushinteger(L, wrapper->engine->renderer->drawCalls);
  return 1;
}

luaL_Reg renderer[] = {
  {"clear", wrap_drawClear},
  {"present", wrap_drawPresent},
  {"setColor", wrap_drawSetColor},
  {"setCircleResolution", wrap_drawSetCircleResolution},
  {"texture", wrap_drawTexture},
  {"sprite", wrap_drawSprite},
  {"rectangleOutline", wrap_drawRectangleOutline},
  {"rectangle", wrap_drawRectangle},
  {"circleOutline", wrap_drawCircleOutline},
  {"circle", wrap_drawCircle},
  {"ellipseOutline", wrap_drawEllipseOutline},
  {"ellipse", wrap_drawEllipse},
  {"getDrawCalls", wrap_getDrawCalls},
  {NULL, NULL}
};

void hb_luaWrapRenderer(lua_State *L) {
  hb_registerModule(L, LUA_RENDERER_NAME, renderer);
}
