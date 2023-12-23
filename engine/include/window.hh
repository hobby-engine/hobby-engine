#ifndef _POINT_ENGINE_WINDOW_H
#define _POINT_ENGINE_WINDOW_H

#include "SDL2/SDL.h"

#include "vec2.hh"

namespace point {

struct WindowSettings {
  const char* Title = "Point Engine";
  int Width = 800, Height = 400;
  int X = SDL_WINDOWPOS_CENTERED, Y = SDL_WINDOWPOS_CENTERED;
  bool Resizable = true;
};

class Window {
    friend class Graphics;
  public:
    Window(); // Default
    Window(const WindowSettings& settings);
    ~Window();
    
    const char* GetTitle() const;
    void SetTitle(const char* title);
    Vec2 GetPosition() const;
    void SetPosition(const Vec2& position);
    Vec2 GetSize() const;
    void SetSize(const Vec2& size);

    void Update();

    inline bool ShouldClose() const {
      return _shouldClose;
    }
    inline void Close() {
      _shouldClose = true;
    }
  private:
    void InitializeWindow(const WindowSettings& settings);

    SDL_Window* _window;
    SDL_GLContext _context;

    bool _shouldClose = false;
    
    // We don't allow more than one window.
    static bool _alreadyInstanced;
};

} // namespace point

#endif // _POINT_ENGINE_WINDOW_H
