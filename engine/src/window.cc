#include "window.hh"

#include <iostream>

#include "SDL2/SDL_video.h"
#include "glad/glad.h"
#include "SDL2/SDL.h"

#include "event/key.hh"
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

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    exit(1);
  }

  // Create window
  uint32_t flags = 0;
  if (settings.Resizable) {
    flags |= SDL_WINDOW_RESIZABLE;
  }

  _window = SDL_CreateWindow(
    settings.Title,
    settings.X, settings.Y,
    settings.Width, settings.Height,
    flags | SDL_WINDOW_OPENGL);
  if (!_window) {
    std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
    exit(1);
  }

  _context = SDL_GL_CreateContext(_window);
  if (!_context) {
    SDL_DestroyWindow(_window);
    std::cerr << "Could not create context: " << SDL_GetError() << std::endl;
    exit(1);
  }

  SDL_GL_MakeCurrent(_window, _context);

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    SDL_DestroyWindow(_window);
    SDL_GL_DeleteContext(_context);
    std::cerr << "Failed to initialize glad." << std::endl;
    exit(1);
  }
}

const char* Window::GetTitle() const {
  return SDL_GetWindowTitle(_window);
}

void Window::SetTitle(const char* title) {
  SDL_SetWindowTitle(_window, title);
}

Vec2 Window::GetPosition() const {
  int x, y;
  SDL_GetWindowPosition(_window, &x, &y);
  return Vec2(x, y);
}

void Window::SetPosition(const Vec2& position) {
  SDL_SetWindowPosition(_window, position.X, position.Y);
}

Vec2 Window::GetSize() const {
  int w, h;
  SDL_GetWindowSize(_window, &w, &h);
  return Vec2(w, h);
}

void Window::SetSize(const Vec2& size) {
  SDL_SetWindowSize(_window, size.W, size.H);
}

void Window::Update() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        Close();
        break;
      case SDL_KEYDOWN: {
        KeyPressedEvent keyPressedEvent(event.key.type, event.key.repeat);
        KeyPressedEvent::PushEvent(keyPressedEvent);
        break;
      }
      case SDL_KEYUP: {
        KeyReleasedEvent keyReleasedEvent(event.key.type);
        KeyReleasedEvent::PushEvent(keyReleasedEvent);
        break;
      }
    }
  }
}

}
