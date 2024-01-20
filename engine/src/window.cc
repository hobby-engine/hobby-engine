#include "window.hh"

#include <stdexcept>

#include "SDL2/SDL.h"

#include "input_types.hh"

namespace Hobby {

Window::Window() {
  // Just use the defaul settings.
  WindowSettings settings;
  Initialize(settings);
}

Window::Window(const WindowSettings& settings)  {
  Initialize(settings);
}

void Window::Initialize(const WindowSettings& settings) {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    throw std::runtime_error(SDL_GetError());
  }

  _windowTitle = settings.Title;

  u32 flags = 0;
  if (settings.Visible) {
    flags |= SDL_WINDOW_SHOWN;
  }

  if (settings.Borderless) {
    flags |= SDL_WINDOW_BORDERLESS;
  }

  if (settings.Resizable) {
    flags |= SDL_WINDOW_RESIZABLE;
  }

  if (settings.Maximized) {
    flags |= SDL_WINDOW_MAXIMIZED;
  }

  if (settings.Minimized) {
    flags |= SDL_WINDOW_MINIMIZED;
  }

  int x = settings.X == -1
    ? SDL_WINDOWPOS_CENTERED
    : settings.X;
  int y = settings.Y == -1
    ? SDL_WINDOWPOS_CENTERED
    : settings.Y;

  _window = SDL_CreateWindow(
    _windowTitle.c_str(),
    x, y,
    settings.Width, settings.Height,
    flags);
  if (_window == nullptr) {
    throw std::runtime_error(SDL_GetError());
  }

  _renderer = SDL_CreateRenderer(
    _window, 0, SDL_RENDERER_ACCELERATED);
  if (_renderer == nullptr) {
    throw std::runtime_error(SDL_GetError());
  }
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

void Window::SetTitle(const std::string& title) {
  _windowTitle = title;
  SDL_SetWindowTitle(_window, _windowTitle.c_str());
}

std::string Window::GetTitle() const {
  return _windowTitle;
}

void Window::SetSize(Vec2 size) {
  SDL_SetWindowSize(_window, size.X, size.Y);
}

Vec2 Window::GetSize() const {
  int w, h;
  SDL_GetWindowSize(_window, &w, &h);
  return Vec2(w, h);
}

bool Window::ShouldClose() const {
  return _shouldClose;
}

void Window::Close() {
  _shouldClose = true;
}

} // namespace Hobby
