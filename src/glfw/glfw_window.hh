#ifndef _HOBBY_OPENGL_WINDOW_HH
#define _HOBBY_OPENGL_WINDOW_HH

#include "glad/glad.h"
#include "engine.hh"
#include "GLFW/glfw3.h"
#include "window.hh"

class GlfwWindow final : public Window
{
public:
  GlfwWindow(Engine& engine, const WindowSettings& settings);
  ~GlfwWindow();

  GLFWwindow* handle;

  const char* getTitle() const override;
  void setTitle(const char* title) override;
  void getSize(int& w, int& h) const override;
  void setSize(int w, int h) override;
  bool isClosed() const override;
  void close() override;
  bool isFocused() const override;
  void present() const override;
  void setCurrent() override;

  inline Engine& getEngine()
  {
    return _engine;
  }

private:
  Engine& _engine;
};

#endif // _HOBBY_OPENGL_WINDOW_HH
