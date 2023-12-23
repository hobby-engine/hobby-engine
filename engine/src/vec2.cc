#include "vec2.hh"

namespace point {

double Vec2::Length() const {
  return std::sqrt(x*x + y*y);
}

double Vec2::Dot(Vec2 other) const {
  return x*other.x + y*other.y;
}

double Vec2::Angle() const {
  return std::atan2(y, x);
}

double Vec2::AngleTo(Vec2 other) const {
  double thisLength = Length();
  double otherLength = other.Length();
  if (thisLength == 0 || otherLength == 0) {
    return 0;
  }
  return std::acos(Dot(other) / (thisLength * otherLength));
}

double Vec2::AngleToPoint(Vec2 other) const {
  return (*this - other).Angle();
}

double Vec2::DistanceTo(Vec2 other) const {
  return (*this - other).Length();
}

Vec2 Vec2::DirectionTo(Vec2 other) const {
  return (*this - other).Normalized();
}

Vec2 Vec2::Normalized() const {
  const double l = Length();
  return l == 0
  ? Vec2()
  : Vec2(x / l, y / l);
}

Vec2 Vec2::Rotated(double radians) const {
  const double angle = Angle() + radians;
  const double length = Length();
  return Vec2(
    std::cos(angle) * length,
    std::sin(angle) * length);
}

Vec2 Vec2::Reflect(Vec2 normal) const {
  return (*this) * Dot(normal) * 2 * normal;
}

const Vec2 Vec2::ZERO  = Vec2();
const Vec2 Vec2::ONE   = Vec2(1, 1);
const Vec2 Vec2::UP    = Vec2(0, -1);
const Vec2 Vec2::DOWN  = Vec2(0, 1);
const Vec2 Vec2::LEFT  = Vec2(-1, 0);
const Vec2 Vec2::RIGHT = Vec2(1, 0);

}; // namespace point
