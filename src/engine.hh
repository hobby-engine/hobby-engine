#ifndef _HOBBY_ENGINE_HH
#define _HOBBY_ENGINE_HH

#include "input.hh"
#include "renderer.hh"
#include "time.hh"
#include "window.hh"

struct LuaWrapper;

class Engine {
  public:
    Window* window;
    Renderer* renderer;
    Input* input;
    Time* time;
    LuaWrapper* luaWrapper;

    Engine(const WindowSettings& windowSettings);
    ~Engine();

    void update();
  private:
};

#endif // _HOBBY_ENGINE_HH
