#include "engine.h"

#include "log.h"
#include "GLFW/glfw3.h"

struct hb_Engine hb_createEngine() {
  hb_fatalAssert(glfwInit(), "Failed to initialize GLFW.\n");

  struct hb_Engine engine;
  engine.window = hb_createWindow("Hobby Engine", 800, 600);
  engine.time = hb_createTime();
  engine.renderer = hb_createRenderer(engine.window);

  return engine;
}

void hb_destroyEngine(struct hb_Engine* engine) {
  hb_destroyWindow();
  hb_destroyTime(engine->time);

  glfwTerminate();
}

void hb_engineStep(struct hb_Engine* engine) {
  hb_timeStep(engine->time);
  hb_rendererStep(engine->renderer);
}
