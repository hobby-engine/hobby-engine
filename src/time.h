#ifndef _HOBBY_TIME_H
#define _HOBBY_TIME_H

#include "typedefs.h"

struct hb_Time {
  f32 deltaTime;
  f32 lastFrameTime;

  f32 fps;
  f32 lastFpsUpdate;
  u32 framesRendered;
};

struct hb_Time* hb_createTime();
void hb_destroyTime(struct hb_Time* time);
void hb_timeStep(struct hb_Time* time);

#endif // _HOBBY_TIME_H
