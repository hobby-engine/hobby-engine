#include "window.hh"

#include <iostream>

#include "SDL2/SDL_events.h"
#include "event/mouse.hh"
#include "glad/glad.h"
#include "SDL2/SDL.h"

#include "event/key.hh"
#include "vec2.hh"

namespace Hobby {

static Input::Key SDLToPoint(SDL_KeyCode key);

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
      case SDL_MOUSEBUTTONUP:
      case SDL_MOUSEBUTTONDOWN: {
        int button = event.button.button;
        switch (button) {
          case 2: button = SDL_BUTTON_RIGHT; break;
          case 3: button = SDL_BUTTON_MIDDLE; break;
        }
        Vec2 position = Vec2(event.button.x, event.button.y);
        
        if (event.button.state == SDL_PRESSED) {
          MousePressedEvent mousePressedEvent(button, position);
          MousePressedEvent::PushEvent(mousePressedEvent);
        } else if (event.button.state == SDL_RELEASED) {
          MouseReleasedEvent mouseReleasedEvent(button, position);
          MouseReleasedEvent::PushEvent(mouseReleasedEvent);
        }
        break;
      }
      case SDL_MOUSEMOTION: {
        Vec2 relative = Vec2(event.motion.xrel, event.motion.yrel);
        Vec2 position = Vec2(event.motion.x, event.motion.y);
        MouseMovedEvent mouseMovedEvent(relative, position);
        MouseMovedEvent::PushEvent(mouseMovedEvent);
        break;
      }
      case SDL_MOUSEWHEEL: {
        Vec2 scroll = Vec2(event.wheel.x, event.wheel.y);
        MouseScrolledEvent mouseScrolledEvent(scroll);
        MouseScrolledEvent::PushEvent(mouseScrolledEvent);
        break;
      }
    }
  }
}

