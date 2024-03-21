#ifndef _HOBBY_WINDOW_H
#define _HOBBY_WINDOW_H

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "basic_types.h"

typedef struct {
  s32 width, height;
  char* title;
  GLFWwindow* glfwWindow;
} hb_Window;

hb_Window* hb_createWindow(const char* title, s32 width, s32 height);
void hb_setupWindow(hb_Window* window);
void hb_destroyWindow(hb_Window* window);

void hb_windowSetTitle(hb_Window* window, const char* title);

#endif // _HOBBY_WINDOW_H
