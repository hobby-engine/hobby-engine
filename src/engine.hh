#ifndef _HOBBY_ENGINE_HH
#define _HOBBY_ENGINE_HH

#include "renderer.hh"
#include "time.hh"
#include "window.hh"

class Engine {
  public:
    Window* window;
    Renderer* renderer;
    Time* time;

    Engine(const WindowSettings& windowSettings);
    ~Engine();

    void update();
  private:
};

#endif // _HOBBY_ENGINE_HH