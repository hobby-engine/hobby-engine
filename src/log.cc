#include "log.hh"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>

static void
msg(FILE* file, const char* prefix, const char* format, va_list args)
{
  std::fprintf(file, "%s", prefix);
  if (format == nullptr) {
    return;
  }
  std::vfprintf(file, format, args);
  std::fprintf(file, "\n");
}

void hlog(const char* format, ...)
{
  std::va_list args;
  va_start(args, format);
  msg(stdout, "[LOG] ", format, args);
  va_end(args);
}

void warn(const char* format, ...)
{
  std::va_list args;
  va_start(args, format);
  msg(stderr, "[WARN] ", format, args);
  va_end(args);
}

void fatal(const char* format, ...)
{
  std::va_list args;
  va_start(args, format);
  msg(stderr, "[FATAL] ", format, args);
  va_end(args);
  std::exit(1);
}

void error(const char* format, ...)
{
  std::va_list args;
  va_start(args, format);
  msg(stderr, "[ERROR] ", format, args);
  va_end(args);
}

bool assert(bool cond, const char* format, ...)
{
  if (cond) {
    return true;
  }
  std::va_list args;
  va_start(args, format);
  msg(stderr, "[ERROR] ", format, args);
  va_end(args);

  return false;
}

void fassert(bool cond, const char* format, ...)
{
  if (cond) {
    return;
  }
  std::va_list args;
  va_start(args, format);
  msg(stderr, "[FATAL] ", format, args);
  va_end(args);
  std::exit(1);
}
