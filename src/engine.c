#include "engine.h"

#include "log.h"
#include "glfw/glfw3.h"

hb_Engine hb_createEngine(hb_Window *window) {
  hb_assert(glfwInit(), "Failed to initialize GLFW.\n");
  hb_setupWindow(window);

  hb_Engine engine;
  engine.window = window;
  engine.time = hb_createTime();
  engine.renderer = hb_createRenderer(window);

  return engine;
}

void hb_destroyEngine(hb_Engine* engine) {
  hb_destroyWindow(engine->window);
  hb_destroyTime(engine->time);

  glfwTerminate();
}

void hb_engineStep(hb_Engine* engine) {
  hb_timeStep(engine->time);
  hb_rendererStep(engine->renderer);
}
