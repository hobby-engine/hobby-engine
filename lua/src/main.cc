#include <iostream>

#include "point.hh"

int main() {
  auto window = point::Window();

  while (!window.ShouldClose()) {
    window.Update();
  }

  return 0;
}
