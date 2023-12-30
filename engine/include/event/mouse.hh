#ifndef _HOBBY_EVENT_MOUSE_H
#define _HOBBY_EVENT_MOUSE_H

#include "event.hh"
#include "vec2.hh"

namespace Hobby {

/// @brief An event representing a mouse button press.
class MousePressedEvent : public Event {
  public:
    IMPL_BUS(MousePressedEvent);

    MousePressedEvent(int button, Vec2 position)
      : _button(button),
        _position(position) {
    }

    /// @brief The button pressed.
    inline int GetButton() const {
      return _button;
    }

    /// @brief The position of the mouse at the time of the event.
    inline Vec2 GetPosition() const {
      return _button;
    }

  private:
    int _button;
    Vec2 _position;
};

/// @brief An event represent a mouse button release.
class MouseReleasedEvent : public Event {
  public:
    IMPL_BUS(MouseReleasedEvent);

    MouseReleasedEvent(int button, Vec2& position)
      : _button(button),
        _position(position) {
    }

    /// @brief The button released.
    inline int GetButton() const {
      return _button;
    }

    /// @brief The position of the mouse at the time of the event.
    inline Vec2 GetPosition() const {
      return _position;
    }

  private:
    int _button;
    Vec2& _position;
};

/// @brief An event represent a mouse movement.
class MouseMovedEvent : public Event {
public:
  IMPL_BUS(MouseMovedEvent);

  MouseMovedEvent(Vec2& relative, Vec2& position)
    : _relative(relative),
      _position(position) {
  }

  /// @brief The motion relative to the previous position.
  inline Vec2 GetRelative() const {
    return _relative;
  }

  /// @brief The position of the mouse at the time of the event.
  inline Vec2 GetPosition() const {
    return _position;
  }

private:
  Vec2& _relative;
  Vec2& _position;
};

/// @brief An event represent a mouse scroll.
class MouseScrolledEvent : public Event {
public:
  IMPL_BUS(MouseScrolledEvent);

  MouseScrolledEvent(Vec2& scroll)
    : _scroll(scroll) {
  }

  inline Vec2 GetScroll() const {
    return _scroll;
  }

private:
  Vec2& _scroll;
};

}; // namespace Hobby

#endif
