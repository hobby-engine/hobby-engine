#include "draw.hh"

#include "SDL2/SDL.h"
#include "SDL2/SDL_render.h"

namespace Hobby::Draw {

struct DrawState {
  DrawState(Window& window)
    : CurrentColor(1, 1, 1),
      DrawWindow(window),
      Renderer(window._renderer) {
  }

  Color CurrentColor;

  DrawState* Enclosing = nullptr;
  Window& DrawWindow;
  SDL_Renderer* Renderer;
};

DrawState* Current;

void Initialize(Window& window) {
  Current = new DrawState(window);
  Texture::Initialize(window);
}

void PushState() {
  DrawState* previous = Current;
  Current = new DrawState(previous->DrawWindow);
  Current->Enclosing = previous;
}

void PopState() {
  DrawState* previous = Current;
  Current = Current->Enclosing;
  delete previous;
}

void SetColor(const Color& color) {
  Current->CurrentColor = color;
  SDL_SetRenderDrawColor(
    Current->Renderer,
    color.GetR8(), color.GetG8(), color.GetB8(), color.GetA8());
}

void Clear() {
  SDL_RenderClear(Current->Renderer);
}

void Present() {
  SDL_RenderPresent(Current->Renderer);
}

void Line(Vec2 start, Vec2 end) {
  SDL_RenderDrawLine(Current->Renderer, start.X, start.Y, end.X, end.Y);
}

void Rectangle(Vec2 position, Vec2 size) {
  SDL_Rect rect = {
    static_cast<int>(position.X), static_cast<int>(position.Y),
    static_cast<int>(size.X), static_cast<int>(size.Y),
  };

  SDL_RenderDrawRect(Current->Renderer, &rect);
}

void FilledRectangle(Vec2 position, Vec2 size) {
  SDL_Rect rect = {
    static_cast<int>(position.X), static_cast<int>(position.Y),
    static_cast<int>(size.X), static_cast<int>(size.Y),
  };

  SDL_RenderFillRect(Current->Renderer, &rect);
}

void DrawTexture(const Texture& texture, Vec2 position) {
  texture.Draw(position);
}

} // namespace Hobby::Draw
