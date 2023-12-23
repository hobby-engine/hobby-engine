#ifndef _POINT_DRAW_H
#define _POINT_DRAW_H

#include "color.hh"
#include "window.hh"

namespace point::draw {

void Initialize(Window& window);

void SetColor(Color color);
void SetBackgroundColor(Color color);
void Clear();
void Present();

} // namespace point::draw

#endif
