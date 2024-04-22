#include "engine.hh"
#include "opengl/gl_renderer.hh"
#include "opengl/gl_window.hh"
#include "opengl/gl_input.hh"
#include "time.hh"
#include "window.hh"
#include "lua_wrapper/wrapper.hh"

Engine::Engine(const WindowSettings& windowSettings) {
  switch (windowSettings.backend) {
    case GraphicsBackend::OpenGL:
      OpenGlWindow* openGlWindow = new OpenGlWindow(windowSettings);
      OpenGlRenderer* openGlRenderer = new OpenGlRenderer(openGlWindow);
      OpenGlInput* openGlInput = new OpenGlInput(openGlWindow);

      glfwSetWindowUserPointer(openGlWindow->handle, this);

      window = openGlWindow;
      renderer = openGlRenderer;
      input = openGlInput;
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
