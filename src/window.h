#ifndef _HOBBY_WINDOW_H
#define _HOBBY_WINDOW_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "typedefs.h"

struct hb_Window {
  s32 width, height;
  char* title;
  GLFWwindow* glfwWindow;
};

struct hb_Window* hb_createWindow(const char* title, s32 width, s32 height);
void hb_destroyWindow(struct hb_Window* window);
void hb_windowStep(struct hb_Window* window);

void hb_windowSetTitle(struct hb_Window* window, const char* title);
void hb_windowSetSize(struct hb_Window* window, s32 width, s32 height);

#endif // _HOBBY_WINDOW_H
