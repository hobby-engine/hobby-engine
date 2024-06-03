#ifndef _HOBBY_LOG_HH
#define _HOBBY_LOG_HH

#include <cstdio>

class Logger
{
public:
  static Logger* instance();

  void raw(const char* format, ...);
  void log(const char* format, ...);
  void warn(const char* format, ...);
  void fatal(const char* format, ...);
  void error(const char* format, ...);
  bool assert(bool cond, const char* format, ...);
  bool fassert(bool cond, const char* format, ...);

private:
  Logger() = default;

  void _msg(FILE* file, const char* prefix, const char* format, va_list args);

  static Logger* _instance;
};

#endif // _HOBBY_LOG_HH
