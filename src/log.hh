#ifndef _HOBBY_LOG_HH
#define _HOBBY_LOG_HH

void hlog(const char* format, ...);
void warn(const char* format, ...);
void fatal(const char* format, ...);
void error(const char* format, ...);
bool assert(bool cond, const char* format, ...);
void fatalAssert(bool cond, const char* format, ...);

#endif // _HOBBY_LOG_HH
