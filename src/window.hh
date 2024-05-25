#ifndef _HOBBY_WINDOW_HH
#define _HOBBY_WINDOW_HH

enum class GraphicsBackend
{
  OpenGL,
};

struct WindowSettings
{
  const char* title = nullptr;
  int width = 800, height = 400;
  int x = -1, y = -1;
  bool canResize = true;
  GraphicsBackend backend = GraphicsBackend::OpenGL;
};

class Engine;

class Window
{
public:
  virtual ~Window()
  {
  }

  static Window* create(Engine& engine, WindowSettings& settings);

  virtual const char* getTitle() const = 0;
  virtual void setTitle(const char* title) = 0;
  virtual void getSize(int& w, int& h) const = 0;
  virtual void setSize(int w, int h) = 0;
  virtual bool isClosed() const = 0;
  virtual void close() = 0;
  virtual bool isFocused() const = 0;
  virtual void present() const = 0;
  virtual void setCurrent() = 0;

private:
};

#endif // _HOBBY_WINDOW_HH
