#include "time.hh"
#include "GLFW/glfw3.h"

#define FPS_UPDATE_FREQ 1

void Time::update()
{
  // TODO: Get rid of this GLFW call somehow.
  double currenttime = glfwGetTime();
  dt = currenttime - _lastframe;
  _lastframe = currenttime;

  total = currenttime;

  _framesrendered++;
  double lastupdate = currenttime - _lastfps;
  if (lastupdate > FPS_UPDATE_FREQ) {
    fps = _framesrendered / lastupdate;
    _lastfps = currenttime;
    _framesrendered = 0;
  }
}
