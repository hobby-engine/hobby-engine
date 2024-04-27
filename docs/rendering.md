# Rendering

Rendering is what gets stuff onto your screen, just call one of these methods to draw something.

### Drawing Functions
- `drawRect(x, y, w, h)` - Draws a rectangle.
- `drawEllipse(x, y, rx, ry=rx)` - Draws an ellipse. If the last argument is left out, it's a circle.
- `drawVertices(vertices)` - Draws arbitary vertices. Array must be flat with every 2 arguments being an `x` and `y` pair.
- `drawBoid(x, y, base, height, angle)` - Draws an angled triangle. Useful for debug and showing direction.
- `wipe(r, g, b, a=1)` - Clears the current render target with the specified color. Usually this is just the window.

### State Functions
- `setDrawColor(r, g, b, a=1)` - Sets the color that is used to draw.
- `swapDrawBuffers()` - Internal stuff. Do not call unless you know what you're doing.

## Textures

Textures are a little different. Create one like so:
```lua
local playerPng = hobby.texture2d("res/player.png")
```
Draw the texture like this:
```lua
playerPng:draw(self.x, self.y)
```
There are a ton of optional arguments for that `draw` method. They are listed below in order. Most of these are self explanatory.
- `x`, `y` - Position
- `rotation`
- `scalex`, `scaley`
- `offsetx`, `offsety` - Changes the offset of the image. Different from just adding to the `x`/`y` because it changes the center of all the other transformations listed.
- `skewx`, `skewy`

Textures also have a couple methods to get extra info about them.
- `texture:getWidth()` - Get the width of the image
- `texture:getHeight()` - Get the height of the image
- `texture:getSize()` - Get both the width and height of the image.