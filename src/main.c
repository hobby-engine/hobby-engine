#include <stdio.h>

#include "engine.h"
#include "basic_types.h"
#include "renderer.h"
#include "time.h"
#include "window.h"

#define WIDTH 800
#define HEIGHT 600

s32 main() {
  hb_Window* window = hb_createWindow("Hobby", WIDTH, HEIGHT);
  hb_Engine engine = hb_createEngine(window);

  while (!glfwWindowShouldClose(window->glfwWindow)) {
    hb_engineStep(&engine);

    glfwPollEvents();

    char title[16];
    sprintf(title, "%.5f", engine.time->fps);
    hb_windowSetTitle(window, title);

    hb_drawClear((hb_Color){0, 0, 0, 1});

    hb_drawSetColor((hb_Color){0, 1, 0, 1});
    hb_drawRectangle(10, 10, 50, 50);
    hb_drawSetColor((hb_Color){1, 0.4, 0.6, 1});
    hb_drawRectangleOutline(10, 10, 50, 50);

    hb_drawPresent();
  }

  hb_destroyEngine(&engine);
  return 0;
}
