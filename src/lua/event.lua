local Event = hobby.class()

function Event:new()
  self.indices = {}
  self.connections = {}
end

function Event:connect(fn, bound)
  hobby.matchType(fn, "function")
  if self.indices[fn] then
    -- Don't connect an event twice.
    error("Cannot disconnect callback that is not connected.")
  end

  table.insert(self.connections, {
    fn = fn,
    bound = bound,
  })

  self.indices[fn] = #self.connections
end

function Event:disconnect(fn)
  local index = self.indices[fn]
  if not index then
    error("Cannot disconnect callback that is not connected.")
  end

  hobby.swapRemove(self.connections, self.indices[fn])
  self.indices[fn] = nil
end

function Event:call(...)
  for _, callback in ipairs(self.connections) do
    if callback.bound then
      callback.fn(callback.bound, ...)
    else
      callback.fn(...)
    end
  end
end

hobby.event = Event
