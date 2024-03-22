function hobby.step()
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
end
