#include "draw.hh"

#include <iostream>
#include <stdexcept>
#include <vector>

#include "glad/glad.h"
#include "SDL2/SDL.h"

namespace point {

Graphics* Graphics::Current = nullptr;

Graphics::Graphics(Window& window)
    : _window(window._window) {
  _enclosing = Current;
  Current = this;
}

Graphics::Graphics() {
  if (Current == nullptr) {
    throw std::runtime_error("There is no initial state. Please pass your window.");
  }

  _enclosing = Current;
  _window = _enclosing->_window;
  
  Current = this;
}

void Graphics::SetColor(Color color) {
  Current->_currentColor = color; 
}

void Graphics::SetBackgroundColor(Color color) {
  Current->_backgroundColor = color; 
}

void Graphics::Pop() {
  if (Current->_enclosing == nullptr) {
    throw std::runtime_error("Invalid pop. Please add a corresponding graphics state.");
  }
  Current = Current->_enclosing;
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

} // namespace point
