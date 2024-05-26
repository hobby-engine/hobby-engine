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

Engine::Engine(const WindowSettings& windowSettings)
{
  switch (windowSettings.backend) {
    case GraphicsBackend::OpenGL:
      GlfwWindow* glfwWindow = new GlfwWindow(*this, windowSettings);

      OpenGlRenderer::initOpenGl();
      OpenGlRenderer* openGlRenderer = new OpenGlRenderer(glfwWindow);

      GlfwInput* glfwInput = new GlfwInput(glfwWindow);

      mainWindow = glfwWindow;
      renderer = openGlRenderer;
      input = glfwInput;
      break;
  }

  time = new Time();

  luaWrapper = new LuaWrapper(*this);
}

Engine::~Engine()
{
  delete mainWindow;
  delete renderer;
  delete input;
  delete time;
  delete luaWrapper;
}

void Engine::update()
{
  // Don't eat up all the system resources for literally no reason.
  if (mainWindow->isFocused()) {
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
  if (mainWindow->isClosed()) {
    stop();
  }

  renderer->update();
  time->update();
}
