function hobby.input.getvector(left, right, up, down)
  hobby.matchtype(left, "number")
  hobby.matchtype(right, "number")
  hobby.matchtype(up, "number")
  hobby.matchtype(down, "number")

  local ix, iy = 0, 0
  if hobby.input.iskeydown(left) then ix = ix - 1 end
  if hobby.input.iskeydown(right) then ix = ix + 1 end
  if hobby.input.iskeydown(up) then iy = iy - 1 end
  if hobby.input.iskeydown(down) then iy = iy + 1 end
  return hobby.vec.normalize(ix, iy)
end

hobby.keyevent = hobby.event()
hobby.keypressed = hobby.event()
hobby.keyreleased = hobby.event()

function hobby.onkeypressed(key, isRepeat)
  hobby.keypressed:call(key, isRepeat)
  hobby.keyevent:call(true, key, isRepeat)
end

function hobby.onkeyreleased(key)
  hobby.keyreleased:call(key)
  hobby.keyevent:call(false, key, nil)
end

local keynames = {}

function hobby.input.keytostring(key)
  local name = keynames[key]
  if not name then
    error("Invalid key.", 1)
  end

  return name
end

local keys = {
  Space        = 32,
  Apostrophe   = 39,
  Comma        = 44,
  Minus        = 45,
  Period       = 46,
  Slash        = 47,
  K0           = 48,
  K1           = 49,
  K2           = 50,
  K3           = 51,
  K4           = 52,
  K5           = 53,
  K6           = 54,
  K7           = 55,
  K8           = 56,
  K9           = 57,
  Semicolon    = 59,
  Equal        = 61,
  A            = 65,
  B            = 66,
  C            = 67,
  D            = 68,
  E            = 69,
  F            = 70,
  G            = 71,
  H            = 72,
  I            = 73,
  J            = 74,
  K            = 75,
  L            = 76,
  M            = 77,
  N            = 78,
  O            = 79,
  P            = 80,
  Q            = 81,
  R            = 82,
  S            = 83,
  T            = 84,
  U            = 85,
  V            = 86,
  W            = 87,
  X            = 88,
  Y            = 89,
  Z            = 90,
  LeftBracket  = 91,
  Backslash    = 92,
  RightBracket = 93,
  GraveAccent  = 96,
  World1       = 161,
  World2       = 162,
  Escape       = 256,
  Enter        = 257,
  Tab          = 258,
  Backspace    = 259,
  Insert       = 260,
  Delete       = 261,
  Right        = 262,
  Left         = 263,
  Down         = 264,
  Up           = 265,
  PageUp       = 266,
  PageDown     = 267,
  Home         = 268,
  End          = 269,
  CapsLock     = 280,
  ScrollLock   = 281,
  NumLock      = 282,
  PrintScreen  = 283,
  Pause        = 284,
  F1           = 290,
  F2           = 291,
  F3           = 292,
  F4           = 293,
  F5           = 294,
  F6           = 295,
  F7           = 296,
  F8           = 297,
  F9           = 298,
  F10          = 299,
  F11          = 300,
  F12          = 301,
  F13          = 302,
  F14          = 303,
  F15          = 304,
  F16          = 305,
  F17          = 306,
  F18          = 307,
  F19          = 308,
  F20          = 309,
  F21          = 310,
  F22          = 311,
  F23          = 312,
  F24          = 313,
  F25          = 314,
  Kp0          = 320,
  Kp1          = 321,
  Kp2          = 322,
  Kp3          = 323,
  Kp4          = 324,
  Kp5          = 325,
  Kp6          = 326,
  Kp7          = 327,
  Kp8          = 328,
  Kp9          = 329,
  KpDecimal    = 330,
  KpDivide     = 331,
  KpMultiply   = 332,
  KpSubtract   = 333,
  KpAdd        = 334,
  KpEnter      = 335,
  KpEqual      = 336,
  LeftShift    = 340,
  LeftControl  = 341,
  LeftAlt      = 342,
  LeftSuper    = 343,
  RightShift   = 344,
  RightControl = 345,
  RightAlt     = 346,
  RightSuper   = 347,
  Menu         = 348,
}

hobby.LMB = 1
hobby.RMB = 2
hobby.MMB = 3
hobby.XB1 = 4
hobby.XB2 = 5

for k, v in pairs(keys) do
  hobby[k] = v
  keynames[v] = k
end
