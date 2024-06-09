function hobby.color8(r, g, b, a)
  return r / 255, g / 255, b / 255, (a or 255) / 255
end

function hobby.matchtype(v, t)
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

function hobby.requirekeys(keys, tbl)
  for _, k in ipairs(keys) do
    if tbl[k] == nil then
      error("Table required key '" .. k .. "', but it had none.", 1)
    end
  end
end

function hobby.overridekeys(dest, src)
  for k, v in pairs(src) do
    dest[k] = v
  end
end

function hobby.injectkeys(dest, src)
  for k, v in pairs(src) do
    dest[k] = dest[k] or v
  end
end

function hobby.copytable(t, deep)
  deep = deep or false
  hobby.matchtype(t, "table")
  hobby.matchtype(deep, "boolean")

  local copy = {}

  for k, v in pairs(t) do
    if type(v) ~= "table" or not deep then
      copy[k] = v
    else
      copy[k] = hobby.copytable(v, deep)
    end
  end

  local mt = getmetatable(t)
  if mt then
    setmetatable(copy, mt)
  end

  return copy
end

function hobby.swapremove(t, i)
  t[i] = t[#t]
  t[#t] = nil
end
