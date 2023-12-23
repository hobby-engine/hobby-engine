#ifndef _POINT_EVENT_H
#define _POINT_EVENT_H

#include <functional>

namespace point {

#define IMPL_BUS(type) \
  static EventBus<type> bus; \
  static inline void AddCallback(std::function<bool(const type& event)> f) { \
    bus.AddCallback(f); \
  } \
  static inline void PushEvent(type& event) { \
    bus.PushEvent(event); \
  }

class Event {
public:
  bool IsHandled = false;
};

template <class T = Event>
class EventBus {
    using CallbackFn = std::function<bool(const T& event)>;
  public:
    EventBus() {
      _callbacks = std::vector<CallbackFn>();
    }
    
    void AddCallback(CallbackFn callback) {
      _callbacks.push_back(callback);
    }
    
    void PushEvent(T& event) {
      for (auto&& callback : _callbacks) {
        event.IsHandled = callback(event);
        if (event.IsHandled) {
          break;
        }
      }
    }
  private:
    std::vector<CallbackFn> _callbacks;
};

} // namespace point

#endif

