#include "gl_window.hh"

#include "GLFW/glfw3.h"
#include "log.hh"

static void onFramebufferSizeChanged(GLFWwindow* window, int width, int height) {
  glfwMakeContextCurrent(window);
  glViewport(0, 0, width, height);
}

OpenGlWindow::OpenGlWindow(const WindowSettings& settings) {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, settings.canResize);

  handle = glfwCreateWindow(
    settings.width, settings.height,
    settings.title,
    nullptr, nullptr);
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

OpenGlWindow::~OpenGlWindow() {
  glfwDestroyWindow(handle);
}

const char* OpenGlWindow::getTitle() const {
  return glfwGetWindowTitle(handle);
}

void OpenGlWindow::setTitle(const char* title) {
  glfwSetWindowTitle(handle, title);
}

void OpenGlWindow::getSize(int& w, int& h) const {
  glfwGetWindowSize(handle, &w, &h);
}

void OpenGlWindow::setSize(int w, int h) {
  glfwSetWindowSize(handle, w, h);
}

bool OpenGlWindow::isClosed() const {
  return glfwWindowShouldClose(handle);
}

void OpenGlWindow::present() const {
  glfwSwapBuffers(handle);
}
