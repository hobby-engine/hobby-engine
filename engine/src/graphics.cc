#include "graphics.hh"

#include <iostream>
#include <stdexcept>
#include <vector>

#include "glad/glad.h"
#include "SDL2/SDL.h"

namespace Hobby {

Graphics* Graphics::Current = nullptr;

void Graphics::Initialize(Window& window) {
  if (Current != nullptr) {
    throw std::runtime_error("Graphics state already initialized.");
  }

  auto newState = new Graphics();
  newState->_window = window._window;
  Current = newState;
}

void Graphics::PushState() {
  if (Current == nullptr) {
    throw std::runtime_error("Graphics state not initialized.");
  }

  auto newState = new Graphics();
  newState->_enclosing = Current;
  newState->_window = Current->_window;
  Current = newState;
}

void Graphics::PopState() {
  if (Current->_enclosing == nullptr) {
    throw std::runtime_error("Invalid pop. Please add a corresponding push call.");
  }

  Graphics* previous = Current;
  Current = Current->_enclosing;

  delete previous;
}

void Graphics::SetColor(Color color) {
  Current->_currentColor = color; 
}

void Graphics::SetBackgroundColor(Color color) {
  Current->_backgroundColor = color; 
}

void Graphics::Clear() {
  Color color = Current->_backgroundColor;
  glClearColor(color.R, color.G, color.B, color.A);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::Present() {
#ifdef POINT_APPLE
  // Nothing happens on MacOS if this ain't here (docs said so!)
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
#endif

  SDL_GL_SwapWindow(Current->_window);
}

} // namespace Hobby
