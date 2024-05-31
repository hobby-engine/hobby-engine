#ifndef _HOBBY_OPENGL_WINDOW_HH
#define _HOBBY_OPENGL_WINDOW_HH

#include "engine.hh"
#include "GLFW/glfw3.h"
#include "window.hh"

class GlfwWindow final : public Window
{
public:
  GlfwWindow(Engine& engine, const WindowOptions& settings);
  ~GlfwWindow();

  GLFWwindow* handle;

  const char* gettitle() const override;
  void settitle(const char* title) override;
  void getsize(int& w, int& h) const override;
  void setsize(int w, int h) override;
  bool isclosed() const override;
  void close() override;
  bool isfocused() const override;
  void present() const override;
  void makecurrent() override;

  inline Engine& getengine()
  {
    return _engine;
  }

private:
  Engine& _engine;
};

#endif // _HOBBY_OPENGL_WINDOW_HH
