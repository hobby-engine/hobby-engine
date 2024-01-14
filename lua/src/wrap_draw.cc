#include "draw.hh"
#include "wrap.hh"

int w_DrawInitialize(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected window object.");
  }

  WindowWrapper* window = static_cast<WindowWrapper*>(lua_touserdata(L, 1));
  Hobby::Draw::Initialize(*window->Window);
  return 0;
}

int w_DrawPushState(lua_State* L) {
  (void)L;
  Hobby::Draw::PushState();
  return 0;
}

int w_DrawPopState(lua_State* L) {
  (void)L;
  Hobby::Draw::PopState();
  return 0;
}

int w_DrawSetColor(lua_State* L) {
  float r = luaL_checknumber(L, 1);
  float g = luaL_checknumber(L, 2);
  float b = luaL_checknumber(L, 3);
  float a = luaL_optnumber(L, 4, 1);
  Hobby::Color color(r, g, b, a);
  Hobby::Draw::SetColor(color);
  return 0;
}

int w_DrawClear(lua_State* L) {
  (void)L;
  Hobby::Draw::Clear();
  return 0;
}

int w_DrawPresent(lua_State* L) {
  (void)L;
  Hobby::Draw::Present();
  return 0;
}

static int w_DrawDrawTexture(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected texture object.");
  }

  float x = luaL_checknumber(L, 2);
  float y = luaL_checknumber(L, 3);

  TextureWrapper* wrapper = static_cast<TextureWrapper*>(lua_touserdata(L, 1));
  Hobby::Draw::DrawTexture(*wrapper->Texture, Hobby::Vec2(x, y));
  return 0;
};

int w_DrawLine(lua_State* L) {
  float sx = luaL_checknumber(L, 1);
  float sy = luaL_checknumber(L, 2);
  float ex = luaL_checknumber(L, 3);
  float ey = luaL_checknumber(L, 4);

  Hobby::Draw::Line(Hobby::Vec2(sx, sy), Hobby::Vec2(ex, ey));
  return 0;
}

int w_DrawRectangle(lua_State* L) {
  float x = luaL_checknumber(L, 1);
  float y = luaL_checknumber(L, 2);
  float w = luaL_checknumber(L, 3);
  float h = luaL_checknumber(L, 4);

  Hobby::Draw::Rectangle(Hobby::Vec2(x, y), Hobby::Vec2(w, h));
  return 0;
}

int w_DrawFilledRectangle(lua_State* L) {
  float x = luaL_checknumber(L, 1);
  float y = luaL_checknumber(L, 2);
  float w = luaL_checknumber(L, 3);
  float h = luaL_checknumber(L, 4);

  Hobby::Draw::FilledRectangle(Hobby::Vec2(x, y), Hobby::Vec2(w, h));
  return 0;
}

luaL_Reg graphicsLib[] = {
  { "Initialize", w_DrawInitialize },
  { "PushState", w_DrawPushState },
  { "PopState", w_DrawPopState },
  { "SetColor", w_DrawSetColor },
  { "Clear", w_DrawClear },
  { "Present", w_DrawPresent },
  { "DrawTexture", w_DrawDrawTexture },
  { "Line", w_DrawLine },
  { "Rectangle", w_DrawRectangle },
  { "FilledRectangle", w_DrawFilledRectangle },
  { nullptr, nullptr },
};

int WrapGraphics(lua_State* L) {
  RegisterModule(L, DRAW_NAME, graphicsLib);
  return LUA_OK;
}
