#ifndef _HOBBY_TIME_HH
#define _HOBBY_TIME_HH

struct Time
{
public:
  void update();

  double getdt() const
  {
    return m_dt;
  }

  double getfps() const
  {
    return m_fps;
  }

  double gettotal() const
  {
    return m_total;
  }

private:
  double m_dt = 0;
  double m_fps = 0;
  double m_total = 0;

  double m_lastframe = 0;
  double m_lastfps = 0;
  int m_framesrendered = 0;
};

#endif // _HOBBY_TIME_HH
