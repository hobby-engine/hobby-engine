require("src.lua.aux")
require("src.lua.class")
require("src.lua.event")
require("src.lua.input")
require("src.lua.math")
require("src.lua.set")

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

  hobby.try(hobby.start)

  while engine:isRunning() do
    hobby.pollEvents()
    engine:update()

    hobby.try(hobby.update)

    hobby.wipe(0.2, 0.2, 0.2)
    hobby.try(hobby.draw)
    hobby.swapDrawBuffers()
  end
end
