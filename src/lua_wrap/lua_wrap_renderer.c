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

static int wrap_drawPresent(hb_UNUSED lua_State* L) {
  struct hb_LuaWrapper* wrapper = hb_getLuaWrapper(L);
  hb_drawPresent(wrapper->engine->renderer);

  return 0;
}

static int wrap_drawSetColor(lua_State* L) {
  struct hb_LuaWrapper* wrapper = hb_getLuaWrapper(L);
  f64 r = lua_tonumber(L, 1);
  f64 g = lua_tonumber(L, 2);
  f64 b = lua_tonumber(L, 3);
  f64 a = luaL_optnumber(L, 4, 1);
  hb_drawSetColor(wrapper->engine->renderer, (struct hb_Color){r, g, b, a});

  return 0;
}

static int wrap_drawSetCircleResolution(lua_State* L) {
  struct hb_LuaWrapper* wrapper = hb_getLuaWrapper(L);
  f64 res = lua_tonumber(L, 1);
  hb_drawSetCircleResolution(wrapper->engine->renderer, res);

  return 0;
}

static int wrap_drawTexture(lua_State* L) {
  struct hb_LuaWrapper* wrapper = hb_getLuaWrapper(L);
  struct hb_LuaData* texture = lua_touserdata(L, 1);
  hb_ensureUserdataIsOfType(L, texture, hb_LUA_DATA_TYPE_TEXTURE, 1);

  f64 x = lua_tonumber(L, 2);
  f64 y = lua_tonumber(L, 3);
  f64 rot = luaL_optnumber(L, 4, 0);
  f64 scalex = luaL_optnumber(L, 5, 1);
  f64 scaley = luaL_optnumber(L, 6, scalex);
  f64 offsetx = luaL_optnumber(L, 7, 0);
  f64 offsety = luaL_optnumber(L, 8, 0);

  hb_drawTextureExt(wrapper->engine->renderer, texture->data, x, y, rot, scalex, scaley, offsetx, offsety);

  return 0;
}

static int wrap_drawSprite(lua_State* L) {
  struct hb_LuaWrapper* wrapper = hb_getLuaWrapper(L);
  struct hb_LuaData* sprite = lua_touserdata(L, 1);
  hb_ensureUserdataIsOfType(L, sprite, hb_LUA_DATA_TYPE_SPRITE, 1);

  hb_drawSprite(wrapper->engine->renderer, sprite->data);

  return 0;
}

static int wrap_drawRectangle(lua_State* L) {
  struct hb_LuaWrapper* wrapper = hb_getLuaWrapper(L);
  f64 x = lua_tonumber(L, 1);
  f64 y = lua_tonumber(L, 2);
  f64 w = lua_tonumber(L, 3);
  f64 h = lua_tonumber(L, 4);

  hb_drawRectangle(wrapper->engine->renderer, x, y, w, h);
  return 0;
}

static int wrap_drawRectangleOutline(lua_State* L) {
  struct hb_LuaWrapper* wrapper = hb_getLuaWrapper(L);
  f64 x = lua_tonumber(L, 1);
  f64 y = lua_tonumber(L, 2);
  f64 w = lua_tonumber(L, 3);
  f64 h = lua_tonumber(L, 4);

  hb_drawRectangleOutline(wrapper->engine->renderer, x, y, w, h);
  return 0;
}

static int wrap_drawEllipse(lua_State* L) {
  struct hb_LuaWrapper* wrapper = hb_getLuaWrapper(L);
  f64 x = lua_tonumber(L, 1);
  f64 y = lua_tonumber(L, 2);
  f64 rx = lua_tonumber(L, 3);
  f64 ry = lua_tonumber(L, 4);

  hb_drawEllipse(wrapper->engine->renderer, x, y, rx, ry);

  return 0;
}

static int wrap_drawEllipseOutline(lua_State* L) {
  struct hb_LuaWrapper* wrapper = hb_getLuaWrapper(L);
  f64 x = lua_tonumber(L, 1);
  f64 y = lua_tonumber(L, 2);
  f64 rx = lua_tonumber(L, 3);
  f64 ry = lua_tonumber(L, 4);

  hb_drawEllipseOutline(wrapper->engine->renderer, x, y, rx, ry);

  return 0;
}

static int wrap_drawCircle(lua_State* L) {
  struct hb_LuaWrapper* wrapper = hb_getLuaWrapper(L);
  f64 x = lua_tonumber(L, 1);
  f64 y = lua_tonumber(L, 2);
  f64 r = lua_tonumber(L, 3);

  hb_drawCircle(wrapper->engine->renderer, x, y, r);
  return 0;
}

static int wrap_drawCircleOutline(lua_State* L) {
  struct hb_LuaWrapper* wrapper = hb_getLuaWrapper(L);
  f64 x = lua_tonumber(L, 1);
  f64 y = lua_tonumber(L, 2);
  f64 r = lua_tonumber(L, 3);

  hb_drawCircleOutline(wrapper->engine->renderer, x, y, r);
  return 0;
}

static int wrap_drawPolygon(lua_State* L) {
  struct hb_LuaWrapper* wrapper = hb_getLuaWrapper(L);
  if (!lua_istable(L, 1)) {
    lua_pushstring(L, "Expected table.");
    return lua_error(L);
  }
  size_t polygonLength = lua_objlen(L, 1);
  size_t verticeSize = polygonLength + 2;
  f32 vertices[verticeSize];

  lua_pushvalue(L, 1);
  lua_pushnil(L);
  while (lua_next(L, -2)) {
    if (lua_isnumber(L, -2) && lua_isnumber(L, -1)) {
      s32 index = lua_tointeger(L, -2) - 1;
      f32 number = lua_tonumber(L, -1);
      vertices[index] = number;
    } else {
      lua_pushstring(L, "Expected a table of indices with number values.");
      return lua_error(L);
    }

    lua_pop(L, 1);
  }

  // Close
  vertices[verticeSize - 2] = vertices[0];
  vertices[verticeSize - 1] = vertices[1];
  
  hb_drawPolygon(wrapper->engine->renderer, vertices, polygonLength);
  return 0;
}

static int wrap_getDrawCalls(lua_State* L) {
  struct hb_LuaWrapper* wrapper = hb_getLuaWrapper(L);

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
  {"polygon", wrap_drawPolygon},
  {"getDrawCalls", wrap_getDrawCalls},
  {NULL, NULL}
};

void hb_luaWrapRenderer(lua_State *L) {
  hb_registerModule(L, LUA_RENDERER_NAME, renderer);
}
