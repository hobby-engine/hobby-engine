#include "window.hh"

#include <iostream>

#include "vec2.hh"

namespace point {

bool Window::_alreadyInstanced = false;

Window::Window() {
  WindowSettings settings = WindowSettings{};
  InitializeWindow(settings);
}

Window::Window(const WindowSettings& settings) {
  InitializeWindow(settings);
}

Window::~Window() {
  SDL_DestroyWindow(_window);
}


void Window::InitializeWindow(const WindowSettings& settings) {
  // Don't allow more than 1 window.
  if (_alreadyInstanced) {
    std::cerr
      << "Already have an instance of a window! Cannot have more than 1!\n"
      << std::endl;
    exit(1);
  }
  _alreadyInstanced = true;

  // Create window
  uint32_t flags = 0;
  if (settings.resizable) {
    flags |= SDL_WINDOW_RESIZABLE;
  }

  _window = SDL_CreateWindow(
    settings.title,
    settings.x, settings.y,
    settings.width, settings.height,
    flags);
  
  if (!_window) {
    std::cerr << "Could not create window." << std::endl;
    exit(1);
  }
}

const char* Window::GetTitle() const {
  return SDL_GetWindowTitle(_window);
}

void Window::SetTitle(const char* title) {
  SDL_SetWindowTitle(_window, title);
}

Vec2i Window::GetPosition() const {
  int x, y;
  SDL_GetWindowPosition(_window, &x, &y);
  return Vec2i(x, y);
}

void Window::SetPosition(const Vec2i& position) {
  SDL_SetWindowPosition(_window, position.x, position.y);
}

Vec2i Window::GetSize() const {
  int x, y;
  SDL_GetWindowSize(_window, &x, &y);
  return Vec2i(x, y);
}

void Window::SetSize(const Vec2i& size) {
  SDL_SetWindowSize(_window, size.x, size.y);
}

void Window::Update() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        Close();
        break;
    }
  }
}

}
