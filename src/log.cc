#include "log.hh"

#include <cstdarg>
#include <cstdlib>

Logger* Logger::_instance = nullptr;

Logger* Logger::instance()
{
  if (_instance == nullptr) {
    _instance = new Logger();
  }
  return _instance;
}

void Logger::_msg(
  FILE* file, const char* prefix, const char* format, va_list args)
{
  if (format == nullptr) {
    return;
  }

  if (prefix != nullptr) {
    std::fprintf(file, "%s", prefix);
  }
  std::vfprintf(file, format, args);
  std::fprintf(file, "\n");
}

void Logger::raw(const char* format, ...)
{
  std::va_list args;
  va_start(args, format);
  _msg(stdout, nullptr, format, args);
  va_end(args);
}

void Logger::log(const char* format, ...)
{
  std::va_list args;
  va_start(args, format);
  _msg(stdout, "[LOG] ", format, args);
  va_end(args);
}

void Logger::warn(const char* format, ...)
{
  std::va_list args;
  va_start(args, format);
  _msg(stderr, "[WARN] ", format, args);
  va_end(args);
}

void Logger::fatal(const char* format, ...)
{
  std::va_list args;
  va_start(args, format);
  _msg(stderr, "[FATAL] ", format, args);
  va_end(args);
  std::exit(1);
}

void Logger::error(const char* format, ...)
{
  std::va_list args;
  va_start(args, format);
  _msg(stderr, "[ERROR] ", format, args);
  va_end(args);
}

bool Logger::assert(bool cond, const char* format, ...)
{
  if (cond) {
    return true;
  }
  std::va_list args;
  va_start(args, format);
  _msg(stderr, "[ERROR] ", format, args);
  va_end(args);

  return false;
}

bool Logger::fassert(bool cond, const char* format, ...)
{
  if (cond) {
    return true;
  }
  std::va_list args;
  va_start(args, format);
  _msg(stderr, "[FATAL] ", format, args);
  va_end(args);

  return false;
}
