#ifndef _HOBBY_OPENGL_INPUT_HH
#define _HOBBY_OPENGL_INPUT_HH

#include "glfw_window.hh"
#include "input.hh"

class GlfwInput final : public Input
{
public:
  GlfwInput(const GlfwWindow* window);

  bool iskeydown(Key key) override;
  bool ismousedown(int button) override;

private:
  const GlfwWindow* _window;
};

#endif // _HOBBY_OPENGL_INPUT_HH
