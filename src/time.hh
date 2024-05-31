#ifndef _HOBBY_TIME_HH
#define _HOBBY_TIME_HH

struct Time
{
public:
  double dt = 0;
  double fps = 0;
  double total = 0;

  void update();

private:
  double _lastframe = 0;
  double _lastfps = 0;
  int _framesrendered = 0;
};

#endif // _HOBBY_TIME_HH
