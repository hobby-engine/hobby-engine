local x = 0

function hobby.update()
  local dt = hobby.dt
  x = x + 100 * dt
end

function hobby.draw()
  hobby.renderer.setColor(1, 0, 0)
  hobby.renderer.drawRect(400 - 150 / 2, 200 - 150 / 2, 150, 150)
  hobby.renderer.drawEllipse(x, 50, 50)
end

