#ifndef _HOBBY_TIME_HH
#define _HOBBY_TIME_HH

struct Time {
  public:
    double dt = 0;
    double fps = 0;
    double totalTime = 0;

    void update();
  private:
    double _lastFrameTime = 0;
    double _lastFpsUpdate = 0;
    int _framesRendered = 0;
};

#endif // _HOBBY_TIME_HH
