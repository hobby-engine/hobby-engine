#include "window.h"

#include <stdlib.h>
#include <string.h>

#include "log.h"

static hb_Window* singleton = NULL;

static void onFramebufferSizeChanged(GLFWwindow* window, s32 width, s32 height) {
  glViewport(0, 0, width, height);
  singleton->width = width;
  singleton->height = height;
}

hb_Window* hb_createWindow(const char* title, s32 width, s32 height) {
  hb_Window* window = (hb_Window*)malloc(sizeof(hb_Window));

  window->glfwWindow = NULL;
  window->width = width;
  window->height = height;
  window->title = (char*)malloc((strlen(title) + 1) * sizeof(char));
  strcpy(window->title, title);

  singleton = window;

  return window;
}

void hb_setupWindow(hb_Window* window) {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* glfwWindow = glfwCreateWindow(
    window->width, window->height, window->title, NULL, NULL);
  if (!glfwWindow) {
    glfwTerminate();
    hb_error("Failed to create window.\n");
  }

  glfwMakeContextCurrent(glfwWindow);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    hb_error("Failed to initialize GLAD.\n");
  }

  glfwSetFramebufferSizeCallback(glfwWindow, onFramebufferSizeChanged);
  
  window->glfwWindow = glfwWindow;
}

void hb_destroyWindow(hb_Window* window) {
  glfwDestroyWindow(window->glfwWindow);
  free(window->title);
}

void hb_windowSetTitle(hb_Window* window, const char* title) {
  free(window->title);
  window->title = (char*)malloc((strlen(title) + 1) * sizeof(char));
  strcpy(window->title, title);

  glfwSetWindowTitle(window->glfwWindow, window->title);
}
