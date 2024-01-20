#include "input.hh"

#include "SDL2/SDL.h"

namespace Hobby::Input {

static SDL_KeyCode ConvertToSDL(KeyType key);

bool IsKeyDown(KeyType key) {
  const uint8_t* state = SDL_GetKeyboardState(nullptr);
  SDL_Scancode scancode = SDL_GetScancodeFromKey(ConvertToSDL(key));
  return state[scancode] ? true : false;
}

static SDL_KeyCode ConvertToSDL(KeyType key) {
  switch (key) {
    case KeyType::UNKNOWN: return SDLK_UNKNOWN;
    case KeyType::F1: return SDLK_F1;
    case KeyType::F2: return SDLK_F2;
    case KeyType::F3: return SDLK_F3;
    case KeyType::F4: return SDLK_F4;
    case KeyType::F5: return SDLK_F5;
    case KeyType::F6: return SDLK_F6;
    case KeyType::F7: return SDLK_F7;
    case KeyType::F8: return SDLK_F8;
    case KeyType::F9: return SDLK_F9;
    case KeyType::F10: return SDLK_F10;
    case KeyType::F11: return SDLK_F11;
    case KeyType::F12: return SDLK_F12;
    case KeyType::F13: return SDLK_F13;
    case KeyType::F14: return SDLK_F14;
    case KeyType::F15: return SDLK_F15;
    case KeyType::F16: return SDLK_F16;
    case KeyType::F17: return SDLK_F17;
    case KeyType::F18: return SDLK_F18;
    case KeyType::F19: return SDLK_F19;
    case KeyType::F20: return SDLK_F20;
    case KeyType::F21: return SDLK_F21;
    case KeyType::F22: return SDLK_F22;
    case KeyType::F23: return SDLK_F23;
    case KeyType::F24: return SDLK_F24;
    case KeyType::ESCAPE: return SDLK_ESCAPE;
    case KeyType::BACKSPACE: return SDLK_BACKSPACE;
    case KeyType::TAB: return SDLK_TAB;
    case KeyType::CAPSLOCK: return SDLK_CAPSLOCK;
    case KeyType::RETURN: return SDLK_RETURN;
    case KeyType::UP: return SDLK_UP;
    case KeyType::DOWN: return SDLK_DOWN;
    case KeyType::LEFT: return SDLK_LEFT;
    case KeyType::RIGHT: return SDLK_RIGHT;
    case KeyType::PRINTSCREEN: return SDLK_PRINTSCREEN;
    case KeyType::SCROLLLOCK: return SDLK_SCROLLLOCK;
    case KeyType::INSERT: return SDLK_INSERT;
    case KeyType::HOME: return SDLK_HOME;
    case KeyType::PAGEUP: return SDLK_PAGEUP;
    case KeyType::PAGEDOWN: return SDLK_PAGEDOWN;
    case KeyType::END: return SDLK_END;
    case KeyType::LGUI: return SDLK_LGUI;
    case KeyType::RGUI: return SDLK_RGUI;
    case KeyType::LSHIFT: return SDLK_LSHIFT;
    case KeyType::RSHIFT: return SDLK_RSHIFT;
    case KeyType::LCTRL: return SDLK_LCTRL;
    case KeyType::RCTRL: return SDLK_RCTRL;
    case KeyType::LALT: return SDLK_LALT;
    case KeyType::RALT: return SDLK_RALT;
    case KeyType::KP_ENTER: return SDLK_KP_ENTER;
    case KeyType::DELETE: return SDLK_DELETE;
    case KeyType::KP_0: return SDLK_KP_0;
    case KeyType::KP_1: return SDLK_KP_1;
    case KeyType::KP_2: return SDLK_KP_2;
    case KeyType::KP_3: return SDLK_KP_3;
    case KeyType::KP_4: return SDLK_KP_4;
    case KeyType::KP_5: return SDLK_KP_5;
    case KeyType::KP_6: return SDLK_KP_6;
    case KeyType::KP_7: return SDLK_KP_7;
    case KeyType::KP_8: return SDLK_KP_8;
    case KeyType::KP_9: return SDLK_KP_9;
    case KeyType::KP_DIVIDE: return SDLK_KP_DIVIDE;
    case KeyType::KP_MULTIPLY: return SDLK_KP_MULTIPLY;
    case KeyType::KP_MINUS: return SDLK_KP_MINUS;
    case KeyType::KP_PLUS: return SDLK_KP_PLUS;
    case KeyType::K0: return SDLK_0;
    case KeyType::K1: return SDLK_1;
    case KeyType::K2: return SDLK_2;
    case KeyType::K3: return SDLK_3;
    case KeyType::K4: return SDLK_4;
    case KeyType::K5: return SDLK_5;
    case KeyType::K6: return SDLK_6;
    case KeyType::K7: return SDLK_7;
    case KeyType::K8: return SDLK_8;
    case KeyType::K9: return SDLK_9;
    case KeyType::A: return SDLK_a;
    case KeyType::B: return SDLK_b;
    case KeyType::C: return SDLK_c;
    case KeyType::D: return SDLK_d;
    case KeyType::E: return SDLK_e;
    case KeyType::F: return SDLK_f;
    case KeyType::G: return SDLK_g;
    case KeyType::H: return SDLK_h;
    case KeyType::I: return SDLK_i;
    case KeyType::J: return SDLK_j;
    case KeyType::K: return SDLK_k;
    case KeyType::L: return SDLK_l;
    case KeyType::M: return SDLK_m;
    case KeyType::N: return SDLK_n;
    case KeyType::O: return SDLK_o;
    case KeyType::P: return SDLK_p;
    case KeyType::Q: return SDLK_q;
    case KeyType::R: return SDLK_r;
    case KeyType::S: return SDLK_s;
    case KeyType::T: return SDLK_t;
    case KeyType::U: return SDLK_u;
    case KeyType::V: return SDLK_v;
    case KeyType::W: return SDLK_w;
    case KeyType::X: return SDLK_x;
    case KeyType::Y: return SDLK_y;
    case KeyType::Z: return SDLK_z;
    case KeyType::SPACE: return SDLK_SPACE;
    case KeyType::COMMA: return SDLK_COMMA;
    case KeyType::PERIOD: return SDLK_PERIOD;
    case KeyType::SLASH: return SDLK_SLASH;
    case KeyType::SEMICOLON: return SDLK_SEMICOLON;
    case KeyType::QUOTE: return SDLK_QUOTE;
    case KeyType::LEFTBRACKET: return SDLK_LEFTBRACKET;
    case KeyType::RIGHTBRACKET: return SDLK_RIGHTBRACKET;
    case KeyType::BACKSLASH: return SDLK_BACKSLASH;
    case KeyType::BACKQUOTE: return SDLK_BACKQUOTE;
    case KeyType::MINUS: return SDLK_MINUS;
    case KeyType::EQUALS: return SDLK_EQUALS;
    default: break;
  }

  return SDLK_UNKNOWN;
}

} // namespace Hobby::Input
