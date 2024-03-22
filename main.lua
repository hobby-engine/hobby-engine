local function printTable(t)
  print("{")
  for k, v in pairs(t) do
    if type(v) == "table" then
      printTable(v)
    else
      print(k, v)
    end
  end
  print("}")
end

function hobby.step()
end

function hobby.draw()
  hobby.renderer.setColor(1, 1, 1);
  hobby.renderer.rectangle(10, 10, 50, 50);
  hobby.renderer.circle(50 + 35, 35, 25);
end

printTable(hobby)
