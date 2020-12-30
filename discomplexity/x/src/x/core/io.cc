#include "io.hh"

#if 0
#include <iostream>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

int __stdout_fileno_get()
{
    return STDOUT_FILENO;
}

int __stdin_fileno_get()
{
    return STDIN_FILENO;
}

void __console_out(const char * s)
{
    std::cout << s;
}

void __console_out(int v)
{
    std::cout << v;
}

void * __malloc(size_t size)
{
    return malloc(size);
}

void __free(void *ptr)
{
    free(ptr);
}

void * __calloc(size_t nmemb, size_t size)
{
    return calloc(nmemb, size);
}

void * __realloc(void *ptr, size_t size)
{
    return realloc(ptr, size);
}

void * __memcpy(void *dest, const void *src, __SIZE_TYPE__ n)
{
    return memcpy(dest, src, n);
}

void * __memset(void *s, int c, __SIZE_TYPE__ n)
{
    return memset(s, c, n);
}

void * __memmove(void *dest, const void *src, __SIZE_TYPE__ n)
{
    return memmove(dest, src, n);
}

int __close(int fd)
{
    return ::close(fd);
}

void __nonblock(int fd)
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

int __nonblock_status_get(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    return (flags & O_NONBLOCK) ? 1 : 0;
}

void __block(int fd)
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

long __write(int fd, const void *buf, __SIZE_TYPE__ count)
{
    return ::write(fd, buf, count);
}

long __read(int fd, void * buf, __SIZE_TYPE__ count)
{
    return ::read(fd, buf, count);
}

int __error_number_get()
{
    return errno;
}

int __error_number_again_get()
{
    return EAGAIN;
}
#endif // 0
