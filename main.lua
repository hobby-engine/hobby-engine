local Player = hobby.class()

function hobby.onKeyPressed(key, isRepeat)
  print(key, isRepeat)
end

function Player:new()
  self.x, self.y = 0, 0
  self.vx, self.vy = 0, 0
  self.speed = 300
  self.accel = 5
end

function Player:update()
  local ix, iy = hobby.getInputVector(hobby.A, hobby.D, hobby.W, hobby.S)

  self.vx = hobby.math.dtLerp(self.vx, ix * self.speed, self.accel)
  self.vy = hobby.math.dtLerp(self.vy, iy * self.speed, self.accel)

  self.x = self.x + self.vx * hobby.dt
  self.y = self.y + self.vy * hobby.dt
end

function Player:draw()
  if hobby.isMousePressed(hobby.LMB) then
    hobby.renderer.setColor(1, 0.5, 0)
  else
    hobby.renderer.setColor(1, 1, 1)
  end
  hobby.renderer.drawEllipse(self.x, self.y, 25)
end

local player = Player()

function hobby.update()
  player:update()
end

function hobby.draw()
  player:draw()
end

