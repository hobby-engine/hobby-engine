# Math

### Functions under the `hobby` namespace
- `frac(x)` - Get the fractional part of a number
- `lerp(a, b, t)` - Linear interpolation
- `dtLerp(a, b, t)` - Consistent between framerates
- `lerpAngle(a, b, t)` - Lerps between two angles in a way that makes sense.
- `wrap(a, min, max)` - Wraps a number.
- `clamp(a, min, max)` - Limits a number to stay between `min` and `max`.
- `sign(a)` - Returns -1 if the number is negative, `1` if it's positive.
- `snapped(a, step)` - Snaps `a` to a multiple of `step`.

### Functions under the `hobby.vec` namespace
Learn what all these functions do somewhere else
(or make a PR to do that (pretty please))
- `dot(x1, y1, x2, y2)`
- `length(x, y)`
- `normalize(x, y)`
- `directionTo(x1, y1, x2, y2)`
- `distanceTo(x1, y1, x2, y2)`
- `angle(x, y)`
- `angleTo(x1, y1, x2, y2)`
- `rotated(x, y, r)` - `r` is in radians.
