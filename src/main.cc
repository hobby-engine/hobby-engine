#include <iostream>

#include "engine.hh"
#include "lua_wrapper/wrapper.hh"

int main() {
  WindowSettings windowSettings = WindowSettings();
  windowSettings.title = "Hobby Engine";
  windowSettings.canResize = false;

  Engine engine {windowSettings};
  LuaWrapper wrapper {engine};

  wrapper.callFunction("run");
}
