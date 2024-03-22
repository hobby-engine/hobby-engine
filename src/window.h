#ifndef _HOBBY_WINDOW_H
#define _HOBBY_WINDOW_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "basic_types.h"

typedef struct {
  s32 width, height;
  char* title;
  GLFWwindow* glfwWindow;
} hb_Window;

hb_Window* hb_createWindow(const char* title, s32 width, s32 height);
void hb_destroyWindow();

void hb_windowSetTitle(const char* title);
void hb_windowSetSize(s32 width, s32 height);

#endif // _HOBBY_WINDOW_H
