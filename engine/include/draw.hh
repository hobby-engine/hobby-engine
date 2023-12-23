#ifndef _POINT_DRAW_H
#define _POINT_DRAW_H

#include "color.hh"
#include "window.hh"

namespace point {

class Graphics {
    friend class Graphics;
  public:
    Graphics(Window& window);
    Graphics();

    static void SetColor(Color color);
    static void SetBackgroundColor(Color color);
    static void Clear();
    static void Present();
    static void Pop();
    
  private:
    static Graphics* Current;
    Graphics* _enclosing = nullptr;
    
    Color _currentColor = Color(1, 1, 1);
    Color _backgroundColor = Color(0, 0, 0);

    SDL_Window* _window;
};

} // namespace point

#endif
