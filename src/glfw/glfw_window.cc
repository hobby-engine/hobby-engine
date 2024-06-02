#include "glfw_window.hh"

#include "GLFW/glfw3.h"
#include "log.hh"
#include "common.hh"

static void onframebuffersizechanged(
  GLFWwindow* window, UNUSED int width, UNUSED int height)
{
  GlfwWindow* customwin = (GlfwWindow*)glfwGetWindowUserPointer(window);
  customwin->getengine().renderer->resizewindow(customwin);
}

GlfwWindow::GlfwWindow(Engine& engine, const WindowOptions& settings)
    : _engine(engine)
{
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, settings.canresize);

  handle = glfwCreateWindow(
    settings.width, settings.height, settings.title, nullptr, nullptr);
  if (!handle) {
    glfwTerminate();
    Logger::instance()->fatal("Failed to initialize glfw window.");
  }

  glfwMakeContextCurrent(handle);

  glfwSetFramebufferSizeCallback(handle, onframebuffersizechanged);
  glfwSetWindowUserPointer(handle, this);
  glfwSwapInterval(0);
}

GlfwWindow::~GlfwWindow()
{
  glfwDestroyWindow(handle);
}

const char* GlfwWindow::gettitle() const
{
  return glfwGetWindowTitle(handle);
}

void GlfwWindow::settitle(const char* title)
{
  glfwSetWindowTitle(handle, title);
}

void GlfwWindow::getsize(int& w, int& h) const
{
  glfwGetWindowSize(handle, &w, &h);
}

void GlfwWindow::setsize(int w, int h)
{
  glfwSetWindowSize(handle, w, h);
}

bool GlfwWindow::isclosed() const
{
  return glfwWindowShouldClose(handle);
}

void GlfwWindow::close()
{
  glfwSetWindowShouldClose(handle, true);
}

bool GlfwWindow::isfocused() const
{
  return glfwGetWindowAttrib(handle, GLFW_FOCUSED) == 1;
}

void GlfwWindow::present() const
{
  glfwSwapBuffers(handle);
}

void GlfwWindow::makecurrent()
{
  glfwMakeContextCurrent(handle);
}
