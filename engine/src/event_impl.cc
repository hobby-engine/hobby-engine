#include "event/key.hh"

namespace point {

EventBus<KeyPressedEvent>  KeyPressedEvent::bus  = EventBus<KeyPressedEvent>();
EventBus<KeyReleasedEvent> KeyReleasedEvent::bus = EventBus<KeyReleasedEvent>();

} // namespace point
