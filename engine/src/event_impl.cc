#include "event/key.hh"
#include "event/mouse.hh"

namespace Hobby {

#define IMPL(type) \
  EventBus<type> type::bus = EventBus<type>();

IMPL(KeyPressedEvent);
IMPL(KeyReleasedEvent);
IMPL(MousePressedEvent);
IMPL(MouseReleasedEvent);
IMPL(MouseMovedEvent);
IMPL(MouseScrolledEvent);

} // namespace Hobby
