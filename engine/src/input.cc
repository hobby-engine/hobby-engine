#include "input.hh"

#include "SDL2/SDL.h"
#include "SDL2/SDL_keycode.h"

namespace Hobby::Input {

static SDL_KeyCode PointToSDL(Key key);

bool IsKeyDown(Key key) {
	const uint8_t* state = SDL_GetKeyboardState(nullptr);
  SDL_Scancode scancode = SDL_GetScancodeFromKey(PointToSDL(key));
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

static SDL_KeyCode PointToSDL(Key key) {
  switch (key) {
    case Key::UNKNOWN:               return SDLK_UNKNOWN;
    case Key::RETURN:                return SDLK_RETURN;
    case Key::ESCAPE:                return SDLK_ESCAPE;
    case Key::BACKSPACE:             return SDLK_BACKSPACE;
    case Key::TAB:                   return SDLK_TAB;
    case Key::SPACE:                 return SDLK_SPACE;
    case Key::EXCLAIM:               return SDLK_EXCLAIM;
    case Key::QUOTEDBL:              return SDLK_QUOTEDBL;
    case Key::HASH:                  return SDLK_HASH;
    case Key::PERCENT:               return SDLK_PERCENT;
    case Key::DOLLAR:                return SDLK_DOLLAR;
    case Key::AMPERSAND:             return SDLK_AMPERSAND;
    case Key::QUOTE:                 return SDLK_QUOTE;
    case Key::LEFTPAREN:             return SDLK_LEFTPAREN;
    case Key::RIGHTPAREN:            return SDLK_RIGHTPAREN;
    case Key::ASTERISK:              return SDLK_ASTERISK;
    case Key::PLUS:                  return SDLK_PLUS;
    case Key::COMMA:                 return SDLK_COMMA;
    case Key::MINUS:                 return SDLK_MINUS;
    case Key::PERIOD:                return SDLK_PERIOD;
    case Key::SLASH:                 return SDLK_SLASH;
    case Key::K0:                    return SDLK_0;
    case Key::K1:                    return SDLK_1;
    case Key::K2:                    return SDLK_2;
    case Key::K3:                    return SDLK_3;
    case Key::K4:                    return SDLK_4;
    case Key::K5:                    return SDLK_5;
    case Key::K6:                    return SDLK_6;
    case Key::K7:                    return SDLK_7;
    case Key::K8:                    return SDLK_8;
    case Key::K9:                    return SDLK_9;
    case Key::COLON:                 return SDLK_COLON;
    case Key::SEMICOLON:             return SDLK_SEMICOLON;
    case Key::LESS:                  return SDLK_LESS;
    case Key::EQUALS:                return SDLK_EQUALS;
    case Key::GREATER:               return SDLK_GREATER;
    case Key::QUESTION:              return SDLK_QUESTION;
    case Key::AT:                    return SDLK_AT;
    case Key::LEFTBRACKET:           return SDLK_LEFTBRACKET;
    case Key::BACKSLASH:             return SDLK_BACKSLASH;
    case Key::RIGHTBRACKET:          return SDLK_RIGHTBRACKET;
    case Key::CARET:                 return SDLK_CARET;
    case Key::UNDERSCORE:            return SDLK_UNDERSCORE;
    case Key::BACKQUOTE:             return SDLK_BACKQUOTE;
    case Key::A:                     return SDLK_a;
    case Key::B:                     return SDLK_b;
    case Key::C:                     return SDLK_c;
    case Key::D:                     return SDLK_d;
    case Key::E:                     return SDLK_e;
    case Key::F:                     return SDLK_f;
    case Key::G:                     return SDLK_g;
    case Key::H:                     return SDLK_h;
    case Key::I:                     return SDLK_i;
    case Key::J:                     return SDLK_j;
    case Key::K:                     return SDLK_k;
    case Key::L:                     return SDLK_l;
    case Key::M:                     return SDLK_m;
    case Key::N:                     return SDLK_n;
    case Key::O:                     return SDLK_o;
    case Key::P:                     return SDLK_p;
    case Key::Q:                     return SDLK_q;
    case Key::R:                     return SDLK_r;
    case Key::S:                     return SDLK_s;
    case Key::T:                     return SDLK_t;
    case Key::U:                     return SDLK_u;
    case Key::V:                     return SDLK_v;
    case Key::W:                     return SDLK_w;
    case Key::X:                     return SDLK_x;
    case Key::Y:                     return SDLK_y;
    case Key::Z:                     return SDLK_z;
    case Key::CAPSLOCK:              return SDLK_CAPSLOCK;
    case Key::F1:                    return SDLK_F1;
    case Key::F2:                    return SDLK_F2;
    case Key::F3:                    return SDLK_F3;
    case Key::F4:                    return SDLK_F4;
    case Key::F5:                    return SDLK_F5;
    case Key::F6:                    return SDLK_F6;
    case Key::F7:                    return SDLK_F7;
    case Key::F8:                    return SDLK_F8;
    case Key::F9:                    return SDLK_F9;
    case Key::F10:                   return SDLK_F10;
    case Key::F11:                   return SDLK_F11;
    case Key::F12:                   return SDLK_F12;
    case Key::PRINTSCREEN:           return SDLK_PRINTSCREEN;
    case Key::SCROLLLOCK:            return SDLK_SCROLLLOCK;
    case Key::PAUSE:                 return SDLK_PAUSE;
    case Key::INSERT:                return SDLK_INSERT;
    case Key::HOME:                  return SDLK_HOME;
    case Key::PAGEUP:                return SDLK_PAGEUP;
    case Key::DELETE:                return SDLK_DELETE;
    case Key::END:                   return SDLK_END;
    case Key::PAGEDOWN:              return SDLK_PAGEDOWN;
    case Key::RIGHT:                 return SDLK_RIGHT;
    case Key::LEFT:                  return SDLK_LEFT;
    case Key::DOWN:                  return SDLK_DOWN;
    case Key::UP:                    return SDLK_UP;
    case Key::NUMLOCKCLEAR:          return SDLK_NUMLOCKCLEAR;
    case Key::KP_DIVIDE:             return SDLK_KP_DIVIDE;
    case Key::KP_MULTIPLY:           return SDLK_KP_MULTIPLY;
    case Key::KP_MINUS:              return SDLK_KP_MINUS;
    case Key::KP_PLUS:               return SDLK_KP_PLUS;
    case Key::KP_ENTER:              return SDLK_KP_ENTER;
    case Key::KP_1:                  return SDLK_KP_1;
    case Key::KP_2:                  return SDLK_KP_2;
    case Key::KP_3:                  return SDLK_KP_3;
    case Key::KP_4:                  return SDLK_KP_4;
    case Key::KP_5:                  return SDLK_KP_5;
    case Key::KP_6:                  return SDLK_KP_6;
    case Key::KP_7:                  return SDLK_KP_7;
    case Key::KP_8:                  return SDLK_KP_8;
    case Key::KP_9:                  return SDLK_KP_9;
    case Key::KP_0:                  return SDLK_KP_0;
    case Key::KP_PERIOD:             return SDLK_KP_PERIOD;
    case Key::APPLICATION:           return SDLK_APPLICATION;
    case Key::POWER:                 return SDLK_POWER;
    case Key::KP_EQUALS:             return SDLK_KP_EQUALS;
    case Key::F13:                   return SDLK_F13;
    case Key::F14:                   return SDLK_F14;
    case Key::F15:                   return SDLK_F15;
    case Key::F16:                   return SDLK_F16;
    case Key::F17:                   return SDLK_F17;
    case Key::F18:                   return SDLK_F18;
    case Key::F19:                   return SDLK_F19;
    case Key::F20:                   return SDLK_F20;
    case Key::F21:                   return SDLK_F21;
    case Key::F22:                   return SDLK_F22;
    case Key::F23:                   return SDLK_F23;
    case Key::F24:                   return SDLK_F24;
    case Key::EXECUTE:               return SDLK_EXECUTE;
    case Key::HELP:                  return SDLK_HELP;
    case Key::MENU:                  return SDLK_MENU;
    case Key::SELECT:                return SDLK_SELECT;
    case Key::STOP:                  return SDLK_STOP;
    case Key::AGAIN:                 return SDLK_AGAIN;
    case Key::UNDO:                  return SDLK_UNDO;
    case Key::CUT:                   return SDLK_CUT;
    case Key::COPY:                  return SDLK_COPY;
    case Key::PASTE:                 return SDLK_PASTE;
    case Key::FIND:                  return SDLK_FIND;
    case Key::MUTE:                  return SDLK_MUTE;
    case Key::VOLUMEUP:              return SDLK_VOLUMEUP;
    case Key::VOLUMEDOWN:            return SDLK_VOLUMEDOWN;
    case Key::KP_COMMA:              return SDLK_KP_COMMA;
    case Key::KP_EQUALSAS400:        return SDLK_KP_EQUALSAS400;
    case Key::ALTERASE:              return SDLK_ALTERASE;
    case Key::SYSREQ:                return SDLK_SYSREQ;
    case Key::CANCEL:                return SDLK_CANCEL;
    case Key::CLEAR:                 return SDLK_CLEAR;
    case Key::PRIOR:                 return SDLK_PRIOR;
    case Key::RETURN2:               return SDLK_RETURN2;
    case Key::SEPARATOR:             return SDLK_SEPARATOR;
    case Key::OUT:                   return SDLK_OUT;
    case Key::OPER:                  return SDLK_OPER;
    case Key::CLEARAGAIN:            return SDLK_CLEARAGAIN;
    case Key::CRSEL:                 return SDLK_CRSEL;
    case Key::EXSEL:                 return SDLK_EXSEL;
    case Key::KP_00:                 return SDLK_KP_00;
    case Key::KP_000:                return SDLK_KP_000;
    case Key::THOUSANDSSEPARATOR:    return SDLK_THOUSANDSSEPARATOR;
    case Key::DECIMALSEPARATOR:      return SDLK_DECIMALSEPARATOR;
    case Key::CURRENCYUNIT:          return SDLK_CURRENCYUNIT;
    case Key::CURRENCYSUBUNIT:       return SDLK_CURRENCYSUBUNIT;
    case Key::KP_LEFTPAREN:          return SDLK_KP_LEFTPAREN;
    case Key::KP_RIGHTPAREN:         return SDLK_KP_RIGHTPAREN;
    case Key::KP_LEFTBRACE:          return SDLK_KP_LEFTBRACE;
    case Key::KP_RIGHTBRACE:         return SDLK_KP_RIGHTBRACE;
    case Key::KP_TAB:                return SDLK_KP_TAB;
    case Key::KP_BACKSPACE:          return SDLK_KP_BACKSPACE;
    case Key::KP_A:                  return SDLK_KP_A;
    case Key::KP_B:                  return SDLK_KP_B;
    case Key::KP_C:                  return SDLK_KP_C;
    case Key::KP_D:                  return SDLK_KP_D;
    case Key::KP_E:                  return SDLK_KP_E;
    case Key::KP_F:                  return SDLK_KP_F;
    case Key::KP_XOR:                return SDLK_KP_XOR;
    case Key::KP_POWER:              return SDLK_KP_POWER;
    case Key::KP_PERCENT:            return SDLK_KP_PERCENT;
    case Key::KP_LESS:               return SDLK_KP_LESS;
    case Key::KP_GREATER:            return SDLK_KP_GREATER;
    case Key::KP_AMPERSAND:          return SDLK_KP_AMPERSAND;
    case Key::KP_DBLAMPERSAND:       return SDLK_KP_DBLAMPERSAND;
    case Key::KP_VERTICALBAR:        return SDLK_KP_VERTICALBAR;
    case Key::KP_DBLVERTICALBAR:     return SDLK_KP_DBLVERTICALBAR;
    case Key::KP_COLON:              return SDLK_KP_COLON;
    case Key::KP_HASH:               return SDLK_KP_HASH;
    case Key::KP_SPACE:              return SDLK_KP_SPACE;
    case Key::KP_AT:                 return SDLK_KP_AT;
    case Key::KP_EXCLAM:             return SDLK_KP_EXCLAM;
    case Key::KP_MEMSTORE:           return SDLK_KP_MEMSTORE;
    case Key::KP_MEMRECALL:          return SDLK_KP_MEMRECALL;
    case Key::KP_MEMCLEAR:           return SDLK_KP_MEMCLEAR;
    case Key::KP_MEMADD:             return SDLK_KP_MEMADD;
    case Key::KP_MEMSUBTRACT:        return SDLK_KP_MEMSUBTRACT;
    case Key::KP_MEMMULTIPLY:        return SDLK_KP_MEMMULTIPLY;
    case Key::KP_MEMDIVIDE:          return SDLK_KP_MEMDIVIDE;
    case Key::KP_PLUSMINUS:          return SDLK_KP_PLUSMINUS;
    case Key::KP_CLEAR:              return SDLK_KP_CLEAR;
    case Key::KP_CLEARENTRY:         return SDLK_KP_CLEARENTRY;
    case Key::KP_BINARY:             return SDLK_KP_BINARY;
    case Key::KP_OCTAL:              return SDLK_KP_OCTAL;
    case Key::KP_DECIMAL:            return SDLK_KP_DECIMAL;
    case Key::KP_HEXADECIMAL:        return SDLK_KP_HEXADECIMAL;
    case Key::LCTRL:                 return SDLK_LCTRL;
    case Key::LSHIFT:                return SDLK_LSHIFT;
    case Key::LALT:                  return SDLK_LALT;
    case Key::LGUI:                  return SDLK_LGUI;
    case Key::RCTRL:                 return SDLK_RCTRL;
    case Key::RSHIFT:                return SDLK_RSHIFT;
    case Key::RALT:                  return SDLK_RALT;
    case Key::RGUI:                  return SDLK_RGUI;
    case Key::MODE:                  return SDLK_MODE;
    case Key::AUDIONEXT:             return SDLK_AUDIONEXT;
    case Key::AUDIOPREV:             return SDLK_AUDIOPREV;
    case Key::AUDIOSTOP:             return SDLK_AUDIOSTOP;
    case Key::AUDIOPLAY:             return SDLK_AUDIOPLAY;
    case Key::AUDIOMUTE:             return SDLK_AUDIOMUTE;
    case Key::MEDIASELECT:           return SDLK_MEDIASELECT;
    case Key::WWW:                   return SDLK_WWW;
    case Key::MAIL:                  return SDLK_MAIL;
    case Key::CALCULATOR:            return SDLK_CALCULATOR;
    case Key::COMPUTER:              return SDLK_COMPUTER;
    case Key::AC_SEARCH:             return SDLK_AC_SEARCH;
    case Key::AC_HOME:               return SDLK_AC_HOME;
    case Key::AC_BACK:               return SDLK_AC_BACK;
    case Key::AC_FORWARD:            return SDLK_AC_FORWARD;
    case Key::AC_STOP:               return SDLK_AC_STOP;
    case Key::AC_REFRESH:            return SDLK_AC_REFRESH;
    case Key::AC_BOOKMARKS:          return SDLK_AC_BOOKMARKS;
    case Key::BRIGHTNESSDOWN:        return SDLK_BRIGHTNESSDOWN;
    case Key::BRIGHTNESSUP:          return SDLK_BRIGHTNESSUP;
    case Key::DISPLAYSWITCH:         return SDLK_DISPLAYSWITCH;
    case Key::KBDILLUMTOGGLE:        return SDLK_KBDILLUMTOGGLE;
    case Key::KBDILLUMDOWN:          return SDLK_KBDILLUMDOWN;
    case Key::KBDILLUMUP:            return SDLK_KBDILLUMUP;
    case Key::EJECT:                 return SDLK_EJECT;
    case Key::SLEEP:                 return SDLK_SLEEP;
    case Key::APP1:                  return SDLK_APP1;
    case Key::APP2:                  return SDLK_APP2;
    case Key::AUDIOREWIND:           return SDLK_AUDIOREWIND;
    case Key::AUDIOFASTFORWARD:      return SDLK_AUDIOFASTFORWARD;
    case Key::SOFTLEFT:              return SDLK_SOFTLEFT;
    case Key::SOFTRIGHT:             return SDLK_SOFTRIGHT;
    case Key::CALL:                  return SDLK_CALL;
    case Key::ENDCALL:               return SDLK_ENDCALL;
  }

  return SDLK_UNKNOWN;
}

} // namespace Hobby::input
