#include <iostream>
#include <cmath>

#include "event/mouse.hh"
#include "point.hh"

bool isPink = true;

bool OnKeyPressed(const point::KeyPressedEvent& event) {
  if (event.GetKey() == point::input::Key::KP_ENTER) {
    isPink = !isPink;

    if (isPink) {
      point::Graphics::SetBackgroundColor(point::Color(1, 0.5, 1));
    } else {
      point::Graphics::SetBackgroundColor(point::Color(0, 0, 0));
    }

    return true;
  }

  return false;
}

float red = 0;

bool OnMouseScrolled(const point::MouseScrolledEvent& event) {
  std::cout << event.GetScroll().Y << std::endl;
  red += static_cast<double>(event.GetScroll().Y) / 20;
  red = fmin(fmax(red, 0), 1);
  point::Graphics::SetBackgroundColor(point::Color(red, 0, 0));
  return false;
}

int main() {
  auto window = point::Window();
  point::Graphics::Initialize(window);

  // point::KeyPressedEvent::AddCallback(OnKeyPressed);
  point::MouseScrolledEvent::AddCallback(OnMouseScrolled);

  point::Graphics::SetBackgroundColor(point::Color(1, 0.5, 1));

  while (!window.ShouldClose()) {
    window.Update();

    point::Graphics::Clear();
    point::Graphics::Present();
  }

  return 0;
}
