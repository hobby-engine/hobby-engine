#ifndef _POINT_DRAW_H
#define _POINT_DRAW_H

#include "color.hh"
#include "window.hh"

namespace point {

/// @brief Holds and mutates graphics state.
class Graphics {
  public:
    /// @brief Sets the color of the current graphics state.
    /// @param color The new draw color.
    static void SetColor(Color color);
    /// @brief Sets the background color of the current graphics state.
    /// @param color The new background color.
    static void SetBackgroundColor(Color color);
    /// @brief Clears the screen using the current graphics state.
    static void Clear();
    /// @brief Presents all changes to the screen.
    static void Present();
    /// @brief Return to previous state. Does not free the current state.
    static void Pop();
    /// @brief Create the initial graphics state.
    ///
    /// If the window is destroyed, then all states created from it are
    /// invalidated.
    ///
    /// @param window The window this state will draw to.
    static void Initialize(Window& window);
    /// @brief Create a new graphics state.
    ///
    /// Does not replace the current state. It will keep a reference to it, and
    /// once `Pop()` is called, it will return to the previous state.
    static void Push();
    
  private:
    Graphics() = default;

    /// @brief The current state.
    static Graphics* Current;
    /// @brief The previous state.
    Graphics* _enclosing = nullptr;
    
    /// @brief The current draw color.
    Color _currentColor = Color(1, 1, 1);
    /// @brief The current clear color.
    Color _backgroundColor = Color(0, 0, 0);
    
    /// @brief The window this state draws to.
    SDL_Window* _window;
};

} // namespace point

#endif
