#ifndef _POINT_COLOR_H
#define _POINT_COLOR_H

#include <cstdint>
namespace point {

/// Stores and manipulates colors.
struct Color {
public:
  /// Create a color from RGBA.
  Color(double r, double g, double b, double a = 1) 
    : R(r),
      G(g),
      B(b),
      A(a) {
  }

  /// Create a color from a hexcode. Assumes RGBA.
  Color(uint32_t hex) {
    SetR8((hex >> 24) & 0xFF);
    SetG8((hex >> 16) & 0xFF);
    SetB8((hex >> 8) & 0xFF);
    SetA8(hex & 0xFF);
  }

  /// Create a color on the scale of 0-255.
  static inline Color From8(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    return Color(
      static_cast<double>(r) / 255,
      static_cast<double>(g) / 255,
      static_cast<double>(b) / 255,
      static_cast<double>(a) / 255);
  }

  /// Red channel.
  double R;
  /// Green channel.
  double G;
  /// Blue channel.
  double B;
  /// Alpha channel; transparency.
  double A;

  /// Get the red channel on a scale of 0-255.
  inline uint8_t GetR8() const {
    return static_cast<uint8_t>(R * 255);
  }
  /// Get the green channel on a scale of 0-255.
  inline uint8_t GetG8() const {
    return static_cast<uint8_t>(G * 255);
  }
  /// Get the blue channel on a scale of 0-255.
  inline uint8_t GetB8() const {
    return static_cast<uint8_t>(B * 255);
  }
  /// Get the alpha channel on a scale of 0-255.
  inline uint8_t GetA8() const {
    return static_cast<uint8_t>(A * 255);
  }

  /// Set the red channel on a scale of 0-255.
  inline void SetR8(uint8_t r) {
    R = static_cast<double>(r) / 255;
  }
  /// Set the green channel on a scale of 0-255.
  inline void SetG8(uint8_t g) {
    G = static_cast<double>(g) / 255;
  }
  /// Set the blue channel on a scale of 0-255.
  inline void SetB8(uint8_t b) {
    B = static_cast<double>(b) / 255;
  }
  /// Set the alpha channel on a scale of 0-255.
  inline void SetA8(uint8_t a) {
    A = static_cast<double>(a) / 255;
  }

  /// Invert this color's bits.
  inline Color Invert() {
    return Color::From8(~GetR8(), ~GetG8(), ~GetB8(), GetA8());
  }

  /// Convert to grayscale.
  inline Color Grayscale() {
    float average = (R + G + B) / 3;
    return Color(average, average, average, A);
  }

  Color operator~() {
    return Invert();
  }
private:
};

}

#endif
