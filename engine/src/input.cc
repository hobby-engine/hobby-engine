#include "input.hh"

#include "SDL2/SDL.h"
#include "SDL2/SDL_keycode.h"

namespace point::input {

static SDL_KeyCode ConvertToSDL(Key key);

bool IsKeyDown(Key key) {
	const uint8_t* state = SDL_GetKeyboardState(nullptr);
  SDL_Scancode scancode = SDL_GetScancodeFromKey(ConvertToSDL(key));
  return state[scancode] ? true : false;
}

bool IsMouseDown(int button) {
	uint32_t state = SDL_GetMouseState(nullptr, nullptr);
  if (button <= 0)
    return false;

  switch (button) {
    case 2:
      button = SDL_BUTTON_RIGHT;
      break;
    case 3:
      button = SDL_BUTTON_MIDDLE;
      break;
  }

  return state & SDL_BUTTON(button) ? true : false;
}

Vec2 GetMousePosition() {
  int x, y;
  SDL_GetMouseState(&x, &y);
  return Vec2(x, y);
}

static SDL_KeyCode ConvertToSDL(Key key) {
  switch (key) {
    case Key::UNKNOWN: return SDLK_UNKNOWN;
    case Key::F1: return SDLK_F1;
    case Key::F2: return SDLK_F2;
    case Key::F3: return SDLK_F3;
    case Key::F4: return SDLK_F4;
    case Key::F5: return SDLK_F5;
    case Key::F6: return SDLK_F6;
    case Key::F7: return SDLK_F7;
    case Key::F8: return SDLK_F8;
    case Key::F9: return SDLK_F9;
    case Key::F10: return SDLK_F10;
    case Key::F11: return SDLK_F11;
    case Key::F12: return SDLK_F12;
    case Key::F13: return SDLK_F13;
    case Key::F14: return SDLK_F14;
    case Key::F15: return SDLK_F15;
    case Key::F16: return SDLK_F16;
    case Key::F17: return SDLK_F17;
    case Key::F18: return SDLK_F18;
    case Key::F19: return SDLK_F19;
    case Key::F20: return SDLK_F20;
    case Key::F21: return SDLK_F21;
    case Key::F22: return SDLK_F22;
    case Key::F23: return SDLK_F23;
    case Key::F24: return SDLK_F24;
    case Key::ESCAPE: return SDLK_ESCAPE;
    case Key::BACKSPACE: return SDLK_BACKSPACE;
    case Key::TAB: return SDLK_TAB;
    case Key::CAPS_LOCK: return SDLK_CAPSLOCK;
    case Key::ENTER: return SDLK_RETURN;
    case Key::UP: return SDLK_UP;
    case Key::DOWN: return SDLK_DOWN;
    case Key::LEFT: return SDLK_LEFT;
    case Key::RIGHT: return SDLK_RIGHT;
    case Key::PRINT_SCREEN: return SDLK_PRINTSCREEN;
    case Key::SCROLL_LOCK: return SDLK_SCROLLLOCK;
    case Key::INSERT: return SDLK_INSERT;
    case Key::HOME: return SDLK_HOME;
    case Key::PAGE_UP: return SDLK_PAGEUP;
    case Key::PAGE_DOWN: return SDLK_PAGEDOWN;
    case Key::DELETE: return SDLK_DELETE;
    case Key::END: return SDLK_END;
    case Key::LSUPER: return SDLK_LGUI;
    case Key::RSUPER: return SDLK_RGUI;
    case Key::LSHIFT: return SDLK_LSHIFT;
    case Key::RSHIFT: return SDLK_RSHIFT;
    case Key::LCTRL: return SDLK_LCTRL;
    case Key::RCTRL: return SDLK_RCTRL;
    case Key::LALT: return SDLK_LALT;
    case Key::RALT: return SDLK_RALT;
    case Key::KP_ENTER: return SDLK_KP_ENTER;
    case Key::KP_DELETE: return SDLK_DELETE;
    case Key::KP_0: return SDLK_KP_0;
    case Key::KP_1: return SDLK_KP_1;
    case Key::KP_2: return SDLK_KP_2;
    case Key::KP_3: return SDLK_KP_3;
    case Key::KP_4: return SDLK_KP_4;
    case Key::KP_5: return SDLK_KP_5;
    case Key::KP_6: return SDLK_KP_6;
    case Key::KP_7: return SDLK_KP_7;
    case Key::KP_8: return SDLK_KP_8;
    case Key::KP_9: return SDLK_KP_9;
    case Key::KP_SLASH: return SDLK_KP_DIVIDE;
    case Key::KP_STAR: return SDLK_KP_MULTIPLY;
    case Key::KP_MINUS: return SDLK_KP_MINUS;
    case Key::KP_PLUS: return SDLK_KP_PLUS;
    case Key::K0: return SDLK_0;
    case Key::K1: return SDLK_1;
    case Key::K2: return SDLK_2;
    case Key::K3: return SDLK_3;
    case Key::K4: return SDLK_4;
    case Key::K5: return SDLK_5;
    case Key::K6: return SDLK_6;
    case Key::K7: return SDLK_7;
    case Key::K8: return SDLK_8;
    case Key::K9: return SDLK_9;
    case Key::A: return SDLK_a;
    case Key::B: return SDLK_b;
    case Key::C: return SDLK_c;
    case Key::D: return SDLK_d;
    case Key::E: return SDLK_e;
    case Key::F: return SDLK_f;
    case Key::G: return SDLK_g;
    case Key::H: return SDLK_h;
    case Key::I: return SDLK_i;
    case Key::J: return SDLK_j;
    case Key::K: return SDLK_k;
    case Key::L: return SDLK_l;
    case Key::M: return SDLK_m;
    case Key::N: return SDLK_n;
    case Key::O: return SDLK_o;
    case Key::P: return SDLK_p;
    case Key::Q: return SDLK_q;
    case Key::R: return SDLK_r;
    case Key::S: return SDLK_s;
    case Key::T: return SDLK_t;
    case Key::U: return SDLK_u;
    case Key::V: return SDLK_v;
    case Key::W: return SDLK_w;
    case Key::X: return SDLK_x;
    case Key::Y: return SDLK_y;
    case Key::Z: return SDLK_z;
    case Key::SPACE: return SDLK_SPACE;
    case Key::COMMA: return SDLK_COMMA;
    case Key::DOT: return SDLK_PERIOD;
    case Key::FORWARD_SLASH: return SDLK_SLASH;
    case Key::SEMICOLON: return SDLK_SEMICOLON;
    case Key::QUOTE: return SDLK_QUOTE;
    case Key::LBRACKET: return SDLK_LEFTBRACKET;
    case Key::RBRACKET: return SDLK_RIGHTBRACKET;
    case Key::BACK_SLASH: return SDLK_BACKSLASH;
    case Key::TICK: return SDLK_BACKQUOTE;
    case Key::MINUS: return SDLK_MINUS;
    case Key::EQUALS: return SDLK_EQUALS;
    default: break;
  }

  return SDLK_UNKNOWN;
}

} // namespace point::input
