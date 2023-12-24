#include "window.hh"

#include <iostream>

#include "SDL2/SDL_video.h"
#include "glad/glad.h"
#include "SDL2/SDL.h"

#include "event/key.hh"
#include "vec2.hh"

namespace point {

static input::Key SDLToPoint(SDL_KeyCode key);

bool Window::_alreadyInstanced = false;

Window::Window() {
  WindowSettings settings = WindowSettings{};
  InitializeWindow(settings);
}

Window::Window(const WindowSettings& settings) {
  InitializeWindow(settings);
}

Window::~Window() {
  SDL_DestroyWindow(_window);
}

void Window::InitializeWindow(const WindowSettings& settings) {
  // Don't allow more than 1 window.
  if (_alreadyInstanced) {
    std::cerr
      << "Already have an instance of a window! Cannot have more than 1!\n"
      << std::endl;
    exit(1);
  }
  _alreadyInstanced = true;

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    exit(1);
  }

  // Create window
  uint32_t flags = 0;
  if (settings.Resizable) {
    flags |= SDL_WINDOW_RESIZABLE;
  }

  _window = SDL_CreateWindow(
    settings.Title,
    settings.X, settings.Y,
    settings.Width, settings.Height,
    flags | SDL_WINDOW_OPENGL);
  if (!_window) {
    std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
    exit(1);
  }

  _context = SDL_GL_CreateContext(_window);
  if (!_context) {
    SDL_DestroyWindow(_window);
    std::cerr << "Could not create context: " << SDL_GetError() << std::endl;
    exit(1);
  }

  SDL_GL_MakeCurrent(_window, _context);

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    SDL_DestroyWindow(_window);
    SDL_GL_DeleteContext(_context);
    std::cerr << "Failed to initialize glad." << std::endl;
    exit(1);
  }
}

const char* Window::GetTitle() const {
  return SDL_GetWindowTitle(_window);
}

void Window::SetTitle(const char* title) {
  SDL_SetWindowTitle(_window, title);
}

Vec2 Window::GetPosition() const {
  int x, y;
  SDL_GetWindowPosition(_window, &x, &y);
  return Vec2(x, y);
}

void Window::SetPosition(const Vec2& position) {
  SDL_SetWindowPosition(_window, position.X, position.Y);
}

Vec2 Window::GetSize() const {
  int w, h;
  SDL_GetWindowSize(_window, &w, &h);
  return Vec2(w, h);
}

void Window::SetSize(const Vec2& size) {
  SDL_SetWindowSize(_window, size.W, size.H);
}

void Window::Update() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        Close();
        break;
      case SDL_KEYDOWN: {
        KeyPressedEvent keyPressedEvent(
          SDLToPoint(static_cast<SDL_KeyCode>(event.key.keysym.sym)), event.key.repeat);
        KeyPressedEvent::PushEvent(keyPressedEvent);
        break;
      }
      case SDL_KEYUP: {
        KeyReleasedEvent keyReleasedEvent(
          SDLToPoint(static_cast<SDL_KeyCode>(event.key.keysym.sym)));
        KeyReleasedEvent::PushEvent(keyReleasedEvent);
        break;
      }
    }
  }
}

