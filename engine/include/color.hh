#ifndef _HOBBY_COLOR_H
#define _HOBBY_COLOR_H

#include "types.hh"

namespace Hobby {

/// @brief Stores and manipulates colors.
struct Color {
public:
  /// @brief Create a color from RGBA.
  Color(f32 r, f32 g, f32 b, f32 a = 1) 
    : R(r),
      G(g),
      B(b),
      A(a) {
  }

  /// @brief Create a color from a hexcode. Assumes RGBA.
  Color(u32 hex) {
    SetR8((hex >> 24) & 0xFF);
    SetG8((hex >> 16) & 0xFF);
    SetB8((hex >> 8) & 0xFF);
    SetA8(hex & 0xFF);
  }

  /// @brief Create a color on the scale of 0-255.
  static inline Color From8(u8 r, u8 g, u8 b, u8 a = 255) {
    return Color(
      static_cast<f32>(r) / 255,
      static_cast<f32>(g) / 255,
      static_cast<f32>(b) / 255,
      static_cast<f32>(a) / 255);
  }

  /// @brief Red channel.
  f32 R;
  /// @brief Green channel.
  f32 G;
  /// @brief Blue channel.
  f32 B;
  /// @brief Alpha channel; transparency.
  f32 A;

  /// @brief Get the red channel on a scale of 0-255.
  inline u8 GetR8() const {
    return static_cast<u8>(R * 255);
  }
  /// @brief Get the green channel on a scale of 0-255.
  inline u8 GetG8() const {
    return static_cast<u8>(G * 255);
  }
  /// @brief Get the blue channel on a scale of 0-255.
  inline u8 GetB8() const {
    return static_cast<u8>(B * 255);
  }
  /// @brief Get the alpha channel on a scale of 0-255.
  inline u8 GetA8() const {
    return static_cast<u8>(A * 255);
  }

  /// @brief Set the red channel on a scale of 0-255.
  inline void SetR8(u8 r) {
    R = static_cast<f32>(r) / 255;
  }
  /// @brief Set the green channel on a scale of 0-255.
  inline void SetG8(u8 g) {
    G = static_cast<f32>(g) / 255;
  }
  /// @brief Set the blue channel on a scale of 0-255.
  inline void SetB8(u8 b) {
    B = static_cast<f32>(b) / 255;
  }
  /// @brief Set the alpha channel on a scale of 0-255.
  inline void SetA8(u8 a) {
    A = static_cast<f32>(a) / 255;
  }

  /// @brief Invert a color.
  inline Color Invert() {
    return Color::From8(~GetR8(), ~GetG8(), ~GetB8(), GetA8());
  }

  /// @brief Convert a color to grayscale.
  inline Color Grayscale() {
    f32 average = (R + G + B) / 3;
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
