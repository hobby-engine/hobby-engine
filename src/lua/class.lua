local nextTypeId = 0

local function getNextTypeId()
  local id = nextTypeId
  nextTypeId = nextTypeId + 1
  return id
end

local function createInstance(class, ...)
  local instance = setmetatable({}, class)
  if instance.new then
    instance:new(...)
  end
  return instance
end

local function super(self, fn, ...)
  local mt = getmetatable(self)
  if not mt.__base then -- no base class
    error("Invalid call to 'base'. No base class.")
  end

  local current = mt.__base
  mt.__base = mt.__base.__base
  local res = current[fn](self, ...)
  mt.__base = current
  return res
end

local function typesMatch(self, other)
  local smt, omt = getmetatable(self), getmetatable(other)
  local match = smt.__id == omt.__id

  if not match and smt.__base then
    local current = smt.__base
    local id = smt.__id
    smt.__base = smt.__base.__base
    smt.__id = current.__id
    match = typesMatch(self, other)
    smt.__base = current
    smt.__id = id
  end
  return match
end

local function isType(self, type)
  local smt = getmetatable(self)
  local match = smt.__id == type.__id

  if not match and smt.__base then
    local current = smt.__base
    local id = smt.__id
    smt.__base = smt.__base.__base
    smt.__id = current.__id
    match = isType(self, type)
    smt.__base = current
    smt.__id = id
  end
  return match
end

local function class(extends)
  local definition = {}
  definition.__index = definition
  definition.__base = extends
  definition.__id = getNextTypeId()

  -- copying down all the base methods so we don't need to search through 
  -- inheritance trees whenever we call something
  if extends then
    for k, v in pairs(extends) do
      if type(v) == "function" then
        definition[k] = v
      end
    end
  end

  setmetatable(definition, {
    __call = createInstance,
    __index = extends,
  })

  definition.super = super
  definition.typesMatch = typesMatch
  definition.isType = isType

  return definition
end

hobby.class = class
