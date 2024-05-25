#ifndef _HOBBY_ENGINE_HH
#define _HOBBY_ENGINE_HH

#include "input.hh"
#include "renderer.hh"
#include "time.hh"
#include "window.hh"

struct LuaWrapper;

class Engine
{
public:
  Window* mainWindow;
  Renderer* renderer;
  Input* input;
  Time* time;
  LuaWrapper* luaWrapper;

  Engine(const WindowSettings& windowSettings);
  ~Engine();

  void update();

  bool isRunning()
  {
    return _isRunning;
  }

  void stop()
  {
    _isRunning = false;
  }

private:
  bool _isRunning = true;
};

#endif // _HOBBY_ENGINE_HH
