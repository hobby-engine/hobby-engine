#include "engine.h"

#include "log.h"
#include "GLFW/glfw3.h"

struct Engine createEngine() {
  fatalAssert(glfwInit(), "Failed to initialize GLFW.\n");

  struct Engine engine;
  engine.window = createWindow("Hobby Engine", 800, 600);
  engine.time = createTime();
  engine.renderer = createRenderer(engine.window);

  return engine;
}

void destroyEngine(struct Engine* engine) {
  destroyWindow(engine->window);
  destroyTime(engine->time);
  free(engine->renderer);

  glfwTerminate();
}

void engineStep(struct Engine* engine) {
  windowStep(engine->window);
  timeStep(engine->time);
  rendererStep(engine->renderer);
}
