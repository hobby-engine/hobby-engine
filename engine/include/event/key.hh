#ifndef _POINT_EVENT_KEY_H
#define _POINT_EVENT_KEY_H

#include "event.hh"

namespace point {

/// @brief An event representing a key press.
class KeyPressedEvent : public Event {
  public:
    IMPL_BUS(KeyPressedEvent);
    
    KeyPressedEvent(int key, bool isRepeated) 
      : _key(key),
        _isRepeated(isRepeated) {
    }

    /// @brief Get the key that was pressed.
    inline int GetKey() const {
      return _key;
    }

    /// @brief Check if the key has been pressed multiple times.
    inline bool IsRepeated() const {
      return _isRepeated;
    }
  private:
    int _key;
    bool _isRepeated;
};

/// @brief An event representing a key release.
class KeyReleasedEvent : public Event {
  public:
    IMPL_BUS(KeyReleasedEvent);

    KeyReleasedEvent(int key)
      : _key(key) {
    }

    /// @brief Get the key that was pressed.
    inline int GetKey() const {
      return _key;
    }

  private:
    int _key;
};

} // namespace point

#endif
