#include "glfw_window.hh"

#include "GLFW/glfw3.h"
#include "log.hh"

static void onFramebufferSizeChanged(GLFWwindow* window, int width, int height)
{
  glfwMakeContextCurrent(window);
  // TODO: Get rid of this
  glViewport(0, 0, width, height);
}

GlfwWindow::GlfwWindow(const WindowSettings& settings)
{
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, settings.canResize);

  handle = glfwCreateWindow(
    settings.width, settings.height, settings.title, nullptr, nullptr);
  if (!handle) {
    glfwTerminate();
    fatal("Failed to initialize glfw window.");
  }

  glfwMakeContextCurrent(handle);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    fatal("Failed to initialize glad.");
  }

  glfwSetFramebufferSizeCallback(handle, onFramebufferSizeChanged);
}

GlfwWindow::~GlfwWindow()
{
  glfwDestroyWindow(handle);
}

const char* GlfwWindow::getTitle() const
{
  return glfwGetWindowTitle(handle);
}

void GlfwWindow::setTitle(const char* title)
{
  glfwSetWindowTitle(handle, title);
}

void GlfwWindow::getSize(int& w, int& h) const
{
  glfwGetWindowSize(handle, &w, &h);
}

void GlfwWindow::setSize(int w, int h)
{
  glfwSetWindowSize(handle, w, h);
}

bool GlfwWindow::isClosed() const
{
  return glfwWindowShouldClose(handle);
}

void GlfwWindow::present() const
{
  glfwSwapBuffers(handle);
}
