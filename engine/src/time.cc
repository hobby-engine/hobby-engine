#include "time.hh"

#include "SDL2/SDL.h"

namespace Hobby::Time {

double CurrentTime = SDL_GetPerformanceCounter();
double DeltaTime = 0;

void Step() {
  double last = CurrentTime;
  CurrentTime = SDL_GetPerformanceCounter();

  DeltaTime = (CurrentTime - last) / (double)SDL_GetPerformanceFrequency();
}

double GetDelta() {
  return DeltaTime;
}

} // namespace Hobby::Time
