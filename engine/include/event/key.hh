#ifndef _HOBBY_EVENT_KEY_H
#define _HOBBY_EVENT_KEY_H

#include "event.hh"
#include "input_types.hh"

namespace Hobby {

/// @brief An event representing a key press.
class KeyPressedEvent : public Event {
  public:
    IMPL_BUS(KeyPressedEvent);
    
    KeyPressedEvent(Input::Key key, bool isRepeated) 
      : _key(key),
        _isRepeated(isRepeated) {
    }

    /// @brief Get the key that was pressed.
    inline Input::Key GetKey() const {
      return _key;
    }

    /// @brief Check if the key has been pressed multiple times.
    inline bool IsRepeated() const {
      return _isRepeated;
    }
  private:
    Input::Key _key;
    bool _isRepeated;
};

/// @brief An event representing a key release.
class KeyReleasedEvent : public Event {
  public:
    IMPL_BUS(KeyReleasedEvent);

    KeyReleasedEvent(Input::Key key)
      : _key(key) {
    }

    /// @brief Get the key that was pressed.
    inline Input::Key GetKey() const {
      return _key;
    }

  private:
    Input::Key _key;
};

} // namespace Hobby

#endif
