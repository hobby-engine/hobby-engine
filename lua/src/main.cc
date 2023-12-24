#include <iostream>

#include "input.hh"
#include "point.hh"

int main() {
  auto window = point::Window();
  point::Graphics::Initialize(window);

  while (!window.ShouldClose()) {
    window.Update();

    if (point::input::IsKeyDown(point::input::Key::KP_ENTER)) {
      point::Graphics::SetBackgroundColor(point::Color(1, 0.5, 1));
    } else {
      point::Graphics::SetBackgroundColor(point::Color(0, 0, 0));
    }

    point::Graphics::Clear();
    point::Graphics::Present();
  }

  return 0;
}
