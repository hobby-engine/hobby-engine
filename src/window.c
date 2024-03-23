#include "window.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

static struct hb_Window* singleton = NULL;

static void onFramebufferSizeChanged(GLFWwindow* window, s32 width, s32 height) {
  glViewport(0, 0, width, height);
  singleton->width = width;
  singleton->height = height;
}

struct hb_Window* hb_createWindow(const char* title, s32 width, s32 height) {
  if (!hb_assert(singleton == NULL, "Cannot make more than one window.")) {
    return NULL;
  }

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

  singleton = window;

  return window;
}

void hb_destroyWindow() {
  glfwDestroyWindow(singleton->glfwWindow);
  free(singleton->title);
}

void hb_windowSetTitle(const char* title) {
  free(singleton->title);
  singleton->title = (char*)malloc((strlen(title) + 1) * sizeof(char));
  strcpy(singleton->title, title);

  glfwSetWindowTitle(singleton->glfwWindow, singleton->title);
}

void hb_windowSetSize(s32 width, s32 height) {
  glfwSetWindowSize(singleton->glfwWindow, width, height);
}
