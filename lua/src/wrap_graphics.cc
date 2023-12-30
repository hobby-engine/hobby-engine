#include "wrap.hh"

#include "point.hh"

int w_GraphicsInitialize(lua_State* L) {
  if (!lua_isuserdata(L, 1)) {
    return luaL_error(L, "Expected window object.");
  }

  WindowWrapper* window = static_cast<WindowWrapper*>(lua_touserdata(L, 1));
  point::Graphics::Initialize(*window->window);
  return 0;
}

int w_GraphicsPushState(lua_State* L) {
  (void)L;
  point::Graphics::PushState();
  return 0;
}

int w_GraphicsPopState(lua_State* L) {
  (void)L;
  point::Graphics::PopState();
  return 0;
}

int w_GraphicsSetColor(lua_State* L) {
  float r = luaL_checknumber(L, 1);
  float g = luaL_checknumber(L, 2);
  float b = luaL_checknumber(L, 3);
  float a = luaL_optnumber(L, 4, 1);
  point::Color color(r, g, b, a);
  point::Graphics::SetColor(color);
  return 0;
}

int w_GraphicsSetBackgroundColor(lua_State* L) {
  float r = luaL_checknumber(L, 1);
  float g = luaL_checknumber(L, 2);
  float b = luaL_checknumber(L, 3);
  float a = luaL_optnumber(L, 4, 1);
  point::Color color(r, g, b, a);
  point::Graphics::SetBackgroundColor(color);
  return 0;
}

int w_GraphicsClear(lua_State* L) {
  (void)L;
  point::Graphics::Clear();
  return 0;
}

int w_GraphicsPresent(lua_State* L) {
  (void)L;
  point::Graphics::Present();
  return 0;
}

luaL_Reg graphicsLib[] = {
  { "Initialize", w_GraphicsInitialize },
  { "PushState", w_GraphicsPushState },
  { "PopState", w_GraphicsPopState },
  { "SetColor", w_GraphicsSetColor },
  { "SetBackgroundColor", w_GraphicsSetBackgroundColor },
  { "Clear", w_GraphicsClear },
  { "Present", w_GraphicsPresent },
  { nullptr, nullptr },
};

int WrapGraphics(lua_State* L) {
  RegisterModule(L, GRAPHICS_NAME, graphicsLib);
  return LUA_OK;
}
