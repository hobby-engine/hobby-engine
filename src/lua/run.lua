require("src.lua.auxiliary")
require("src.lua.class")
require("src.lua.event")
require("src.lua.input")
require("src.lua.math")
require("src.lua.set")
require("src.lua.thing")

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
  local engine = hobby.getengine()
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
