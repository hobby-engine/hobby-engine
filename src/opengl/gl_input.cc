#include "gl_input.hh"

bool OpenGlInput::isKeyPressed(Key key) {
  int state = glfwGetKey(_window->handle, (int)key);
  return state == GLFW_PRESS;
}

bool OpenGlInput::isMousePressed(int button) {
  int state = glfwGetMouseButton(_window->handle, button);
  return state == GLFW_PRESS;
}
