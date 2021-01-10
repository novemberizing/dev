#include "string.hh"

#if 0
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

unsigned long __strlen(const char * s) { return ::strlen(s); }
int __strcmp(const char * x, const char * y){ return ::strcmp(x, y); }
int __strncmp(const char * x, const char * y, __SIZE_TYPE__ n){ return ::strncmp(x, y, n); }


int __snprintf(char *str, __SIZE_TYPE__ n, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int result = vsnprintf(str, n, format, ap);
    va_end(ap);
    return result;
}
#endif // 0
