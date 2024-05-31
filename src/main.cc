#include "engine.hh"
#include "lua_wrapper/wrapper.hh"

int main()
{
  WindowOptions winopt = WindowOptions();
  winopt.title = "Hobby Engine";
  winopt.canresize = false;

  Engine engine{winopt};

  engine.luawrap->callfunction("run", 0);
}
