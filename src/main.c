#include <stdlib.h>

#include "lua_wrap/lua_wrapper.h"
#include "engine.h"
#include "basic_types.h"
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
  hb_windowSetSize(500, 500);

  struct hb_LuaWrapper* wrapper = hb_createLuaWrapper(&engine);

  hb_callLuaCallback(wrapper, "start");

  glfwSwapInterval(0);

  while (!glfwWindowShouldClose(engine.window->glfwWindow)) {
    hb_engineStep(&engine);

    hb_callLuaCallback(wrapper, "step");

    glfwPollEvents();

    hb_drawClear((struct hb_Color){0, 0, 0, 1});
    hb_drawSetColor((struct hb_Color){1, 1, 1, 1});
    hb_callLuaCallback(wrapper, "draw");
    hb_drawPresent();
  }

  hb_destroyEngine(&engine);
  hb_destroyLuaWrapper(wrapper);
  return 0;
}
