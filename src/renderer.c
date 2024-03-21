#include "renderer.h"

hb_Renderer hb_createRenderer(hb_Window* window) {
  hb_Renderer renderer;
  renderer.window = window;

  return renderer;
}
