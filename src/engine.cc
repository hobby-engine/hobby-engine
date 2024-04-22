#include "engine.hh"
#include "opengl/gl_renderer.hh"
#include "opengl/gl_window.hh"
#include "time.hh"
#include "window.hh"

Engine::Engine(const WindowSettings& windowSettings) {
  switch (windowSettings.backend) {
    case GraphicsBackend::OpenGL:
      OpenGlWindow* openGlWindow = new OpenGlWindow(windowSettings);
      OpenGlRenderer* openGlRenderer = new OpenGlRenderer(openGlWindow);
      window = openGlWindow;
      renderer = openGlRenderer;
      break;
  }

  time = new Time();
}

Engine::~Engine() {
  delete window;
  delete renderer;
  delete time;
}

void Engine::update() {
  renderer->update();
  time->update();
}
