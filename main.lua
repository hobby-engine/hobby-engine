local Player = hobby.class()

function Player:new()
  self.x, self.y = 0, 0
  self.t = 0
end

function Player:update()
  self.t = self.t + hobby.dt
  self.x = math.cos(self.t) * 100 + 400
  self.y = math.sin(self.t) * 100 + 200
end

function Player:draw()
  hobby.renderer.setColor(1, 1, 1)
  hobby.renderer.drawEllipse(self.x, self.y, 25)
end

local player = Player()

function hobby.update()
  player:update()
end

function hobby.draw()
  player:draw()
end

