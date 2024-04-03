#include <stdlib.h>

#include "lua_wrap/lua_wrapper.h"
#include "engine.h"
#include "typedefs.h"
#include "renderer.h"
#include "window.h"

#define WIDTH 800
#define HEIGHT 600

f32 randf(f32 min, f32 max) {
  f32 r = (f32)(rand() % 1000) / 1000;
  return r * (max - min) + min;
}

s32 main() {
  struct Engine engine = createEngine();

  struct LuaWrapper* wrapper = createLuaWrapper(&engine);

  callLuaCallback(wrapper, "start");

  while (!glfwWindowShouldClose(engine.window->glfwWindow)) {
    engineStep(&engine);

    callLuaCallback(wrapper, "step");

    glfwPollEvents();

    drawClear((struct Color){0, 0, 0, 1});
    drawSetColor(engine.renderer, (struct Color){1, 1, 1, 1});
    callLuaCallback(wrapper, "draw");
    drawPresent(engine.renderer);
  }

  destroyLuaWrapper(wrapper);
  return 0;
}
