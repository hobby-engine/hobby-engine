#include "log.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static void logMessage(FILE* file, const char* prefix, const char* format, va_list args) {
  fprintf(file, "%s", prefix);
  vfprintf(file, format, args);
  fprintf(file, "\n");
}

void hlog(const char* format, ...) {
  va_list args;
  va_start(args, format);
  logMessage(stdout, "[LOG] ", format, args);
  va_end(args);
}

void warn(const char* format, ...) {
  va_list args;
  va_start(args, format);
  logMessage(stderr, "[WARN] ", format, args);
  va_end(args);
}

void fatal(const char* format, ...) {
  va_list args;
  va_start(args, format);
  logMessage(stderr, "[FATAL] ", format, args);
  va_end(args);
  exit(1);
}

void error(const char* format, ...) {
  va_list args;
  va_start(args, format);
  logMessage(stderr, "[ERROR] ", format, args);
  va_end(args);
}

bool assert(bool cond, const char* format, ...) {
  if (cond) {
    return true;
  }
  va_list args;
  va_start(args, format);
  logMessage(stderr, "[ERROR] ", format, args);
  va_end(args);

  return false;
}

void fatalAssert(bool cond, const char* format, ...) {
  if (cond) {
    return;
  }
  va_list args;
  va_start(args, format);
  logMessage(stderr, "[FATAL] ", format, args);
  va_end(args);
  exit(1);
}
