#include "window.hh"
#include "glfw/glfw_window.hh"

Window* Window::create(Engine& engine, WindowSettings& settings)
{
  switch (settings.backend) {
    case GraphicsBackend::OpenGL:
      return new GlfwWindow(engine, settings);
  }
}
