#ifndef _HOBBY_DRAW_H
#define _HOBBY_DRAW_H

#include "color.hh"
#include "texture.hh"
#include "window.hh"

namespace Hobby::Draw {

enum class ColorBlending {
  ALPHA,
  ADD,
  MOD,
  MULTIPLY
};

void Initialize(Window& window);

void SetColor(const Color& color);
void PushState();
void PopState();
void Clear();
void Present();
void Line(Vec2 start, Vec2 end);
void Rectangle(Vec2 position, Vec2 size);
void FilledRectangle(Vec2 position, Vec2 size);
void DrawTexture(const Texture& texture, Vec2 position);

} // namespace Hobby::Draw

#endif // _HOBBY_DRAW_H
