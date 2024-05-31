#ifndef _LUA_MATH_HH
#define _LUA_MATH_HH

const char scriptmathlua[] = R"lua(
hobby.math = {}

function hobby.frac(x)
  return x - math.floor(x)
end

function hobby.lerp(a, b, t)
  return (b - a) * t + a
end

function hobby.dtlerp(a, b, t)
  return hobby.lerp(b, a, 0.5^(hobby.dt * t))
end

function hobby.anglediff(a, b)
  local diff = (b - a) % (math.pi * 2)
  return (2 * diff) % (math.pi * 2) - diff
end

function hobby.lerpangle(a, b, t)
  return a + hobby.anglediff(a, b) * (1 - 0.5^t)
end

function hobby.wrap(a, min, max)
  return (a % (max - min)) + min
end

function hobby.clamp(a, min, max)
  if a > max then
    return max
  elseif a < min then
    return min
  end
  return a
end

function hobby.sign(a)
  return a < 0 and -1 or 1
end

function hobby.snapped(a, step)
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

function hobby.vec.directionbetween(x, y, xx, yy)
  return hobby.vec.normalize(xx - x, yy - y)
end

function hobby.vec.distancebetween(x, y, xx, yy)
  return hobby.vec.length(x - xx, y - yy)
end

function hobby.vec.angle(x, y)
  return math.atan2(y, x)
end

function hobby.vec.anglebetween(x, y, xx, yy)
  return hobby.vec.angle(xx - x, yy - y)
end

function hobby.vec.rotated(x, y, r)
  local t = hobby.vec.angle(x, y) + r
  local l = hobby.vec.length(x, y)

  local nx = math.cos(t) * l
  local ny = math.sin(t) * l

  return nx, ny
end
)lua";

#endif // _LUA_MATH_HH