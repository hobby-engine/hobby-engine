# API
The Hobby API is designed to be silly and beginner-friendly.<br>
Just know these docs are incomplete because I am lazy.

# Rendering

## `setDrawColor(r, g, b, a=1)`
Sets the color that all subsequent draw calls will use (With some exceptions).

### Example
```lua
hobby.setDrawColor(1, 0.5, 0)
```

## `drawRect(x, y, w, h)`
Draws a filled-in rectangle.

### Example
```lua
hobby.drawRect(50, 50, 150, 75)
```

## `drawEllipse(x, y, rx, ry=rx)`
Draws an ellipse. If the last argument is left out, it will draw a circle.

### Example
```lua
hobby.drawEllipse(50, 50, 20)
```

## `wipe()`
Wipes the current render target.

### Example
```lua
hobby.wipe()
```

## `swapDrawBuffers()`
Swaps the draw buffers. :)

### Example
```lua
hobby.swapDrawBuffers()
```

# Input

## `isKeyPressed(key)`
Checks if a key is currently pressed.

### Parameters
- `key` - `number` - The key to check.

### Examples
```lua
if hobby.isKeyPressed(hobby.Space) then
    self:jump()
end
```

## `isMousePressed(button)`
Checks if a mouse button is pressed.

### Parameters
- `button` - `number` - The button to check.

### Examples
```lua
if hobby.isMousePressed(hobby.LMB) then -- LMB = 1, RMB = 2, MMB = 3
    self:shoot()
end
```