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
  Window* mainwin;
  Renderer* renderer;
  Input* input;
  Time* time;
  LuaWrapper* luawrap;

  Engine(const WindowOptions& winopt);
  ~Engine();

  void update();

  bool isrunning()
  {
    return _isrunning;
  }

  void stop()
  {
    _isrunning = false;
  }

private:
  bool _isrunning = true;
};

#endif // _HOBBY_ENGINE_HH
