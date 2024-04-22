#ifndef _HOBBY_OPENGL_INPUT_HH
#define _HOBBY_OPENGL_INPUT_HH

#include "input.hh"
#include "gl_window.hh"

class OpenGlInput final : public Input {
  public:
    OpenGlInput(const OpenGlWindow* window)
      : _window(window) {
    }

    bool isKeyPressed(Key key) override;
    bool isMousePressed(int button) override;
  private:
    const OpenGlWindow* _window;
};

#endif // _HOBBY_OPENGL_INPUT_HH
