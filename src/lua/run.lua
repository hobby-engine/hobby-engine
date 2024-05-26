function hobby.run()
  local engine = hobby.engine()
  local mainWindow = hobby.mainwindow()

  hobby.try(hobby.start)

  while engine:isrunning() do
    hobby.pollevents()
    engine:update()

    hobby.try(hobby.onupdate)

    mainWindow:setcurrent()
    hobby.draw.clear(0.2, 0.2, 0.2)
    hobby.try(hobby.ondraw)
    hobby.draw.swap()
  end
end
