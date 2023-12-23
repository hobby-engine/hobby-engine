#include "draw.hh"

#include <SDL2/SDL_video.h>
#include <iostream>
#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace point::draw {

class GraphicsState {
  public:
    GraphicsState(Window& window)
      : CurrentColor(1, 1, 1), 
      BackgroundColor(0, 0, 0),
      _window(window) {
    }
    
    Color CurrentColor;
    Color BackgroundColor;

    inline SDL_Window* GetWindow() {
      return _window.GetWindow();
    }
  private:
    Window& _window;
};

std::vector<GraphicsState> states;

static inline GraphicsState& State() {
  return states.back();
}

void Initialize(Window& window) {
  states = std::vector<GraphicsState>();
  states.reserve(16);

  states.emplace_back(GraphicsState(window));
}

void SetColor(Color color) {
  State().CurrentColor = color;
}

void SetBackgroundColor(Color color) {
  State().BackgroundColor = color;
}

void Clear() {
  Color color = State().BackgroundColor;
  glClearColor(color.R, color.G, color.B, color.A);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Present() {
#ifdef POINT_APPLE
  // Nothing happens on MacOS if this ain't here (docs said so!)
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
#endif

  SDL_GL_SwapWindow(State().GetWindow());
}

} // namespace point::draw
