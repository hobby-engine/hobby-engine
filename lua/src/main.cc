#include <iostream>

#include "event/key.hh"
#include "point.hh"

bool showColor = true;

bool OnKeyPressed(const point::KeyReleasedEvent& event) {
  showColor = !showColor;

  if (showColor) {
    point::Graphics::SetBackgroundColor(point::Color(1, 0.5, 1));
  } else {
    point::Graphics::SetBackgroundColor(point::Color(0, 0, 0));
  }
  
  return false;
}

int main() {
  auto window = point::Window();
  auto graphicsState = point::Graphics(window);

  point::Graphics::SetBackgroundColor(point::Color(1, 0.5, 1));
  point::KeyReleasedEvent::AddCallback(OnKeyPressed);

  while (!window.ShouldClose()) {
    window.Update();

    point::Graphics::Clear();
    point::Graphics::Present();
  }

  return 0;
}
