#ifndef _POINT_ENGINE_VEC2_H
#define _POINT_ENGINE_VEC2_H

#include <cmath>

namespace point {

class Vec2 {
  public:
    union { double x, w; };
    union { double y, h; };

    static const Vec2 ZERO;
    static const Vec2 ONE;
    static const Vec2 UP;
    static const Vec2 DOWN;
    static const Vec2 LEFT;
    static const Vec2 RIGHT;

    Vec2(double x = 0, double y = 0)
      : x(x), y(y) {
    }

    Vec2(Vec2& other) // Copy
      : x(other.x), y(other.y) {
    }

    inline double Length() const;
    inline double Dot(Vec2 other) const;
    inline double Angle() const;
    inline double AngleTo(Vec2 other) const;
    inline double AngleToPoint(Vec2 other) const;
    inline double DistanceTo(Vec2 other) const;
    inline Vec2 DirectionTo(Vec2 other) const;
    inline Vec2 Normalized() const;
    inline Vec2 Rotated(double radians) const;
    Vec2 Reflect(Vec2 normal) const;

    Vec2 operator=(const Vec2 rhs) {
      x = rhs.x;
      y = rhs.y;
      return *this;
    }

    Vec2 operator+(const Vec2 rhs) const {
      return Vec2(x + rhs.x, y + rhs.y);
    }

    Vec2 operator+=(const Vec2 rhs) {
      x += rhs.x;
      y += rhs.y;
      return *this;
    }

    Vec2 operator-(const Vec2 rhs) const {
      return Vec2(x - rhs.x, y - rhs.y);
    }

    Vec2 operator-=(const Vec2 rhs) {
      x -= rhs.x;
      y -= rhs.y;
      return *this;
    }

    Vec2 operator*(const Vec2& rhs) const {
      return Vec2(x * rhs.x, y * rhs.y);
    }

    Vec2 operator*(double rhs) const {
      return Vec2(x * rhs, y * rhs);
    }

    Vec2 operator*=(const Vec2& rhs) {
      x *= rhs.x;
      y *= rhs.y;
      return *this;
    }

    Vec2 operator*=(double rhs) {
      x *= rhs;
      y *= rhs;
      return *this;
    }

    Vec2 operator/(const Vec2& rhs) const {
      return Vec2(x / rhs.x, y / rhs.y);
    }

    Vec2 operator/(double rhs) const {
      return Vec2(x / rhs, y / rhs);
    }

    Vec2 operator/=(const Vec2& rhs) {
      x /= rhs.x;
      y /= rhs.y;
      return *this;
    }

    Vec2 operator/=(double rhs) {
      x /= rhs;
      y /= rhs;
      return *this;
    }
};

} // namespace point

#endif // _POINT_ENGINE_VEC2_H 
