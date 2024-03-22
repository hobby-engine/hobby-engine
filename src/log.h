#ifndef _HOBBY_ERROR_H
#define _HOBBY_ERROR_H

#include <stdbool.h>

void hb_log(const char* format, ...);
void hb_warn(const char* format, ...);
void hb_fatal(const char* format, ...);
void hb_error(const char* format, ...);
void hb_assert(bool cond, const char* format, ...);
void hb_fatalAssert(bool cond, const char* format, ...);

#endif // _HOBBY_ERROR_H
