#ifndef _POINT_ENGINE_WINDOW_H
#define _POINT_ENGINE_WINDOW_H

#include "SDL2/SDL.h"

#include "vec2.hh"

namespace point {

struct WindowSettings {
  const char* title = "Point Engine";
  int width = 800, height = 400;
  int x = SDL_WINDOWPOS_CENTERED, y = SDL_WINDOWPOS_CENTERED;
  bool resizable = true;
};

class Window {
    friend class GraphicsState;
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
    inline SDL_Window* GetWindow() const {
      return _window;
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
