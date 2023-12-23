#ifndef _POINT_DRAW_H
#define _POINT_DRAW_H

#include "color.hh"
#include "window.hh"

namespace point {

/// @brief Holds and mutates graphics state.
class Graphics {
  public:
    /// @brief Initial constructor, the first state must use this constructor.
    ///
    /// Other states made after this can infer the window from the previous one.
    /// This constructor will not replace current state, assuming there is one.
    /// Instead, it will keep a reference to it, and will return to that state 
    /// when `Pop()` is called.
    /// It does not own the window. If the window is destroyed then the graphics
    /// state is invalidated.
    ///
    /// @param window The window this state will draw to.
    Graphics(Window& window);
    /// @brief Default constructor. Infers window from the previous state.
    ///
    /// Will not replace current state. Instead, it will keep a reference to it,
    /// and will return to that state when `Pop()` is called. If this is used to
    /// create the initial state, it will throw an error.
    Graphics();

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
    
  private:
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
