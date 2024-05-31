local nexttypeid = 0

local function nextid()
  local id = nexttypeid
  nexttypeid = nexttypeid + 1
  return id
end

local function createinst(class, ...)
  local instance = setmetatable({}, class)
  if instance.new then
    instance:new(...)
  end
  return instance
end

local function super(self, fn, ...)
  local mt = getmetatable(self)
  if not mt.__base then -- no base class
    hobby.fatal("Invalid call to 'base'. No base class.")
  end

  local current = mt.__base
  mt.__base = mt.__base.__base
  local res = current[fn](self, ...)
  mt.__base = current
  return res
end

local function typesmatch(self, other)
  local smt, omt = getmetatable(self), getmetatable(other)
  local match = smt.__id == omt.__id

  if not match and smt.__base then
    local current = smt.__base
    local id = smt.__id
    smt.__base = smt.__base.__base
    smt.__id = current.__id
    match = typesmatch(self, other)
    smt.__base = current
    smt.__id = id
  end
  return match
end

local function istype(self, type)
  local smt = getmetatable(self)
  local match = smt.__id == type.__id

  if not match and smt.__base then
    local current = smt.__base
    local id = smt.__id
    smt.__base = smt.__base.__base
    smt.__id = current.__id
    match = istype(self, type)
    smt.__base = current
    smt.__id = id
  end
  return match
end

local function class(extends)
  local definition = {}
  definition.__index = definition
  definition.__base = extends
  definition.__id = nextid()

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
    __call = createinst,
    __index = extends,
  })

  definition.super = super
  definition.typesmatch = typesmatch
  definition.istype = istype

  return definition
end

hobby.class = class
