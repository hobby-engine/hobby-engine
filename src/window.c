#include "window.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

static void onFramebufferSizeChanged(hb_UNUSED GLFWwindow* window, s32 width, s32 height) {
  glViewport(0, 0, width, height);
}

struct hb_Window* hb_createWindow(const char* title, s32 width, s32 height) {
  struct hb_Window* window = (struct hb_Window*)malloc(sizeof(struct hb_Window));

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* glfwWindow = glfwCreateWindow(
    width, height, title, NULL, NULL);
  if (!glfwWindow) {
    glfwTerminate();
    hb_fatal("Failed to create window.\n");
  }

  glfwMakeContextCurrent(glfwWindow);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    hb_fatal("Failed to initialize GLAD.\n");
  }

  glfwSetFramebufferSizeCallback(glfwWindow, onFramebufferSizeChanged);
  
  window->glfwWindow = glfwWindow;
  window->width = width;
  window->height = height;
  window->title = (char*)malloc((strlen(title) + 1) * sizeof(char));
  strcpy(window->title, title);

  return window;
}

void hb_destroyWindow(struct hb_Window* window) {
  glfwDestroyWindow(window->glfwWindow);
  free(window->title);
  free(window);
}

void hb_windowStep(struct hb_Window* window) {
  s32 width, height;
  glfwGetWindowSize(window->glfwWindow, &width, &height);

  window->width = width;
  window->height = height;
}

void hb_windowSetTitle(struct hb_Window* window, const char* title) {
  free(window->title);
  window->title = (char*)malloc((strlen(title) + 1) * sizeof(char));
  strcpy(window->title, title);

  glfwSetWindowTitle(window->glfwWindow, window->title);
}

void hb_windowSetSize(struct hb_Window* window, s32 width, s32 height) {
  glfwSetWindowSize(window->glfwWindow, width, height);
}
