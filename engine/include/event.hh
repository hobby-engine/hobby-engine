#ifndef _HOBBY_EVENT_H
#define _HOBBY_EVENT_H

#include <functional>

namespace Hobby {

#define IMPL_BUS(type) \
  static EventBus<type> bus; \
  static inline void AddCallback(std::function<bool(const type& event)> f) { \
    bus.AddCallback(f); \
  } \
  static inline void PushEvent(type& event) { \
    bus.PushEvent(event); \
  }

/// @brief Base class for all events.
class Event {
public:
  /// Whether or not this event has been handled yet.
  bool IsHandled = false;
};

/// @brief Keeps track of event callbacks and calls them when an
/// event is given.
///
/// Events are called on demand, so when a key is pressed, it calls every
/// callback immediately. TODO: Make an event queue instead of calling
/// immediately.
template <class T = Event>
class EventBus {
    using CallbackFn = std::function<bool(const T& event)>;
  public:
    EventBus() {
      _callbacks = std::vector<CallbackFn>();
    }
    
    /// @brief Add a callback to the event bus.
    /// @param callback The callback.
    void AddCallback(CallbackFn callback) {
      _callbacks.push_back(callback);
    }
    
    /// @brief Call all callbacks with the new event.
    /// @param event The new event.
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

} // namespace Hobby

#endif

