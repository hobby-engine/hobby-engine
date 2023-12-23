#ifndef _POINT_COLOR_H
#define _POINT_COLOR_H

#include <cstdint>
namespace point {

/// @brief Stores and manipulates colors.
struct Color {
public:
  /// @brief Create a color from RGBA.
  Color(double r, double g, double b, double a = 1) 
    : R(r),
      G(g),
      B(b),
      A(a) {
  }

  /// @brief Create a color from a hexcode. Assumes RGBA.
  Color(uint32_t hex) {
    SetR8((hex >> 24) & 0xFF);
    SetG8((hex >> 16) & 0xFF);
    SetB8((hex >> 8) & 0xFF);
    SetA8(hex & 0xFF);
  }

  /// @brief Create a color on the scale of 0-255.
  static inline Color From8(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    return Color(
      static_cast<double>(r) / 255,
      static_cast<double>(g) / 255,
      static_cast<double>(b) / 255,
      static_cast<double>(a) / 255);
  }

  /// @brief Red channel.
  double R;
  /// @brief Green channel.
  double G;
  /// @brief Blue channel.
  double B;
  /// @brief Alpha channel; transparency.
  double A;

  /// @brief Get the red channel on a scale of 0-255.
  inline uint8_t GetR8() const {
    return static_cast<uint8_t>(R * 255);
  }
  /// @brief Get the green channel on a scale of 0-255.
  inline uint8_t GetG8() const {
    return static_cast<uint8_t>(G * 255);
  }
  /// @brief Get the blue channel on a scale of 0-255.
  inline uint8_t GetB8() const {
    return static_cast<uint8_t>(B * 255);
  }
  /// @brief Get the alpha channel on a scale of 0-255.
  inline uint8_t GetA8() const {
    return static_cast<uint8_t>(A * 255);
  }

  /// @brief Set the red channel on a scale of 0-255.
  inline void SetR8(uint8_t r) {
    R = static_cast<double>(r) / 255;
  }
  /// @brief Set the green channel on a scale of 0-255.
  inline void SetG8(uint8_t g) {
    G = static_cast<double>(g) / 255;
  }
  /// @brief Set the blue channel on a scale of 0-255.
  inline void SetB8(uint8_t b) {
    B = static_cast<double>(b) / 255;
  }
  /// @brief Set the alpha channel on a scale of 0-255.
  inline void SetA8(uint8_t a) {
    A = static_cast<double>(a) / 255;
  }

  /// @brief Invert a color.
  inline Color Invert() {
    return Color::From8(~GetR8(), ~GetG8(), ~GetB8(), GetA8());
  }

  /// @brief Convert a color to grayscale.
  inline Color Grayscale() {
    float average = (R + G + B) / 3;
    return Color(average, average, average, A);
  }

  /// @brief Invert a color.
  Color operator~() {
    return Invert();
  }
private:
};

}

#endif
