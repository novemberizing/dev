#ifndef   __X_CORE__STRING__HH__
#define   __X_CORE__STRING__HH__

#if 0
extern __SIZE_TYPE__ __strlen(const char * s);
extern int __strcmp(const char * x, const char * y);
extern int __strncmp(const char * x, const char * y, __SIZE_TYPE__ n);

extern int __snprintf(char *str, __SIZE_TYPE__ n, const char *format, ...);
#else
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

inline unsigned long __strlen(const char * s) { return ::strlen(s); }
inline int __strcmp(const char * x, const char * y){ return ::strcmp(x, y); }
inline int __strncmp(const char * x, const char * y, __SIZE_TYPE__ n){ return ::strncmp(x, y, n); }
inline int __snprintf(char *str, __SIZE_TYPE__ n, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int result = vsnprintf(str, n, format, ap);
    va_end(ap);
    return result;
}
#endif //


#endif // __X_CORE__STRING__HH__
