local Set = hobby.class()
Set.__metatable = false

function Set:new(doinit)
  self.values = {}

  if doinit then
    for _, v in ipairs(doinit) do
      self:add(v)
    end
  end
end

function Set:has(v)
  return self.values[v] == true
end

function Set:add(v)
  self.values[v] = true
end

function Set:remove(v)
  self.values[v] = nil
end

function Set:__tostring()
  local str = "{"
  for v, _ in pairs(self.values) do
    if type(v) == "string" then
      str = str .. "\"" .. tostring(v) .. "\""
    else
      str = str .. tostring(v)
    end

    if next(self.values, v) then
      str = str .. ", "
    end
  end
  str = str .. "}"
  return str
end

hobby.set = Set