static input::Key SDLToPoint(SDL_KeyCode key) {
  switch (key) {
    case SDLK_UNKNOWN:               return input::Key::UNKNOWN;
    case SDLK_RETURN:                return input::Key::RETURN;
    case SDLK_ESCAPE:                return input::Key::ESCAPE;
    case SDLK_BACKSPACE:             return input::Key::BACKSPACE;
    case SDLK_TAB:                   return input::Key::TAB;
    case SDLK_SPACE:                 return input::Key::SPACE;
    case SDLK_EXCLAIM:               return input::Key::EXCLAIM;
    case SDLK_QUOTEDBL:              return input::Key::QUOTEDBL;
    case SDLK_HASH:                  return input::Key::HASH;
    case SDLK_PERCENT:               return input::Key::PERCENT;
    case SDLK_DOLLAR:                return input::Key::DOLLAR;
    case SDLK_AMPERSAND:             return input::Key::AMPERSAND;
    case SDLK_QUOTE:                 return input::Key::QUOTE;
    case SDLK_LEFTPAREN:             return input::Key::LEFTPAREN;
    case SDLK_RIGHTPAREN:            return input::Key::RIGHTPAREN;
    case SDLK_ASTERISK:              return input::Key::ASTERISK;
    case SDLK_PLUS:                  return input::Key::PLUS;
    case SDLK_COMMA:                 return input::Key::COMMA;
    case SDLK_MINUS:                 return input::Key::MINUS;
    case SDLK_PERIOD:                return input::Key::PERIOD;
    case SDLK_SLASH:                 return input::Key::SLASH;
    case SDLK_0:                     return input::Key::K0;
    case SDLK_1:                     return input::Key::K1;
    case SDLK_2:                     return input::Key::K2;
    case SDLK_3:                     return input::Key::K3;
    case SDLK_4:                     return input::Key::K4;
    case SDLK_5:                     return input::Key::K5;
    case SDLK_6:                     return input::Key::K6;
    case SDLK_7:                     return input::Key::K7;
    case SDLK_8:                     return input::Key::K8;
    case SDLK_9:                     return input::Key::K9;
    case SDLK_COLON:                 return input::Key::COLON;
    case SDLK_SEMICOLON:             return input::Key::SEMICOLON;
    case SDLK_LESS:                  return input::Key::LESS;
    case SDLK_EQUALS:                return input::Key::EQUALS;
    case SDLK_GREATER:               return input::Key::GREATER;
    case SDLK_QUESTION:              return input::Key::QUESTION;
    case SDLK_AT:                    return input::Key::AT;
    case SDLK_LEFTBRACKET:           return input::Key::LEFTBRACKET;
    case SDLK_BACKSLASH:             return input::Key::BACKSLASH;
    case SDLK_RIGHTBRACKET:          return input::Key::RIGHTBRACKET;
    case SDLK_CARET:                 return input::Key::CARET;
    case SDLK_UNDERSCORE:            return input::Key::UNDERSCORE;
    case SDLK_BACKQUOTE:             return input::Key::BACKQUOTE;
    case SDLK_a:                     return input::Key::A;
    case SDLK_b:                     return input::Key::B;
    case SDLK_c:                     return input::Key::C;
    case SDLK_d:                     return input::Key::D;
    case SDLK_e:                     return input::Key::E;
    case SDLK_f:                     return input::Key::F;
    case SDLK_g:                     return input::Key::G;
    case SDLK_h:                     return input::Key::H;
    case SDLK_i:                     return input::Key::I;
    case SDLK_j:                     return input::Key::J;
    case SDLK_k:                     return input::Key::K;
    case SDLK_l:                     return input::Key::L;
    case SDLK_m:                     return input::Key::M;
    case SDLK_n:                     return input::Key::N;
    case SDLK_o:                     return input::Key::O;
    case SDLK_p:                     return input::Key::P;
    case SDLK_q:                     return input::Key::Q;
    case SDLK_r:                     return input::Key::R;
    case SDLK_s:                     return input::Key::S;
    case SDLK_t:                     return input::Key::T;
    case SDLK_u:                     return input::Key::U;
    case SDLK_v:                     return input::Key::V;
    case SDLK_w:                     return input::Key::W;
    case SDLK_x:                     return input::Key::X;
    case SDLK_y:                     return input::Key::Y;
    case SDLK_z:                     return input::Key::Z;
    case SDLK_CAPSLOCK:              return input::Key::CAPSLOCK;
    case SDLK_F1:                    return input::Key::F1;
    case SDLK_F2:                    return input::Key::F2;
    case SDLK_F3:                    return input::Key::F3;
    case SDLK_F4:                    return input::Key::F4;
    case SDLK_F5:                    return input::Key::F5;
    case SDLK_F6:                    return input::Key::F6;
    case SDLK_F7:                    return input::Key::F7;
    case SDLK_F8:                    return input::Key::F8;
    case SDLK_F9:                    return input::Key::F9;
    case SDLK_F10:                   return input::Key::F10;
    case SDLK_F11:                   return input::Key::F11;
    case SDLK_F12:                   return input::Key::F12;
    case SDLK_PRINTSCREEN:           return input::Key::PRINTSCREEN;
    case SDLK_SCROLLLOCK:            return input::Key::SCROLLLOCK;
    case SDLK_PAUSE:                 return input::Key::PAUSE;
    case SDLK_INSERT:                return input::Key::INSERT;
    case SDLK_HOME:                  return input::Key::HOME;
    case SDLK_PAGEUP:                return input::Key::PAGEUP;
    case SDLK_DELETE:                return input::Key::DELETE;
    case SDLK_END:                   return input::Key::END;
    case SDLK_PAGEDOWN:              return input::Key::PAGEDOWN;
    case SDLK_RIGHT:                 return input::Key::RIGHT;
    case SDLK_LEFT:                  return input::Key::LEFT;
    case SDLK_DOWN:                  return input::Key::DOWN;
    case SDLK_UP:                    return input::Key::UP;
    case SDLK_NUMLOCKCLEAR:          return input::Key::NUMLOCKCLEAR;
    case SDLK_KP_DIVIDE:             return input::Key::KP_DIVIDE;
    case SDLK_KP_MULTIPLY:           return input::Key::KP_MULTIPLY;
    case SDLK_KP_MINUS:              return input::Key::KP_MINUS;
    case SDLK_KP_PLUS:               return input::Key::KP_PLUS;
    case SDLK_KP_ENTER:              return input::Key::KP_ENTER;
    case SDLK_KP_1:                  return input::Key::KP_1;
    case SDLK_KP_2:                  return input::Key::KP_2;
    case SDLK_KP_3:                  return input::Key::KP_3;
    case SDLK_KP_4:                  return input::Key::KP_4;
    case SDLK_KP_5:                  return input::Key::KP_5;
    case SDLK_KP_6:                  return input::Key::KP_6;
    case SDLK_KP_7:                  return input::Key::KP_7;
    case SDLK_KP_8:                  return input::Key::KP_8;
    case SDLK_KP_9:                  return input::Key::KP_9;
    case SDLK_KP_0:                  return input::Key::KP_0;
    case SDLK_KP_PERIOD:             return input::Key::KP_PERIOD;
    case SDLK_APPLICATION:           return input::Key::APPLICATION;
    case SDLK_POWER:                 return input::Key::POWER;
    case SDLK_KP_EQUALS:             return input::Key::KP_EQUALS;
    case SDLK_F13:                   return input::Key::F13;
    case SDLK_F14:                   return input::Key::F14;
    case SDLK_F15:                   return input::Key::F15;
    case SDLK_F16:                   return input::Key::F16;
    case SDLK_F17:                   return input::Key::F17;
    case SDLK_F18:                   return input::Key::F18;
    case SDLK_F19:                   return input::Key::F19;
    case SDLK_F20:                   return input::Key::F20;
    case SDLK_F21:                   return input::Key::F21;
    case SDLK_F22:                   return input::Key::F22;
    case SDLK_F23:                   return input::Key::F23;
    case SDLK_F24:                   return input::Key::F24;
    case SDLK_EXECUTE:               return input::Key::EXECUTE;
    case SDLK_HELP:                  return input::Key::HELP;
    case SDLK_MENU:                  return input::Key::MENU;
    case SDLK_SELECT:                return input::Key::SELECT;
    case SDLK_STOP:                  return input::Key::STOP;
    case SDLK_AGAIN:                 return input::Key::AGAIN;
    case SDLK_UNDO:                  return input::Key::UNDO;
    case SDLK_CUT:                   return input::Key::CUT;
    case SDLK_COPY:                  return input::Key::COPY;
    case SDLK_PASTE:                 return input::Key::PASTE;
    case SDLK_FIND:                  return input::Key::FIND;
    case SDLK_MUTE:                  return input::Key::MUTE;
    case SDLK_VOLUMEUP:              return input::Key::VOLUMEUP;
    case SDLK_VOLUMEDOWN:            return input::Key::VOLUMEDOWN;
    case SDLK_KP_COMMA:              return input::Key::KP_COMMA;
    case SDLK_KP_EQUALSAS400:        return input::Key::KP_EQUALSAS400;
    case SDLK_ALTERASE:              return input::Key::ALTERASE;
    case SDLK_SYSREQ:                return input::Key::SYSREQ;
    case SDLK_CANCEL:                return input::Key::CANCEL;
    case SDLK_CLEAR:                 return input::Key::CLEAR;
    case SDLK_PRIOR:                 return input::Key::PRIOR;
    case SDLK_RETURN2:               return input::Key::RETURN2;
    case SDLK_SEPARATOR:             return input::Key::SEPARATOR;
    case SDLK_OUT:                   return input::Key::OUT;
    case SDLK_OPER:                  return input::Key::OPER;
    case SDLK_CLEARAGAIN:            return input::Key::CLEARAGAIN;
    case SDLK_CRSEL:                 return input::Key::CRSEL;
    case SDLK_EXSEL:                 return input::Key::EXSEL;
    case SDLK_KP_00:                 return input::Key::KP_00;
    case SDLK_KP_000:                return input::Key::KP_000;
    case SDLK_THOUSANDSSEPARATOR:    return input::Key::THOUSANDSSEPARATOR;
    case SDLK_DECIMALSEPARATOR:      return input::Key::DECIMALSEPARATOR;
    case SDLK_CURRENCYUNIT:          return input::Key::CURRENCYUNIT;
    case SDLK_CURRENCYSUBUNIT:       return input::Key::CURRENCYSUBUNIT;
    case SDLK_KP_LEFTPAREN:          return input::Key::KP_LEFTPAREN;
    case SDLK_KP_RIGHTPAREN:         return input::Key::KP_RIGHTPAREN;
    case SDLK_KP_LEFTBRACE:          return input::Key::KP_LEFTBRACE;
    case SDLK_KP_RIGHTBRACE:         return input::Key::KP_RIGHTBRACE;
    case SDLK_KP_TAB:                return input::Key::KP_TAB;
    case SDLK_KP_BACKSPACE:          return input::Key::KP_BACKSPACE;
    case SDLK_KP_A:                  return input::Key::KP_A;
    case SDLK_KP_B:                  return input::Key::KP_B;
    case SDLK_KP_C:                  return input::Key::KP_C;
    case SDLK_KP_D:                  return input::Key::KP_D;
    case SDLK_KP_E:                  return input::Key::KP_E;
    case SDLK_KP_F:                  return input::Key::KP_F;
    case SDLK_KP_XOR:                return input::Key::KP_XOR;
    case SDLK_KP_POWER:              return input::Key::KP_POWER;
    case SDLK_KP_PERCENT:            return input::Key::KP_PERCENT;
    case SDLK_KP_LESS:               return input::Key::KP_LESS;
    case SDLK_KP_GREATER:            return input::Key::KP_GREATER;
    case SDLK_KP_AMPERSAND:          return input::Key::KP_AMPERSAND;
    case SDLK_KP_DBLAMPERSAND:       return input::Key::KP_DBLAMPERSAND;
    case SDLK_KP_VERTICALBAR:        return input::Key::KP_VERTICALBAR;
    case SDLK_KP_DBLVERTICALBAR:     return input::Key::KP_DBLVERTICALBAR;
    case SDLK_KP_COLON:              return input::Key::KP_COLON;
    case SDLK_KP_HASH:               return input::Key::KP_HASH;
    case SDLK_KP_SPACE:              return input::Key::KP_SPACE;
    case SDLK_KP_AT:                 return input::Key::KP_AT;
    case SDLK_KP_EXCLAM:             return input::Key::KP_EXCLAM;
    case SDLK_KP_MEMSTORE:           return input::Key::KP_MEMSTORE;
    case SDLK_KP_MEMRECALL:          return input::Key::KP_MEMRECALL;
    case SDLK_KP_MEMCLEAR:           return input::Key::KP_MEMCLEAR;
    case SDLK_KP_MEMADD:             return input::Key::KP_MEMADD;
    case SDLK_KP_MEMSUBTRACT:        return input::Key::KP_MEMSUBTRACT;
    case SDLK_KP_MEMMULTIPLY:        return input::Key::KP_MEMMULTIPLY;
    case SDLK_KP_MEMDIVIDE:          return input::Key::KP_MEMDIVIDE;
    case SDLK_KP_PLUSMINUS:          return input::Key::KP_PLUSMINUS;
    case SDLK_KP_CLEAR:              return input::Key::KP_CLEAR;
    case SDLK_KP_CLEARENTRY:         return input::Key::KP_CLEARENTRY;
    case SDLK_KP_BINARY:             return input::Key::KP_BINARY;
    case SDLK_KP_OCTAL:              return input::Key::KP_OCTAL;
    case SDLK_KP_DECIMAL:            return input::Key::KP_DECIMAL;
    case SDLK_KP_HEXADECIMAL:        return input::Key::KP_HEXADECIMAL;
    case SDLK_LCTRL:                 return input::Key::LCTRL;
    case SDLK_LSHIFT:                return input::Key::LSHIFT;
    case SDLK_LALT:                  return input::Key::LALT;
    case SDLK_LGUI:                  return input::Key::LGUI;
    case SDLK_RCTRL:                 return input::Key::RCTRL;
    case SDLK_RSHIFT:                return input::Key::RSHIFT;
    case SDLK_RALT:                  return input::Key::RALT;
    case SDLK_RGUI:                  return input::Key::RGUI;
    case SDLK_MODE:                  return input::Key::MODE;
    case SDLK_AUDIONEXT:             return input::Key::AUDIONEXT;
    case SDLK_AUDIOPREV:             return input::Key::AUDIOPREV;
    case SDLK_AUDIOSTOP:             return input::Key::AUDIOSTOP;
    case SDLK_AUDIOPLAY:             return input::Key::AUDIOPLAY;
    case SDLK_AUDIOMUTE:             return input::Key::AUDIOMUTE;
    case SDLK_MEDIASELECT:           return input::Key::MEDIASELECT;
    case SDLK_WWW:                   return input::Key::WWW;
    case SDLK_MAIL:                  return input::Key::MAIL;
    case SDLK_CALCULATOR:            return input::Key::CALCULATOR;
    case SDLK_COMPUTER:              return input::Key::COMPUTER;
    case SDLK_AC_SEARCH:             return input::Key::AC_SEARCH;
    case SDLK_AC_HOME:               return input::Key::AC_HOME;
    case SDLK_AC_BACK:               return input::Key::AC_BACK;
    case SDLK_AC_FORWARD:            return input::Key::AC_FORWARD;
    case SDLK_AC_STOP:               return input::Key::AC_STOP;
    case SDLK_AC_REFRESH:            return input::Key::AC_REFRESH;
    case SDLK_AC_BOOKMARKS:          return input::Key::AC_BOOKMARKS;
    case SDLK_BRIGHTNESSDOWN:        return input::Key::BRIGHTNESSDOWN;
    case SDLK_BRIGHTNESSUP:          return input::Key::BRIGHTNESSUP;
    case SDLK_DISPLAYSWITCH:         return input::Key::DISPLAYSWITCH;
    case SDLK_KBDILLUMTOGGLE:        return input::Key::KBDILLUMTOGGLE;
    case SDLK_KBDILLUMDOWN:          return input::Key::KBDILLUMDOWN;
    case SDLK_KBDILLUMUP:            return input::Key::KBDILLUMUP;
    case SDLK_EJECT:                 return input::Key::EJECT;
    case SDLK_SLEEP:                 return input::Key::SLEEP;
    case SDLK_APP1:                  return input::Key::APP1;
    case SDLK_APP2:                  return input::Key::APP2;
    case SDLK_AUDIOREWIND:           return input::Key::AUDIOREWIND;
    case SDLK_AUDIOFASTFORWARD:      return input::Key::AUDIOFASTFORWARD;
    case SDLK_SOFTLEFT:              return input::Key::SOFTLEFT;
    case SDLK_SOFTRIGHT:             return input::Key::SOFTRIGHT;
    case SDLK_CALL:                  return input::Key::CALL;
    case SDLK_ENDCALL:               return input::Key::ENDCALL;
  }

  return input::Key::UNKNOWN;
}

}
