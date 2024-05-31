#ifndef _LUA_THING_HH
#define _LUA_THING_HH

const char scriptthinglua[] = R"lua(
local things = {}

local internal = {}

local function defaultstbl(opts)
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

      hobby.matchtype(lower, "number")
      hobby.matchtype(upper, "number")

      local default = v.default
      hobby.matchtype(default, "number")

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

  if not internal[t] then
    error("Thing does not have defaults.", 1)
  end

  hobby.injectkeys(instance, internal[t].defaults)

  if instance.new then
    instance:new(...)
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
      defaults = defaultstbl(opts),
    }
  end

  getmetatable(thing).__call = default
  return thing
end
)lua";

#endif // _LUA_THING_HH