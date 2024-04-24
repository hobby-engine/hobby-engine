local things = {}

local internal = {}

local function getDefaultsTable(opts)
  local defaults = {}

  for k, v in pairs(opts) do
    if type(k) ~= "string" then
      goto continue
    end

    if type(v) == "table" then -- This is a range
      if #v ~= 2 then
        error("Range '" .. k .. "' must have an upper and lower bound.", 3)
      end

      local lower = v[1]
      local upper = v[2]

      hobby.matchType(lower, "number")
      hobby.matchType(upper, "number")

      local default = v.default
      hobby.matchType(default, "number")

      if default then
        if default < lower or default > upper then
          error("Default for range '" .. k .. "' is out of bounds.", 3)
        end
        defaults[k] = default
      else
        defaults[k] = upper
      end
    else
      defaults[k] = v
    end

    ::continue::
  end

  return defaults
end

local function default(t, ...)
  local instance = setmetatable({}, t)
  instance.x = 0
  instance.y = 0

  if instance.new then
    if not internal[t] then
      error("Thing does not have defaults.", 1)
    end

    instance:new(internal[t].defaults, ...)
  end
  return instance
end

local function create(t, p, ...)
  local instance = setmetatable({}, t)
  instance.x = 0
  instance.y = 0

  if instance.new then
    local defaults = internal[t].defaults
    for k, v in pairs(defaults) do
      p[k] = p[k] or v
    end
    instance:new(p, ...)
  end
  return instance
end

function hobby.thing(opts)
  local thing = hobby.class()

  if opts then
    if type(opts[1]) ~= "string" then
      error("Index [1] of thing opts must be the thing name.")
    end

    local name = opts[1]
    internal[thing] = {
      opts = opts,
      name = name,
      defaults = getDefaultsTable(opts),
    }
  end

  getmetatable(thing).__call = default
  thing.create = create
  return thing
end
