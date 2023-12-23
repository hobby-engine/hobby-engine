#ifndef _POINT_ENGINE_WINDOW_H
#define _POINT_ENGINE_WINDOW_H

#include "SDL2/SDL.h"

#include "vec2.hh"

namespace point {

/// @brief Settings to initialize a window with.
struct WindowSettings {
  const char* Title = "Point Engine";
  int Width = 800, Height = 400;
  int X = SDL_WINDOWPOS_CENTERED, Y = SDL_WINDOWPOS_CENTERED;
  bool Resizable = true;
};

/// @brief Holds and manages window state and events.
///
/// This class is a singleton. Constructors will throw an error if they see more
/// than one instance.
class Window {
    friend class Graphics;
  public:
    /// @brief Default constructor. Uses the default settings in `WindowSettings`.
    Window();
    /// @brief Constructor to use custom settings.
    Window(const WindowSettings& settings);
    ~Window();
    
    /// @brief Get the title of the window.
    const char* GetTitle() const;
    /// @brief Set the title of the window.
    /// @param title The new title.
    void SetTitle(const char* title);
    /// @brief Get the position of the window.
    Vec2 GetPosition() const;
    /// @brief Set the position of the window.
    /// @param position The new position.
    void SetPosition(const Vec2& position);
    /// @brief Get the size of the window.
    Vec2 GetSize() const;
    /// @brief Set the size of the window.
    /// @param size The new size.
    void SetSize(const Vec2& size);

    /// @brief Update window and events.
    void Update();

    /// @brief Check if whether the window should close yet.
    inline bool ShouldClose() const {
      return _shouldClose;
    }
    /// @brief Close the window.
    inline void Close() {
      _shouldClose = true;
    }
  private:
    /// @brief Initialize window state.
    void InitializeWindow(const WindowSettings& settings);

    // State
    SDL_Window* _window;
    SDL_GLContext _context;
    bool _shouldClose = false;
    
    // We don't allow more than one window.
    static bool _alreadyInstanced;
};

} // namespace point

#endif // _POINT_ENGINE_WINDOW_H
