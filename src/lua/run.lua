require("src.lua.aux")

function hobby.run()
  local engine = hobby.getEngine()

  hobby.aux.try(hobby.start)

  while engine:isRunning() do
    hobby.pollEvents()
    engine:update()

    hobby.aux.try(hobby.update)

    hobby.renderer.clear(0.2, 0.2, 0.2)
    hobby.aux.try(hobby.draw)
    hobby.renderer.present()
  end
end
