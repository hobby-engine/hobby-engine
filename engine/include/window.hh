#ifndef _HOBBY_WINDOW_H
#define _HOBBY_WINDOW_H

#include "vec2.hh"
#include <string>

struct SDL_Window;
struct SDL_Renderer;

namespace Hobby {

namespace Draw {

struct DrawState;

}

struct WindowSettings {
  std::string Title = "Hobby Engine";
  int X = -1, Y = -1;
  int Width = 800, Height = 400;
  bool Resizable = true;
  bool Borderless = false;
  bool Visible = true;
  bool Minimized = false;
  bool Maximized = false;
};

class Window {
    friend Draw::DrawState;
    friend class Texture;
  public:
    Window();
    Window(const WindowSettings& settings);
    
    void SetTitle(const std::string& title);
    std::string GetTitle() const;
    void SetSize(Vec2 size);
    Vec2 GetSize() const;

    bool ShouldClose() const;
    void Close();

    void Update();
  private:

    void Initialize(const WindowSettings& settings);

    bool _shouldClose = false;
    std::string _windowTitle;

    SDL_Window* _window;
    SDL_Renderer* _renderer;
};

} // namespace Hobby

#endif // _HOBBY_ENGINE_H
