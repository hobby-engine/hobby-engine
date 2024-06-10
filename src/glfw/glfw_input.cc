#include "glfw_input.hh"

#include "GLFW/glfw3.h"
#include "common.hh"
#include "engine.hh"
#include "lua_wrapper/wrapper.hh"

static void onkeypressed(
  GLFWwindow* window, int key, UNUSED int scancode, int action, UNUSED int mode)
{
  GlfwWindow* customwin = (GlfwWindow*)glfwGetWindowUserPointer(window);

  if (action == GLFW_PRESS || action == GLFW_REPEAT) {
    customwin->getengine().luawrap->callfunction(
      "onkeypressed", 2, LuaType::Int, key, LuaType::Boolean,
      (int)action == GLFW_REPEAT);
  } else {
    customwin->getengine().luawrap->callfunction(
      "onkeyreleased", 1, LuaType::Int, key);
  }
}

GlfwInput::GlfwInput(const GlfwWindow* window) : _window(window)
{
  glfwSetKeyCallback(_window->gethandle(), onkeypressed);
}

bool GlfwInput::iskeydown(Key key)
{
  int state = glfwGetKey(_window->gethandle(), (int)key);
  return state == GLFW_PRESS;
}

bool GlfwInput::ismousedown(int button)
{
  int state = glfwGetMouseButton(_window->gethandle(), button);
  return state == GLFW_PRESS;
}
