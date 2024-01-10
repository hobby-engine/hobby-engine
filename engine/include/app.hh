#ifndef _HOBBY_APP_H
#define _HOBBY_APP_H

#include <memory>

#include "window.hh"

namespace Hobby {

class App {
public:
  App();
  App(const WindowSettings& windowSettings);

  void Run();
  
  virtual void Ready() = 0;
  virtual void Step() = 0;
  virtual void Draw() = 0;

  inline Window& GetWindow() {
    return *_window;
  }
  
private:
  void Initialize(const WindowSettings& windowSettings);

  Window* _window;
};

} // namespace Hobby

#endif // _HOBBY_APP_H
