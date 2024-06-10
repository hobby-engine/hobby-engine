#include "window.hh"
#include "glfw/glfw_window.hh"

Window::~Window()
{
}

Window* Window::create(Engine& engine, WindowOptions& winopt)
{
  switch (winopt.backend) {
    case GraphicsBackend::OpenGL:
      return new GlfwWindow(engine, winopt);
  }

  // Unreachable.
  return nullptr;
}
