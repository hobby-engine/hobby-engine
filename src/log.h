#ifndef _HOBBY_ERROR_H
#define _HOBBY_ERROR_H

#include <stdbool.h>

void hlog(const char* format, ...);
void warn(const char* format, ...);
void fatal(const char* format, ...);
void error(const char* format, ...);
bool assert(bool cond, const char* format, ...);
void fatalAssert(bool cond, const char* format, ...);

#endif // _HOBBY_ERROR_H
