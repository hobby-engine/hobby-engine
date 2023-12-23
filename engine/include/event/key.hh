#ifndef _POINT_EVENT_KEY_H
#define _POINT_EVENT_KEY_H

#include "event.hh"

namespace point {

class KeyPressedEvent : public Event {
  public:
    IMPL_BUS(KeyPressedEvent);
    
    KeyPressedEvent(int key, bool isRepeated) 
      : _key(key),
        _isRepeated(isRepeated) {
    }

    inline int GetKey() const {
      return _key;
    }

    inline bool IsRepeated() const {
      return _isRepeated;
    }
  private:
    int _key;
    bool _isRepeated;
};

class KeyReleasedEvent : public Event {
  public:
    IMPL_BUS(KeyReleasedEvent);

    KeyReleasedEvent(int key)
      : _key(key) {
    }

    inline int GetKey() const {
      return _key;
    }

  private:
    int _key;
};

} // namespace point

#endif
