function hobby.run()
  local engine = hobby.getengine()
  local mainWindow = hobby.getmainwindow()

  if hobby.onstart then
    hobby.onstart()
  end

  while engine:isrunning() do
    hobby.pollevents()
    engine:update()

    if hobby.onupdate then
      hobby.onupdate()
    end

    mainWindow:makecurrent()
    hobby.draw.clear(0.2, 0.2, 0.2)
    if hobby.ondraw then
      hobby.ondraw()
    end
    hobby.draw.swap()
  end
end
