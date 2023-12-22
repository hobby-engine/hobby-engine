#ifndef _POINT_ENGINE_VEC2_H
#define _POINT_ENGINE_VEC2_H

#include <cmath>

namespace point {

template <class T>
class Vec2Template {
  public:
    T x, y;

    Vec2Template(T x = 0, T y = 0)
      : x(x), y(y) {
    }

    Vec2Template(Vec2Template<T>& other) // Copy
      : x(other.x), y(other.y) {
    }

    inline double Length() const {
      return std::sqrt(x*x + y*y);
    }

    inline double Dot(Vec2Template<T> other) const {
      return x*other.x + y*other.y;
    }

    inline double Angle() const {
      return std::atan2(y, x);
    }

    inline double AngleTo(Vec2Template<T> other) const {
      return (*this - other).Angle();
    }

    inline double DistanceTo(Vec2Template<T> other) const {
      return (*this - other).Length();
    }

    inline Vec2Template<T> DirectionTo(Vec2Template<T> other) const {
      return (*this - other).Normalized();
    }

    Vec2Template<T> Normalized() const {
      const double l = Length();
      return l == 0
        ? Vec2Template<T>()
        : Vec2Template<T>(x / l, y / l);
    }

    Vec2Template<T> Rotated(double radians) const {
      const double angle = Angle() + radians;
      const double length = Length();
      return Vec2Template<T>(
        std::cos(angle) * length,
        std::sin(angle) * length);
    }

  Vec2Template<T> operator=(Vec2Template<T> rhs) {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }
};

using Vec2 = Vec2Template<double>;
using Vec2f = Vec2Template<float>;
using Vec2i = Vec2Template<int>;

template <class T>
Vec2Template<T> operator+(Vec2Template<T> lhs, Vec2Template<T> rhs) {
  return Vec2Template<T>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <class T>
Vec2Template<T> operator+=(Vec2Template<T> lhs, Vec2Template<T> rhs) {
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  return lhs;
}

template <class T>
Vec2Template<T> operator-(Vec2Template<T> lhs, Vec2Template<T> rhs) {
  return Vec2Template<T>(lhs.x - rhs.x, lhs.y - rhs.y);
}

template <class T>
Vec2Template<T> operator-=(Vec2Template<T> lhs, Vec2Template<T> rhs) {
  lhs.x -= rhs.x;
  lhs.y -= rhs.y;
  return lhs;
}

template <class T>
Vec2Template<T> operator*(Vec2Template<T> lhs, Vec2Template<T> rhs) {
  return Vec2Template<T>(lhs.x * rhs.x, lhs.y * rhs.y);
}

template <class T>
Vec2Template<T> operator*(Vec2Template<T> lhs, T rhs) {
  return Vec2Template<T>(lhs.x * rhs, lhs.y * rhs);
}

template <class T>
Vec2Template<T> operator*=(Vec2Template<T> lhs, Vec2Template<T> rhs) {
  lhs.x *= rhs.x;
  lhs.y *= rhs.y;
  return lhs;
}

template <class T>
Vec2Template<T> operator*=(Vec2Template<T> lhs, T rhs) {
  lhs.x *= rhs;
  lhs.y *= rhs;
  return lhs;
}

template <class T>
Vec2Template<T> operator/(Vec2Template<T> lhs, Vec2Template<T> rhs) {
  return Vec2Template<T>(lhs.x / rhs.x, lhs.y / rhs.y);
}

template <class T>
Vec2Template<T> operator/(Vec2Template<T> lhs, T rhs) {
  return Vec2Template<T>(lhs.x / rhs, lhs.y / rhs);
}

template <class T>
Vec2Template<T> operator/=(Vec2Template<T> lhs, Vec2Template<T> rhs) {
  lhs.x /= rhs.x;
  lhs.y /= rhs.y;
  return lhs;
}

template <class T>
Vec2Template<T> operator/=(Vec2Template<T> lhs, T rhs) {
  lhs.x /= rhs;
  lhs.y /= rhs;
  return lhs;
}

} // namespace point

#endif // _POINT_ENGINE_VEC2_H 
