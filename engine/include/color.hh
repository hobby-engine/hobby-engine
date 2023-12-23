#ifndef _POINT_COLOR_H
#define _POINT_COLOR_H

#include <cstdint>
namespace point {

struct Color {
public:
  Color(double r, double g, double b, double a = 1) 
    : R(r),
    G(g),
    B(b),
    A(a) {
  }

  static inline Color From8(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    return Color(
      static_cast<double>(r) / 255,
      static_cast<double>(g) / 255,
      static_cast<double>(b) / 255,
      static_cast<double>(a) / 255);
  }

  double R, G, B, A;

  inline uint8_t GetR8() const {
    return static_cast<uint8_t>(R * 255);
  }
  inline uint8_t GetG8() const {
    return static_cast<uint8_t>(G * 255);
  }
  inline uint8_t GetB8() const {
    return static_cast<uint8_t>(B * 255);
  }
  inline uint8_t GetA8() const {
    return static_cast<uint8_t>(A * 255);
  }

  inline void SetR8(uint8_t r) {
    R = static_cast<double>(r) / 255;
  }
  inline void SetG8(uint8_t g) {
    G = static_cast<double>(g) / 255;
  }
  inline void SetB8(uint8_t b) {
    B = static_cast<double>(b) / 255;
  }
  inline void SetA8(uint8_t a) {
    A = static_cast<double>(a) / 255;
  }
private:
};

}

#endif
