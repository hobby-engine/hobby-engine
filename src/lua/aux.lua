
function hobby.try(func, ...)
  if type(func) == "function" then
    return func(...)
  end
  return nil;
end

function hobby.matchType(v, t)
  if type(v) == "table" and type(t) == "table" then
    local vmt = getmetatable(v)
    if vmt.__id ~= t.__id then
      error("Expected class type with id " .. t.__id .. ".", 2)
    end
    return
  end

  if type(v) ~= t then
    error("Expected type of '" .. t .. "'.", 2)
  end
end

function hobby.copyTable(t, deep)
  deep = deep or false
  hobby.matchType(t, "table")
  hobby.matchType(deep, "boolean")

  local copy = {}

  for k, v in pairs(t) do
    if type(v) ~= "table" or not deep then
      copy[k] = v
    else
      copy[k] = hobby.copyTable(v, deep)
    end
  end

  local mt = getmetatable(t)
  if mt then
    setmetatable(copy, mt)
  end

  return copy
end

function hobby.swapRemove(t, i)
  t[i] = t[#t]
  t[#t] = nil
end
