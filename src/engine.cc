#include "engine.hh"
#include "opengl/gl_renderer.hh"
#include "opengl/gl_window.hh"
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
}

Engine::~Engine() {
  delete window;
  delete renderer;
}

void Engine::update() {
  renderer->update();
}
