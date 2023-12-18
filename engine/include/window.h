#ifndef _POINT_ENGINE_WINDOW_H
#define _POINT_ENGINE_WINDOW_H

#include "SDL2/SDL.h"

#include "vec2.h"

namespace point {

struct WindowSettings {
  const char* title = "Point Engine";
  int width = 800, height = 400;
  int x = SDL_WINDOWPOS_CENTERED, y = SDL_WINDOWPOS_CENTERED;
  bool resizable = true;
};

class Window {
  public:
    Window(); // Default
    Window(const WindowSettings& settings);
    ~Window();
    
    const char* GetTitle() const;
    void SetTitle(const char* title);
    Vec2i GetPosition() const;
    void SetPosition(const Vec2i& position);
    Vec2i GetSize() const;
    void SetSize(const Vec2i& size);

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
    SDL_GLContext* _context;

    bool _shouldClose = false;
    
    // We don't allow more than one window.
    static bool _alreadyInstanced;
};

} // namespace point

#endif // _POINT_ENGINE_WINDOW_H
