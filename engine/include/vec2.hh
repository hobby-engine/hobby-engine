#ifndef _HOBBY_ENGINE_VEC2_H
#define _HOBBY_ENGINE_VEC2_H

#include <cmath>

namespace Hobby {

/// Represents a point or vector in 2D space.
class Vec2 {
  public:
    /// @brief Position on the X axis. W is an alias.
    union { double X, W; };
    /// @brief Position on the Y axis. H is an alias.
    union { double Y, H; };

    /// @brief Default vector initialized to (0, 0)
    static const Vec2 ZERO;
    /// @brief Default vector initialized to (1, 1)
    static const Vec2 ONE;
    /// @brief Default vector initialized to (0, -1)
    static const Vec2 UP;
    /// @brief Default vector initialized to (0, 1)
    static const Vec2 DOWN;
    /// @brief Default vector initialized to (-1, 0)
    static const Vec2 LEFT;
    /// @brief Default vector initialized to (1, 0)
    static const Vec2 RIGHT;

    /// @brief Initialize with x and y.
    Vec2(double x = 0, double y = 0)
      : X(x), Y(y) {
    }

    /// @brief Copy constructor.
    Vec2(Vec2& other)
      : X(other.X), Y(other.Y) {
    }

    /// @brief Get the length of a vector.
    inline double Length() const;
    /// @brief Get the dot product of two vectors.
    /// @param other The vector to get the dot product with.
    inline double Dot(Vec2 other) const;
    /// @brief Get the angle of a vector.
    inline double Angle() const;
    /// @brief Get the angle between two vectors.
    /// @param other The vector to compare against.
    inline double AngleTo(Vec2 other) const;
    /// @brief Get the angle from one point to other.
    /// @param other The point to get an angle to.
    inline double AngleToPoint(Vec2 other) const;
    /// @brief Get the distance to another point.
    /// @param other The point to get the distance to.
    inline double DistanceTo(Vec2 other) const;
    /// @brief Get the direction to another point, in the form of a vector.
    /// @param other The point to get the direction towards.
    inline Vec2 DirectionTo(Vec2 other) const;
    /// @brief Normalize a vector.
    /// @return A unit vector.
    inline Vec2 Normalized() const;
    /// @brief Rotate a vector, while preserving the magnitude.
    /// @param radians The angle to rotate by, in radians.
    inline Vec2 Rotated(double radians) const;
    /// @brief Reflect a vector off a normal.
    /// @param normal The normal of the surface to reflect off of.
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

} // namespace Hobby

#endif // _HOBBY_ENGINE_VEC2_H 