static Input::Key SDLToPoint(SDL_KeyCode key) {
  switch (key) {
    case SDLK_UNKNOWN:               return Input::Key::UNKNOWN;
    case SDLK_RETURN:                return Input::Key::RETURN;
    case SDLK_ESCAPE:                return Input::Key::ESCAPE;
    case SDLK_BACKSPACE:             return Input::Key::BACKSPACE;
    case SDLK_TAB:                   return Input::Key::TAB;
    case SDLK_SPACE:                 return Input::Key::SPACE;
    case SDLK_EXCLAIM:               return Input::Key::EXCLAIM;
    case SDLK_QUOTEDBL:              return Input::Key::QUOTEDBL;
    case SDLK_HASH:                  return Input::Key::HASH;
    case SDLK_PERCENT:               return Input::Key::PERCENT;
    case SDLK_DOLLAR:                return Input::Key::DOLLAR;
    case SDLK_AMPERSAND:             return Input::Key::AMPERSAND;
    case SDLK_QUOTE:                 return Input::Key::QUOTE;
    case SDLK_LEFTPAREN:             return Input::Key::LEFTPAREN;
    case SDLK_RIGHTPAREN:            return Input::Key::RIGHTPAREN;
    case SDLK_ASTERISK:              return Input::Key::ASTERISK;
    case SDLK_PLUS:                  return Input::Key::PLUS;
    case SDLK_COMMA:                 return Input::Key::COMMA;
    case SDLK_MINUS:                 return Input::Key::MINUS;
    case SDLK_PERIOD:                return Input::Key::PERIOD;
    case SDLK_SLASH:                 return Input::Key::SLASH;
    case SDLK_0:                     return Input::Key::K0;
    case SDLK_1:                     return Input::Key::K1;
    case SDLK_2:                     return Input::Key::K2;
    case SDLK_3:                     return Input::Key::K3;
    case SDLK_4:                     return Input::Key::K4;
    case SDLK_5:                     return Input::Key::K5;
    case SDLK_6:                     return Input::Key::K6;
    case SDLK_7:                     return Input::Key::K7;
    case SDLK_8:                     return Input::Key::K8;
    case SDLK_9:                     return Input::Key::K9;
    case SDLK_COLON:                 return Input::Key::COLON;
    case SDLK_SEMICOLON:             return Input::Key::SEMICOLON;
    case SDLK_LESS:                  return Input::Key::LESS;
    case SDLK_EQUALS:                return Input::Key::EQUALS;
    case SDLK_GREATER:               return Input::Key::GREATER;
    case SDLK_QUESTION:              return Input::Key::QUESTION;
    case SDLK_AT:                    return Input::Key::AT;
    case SDLK_LEFTBRACKET:           return Input::Key::LEFTBRACKET;
    case SDLK_BACKSLASH:             return Input::Key::BACKSLASH;
    case SDLK_RIGHTBRACKET:          return Input::Key::RIGHTBRACKET;
    case SDLK_CARET:                 return Input::Key::CARET;
    case SDLK_UNDERSCORE:            return Input::Key::UNDERSCORE;
    case SDLK_BACKQUOTE:             return Input::Key::BACKQUOTE;
    case SDLK_a:                     return Input::Key::A;
    case SDLK_b:                     return Input::Key::B;
    case SDLK_c:                     return Input::Key::C;
    case SDLK_d:                     return Input::Key::D;
    case SDLK_e:                     return Input::Key::E;
    case SDLK_f:                     return Input::Key::F;
    case SDLK_g:                     return Input::Key::G;
    case SDLK_h:                     return Input::Key::H;
    case SDLK_i:                     return Input::Key::I;
    case SDLK_j:                     return Input::Key::J;
    case SDLK_k:                     return Input::Key::K;
    case SDLK_l:                     return Input::Key::L;
    case SDLK_m:                     return Input::Key::M;
    case SDLK_n:                     return Input::Key::N;
    case SDLK_o:                     return Input::Key::O;
    case SDLK_p:                     return Input::Key::P;
    case SDLK_q:                     return Input::Key::Q;
    case SDLK_r:                     return Input::Key::R;
    case SDLK_s:                     return Input::Key::S;
    case SDLK_t:                     return Input::Key::T;
    case SDLK_u:                     return Input::Key::U;
    case SDLK_v:                     return Input::Key::V;
    case SDLK_w:                     return Input::Key::W;
    case SDLK_x:                     return Input::Key::X;
    case SDLK_y:                     return Input::Key::Y;
    case SDLK_z:                     return Input::Key::Z;
    case SDLK_CAPSLOCK:              return Input::Key::CAPSLOCK;
    case SDLK_F1:                    return Input::Key::F1;
    case SDLK_F2:                    return Input::Key::F2;
    case SDLK_F3:                    return Input::Key::F3;
    case SDLK_F4:                    return Input::Key::F4;
    case SDLK_F5:                    return Input::Key::F5;
    case SDLK_F6:                    return Input::Key::F6;
    case SDLK_F7:                    return Input::Key::F7;
    case SDLK_F8:                    return Input::Key::F8;
    case SDLK_F9:                    return Input::Key::F9;
    case SDLK_F10:                   return Input::Key::F10;
    case SDLK_F11:                   return Input::Key::F11;
    case SDLK_F12:                   return Input::Key::F12;
    case SDLK_PRINTSCREEN:           return Input::Key::PRINTSCREEN;
    case SDLK_SCROLLLOCK:            return Input::Key::SCROLLLOCK;
    case SDLK_PAUSE:                 return Input::Key::PAUSE;
    case SDLK_INSERT:                return Input::Key::INSERT;
    case SDLK_HOME:                  return Input::Key::HOME;
    case SDLK_PAGEUP:                return Input::Key::PAGEUP;
    case SDLK_DELETE:                return Input::Key::DELETE;
    case SDLK_END:                   return Input::Key::END;
    case SDLK_PAGEDOWN:              return Input::Key::PAGEDOWN;
    case SDLK_RIGHT:                 return Input::Key::RIGHT;
    case SDLK_LEFT:                  return Input::Key::LEFT;
    case SDLK_DOWN:                  return Input::Key::DOWN;
    case SDLK_UP:                    return Input::Key::UP;
    case SDLK_NUMLOCKCLEAR:          return Input::Key::NUMLOCKCLEAR;
    case SDLK_KP_DIVIDE:             return Input::Key::KP_DIVIDE;
    case SDLK_KP_MULTIPLY:           return Input::Key::KP_MULTIPLY;
    case SDLK_KP_MINUS:              return Input::Key::KP_MINUS;
    case SDLK_KP_PLUS:               return Input::Key::KP_PLUS;
    case SDLK_KP_ENTER:              return Input::Key::KP_ENTER;
    case SDLK_KP_1:                  return Input::Key::KP_1;
    case SDLK_KP_2:                  return Input::Key::KP_2;
    case SDLK_KP_3:                  return Input::Key::KP_3;
    case SDLK_KP_4:                  return Input::Key::KP_4;
    case SDLK_KP_5:                  return Input::Key::KP_5;
    case SDLK_KP_6:                  return Input::Key::KP_6;
    case SDLK_KP_7:                  return Input::Key::KP_7;
    case SDLK_KP_8:                  return Input::Key::KP_8;
    case SDLK_KP_9:                  return Input::Key::KP_9;
    case SDLK_KP_0:                  return Input::Key::KP_0;
    case SDLK_KP_PERIOD:             return Input::Key::KP_PERIOD;
    case SDLK_APPLICATION:           return Input::Key::APPLICATION;
    case SDLK_POWER:                 return Input::Key::POWER;
    case SDLK_KP_EQUALS:             return Input::Key::KP_EQUALS;
    case SDLK_F13:                   return Input::Key::F13;
    case SDLK_F14:                   return Input::Key::F14;
    case SDLK_F15:                   return Input::Key::F15;
    case SDLK_F16:                   return Input::Key::F16;
    case SDLK_F17:                   return Input::Key::F17;
    case SDLK_F18:                   return Input::Key::F18;
    case SDLK_F19:                   return Input::Key::F19;
    case SDLK_F20:                   return Input::Key::F20;
    case SDLK_F21:                   return Input::Key::F21;
    case SDLK_F22:                   return Input::Key::F22;
    case SDLK_F23:                   return Input::Key::F23;
    case SDLK_F24:                   return Input::Key::F24;
    case SDLK_EXECUTE:               return Input::Key::EXECUTE;
    case SDLK_HELP:                  return Input::Key::HELP;
    case SDLK_MENU:                  return Input::Key::MENU;
    case SDLK_SELECT:                return Input::Key::SELECT;
    case SDLK_STOP:                  return Input::Key::STOP;
    case SDLK_AGAIN:                 return Input::Key::AGAIN;
    case SDLK_UNDO:                  return Input::Key::UNDO;
    case SDLK_CUT:                   return Input::Key::CUT;
    case SDLK_COPY:                  return Input::Key::COPY;
    case SDLK_PASTE:                 return Input::Key::PASTE;
    case SDLK_FIND:                  return Input::Key::FIND;
    case SDLK_MUTE:                  return Input::Key::MUTE;
    case SDLK_VOLUMEUP:              return Input::Key::VOLUMEUP;
    case SDLK_VOLUMEDOWN:            return Input::Key::VOLUMEDOWN;
    case SDLK_KP_COMMA:              return Input::Key::KP_COMMA;
    case SDLK_KP_EQUALSAS400:        return Input::Key::KP_EQUALSAS400;
    case SDLK_ALTERASE:              return Input::Key::ALTERASE;
    case SDLK_SYSREQ:                return Input::Key::SYSREQ;
    case SDLK_CANCEL:                return Input::Key::CANCEL;
    case SDLK_CLEAR:                 return Input::Key::CLEAR;
    case SDLK_PRIOR:                 return Input::Key::PRIOR;
    case SDLK_RETURN2:               return Input::Key::RETURN2;
    case SDLK_SEPARATOR:             return Input::Key::SEPARATOR;
    case SDLK_OUT:                   return Input::Key::OUT;
    case SDLK_OPER:                  return Input::Key::OPER;
    case SDLK_CLEARAGAIN:            return Input::Key::CLEARAGAIN;
    case SDLK_CRSEL:                 return Input::Key::CRSEL;
    case SDLK_EXSEL:                 return Input::Key::EXSEL;
    case SDLK_KP_00:                 return Input::Key::KP_00;
    case SDLK_KP_000:                return Input::Key::KP_000;
    case SDLK_THOUSANDSSEPARATOR:    return Input::Key::THOUSANDSSEPARATOR;
    case SDLK_DECIMALSEPARATOR:      return Input::Key::DECIMALSEPARATOR;
    case SDLK_CURRENCYUNIT:          return Input::Key::CURRENCYUNIT;
    case SDLK_CURRENCYSUBUNIT:       return Input::Key::CURRENCYSUBUNIT;
    case SDLK_KP_LEFTPAREN:          return Input::Key::KP_LEFTPAREN;
    case SDLK_KP_RIGHTPAREN:         return Input::Key::KP_RIGHTPAREN;
    case SDLK_KP_LEFTBRACE:          return Input::Key::KP_LEFTBRACE;
    case SDLK_KP_RIGHTBRACE:         return Input::Key::KP_RIGHTBRACE;
    case SDLK_KP_TAB:                return Input::Key::KP_TAB;
    case SDLK_KP_BACKSPACE:          return Input::Key::KP_BACKSPACE;
    case SDLK_KP_A:                  return Input::Key::KP_A;
    case SDLK_KP_B:                  return Input::Key::KP_B;
    case SDLK_KP_C:                  return Input::Key::KP_C;
    case SDLK_KP_D:                  return Input::Key::KP_D;
    case SDLK_KP_E:                  return Input::Key::KP_E;
    case SDLK_KP_F:                  return Input::Key::KP_F;
    case SDLK_KP_XOR:                return Input::Key::KP_XOR;
    case SDLK_KP_POWER:              return Input::Key::KP_POWER;
    case SDLK_KP_PERCENT:            return Input::Key::KP_PERCENT;
    case SDLK_KP_LESS:               return Input::Key::KP_LESS;
    case SDLK_KP_GREATER:            return Input::Key::KP_GREATER;
    case SDLK_KP_AMPERSAND:          return Input::Key::KP_AMPERSAND;
    case SDLK_KP_DBLAMPERSAND:       return Input::Key::KP_DBLAMPERSAND;
    case SDLK_KP_VERTICALBAR:        return Input::Key::KP_VERTICALBAR;
    case SDLK_KP_DBLVERTICALBAR:     return Input::Key::KP_DBLVERTICALBAR;
    case SDLK_KP_COLON:              return Input::Key::KP_COLON;
    case SDLK_KP_HASH:               return Input::Key::KP_HASH;
    case SDLK_KP_SPACE:              return Input::Key::KP_SPACE;
    case SDLK_KP_AT:                 return Input::Key::KP_AT;
    case SDLK_KP_EXCLAM:             return Input::Key::KP_EXCLAM;
    case SDLK_KP_MEMSTORE:           return Input::Key::KP_MEMSTORE;
    case SDLK_KP_MEMRECALL:          return Input::Key::KP_MEMRECALL;
    case SDLK_KP_MEMCLEAR:           return Input::Key::KP_MEMCLEAR;
    case SDLK_KP_MEMADD:             return Input::Key::KP_MEMADD;
    case SDLK_KP_MEMSUBTRACT:        return Input::Key::KP_MEMSUBTRACT;
    case SDLK_KP_MEMMULTIPLY:        return Input::Key::KP_MEMMULTIPLY;
    case SDLK_KP_MEMDIVIDE:          return Input::Key::KP_MEMDIVIDE;
    case SDLK_KP_PLUSMINUS:          return Input::Key::KP_PLUSMINUS;
    case SDLK_KP_CLEAR:              return Input::Key::KP_CLEAR;
    case SDLK_KP_CLEARENTRY:         return Input::Key::KP_CLEARENTRY;
    case SDLK_KP_BINARY:             return Input::Key::KP_BINARY;
    case SDLK_KP_OCTAL:              return Input::Key::KP_OCTAL;
    case SDLK_KP_DECIMAL:            return Input::Key::KP_DECIMAL;
    case SDLK_KP_HEXADECIMAL:        return Input::Key::KP_HEXADECIMAL;
    case SDLK_LCTRL:                 return Input::Key::LCTRL;
    case SDLK_LSHIFT:                return Input::Key::LSHIFT;
    case SDLK_LALT:                  return Input::Key::LALT;
    case SDLK_LGUI:                  return Input::Key::LGUI;
    case SDLK_RCTRL:                 return Input::Key::RCTRL;
    case SDLK_RSHIFT:                return Input::Key::RSHIFT;
    case SDLK_RALT:                  return Input::Key::RALT;
    case SDLK_RGUI:                  return Input::Key::RGUI;
    case SDLK_MODE:                  return Input::Key::MODE;
    case SDLK_AUDIONEXT:             return Input::Key::AUDIONEXT;
    case SDLK_AUDIOPREV:             return Input::Key::AUDIOPREV;
    case SDLK_AUDIOSTOP:             return Input::Key::AUDIOSTOP;
    case SDLK_AUDIOPLAY:             return Input::Key::AUDIOPLAY;
    case SDLK_AUDIOMUTE:             return Input::Key::AUDIOMUTE;
    case SDLK_MEDIASELECT:           return Input::Key::MEDIASELECT;
    case SDLK_WWW:                   return Input::Key::WWW;
    case SDLK_MAIL:                  return Input::Key::MAIL;
    case SDLK_CALCULATOR:            return Input::Key::CALCULATOR;
    case SDLK_COMPUTER:              return Input::Key::COMPUTER;
    case SDLK_AC_SEARCH:             return Input::Key::AC_SEARCH;
    case SDLK_AC_HOME:               return Input::Key::AC_HOME;
    case SDLK_AC_BACK:               return Input::Key::AC_BACK;
    case SDLK_AC_FORWARD:            return Input::Key::AC_FORWARD;
    case SDLK_AC_STOP:               return Input::Key::AC_STOP;
    case SDLK_AC_REFRESH:            return Input::Key::AC_REFRESH;
    case SDLK_AC_BOOKMARKS:          return Input::Key::AC_BOOKMARKS;
    case SDLK_BRIGHTNESSDOWN:        return Input::Key::BRIGHTNESSDOWN;
    case SDLK_BRIGHTNESSUP:          return Input::Key::BRIGHTNESSUP;
    case SDLK_DISPLAYSWITCH:         return Input::Key::DISPLAYSWITCH;
    case SDLK_KBDILLUMTOGGLE:        return Input::Key::KBDILLUMTOGGLE;
    case SDLK_KBDILLUMDOWN:          return Input::Key::KBDILLUMDOWN;
    case SDLK_KBDILLUMUP:            return Input::Key::KBDILLUMUP;
    case SDLK_EJECT:                 return Input::Key::EJECT;
    case SDLK_SLEEP:                 return Input::Key::SLEEP;
    case SDLK_APP1:                  return Input::Key::APP1;
    case SDLK_APP2:                  return Input::Key::APP2;
    case SDLK_AUDIOREWIND:           return Input::Key::AUDIOREWIND;
    case SDLK_AUDIOFASTFORWARD:      return Input::Key::AUDIOFASTFORWARD;
    case SDLK_SOFTLEFT:              return Input::Key::SOFTLEFT;
    case SDLK_SOFTRIGHT:             return Input::Key::SOFTRIGHT;
    case SDLK_CALL:                  return Input::Key::CALL;
    case SDLK_ENDCALL:               return Input::Key::ENDCALL;
  }

  return Input::Key::UNKNOWN;
}

}
