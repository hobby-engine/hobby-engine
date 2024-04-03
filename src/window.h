#ifndef _HOBBY_WINDOW_H
#define _HOBBY_WINDOW_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "typedefs.h"

struct Window {
  s32 width, height;
  char* title;
  GLFWwindow* glfwWindow;
};

struct Window* createWindow(const char* title, s32 width, s32 height);
void destroyWindow(struct Window* window);
void windowStep(struct Window* window);

void windowSetTitle(struct Window* window, const char* title);
void windowSetSize(struct Window* window, s32 width, s32 height);

#endif // _HOBBY_WINDOW_H
