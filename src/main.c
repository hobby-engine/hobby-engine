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
  struct hb_Engine engine = hb_createEngine();

  struct hb_LuaWrapper* wrapper = hb_createLuaWrapper(&engine);

  hb_callLuaCallback(wrapper, "start");

  while (!glfwWindowShouldClose(engine.window->glfwWindow)) {
    hb_engineStep(&engine);

    hb_callLuaCallback(wrapper, "step");

    glfwPollEvents();

    hb_drawClear((struct hb_Color){0, 0, 0, 1});
    hb_drawSetColor(engine.renderer, (struct hb_Color){1, 1, 1, 1});
    hb_callLuaCallback(wrapper, "draw");
    hb_drawPresent(engine.renderer);
  }

  hb_destroyLuaWrapper(wrapper);
  return 0;
}
