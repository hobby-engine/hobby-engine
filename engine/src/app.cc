#include "app.hh"
#include "color.hh"
#include "draw.hh"
#include "time.hh"

namespace Hobby {

App::App() {
  WindowSettings windowSettings;
  Initialize(windowSettings);
}

App::App(const WindowSettings& windowSettings) {
  Initialize(windowSettings);
}

void App::Initialize(const WindowSettings& windowSettings) {
  _window = new Window(windowSettings);
  Draw::Initialize(*_window);
}

void App::Run() {
  while (!_window->ShouldClose()) {
    Time::Step();
    _window->Update();

    Step();

    Draw::SetColor(Color(0, 0, 0));
    Draw::Clear();
    Draw::SetColor(Color(1, 1, 1));
    Draw();
    Draw::Present();
  }
}

} // namespace Hobby
