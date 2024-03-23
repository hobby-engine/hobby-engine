#ifndef _HOBBY_ENGINE_H
#define _HOBBY_ENGINE_H

#include "renderer.h"
#include "time.h"

#include "window.h"

struct hb_Engine {
  struct hb_Time* time;
  struct hb_Window* window;
  struct hb_Renderer* renderer;
};

struct hb_Engine hb_createEngine();
void hb_destroyEngine(struct hb_Engine* engine);
void hb_engineStep(struct hb_Engine* engine);

#endif // _HOBBY_ENGINE_H
