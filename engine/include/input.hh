#ifndef _POINT_INPUT_H
#define _POINT_INPUT_H

#include "input_types.hh"
#include "vec2.hh"

/// @namespace point::input
/// @brief Holds input related things.

namespace point::input {

/// @brief Check if the specified key is pressed.
/// @param key The key to check.
bool IsKeyDown(Key key);
/// @brief Check if the specified mouse button is pressed.
/// @param button The mouse button to check.
bool IsMouseDown(int button);
/// @brief Get the mouse position in pixels, relative to the top-left corner
/// of the window.
Vec2 GetMousePosition();

} // namespace point::input

#endif
