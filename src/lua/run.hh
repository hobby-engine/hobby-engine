#ifndef _LUA_RUN_HH
#define _LUA_RUN_HH

const char scriptRunLua[] = R"lua(
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
)lua";

#endif // _LUA_RUN_HH