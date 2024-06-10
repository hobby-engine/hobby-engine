#include "log.hh"

#include <cstdarg>
#include <cstdlib>

Logger* Logger::m_instance = nullptr;

Logger* Logger::instance()
{
  if (m_instance == nullptr) {
    m_instance = new Logger();
  }
  return m_instance;
}

void Logger::m_msg(
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
  m_msg(stdout, nullptr, format, args);
  va_end(args);
}

void Logger::log(const char* format, ...)
{
  std::va_list args;
  va_start(args, format);
  m_msg(stdout, "[LOG] ", format, args);
  va_end(args);
}

void Logger::warn(const char* format, ...)
{
  std::va_list args;
  va_start(args, format);
  m_msg(stderr, "[WARN] ", format, args);
  va_end(args);
}

void Logger::fatal(const char* format, ...)
{
  std::va_list args;
  va_start(args, format);
  m_msg(stderr, "[FATAL] ", format, args);
  va_end(args);
  std::exit(1);
}

void Logger::error(const char* format, ...)
{
  std::va_list args;
  va_start(args, format);
  m_msg(stderr, "[ERROR] ", format, args);
  va_end(args);
}

bool Logger::assert(bool cond, const char* format, ...)
{
  if (cond) {
    return true;
  }
  std::va_list args;
  va_start(args, format);
  m_msg(stderr, "[ERROR] ", format, args);
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
  m_msg(stderr, "[FATAL] ", format, args);
  va_end(args);

  return false;
}
