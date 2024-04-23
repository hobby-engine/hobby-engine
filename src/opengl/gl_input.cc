#include "gl_input.hh"

#include "GLFW/glfw3.h"
#include "common.hh"
#include "engine.hh"
#include "lua_wrapper/wrapper.hh"

static void onKeyPressed(
    GLFWwindow* window, 
    int key, UNUSED int scancode, int action, UNUSED int mode) {
  Engine* engine = (Engine*)glfwGetWindowUserPointer(window);
  engine->input->setKeyPressed((Key)key, action != GLFW_RELEASE);

  if (action == GLFW_PRESS || action == GLFW_REPEAT) {
    engine->luaWrapper->callFunction(
      "onKeyPressed", 2,
      LuaType::Int, key, LuaType::Boolean, (int)action == GLFW_REPEAT);
  } else {
    engine->luaWrapper->callFunction(
      "onKeyReleased", 1,
      LuaType::Int, key);
  }
}

OpenGlInput::OpenGlInput(const OpenGlWindow* window)
    : _window(window) {
  for (int i = 0; i < (int)Key::Max; i++) {
    state[i] = false;
  }

  glfwSetKeyCallback(window->handle, onKeyPressed);
}

void OpenGlInput::setKeyPressed(Key key, bool isPressed) {
  justPressed[(int)key] = isPressed && !state[(int)key];
  state[(int)key] = isPressed;
}

void OpenGlInput::update() {
  for (int i = 0; i < (int)Key::Max; i++) {
    justPressed[i] = false;
  }
}

bool OpenGlInput::isKeyPressed(Key key) {
  int state = glfwGetKey(_window->handle, (int)key);
  return state == GLFW_PRESS;
}

bool OpenGlInput::isMousePressed(int button) {
  int state = glfwGetMouseButton(_window->handle, button);
  return state == GLFW_PRESS;
}
