local Player = hobby.class()

function Player:new()
  self.x, self.y = 0, 0
  self.vx, self.vy = 0, 0
  self.ix, self.iy = 0, 0
  self.speed = 300
  self.accel = 5

  hobby.keyEvent:connect(self.onKeyEvent, self)
end

function Player:update()
  self.vx = hobby.math.dtLerp(self.vx, self.ix * self.speed, self.accel)
  self.vy = hobby.math.dtLerp(self.vy, self.iy * self.speed, self.accel)

  self.x = self.x + self.vx * hobby.dt
  self.y = self.y + self.vy * hobby.dt
end

function Player:draw()
  hobby.setDrawColor(1, 1, 1)
  hobby.drawEllipse(self.x, self.y, 25)
end

function Player:onKeyEvent(_, _, _)
  self.ix, self.iy = hobby.getInputVector(hobby.A, hobby.D, hobby.W, hobby.S)
end

function Player:onKeyReleased(key)
  print("Released", key)
end

local player = Player()

function hobby.update()
  player:update()
end

function hobby.draw()
  player:draw()
end

