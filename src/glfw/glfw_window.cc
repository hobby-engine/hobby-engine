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

  _handle = glfwCreateWindow(
    settings.width, settings.height, settings.title, nullptr, nullptr);
  if (!_handle) {
    glfwTerminate();
    Logger::instance()->fatal("Failed to initialize glfw window.");
  }

  glfwMakeContextCurrent(_handle);

  glfwSetFramebufferSizeCallback(_handle, onframebuffersizechanged);
  glfwSetWindowUserPointer(_handle, this);
  glfwSwapInterval(0);
}

GlfwWindow::~GlfwWindow()
{
  glfwDestroyWindow(_handle);
}

const char* GlfwWindow::gettitle() const
{
  return glfwGetWindowTitle(_handle);
}

void GlfwWindow::settitle(const char* title)
{
  glfwSetWindowTitle(_handle, title);
}

void GlfwWindow::getsize(int& w, int& h) const
{
  glfwGetWindowSize(_handle, &w, &h);
}

void GlfwWindow::setsize(int w, int h)
{
  glfwSetWindowSize(_handle, w, h);
}

bool GlfwWindow::isclosed() const
{
  return glfwWindowShouldClose(_handle);
}

void GlfwWindow::close()
{
  glfwSetWindowShouldClose(_handle, true);
}

bool GlfwWindow::isfocused() const
{
  return glfwGetWindowAttrib(_handle, GLFW_FOCUSED) == 1;
}

void GlfwWindow::present() const
{
  glfwSwapBuffers(_handle);
}

void GlfwWindow::makecurrent()
{
  glfwMakeContextCurrent(_handle);
}
