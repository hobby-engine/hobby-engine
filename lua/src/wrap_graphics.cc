#include "wrap.hh"

int w_GraphicsInitialize(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected window object.");
  }

  WindowWrapper* window = static_cast<WindowWrapper*>(lua_touserdata(L, 1));
  Hobby::Draw::Initialize(*window->window);
  return 0;
}

int w_GraphicsPushState(lua_State* L) {
  (void)L;
  Hobby::Draw::PushState();
  return 0;
}

int w_GraphicsPopState(lua_State* L) {
  (void)L;
  Hobby::Draw::PopState();
  return 0;
}

int w_GraphicsSetColor(lua_State* L) {
  float r = luaL_checknumber(L, 1);
  float g = luaL_checknumber(L, 2);
  float b = luaL_checknumber(L, 3);
  float a = luaL_optnumber(L, 4, 1);
  Hobby::Color color(r, g, b, a);
  Hobby::Draw::SetColor(color);
  return 0;
}

int w_GraphicsClear(lua_State* L) {
  (void)L;
  Hobby::Draw::Clear();
  return 0;
}

int w_GraphicsPresent(lua_State* L) {
  (void)L;
  Hobby::Draw::Present();
  return 0;
}

int w_GraphicsLine(lua_State* L) {
  float sx = luaL_checknumber(L, 1);
  float sy = luaL_checknumber(L, 2);
  float ex = luaL_checknumber(L, 3);
  float ey = luaL_checknumber(L, 4);

  Hobby::Draw::Line(Hobby::Vec2(sx, sy), Hobby::Vec2(ex, ey));
  return 0;
}

int w_GraphicsRectangle(lua_State* L) {
  float x = luaL_checknumber(L, 1);
  float y = luaL_checknumber(L, 2);
  float w = luaL_checknumber(L, 3);
  float h = luaL_checknumber(L, 4);

  Hobby::Draw::Rectangle(Hobby::Vec2(x, y), Hobby::Vec2(w, h));
  return 0;
}

int w_GraphicsFilledRectangle(lua_State* L) {
  float x = luaL_checknumber(L, 1);
  float y = luaL_checknumber(L, 2);
  float w = luaL_checknumber(L, 3);
  float h = luaL_checknumber(L, 4);

  Hobby::Draw::FilledRectangle(Hobby::Vec2(x, y), Hobby::Vec2(w, h));
  return 0;
}

luaL_Reg graphicsLib[] = {
  { "Initialize", w_GraphicsInitialize },
  { "PushState", w_GraphicsPushState },
  { "PopState", w_GraphicsPopState },
  { "SetColor", w_GraphicsSetColor },
  { "Clear", w_GraphicsClear },
  { "Present", w_GraphicsPresent },
  { "Line", w_GraphicsLine },
  { "Rectangle", w_GraphicsRectangle },
  { "FilledRectangle", w_GraphicsFilledRectangle },
  { nullptr, nullptr },
};

int WrapGraphics(lua_State* L) {
  RegisterModule(L, DRAW_NAME, graphicsLib);
  return LUA_OK;
}
