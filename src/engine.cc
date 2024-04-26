#include "engine.hh"
#include "opengl/gl_renderer.hh"
#include "glfw/glfw_window.hh"
#include "glfw/glfw_input.hh"
#include "time.hh"
#include "window.hh"
#include "lua_wrapper/wrapper.hh"

Engine::Engine(const WindowSettings& windowSettings) {
  switch (windowSettings.backend) {
    case GraphicsBackend::OpenGL:
      GlfwWindow* glfwWindow = new GlfwWindow(windowSettings);
      OpenGlRenderer* openGlRenderer = new OpenGlRenderer(glfwWindow);
      GlfwInput* glfwInput = new GlfwInput(glfwWindow);

      glfwSetWindowUserPointer(glfwWindow->handle, this);

      window = glfwWindow;
      renderer = openGlRenderer;
      input = glfwInput;
      break;
  }

  time = new Time();

  luaWrapper = new LuaWrapper(*this);
}

Engine::~Engine() {
  delete window;
  delete renderer;
  delete input;
  delete time;
  delete luaWrapper;
}

void Engine::update() {
  renderer->update();
  time->update();
}
