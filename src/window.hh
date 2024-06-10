#ifndef _HOBBY_WINDOW_HH
#define _HOBBY_WINDOW_HH

enum class GraphicsBackend
{
  OpenGL,
};

struct WindowOptions
{
  const char* title = nullptr;
  int width = 800, height = 400;
  int x = -1, y = -1;
  bool canresize = true;
  GraphicsBackend backend = GraphicsBackend::OpenGL;
};

class Engine;

class Window
{
public:
  virtual ~Window();

  static Window* create(Engine& engine, WindowOptions& winopt);

  virtual const char* gettitle() const = 0;
  virtual void settitle(const char* title) = 0;
  virtual void getsize(int& w, int& h) const = 0;
  virtual void setsize(int w, int h) = 0;
  virtual bool isclosed() const = 0;
  virtual void close() = 0;
  virtual bool isfocused() const = 0;
  virtual void present() const = 0;
  virtual void makecurrent() = 0;

private:
};

#endif // _HOBBY_WINDOW_HH
