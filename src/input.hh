#ifndef _HOBBY_INPUT_HH
#define _HOBBY_INPUT_HH

#include "key.hh"

class Input
{
public:
  virtual ~Input()
  {
  }

  virtual bool iskeydown(Key key) = 0;
  virtual bool ismousedown(int button) = 0;
};

#endif // _HOBBY_INPUT_HH
