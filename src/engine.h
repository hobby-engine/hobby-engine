#ifndef _HOBBY_ENGINE_H
#define _HOBBY_ENGINE_H

#include "renderer.h"
#include "time.h"

#include "window.h"

struct Engine {
  struct Time* time;
  struct Window* window;
  struct Renderer* renderer;
};

struct Engine createEngine();
void destroyEngine(struct Engine* engine);
void engineStep(struct Engine* engine);

#endif // _HOBBY_ENGINE_H
