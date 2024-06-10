#include "time.hh"
#include "GLFW/glfw3.h"

#define FPS_UPDATE_FREQ 1

void Time::update()
{
  // TODO: Get rid of this GLFW call somehow.
  double currenttime = glfwGetTime();
  m_dt = currenttime - m_lastframe;
  m_lastframe = currenttime;

  m_total = currenttime;

  m_framesrendered++;
  double lastupdate = currenttime - m_lastfps;
  if (lastupdate > FPS_UPDATE_FREQ) {
    m_fps = m_framesrendered / lastupdate;
    m_lastfps = currenttime;
    m_framesrendered = 0;
  }
}
