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
    return m_isrunning;
  }

  void stop()
  {
    m_isrunning = false;
  }

private:
  bool m_isrunning = true;
};

#endif // _HOBBY_ENGINE_HH
