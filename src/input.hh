#ifndef _HOBBY_INPUT_HH
#define _HOBBY_INPUT_HH

#include "key.hh"

class Input {
  public:
    bool isKeyPressed(Key key);
    bool isKeyJustPressed(Key key);
};

#endif // _HOBBY_INPUT_HH
