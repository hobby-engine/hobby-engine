#ifndef _HOBBY_ENGINE_H
#define _HOBBY_ENGINE_H

#include "renderer.h"
#include "time.h"

#include "window.h"

typedef struct {
  hb_Time* time;
  hb_Window* window;
  hb_Renderer* renderer;
} hb_Engine;

hb_Engine hb_createEngine();
void hb_destroyEngine(hb_Engine* engine);
void hb_engineStep(hb_Engine* engine);

#endif // _HOBBY_ENGINE_H
