#ifndef _POINT_ENGINE_VEC2_H
#define _POINT_ENGINE_VEC2_H

#include <cmath>

namespace point {

class Vec2 {
  public:
    union { double x, w; };
    union { double y, h; };

    Vec2(double x = 0, double y = 0)
      : x(x), y(y) {
    }

    Vec2(Vec2& other) // Copy
      : x(other.x), y(other.y) {
    }

    inline double Length() const {
      return std::sqrt(x*x + y*y);
    }

    inline double Dot(Vec2 other) const {
      return x*other.x + y*other.y;
    }

    inline double Angle() const {
      return std::atan2(y, x);
    }

    inline double AngleTo(Vec2 other) const {
      return (*this - other).Angle();
    }

    inline double DistanceTo(Vec2 other) const {
      return (*this - other).Length();
    }

    inline Vec2 DirectionTo(Vec2 other) const {
      return (*this - other).Normalized();
    }

    Vec2 Normalized() const {
      const double l = Length();
      return l == 0
        ? Vec2()
        : Vec2(x / l, y / l);
    }

    Vec2 Rotated(double radians) const {
      const double angle = Angle() + radians;
      const double length = Length();
      return Vec2(
        std::cos(angle) * length,
        std::sin(angle) * length);
    }

    Vec2 Reflect(Vec2 normal) const {
      return (*this) * Dot(normal) * 2 * normal;
    }

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
