#include "time.hh"
#include "GLFW/glfw3.h"

#define FPS_UPDATE_FREQ 1

void Time::update()
{
  // TODO: Get rid of this GLFW call somehow.
  double currentTime = glfwGetTime();
  dt = currentTime - _lastFrameTime;
  _lastFrameTime = currentTime;

  totalTime = currentTime;

  _framesRendered++;
  double timeSinceLastUpdate = currentTime - _lastFpsUpdate;
  if (timeSinceLastUpdate > FPS_UPDATE_FREQ) {
    fps = _framesRendered / timeSinceLastUpdate;
    _lastFpsUpdate = currentTime;
    _framesRendered = 0;
  }
}
