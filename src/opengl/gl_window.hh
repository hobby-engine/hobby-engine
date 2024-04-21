#ifndef _HOBBY_OPENGL_WINDOW_HH
#define _HOBBY_OPENGL_WINDOW_HH

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "window.hh"

class OpenGlWindow final : public Window {
  public:
    OpenGlWindow(const WindowSettings& settings);
    ~OpenGlWindow();

    GLFWwindow* handle;

    const char* getTitle() const override;
    void setTitle(const char* title) override;
    void getSize(int& w, int& h) const override;
    void setSize(int w, int h) override;
    bool isClosed() const override;
    void present() const override;

  private:
};

#endif // _HOBBY_OPENGL_WINDOW_HH
