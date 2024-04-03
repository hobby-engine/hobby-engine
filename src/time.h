#ifndef _HOBBY_TIME_H
#define _HOBBY_TIME_H

#include "typedefs.h"

struct Time {
  f32 deltaTime;
  f32 lastFrameTime;

  f32 fps;
  f32 lastFpsUpdate;
  u32 framesRendered;
};

struct Time* createTime();
void destroyTime(struct Time* time);
void timeStep(struct Time* time);

#endif // _HOBBY_TIME_H
