#ifndef   __X_CORE__IO__HH__
#define   __X_CORE__IO__HH__

#if 0
extern int __error_number_get();
extern int __error_number_again_get();
extern void __console_out(const char * s);
extern void __console_out(int v);
extern void * __malloc(__SIZE_TYPE__ size);
extern void __free(void *ptr);
extern void * __calloc(__SIZE_TYPE__ nmemb, __SIZE_TYPE__ size);
extern void * __realloc(void *ptr, __SIZE_TYPE__ size);
extern void * __memcpy(void *dest, const void *src, __SIZE_TYPE__ n);
extern void * __memset(void *s, int c, __SIZE_TYPE__ n);
extern void * __memmove(void *dest, const void *src, __SIZE_TYPE__ n);

extern int __close(int fd);

extern void __nonblock(int fd);
extern void __block(int fd);
extern int __nonblock_status_get(int fd);
extern int __stdout_fileno_get();
extern int __stdin_fileno_get();

extern long __write(int fd, const void *buf, __SIZE_TYPE__ count);
extern long __read(int fd, void * buf, __SIZE_TYPE__ count);
#else
#include <iostream>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

inline int __stdout_fileno_get()
{
    return STDOUT_FILENO;
}

inline int __stdin_fileno_get()
{
    return STDIN_FILENO;
}

inline void __console_out(const char * s)
{
    std::cout << s;
}

inline void __console_out(int v)
{
    std::cout << v;
}

inline void * __malloc(size_t size)
{
    return malloc(size);
}

inline void __free(void *ptr)
{
    free(ptr);
}

inline void * __calloc(size_t nmemb, size_t size)
{
    return calloc(nmemb, size);
}

inline void * __realloc(void *ptr, size_t size)
{
    return realloc(ptr, size);
}

inline void * __memcpy(void *dest, const void *src, __SIZE_TYPE__ n)
{
    return memcpy(dest, src, n);
}

inline void * __memset(void *s, int c, __SIZE_TYPE__ n)
{
    return memset(s, c, n);
}

inline void * __memmove(void *dest, const void *src, __SIZE_TYPE__ n)
{
    return memmove(dest, src, n);
}

inline int __close(int fd)
{
    return ::close(fd);
}

inline void __nonblock(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if(flags != -1)
    {
        if(fcntl(fd, F_SETFL, flags | O_NONBLOCK) != -1)
        {

        }
        else
        {
            // exceptional();
        }
    }
    else
    {
        // exceptional();
    }
}

inline int __nonblock_status_get(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    return (flags & O_NONBLOCK) ? 1 : 0;
}

inline void __block(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if(flags != -1)
    {
        if(fcntl(fd, F_SETFL, flags & (~O_NONBLOCK)) != -1)
        {

        }
        else
        {
            // exceptional();
        }
    }
    else
    {
        // exceptional();
    }
}

inline long __write(int fd, const void *buf, __SIZE_TYPE__ count)
{
    return ::write(fd, buf, count);
}

inline long __read(int fd, void * buf, __SIZE_TYPE__ count)
{
    return ::read(fd, buf, count);
}

inline int __error_number_get()
{
    return errno;
}

inline int __error_number_again_get()
{
    return EAGAIN;
}
#endif //

#endif // __X_CORE__IO__HH__
