# Events

Events are objects used to tell other, possibly unrelated parts of your game that something happened, without you needing to know they even exist.

### Usage
You can create an event really easily:
```lua
local playerTookDamage = hobby.event()
```
Once you have an event, you can connect any function to it.
```lua
function playerDamageCallback(hp, damage)
  -- Just log
  print(hp, damage)
end

playerTookDamage:connect(playerDamageCallback)
```
Now that it's connected, the event has registered it and whenever it's called, it will also be called. You can connect as many functions as you want to any event.
```lua
-- Call event with 75 hp and 25 damage
playerTookDamage:call(75, 25)
```
Connecting to class methods is also very easy. It's just an extra argument:
```lua  
function MyClass:new()
  playerTookDamage:connect(self.playerDamageCallback, self)  
end
```
The second argument (`self`) tells the event what object this event should use to call `self.myFunction`.

### API
List of functions for easy reference.

- `hobby.event()` - Make an event
- `event:connect(callback, bound=nil)` - Connect a function. `bound` is used as the first argument.
- `event:call(...)` - Call the event with whatever arguments:.