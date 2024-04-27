# Input

See [events](events.md) first.

- `isKeyPressed(key)`
- `isMousePressed(button)`
- `getInputVector(left, right, up, down)` - Returns a normalized vector using the passed keys as directions.
- `keyToString(key)` - Converts the given key to a string.

### Examples
```lua
function Player:update()
    local ix, iy = hobby.getInputVector(hobby.A, hobby.D, hobby.W, hobby.S)

    self.vx = hobby.dtLerp(self.vx, ix * self.speed, self.accel)
    self.vy = hobby.dtLerp(self.vy, iy * self.speed, self.accel)
    
    self.x = self.x + self.vx * hobby.dt
    self.y = self.y + self.vy * hobby.dt
end
```

```lua
if hobby.isKeyPressed(hobby.Space) then
    self:jump()
end
```

```lua
if hobby.isMousePressed(hobby.LMB) then
    self:shoot(self:getClosestTarget())
end
```

### Events
You also have some events. You can use these to make it so an action only triggers once when you press a key.
- `keyEvent(isPressed, key, isRepeat)` - Called when a key is pressed or released.
- `keyPressed(key, isRepeat)` - Called when a key is pressed.
- `keyReleased(key)` - Called when a key is released.

The `keyEvent` event is called *after* `keyPressed` or `keyReleased`.

### Keys
There are a ton of keys. I'd list them all, but I don't want to do that.
Refer to [input.lua](/src/lua/input.lua).