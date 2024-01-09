#ifndef _HOBBY_TRANSFORM_h
#define _HOBBY_TRANSFORM_h

#include "types.hh"
#include "vec2.hh"

namespace Hobby {

/// @brief Represents the position, scale, rotation, and offset of something.
class Transform {
public:
  Transform()
    : Position(Vec2()),
      Scale(Vec2(1, 1)),
      Offset(Vec2()),
      Rotation(0) {
  }
  Transform(Vec2 position, f32 rotation, Vec2 scale, Vec2 offset)
    : Position(position),
      Scale(scale),
      Offset(offset),
      Rotation(rotation) {
  }

  /// @brief Position of the transform.
  Vec2 Position;
  /// @brief Scale of the transform.
  Vec2 Scale;
  /// @brief Offset of the transform.
  Vec2 Offset;
  /// @brief Rotation of the transform.
  f32 Rotation;
};

} // namespace Hobby

#endif // _HOBBY_TRANSFORM_h
