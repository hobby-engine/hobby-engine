#include <iostream>

#include "point.h"

int main() {
  auto window = point::Window();

  while (!window.ShouldClose()) {
    window.Update();
  }

  return 0;
}
