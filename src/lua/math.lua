hobby.math = {}

function hobby.math.frac(x)
  return x - math.floor(x)
end

function hobby.math.lerp(a, b, t)
  return (b - a) * t + a
end

function hobby.math.dtLerp(a, b, t)
  return hobby.math.lerp(b, a, 0.5^(hobby.dt * t))
end

function hobby.math.angleDiff(a, b)
  local diff = (b - a) % (math.pi * 2)
  return (2 * diff) % (math.pi * 2) - diff
end

function hobby.math.lerpAngle(a, b, t)
  return a + hobby.math.angleDiff(a, b) * (1 - 0.5^t)
end

function hobby.math.wrap(a, min, max)
  return (a % (max - min)) + min
end

function hobby.math.clamp(a, min, max)
  if a > max then
    return max
  elseif a < min then
    return min
  end
  return a
end

function hobby.math.sign(a)
  return a < 0 and -1 or 1
end

function hobby.math.snapped(a, step)
  if step ~= 0 then
    return math.floor(a / step + 0.5) * step
  end
  return step
end

hobby.vec = {}

function hobby.vec.length(x, y)
  return math.sqrt(x ^ 2 + y ^ 2)
end

function hobby.vec.normalize(x, y)
  local l = hobby.vec.length(x, y)
  if l == 0 then
    return 0, 0
  end
  return x / l, y / l
end

function hobby.vec.dot(x, y, xx, yy)
  return x * xx + y * yy
end

function hobby.vec.directionTo(x, y, xx, yy)
  return hobby.vec.normalize(xx - x, yy - y)
end

function hobby.vec.distanceTo(x, y, xx, yy)
  return hobby.vec.length(x - xx, y - yy)
end

function hobby.vec.angle(x, y)
  local angle = math.atan2(y, x)
  if angle < 0 then
    angle = angle + math.pi * 2
  end
  return angle
end

function hobby.vec.angleTo(x, y, xx, yy)
  return hobby.vec.angle(xx - x, yy - y)
end

function hobby.vec.rotated(x, y, r)
  local newRot = hobby.vec.angle(x, y) + r
  local l = hobby.vec.length(x, y)

  local nx = math.cos(newRot) * l
  local ny = math.sin(newRot) * l

  return nx, ny
end
