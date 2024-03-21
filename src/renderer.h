#ifndef _HOBBY_RENDERER_H
#define _HOBBY_RENDERER_H

#include "window.h"

typedef struct {
  hb_Window* window;
} hb_Renderer;

hb_Renderer hb_createRenderer(hb_Window* window);

#endif // _HOBBY_RENDERER_H
