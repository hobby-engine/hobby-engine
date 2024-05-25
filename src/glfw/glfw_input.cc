#include "glfw_input.hh"

#include "GLFW/glfw3.h"
#include "common.hh"
#include "engine.hh"
#include "lua_wrapper/wrapper.hh"

static void onKeyPressed(
  GLFWwindow* window, int key, UNUSED int scancode, int action, UNUSED int mode)
{
  GlfwWindow* cWindow = (GlfwWindow*)glfwGetWindowUserPointer(window);

  if (action == GLFW_PRESS || action == GLFW_REPEAT) {
    cWindow->getEngine().luaWrapper->callFunction(
      "onKeyPressed", 2, LuaType::Int, key, LuaType::Boolean,
      (int)action == GLFW_REPEAT);
  } else {
    cWindow->getEngine().luaWrapper->callFunction(
      "onKeyReleased", 1, LuaType::Int, key);
  }
}

GlfwInput::GlfwInput(const GlfwWindow* window) : _window(window)
{
  for (int i = 0; i < (int)Key::Max; i++) {
    state[i] = false;
  }

  glfwSetKeyCallback(window->handle, onKeyPressed);
}

bool GlfwInput::isKeyPressed(Key key)
{
  int state = glfwGetKey(_window->handle, (int)key);
  return state == GLFW_PRESS;
}

bool GlfwInput::isMousePressed(int button)
{
  int state = glfwGetMouseButton(_window->handle, button);
  return state == GLFW_PRESS;
}
