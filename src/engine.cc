#include "engine.hh"
#include "glfw/glfw_input.hh"
#include "glfw/glfw_window.hh"
#include "lua_wrapper/wrapper.hh"
#include "opengl/gl_renderer.hh"
#include "time.hh"
#include "window.hh"

#if defined(HB_POSIX)
#include <unistd.h>
#elif defined(HB_WINDOWS)
// I HATE WINDOWS SO MUCH
#include <windows.h>
#endif

Engine::Engine(const WindowOptions& winopt)
{
  switch (winopt.backend) {
    case GraphicsBackend::OpenGL:
      GlfwWindow* glfwwin = new GlfwWindow(*this, winopt);

      OpenGlRenderer::initopengl();
      OpenGlRenderer* glrenderer = new OpenGlRenderer(glfwwin);

      GlfwInput* glfwinput = new GlfwInput(glfwwin);

      mainwin = glfwwin;
      renderer = glrenderer;
      input = glfwinput;
      break;
  }

  time = new Time();

  luawrap = new LuaWrapper(*this);
}

Engine::~Engine()
{
  delete mainwin;
  delete renderer;
  delete input;
  delete time;
  delete luawrap;
}

void Engine::update()
{
  // Don't eat up all the system resources for literally no reason.
  if (mainwin->isfocused()) {
    // TODO: Maybe reformat this so that the else clause is in each case?
#if defined(HB_POSIX)
    usleep(1000);
#elif defined(HB_WINDOWS)
    Sleep(1);
#endif
  } else {
#if defined(HB_POSIX)
    usleep(2000);
#elif defined(HB_WINDOWS)
    Sleep(2);
#endif
  }

  // There's nothing left to live for.
  if (mainwin->isclosed()) {
    stop();
  }

  renderer->update();
  time->update();
}
