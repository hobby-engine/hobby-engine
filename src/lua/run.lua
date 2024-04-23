require("src.lua.aux")
require("src.lua.class")
require("src.lua.event")
require("src.lua.input")
require("src.lua.math")

function print(...)
  local msg = ""
  local args = {...}
  for i, v in ipairs(args) do
    msg = msg .. tostring(v)
    if i ~= #args then
      msg = msg .. "\t"
    end
  end

  hobby.log(msg)
end

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
