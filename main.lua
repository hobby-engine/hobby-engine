local Player = hobby.thing {
  "Player",
  hp = {0, 100, default=100},
  speed = 300,
  accel = 10,
}

function Player:new()
  self.vx, self.vy = 0, 0
  self.texture = hobby.texture2d("res/test_img.png")
end

function Player:update()
  local ix, iy = hobby.getInputVector(hobby.A, hobby.D, hobby.W, hobby.S)

  self.vx = hobby.dtLerp(self.vx, ix * self.speed, self.accel)
  self.vy = hobby.dtLerp(self.vy, iy * self.speed, self.accel)

  self.x = self.x + self.vx * hobby.dt
  self.y = self.y + self.vy * hobby.dt
end

function Player:draw()
  hobby.setDrawColor(1, 1, 1)
  hobby.drawBoid(self.x, self.y, 12, 24, hobby.vec.angle(self.vx, self.vy))
  self.texture:draw(self.x, self.y, 0, 0.4)
end

local player = Player()

function hobby.update()
  player:update()
end

function hobby.draw()
  player:draw()
end
