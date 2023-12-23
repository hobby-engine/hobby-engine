#ifndef _POINT_ENGINE_VEC2_H
#define _POINT_ENGINE_VEC2_H

#include <cmath>

namespace point {

class Vec2 {
  public:
    union { double X, W; };
    union { double Y, H; };

    static const Vec2 ZERO;
    static const Vec2 ONE;
    static const Vec2 UP;
    static const Vec2 DOWN;
    static const Vec2 LEFT;
    static const Vec2 RIGHT;

    Vec2(double x = 0, double y = 0)
      : X(x), Y(y) {
    }

    Vec2(Vec2& other) // Copy
      : X(other.X), Y(other.Y) {
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
      X = rhs.X;
      Y = rhs.Y;
      return *this;
    }

    Vec2 operator+(const Vec2 rhs) const {
      return Vec2(X + rhs.X, Y + rhs.Y);
    }

    Vec2 operator+=(const Vec2 rhs) {
      X += rhs.X;
      Y += rhs.Y;
      return *this;
    }

    Vec2 operator-(const Vec2 rhs) const {
      return Vec2(X - rhs.X, Y - rhs.Y);
    }

    Vec2 operator-=(const Vec2 rhs) {
      X -= rhs.X;
      Y -= rhs.Y;
      return *this;
    }

    Vec2 operator*(const Vec2& rhs) const {
      return Vec2(X * rhs.X, Y * rhs.Y);
    }

    Vec2 operator*(double rhs) const {
      return Vec2(X * rhs, Y * rhs);
    }

    Vec2 operator*=(const Vec2& rhs) {
      X *= rhs.X;
      Y *= rhs.Y;
      return *this;
    }

    Vec2 operator*=(double rhs) {
      X *= rhs;
      Y *= rhs;
      return *this;
    }

    Vec2 operator/(const Vec2& rhs) const {
      return Vec2(X / rhs.X, Y / rhs.Y);
    }

    Vec2 operator/(double rhs) const {
      return Vec2(X / rhs, Y / rhs);
    }

    Vec2 operator/=(const Vec2& rhs) {
      X /= rhs.X;
      Y /= rhs.Y;
      return *this;
    }

    Vec2 operator/=(double rhs) {
      X /= rhs;
      Y /= rhs;
      return *this;
    }
};

} // namespace point

#endif // _POINT_ENGINE_VEC2_H 
