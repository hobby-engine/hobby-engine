#include <iostream>

#include "point.hh"

int main() {
  auto window = point::Window();
  auto graphicsState = point::Graphics(window);

  point::Graphics::SetBackgroundColor(point::Color(1, 0.5, 1));

  while (!window.ShouldClose()) {
    window.Update();

    point::Graphics::Clear();
    point::Graphics::Present();
  }

  return 0;
}
