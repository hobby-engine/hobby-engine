#ifndef _HOBBY_OPENGL_INPUT_HH
#define _HOBBY_OPENGL_INPUT_HH

#include "glfw_window.hh"
#include "input.hh"

class GlfwInput final : public Input
{
public:
  GlfwInput(const GlfwWindow* window);

  bool isKeyPressed(Key key) override;
  bool isMousePressed(int button) override;

private:
  const GlfwWindow* _window;
  bool state[(int)Key::Max];
  bool justPressed[(int)Key::Max];
};

#endif // _HOBBY_OPENGL_INPUT_HH
