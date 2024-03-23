local texture = hobby.texture.create("res/test_img.png")
local t = 0

function hobby.step()
  local dt = hobby.time.getDeltaTime()
  t = t + dt

  print(hobby.time.getFps(), hobby.time.getDeltaTime(), hobby.renderer.getDrawCalls())
end

function hobby.draw()
  hobby.renderer.setColor(1, 0, 0)
  hobby.renderer.rectangle(10, 10, 50, 50)
  hobby.renderer.circle(50 + 35, 35, 25)
  hobby.renderer.ellipse(200, 200, 25, 50)

  hobby.renderer.setColor(0, 1, 0)
  hobby.renderer.rectangleOutline(10, 10 + 50, 50, 50)
  hobby.renderer.circleOutline(50 + 35, 35 + 50, 25)
  hobby.renderer.ellipseOutline(200 + 50, 200, 25, 50)

  hobby.renderer.polygon({
    500, 500,
    550, 550,
    450, 550,
  })

  hobby.renderer.texture(texture, 10, 250 + math.sin(t) * 20, 0, 0.2)
  hobby.renderer.circle(500, 250 + math.sin(t) * 20, 25)
end
