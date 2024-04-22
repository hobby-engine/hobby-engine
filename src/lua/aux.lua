hobby.aux = {}

function hobby.aux.try(func, ...)
  if type(func) == "function" then
    return func(...)
  end
  return nil;
end

function hobby.aux.matchType(v, t)
  if type(v) == "table" and type(t) == "table" then
    local vmt = getmetatable(v)
    if vmt.__id ~= t.__id then
      error("Expected class type with id " .. t.__id .. ".")
    end
    return
  end

  if type(v) ~= t then
    error("Expected type of '" .. t .. "'.")
  end
end

function hobby.aux.copyTable(t, deep)
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
