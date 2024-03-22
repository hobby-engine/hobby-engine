#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265358979323846

#include "engine.h"
#include "basic_types.h"
#include "renderer.h"
#include "texture.h"
#include "time.h"
#include "window.h"

#define WIDTH 800
#define HEIGHT 600

f32 randf(f32 min, f32 max) {
  f32 r = (f32)(rand() % 1000) / 1000;
  return r * (max - min) + min;
}

s32 main() {
  srand(time(NULL));

  hb_Engine engine = hb_createEngine();
  hb_windowSetSize(500, 500);

  hb_Texture texture = hb_createTexture("res/test_img.png");

  while (!glfwWindowShouldClose(engine.window->glfwWindow)) {
    hb_engineStep(&engine);

    printf("%d\n", engine.renderer->drawCalls);

    glfwPollEvents();

    char title[16];
    sprintf(title, "%.5f", engine.time->fps);
    hb_windowSetTitle(title);

    hb_drawClear((hb_Color){0, 0, 0, 1});

    hb_drawSetColor((hb_Color){0, 1, 0, 1});

    f32 w = 50, h = 50;

    s32 i = 0;
    for (f32 x = 0; x < 10; x++) {
      for (f32 y = 0; y < 10; y++) {
        f32 dx = x * (w + 10) + 10;
        f32 dy = y * (h + 10) + 10;
        srand(i);
        hb_drawSetColor(
          (hb_Color){randf(0, 1), randf(0, 1), randf(0, 1), 1});
        hb_drawRectangle(dx, dy, w, h);

        i++;
      }
    }

    hb_drawTexture(&texture, 200, 200, PI / 4, 0.25, 0.25);

    hb_drawPresent();
  }

  hb_destroyEngine(&engine);
  return 0;
}
