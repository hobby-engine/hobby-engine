#ifndef _POINT_EVENT_KEY_H
#define _POINT_EVENT_KEY_H

#include "event.hh"
#include "input_types.hh"

namespace point {

/// @brief An event representing a key press.
class KeyPressedEvent : public Event {
  public:
    IMPL_BUS(KeyPressedEvent);
    
    KeyPressedEvent(input::Key key, bool isRepeated) 
      : _key(key),
        _isRepeated(isRepeated) {
    }

    /// @brief Get the key that was pressed.
    inline input::Key GetKey() const {
      return _key;
    }

    /// @brief Check if the key has been pressed multiple times.
    inline bool IsRepeated() const {
      return _isRepeated;
    }
  private:
    input::Key _key;
    bool _isRepeated;
};

/// @brief An event representing a key release.
class KeyReleasedEvent : public Event {
  public:
    IMPL_BUS(KeyReleasedEvent);

    KeyReleasedEvent(input::Key key)
      : _key(key) {
    }

    /// @brief Get the key that was pressed.
    inline input::Key GetKey() const {
      return _key;
    }

  private:
    input::Key _key;
};

} // namespace point

#endif
