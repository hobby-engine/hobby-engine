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
    : m_engine(engine)
{
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, settings.canresize);

  m_handle = glfwCreateWindow(
    settings.width, settings.height, settings.title, nullptr, nullptr);
  if (!m_handle) {
    glfwTerminate();
    Logger::instance()->fatal("Failed to initialize glfw window.");
  }

  glfwMakeContextCurrent(m_handle);

  glfwSetFramebufferSizeCallback(m_handle, onframebuffersizechanged);
  glfwSetWindowUserPointer(m_handle, this);
  glfwSwapInterval(0);
}

GlfwWindow::~GlfwWindow()
{
  glfwDestroyWindow(m_handle);
}

const char* GlfwWindow::gettitle() const
{
  return glfwGetWindowTitle(m_handle);
}

void GlfwWindow::settitle(const char* title)
{
  glfwSetWindowTitle(m_handle, title);
}

void GlfwWindow::getsize(int& w, int& h) const
{
  glfwGetWindowSize(m_handle, &w, &h);
}

void GlfwWindow::setsize(int w, int h)
{
  glfwSetWindowSize(m_handle, w, h);
}

bool GlfwWindow::isclosed() const
{
  return glfwWindowShouldClose(m_handle);
}

void GlfwWindow::close()
{
  glfwSetWindowShouldClose(m_handle, true);
}

bool GlfwWindow::isfocused() const
{
  return glfwGetWindowAttrib(m_handle, GLFW_FOCUSED) == 1;
}

void GlfwWindow::present() const
{
  glfwSwapBuffers(m_handle);
}

void GlfwWindow::makecurrent()
{
  glfwMakeContextCurrent(m_handle);
}
