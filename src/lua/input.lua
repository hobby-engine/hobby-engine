function hobby.getInputVector(left, right, up, down)
  hobby.aux.matchType(left, "number")
  hobby.aux.matchType(right, "number")
  hobby.aux.matchType(up, "number")
  hobby.aux.matchType(down, "number")

  local ix, iy = 0, 0
  if hobby.isKeyPressed(left) then ix = ix - 1 end
  if hobby.isKeyPressed(right) then ix = ix + 1 end
  if hobby.isKeyPressed(up) then iy = iy - 1 end
  if hobby.isKeyPressed(down) then iy = iy + 1 end
  return hobby.vec.normalize(ix, iy)
end

hobby.keyEvent = hobby.event()
hobby.keyPressed = hobby.event()
hobby.keyReleased = hobby.event()

function hobby.onKeyPressed(key, isRepeat)
  hobby.keyPressed:call(key, isRepeat)
  hobby.keyEvent:call(true, key, isRepeat)
end

function hobby.onKeyReleased(key)
  hobby.keyReleased:call(key)
  hobby.keyEvent:call(false, key, nil)
end

hobby.LMB = 1
hobby.RMB = 2
hobby.MMB = 3
hobby.XB1 = 4
hobby.XB2 = 5

hobby.Space        = 32
hobby.Apostrophe   = 39
hobby.Comma        = 44
hobby.Minus        = 45
hobby.Period       = 46
hobby.Slash        = 47
hobby.K0           = 48
hobby.K1           = 49
hobby.K2           = 50
hobby.K3           = 51
hobby.K4           = 52
hobby.K5           = 53
hobby.K6           = 54
hobby.K7           = 55
hobby.K8           = 56
hobby.K9           = 57
hobby.Semicolon    = 59
hobby.Equal        = 61
hobby.A            = 65
hobby.B            = 66
hobby.C            = 67
hobby.D            = 68
hobby.E            = 69
hobby.F            = 70
hobby.G            = 71
hobby.H            = 72
hobby.I            = 73
hobby.J            = 74
hobby.K            = 75
hobby.L            = 76
hobby.M            = 77
hobby.N            = 78
hobby.O            = 79
hobby.P            = 80
hobby.Q            = 81
hobby.R            = 82
hobby.S            = 83
hobby.T            = 84
hobby.U            = 85
hobby.V            = 86
hobby.W            = 87
hobby.X            = 88
hobby.Y            = 89
hobby.Z            = 90
hobby.LeftBracket  = 91
hobby.Backslash    = 92
hobby.RightBracket = 93
hobby.GraveAccent  = 96
hobby.World1       = 161
hobby.World2       = 162
hobby.Escape       = 256
hobby.Enter        = 257
hobby.Tab          = 258
hobby.Backspace    = 259
hobby.Insert       = 260
hobby.Delete       = 261
hobby.Right        = 262
hobby.Left         = 263
hobby.Down         = 264
hobby.Up           = 265
hobby.PageUp       = 266
hobby.PageDown     = 267
hobby.Home         = 268
hobby.End          = 269
hobby.CapsLock     = 280
hobby.ScrollLock   = 281
hobby.NumLock      = 282
hobby.PrintScreen  = 283
hobby.Pause        = 284
hobby.F1           = 290
hobby.F2           = 291
hobby.F3           = 292
hobby.F4           = 293
hobby.F5           = 294
hobby.F6           = 295
hobby.F7           = 296
hobby.F8           = 297
hobby.F9           = 298
hobby.F10          = 299
hobby.F11          = 300
hobby.F12          = 301
hobby.F13          = 302
hobby.F14          = 303
hobby.F15          = 304
hobby.F16          = 305
hobby.F17          = 306
hobby.F18          = 307
hobby.F19          = 308
hobby.F20          = 309
hobby.F21          = 310
hobby.F22          = 311
hobby.F23          = 312
hobby.F24          = 313
hobby.F25          = 314
hobby.Kp0          = 320
hobby.Kp1          = 321
hobby.Kp2          = 322
hobby.Kp3          = 323
hobby.Kp4          = 324
hobby.Kp5          = 325
hobby.Kp6          = 326
hobby.Kp7          = 327
hobby.Kp8          = 328
hobby.Kp9          = 329
hobby.KpDecimal    = 330
hobby.KpDivide     = 331
hobby.KpMultiply   = 332
hobby.KpSubtract   = 333
hobby.KpAdd        = 334
hobby.KpEnter      = 335
hobby.KpEqual      = 336
hobby.LeftShift    = 340
hobby.LeftControl  = 341
hobby.LeftAlt      = 342
hobby.LeftSuper    = 343
hobby.RightShift   = 344
hobby.RightControl = 345
hobby.RightAlt     = 346
hobby.RightSuper   = 347
hobby.Menu         = 348
