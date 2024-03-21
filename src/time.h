#ifndef _HOBBY_TIME_H
#define _HOBBY_TIME_H

#include "basic_types.h"

typedef struct {
  f32 deltaTime;
  f32 lastFrameTime;

  f32 fps;
  f32 lastFpsUpdate;
  u32 framesRendered;
} hb_Time;

hb_Time* hb_createTime();
void hb_destroyTime(hb_Time* time);
void hb_timeStep(hb_Time* time);

#endif // _HOBBY_TIME_H
