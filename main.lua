local Player = hobby.class()

function Player:new()
  self.x, self.y = 0, 0
  self.vx, self.vy = 0, 0
  self.ix, self.iy = 0, 0
  self.speed = 300
  self.accel = 5

  self.texture = hobby.texture2d("res/test_img.png")

  hobby.keyEvent:connect(self.onKeyEvent, self)
end

function Player:update()
  self.vx = hobby.dtLerp(self.vx, self.ix * self.speed, self.accel)
  self.vy = hobby.dtLerp(self.vy, self.iy * self.speed, self.accel)

  self.x = self.x + self.vx * hobby.dt
  self.y = self.y + self.vy * hobby.dt
end

function Player:draw()
  hobby.setDrawColor(1, 1, 1)
  self.texture:draw(self.x, self.y, 0, 0.4)
  hobby.drawBoid(self.x, self.y, 12, 25, hobby.vec.angle(self.vx, self.vy))
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

