#ifndef _POINT_EVENT_MOUSE_H
#define _POINT_EVENT_MOUSE_H

#include "event.hh"
#include "vec2.hh"

namespace point {

class MousePressedEvent : public Event {
  public:
    IMPL_BUS(MousePressedEvent);

    MousePressedEvent(int button, Vec2 position)
      : _button(button),
        _position(position) {
    }

    inline int GetButton() const {
      return _button;
    }

    inline Vec2 GetPosition() const {
      return _button;
    }

  private:
    int _button;
    Vec2 _position;
};

class MouseReleasedEvent : public Event {
  public:
    IMPL_BUS(MouseReleasedEvent);

    MouseReleasedEvent(int button, Vec2& position)
      : _button(button),
        _position(position) {
    }

    inline int GetButton() const {
      return _button;
    }

    inline Vec2 GetPosition() const {
      return _position;
    }

  private:
    int _button;
    Vec2& _position;
};

class MouseMovedEvent : public Event {
public:
  IMPL_BUS(MouseMovedEvent);

  MouseMovedEvent(Vec2& relative, Vec2& position)
    : _relative(relative),
      _position(position) {
  }

  inline Vec2 GetRelative() const {
    return _relative;
  }

  inline Vec2 GetPosition() const {
    return _position;
  }

private:
  Vec2& _relative;
  Vec2& _position;
};

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

}; // namespace point

#endif
