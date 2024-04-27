# Things

Things in Hobby represent something in the world.
If you need to differentiate between Things (Hobby) and
things (objects), then capitalize the T if you mean
hobby's Things.

```lua
local Player = hobby.thing {
    "Player"
    hp = {0, 100, default=100}
    speed = 300,
    accel = 10,
}
```
What's going on here?

This is mostly for the future editor.

The `"Player"` is the name that will be displayed in the editor.

The `hp` field is a property that will be exposed in the editor.
It will be limited to a value between 0 and 100.

The `speed` and `accel` fields are just numbers that can be set
to anything you want.

```lua
function Player:new()
    self.vx, self.vy = 0, 0
    self.texture = hobby.texture2d("res/player.png")
end
```

Okay, so in this snippet, we are initializing the velocity vector, 
and creating an image. These are defined here so they aren't exposed
in the editor. The previous section is ONLY for properties you want
to show up in the editor.

```lua
function Player:update()
  local ix, iy = hobby.getInputVector(hobby.A, hobby.D, hobby.W, hobby.S)

  self.vx = hobby.dtLerp(self.vx, ix * self.speed, self.accel)
  self.vy = hobby.dtLerp(self.vy, iy * self.speed, self.accel)

  self.x = self.x + self.vx * hobby.dt
  self.y = self.y + self.vy * hobby.dt
end
```
This is the update method for a Thing.

First, we are getting a direction for input using `hobby.getInputVector()`. 
This will use the keys WASD and return a vector pointing in the direction
that your player would go if the game was top-down.

Then, we use `hobby.dtLerp` to smoothly move the velocity from wherever it
was to the direction we want to go.
`hobby.lerp` would *work*, but if someone is running at a different frame
rate, then the acceleration would have minor differences.

```lua
function Player:draw()
  hobby.setDrawColor(1, 1, 1)
  local w, h = self.texture:getWidth(), self.texture:getHeight()
  self.texture:draw(self.x, self.y, 0, 1, 1, -w/2, -h/2)
end
```
Now we're drawing the player.

We initialize the draw color to white with `hobby.setDrawColor()`. Hobby
doesn't reset the draw color when a draw function is called, so we have to
manually reset it here.

Then we draw the texture at our position (`self.x`, and `self.y`). The 
next argument is rotation, which we don't want, so it's set to `0`.
Then there's `scalex` and `scaley`, We don't need scaling, so set them
both to `1`. Finally, there's offset, we want to center our sprite,
so we offset it by half the size.