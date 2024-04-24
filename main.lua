local Player = hobby.thing {
  "Player",
  hp = {0, 100},
  speed = 300,
  accel = 10,
}

function Player:new(p)
  self.hp    = p.hp
  self.speed = p.speed
  self.accel = p.accel

  self.vx, self.vy = 0, 0
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
end

local player = Player:create({accel=0.2})

function hobby.update()
  player:update()
end

function hobby.draw()
  player:draw()
end

local set = hobby.set()
set:add({1, 2, 3})
set:add("pasta sauce")
set:add(2)
set:add(true)
set:add(4)
set:remove(2)
print(set, set:has(2), set:has(true))
