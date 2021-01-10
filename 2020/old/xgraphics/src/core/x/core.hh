#ifndef   __X__CORE__HH__
#define   __X__CORE__HH__

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/time.h>

#include <functional>
#include <initializer_list>
#include <exception>

namespace x
{
    inline void * __core_malloc(size_t n)
    {
        return ::malloc(n);
    }

    inline void __core_free(void * o)
    {
        ::free(o);
    }

    inline void * __core_realloc(void * o, size_t n)
    {
        return ::realloc(o, n);
    }

    inline void * __core_memcpy(void * destination, const void * source, size_t n)
    {
        return ::memcpy(destination, source, n);
    }

    inline void * __core_memmove(void * destination, const void * source, size_t n)
    {
        return ::memmove(destination, source, n);
    }

    inline int __core_random()
    {
        return ::random();
    }

    inline time_t __core_time(time_t * tloc)
    {
        return ::time(tloc);
    }

    inline void __core_srandom(unsigned int seed)
    {
        ::srandom(seed);
    }

    inline int __core_strcmp(const char * x, const char * y)
    {
        return ::strcmp(x, y);
    }

    inline int __core_strncmp(const char * x, const char * y, size_t n)
    {
        return ::strncmp(x, y, n);
    }

    inline size_t __core_strlen(const char * s)
    {
        return ::strlen(s);
    }

    inline int __core_close(int fd)
    {
        return ::close(fd);
    }

    inline int __core_snprintf(char *str, size_t size, const char *format, ...)
    {
        va_list ap;
        va_start(ap, format);
        int result = ::vsnprintf(str, size, format, ap);
        va_end(ap);
        return result;
    }

    inline int __core_printf(const char * format, ...)
    {
        va_list ap;
        va_start(ap, format);
        int result = ::vprintf(format, ap);
        va_end(ap);
        return result;
    }

    inline int __core_stdout_fileno_get()
    {
        return STDOUT_FILENO;
    }

    inline int __core_stdin_fileno_get()
    {
        return STDIN_FILENO;
    }

    inline ssize_t __core_write(int fd, const void *buf, size_t count)
    {
        return ::write(fd, buf, count);
    }

    inline int __core_error_get()
    {
        return errno;
    }

    inline int __core_error_again()
    {
        return EAGAIN;
    }

    inline void __core_nonblock(int fd)
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

    inline int __core_nonblock_status_get(int fd)
    {
        int flags = fcntl(fd, F_GETFL, 0);
        return (flags & O_NONBLOCK) ? 1 : 0;
    }

    inline void __core_block(int fd)
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

    inline ssize_t __core_read(int fd, void *buf, size_t count)
    {
        return ::read(fd, buf, count);
    }

    inline int __core_open(const char *pathname, int flags)
    {
        return ::open(pathname, flags);
    }
    inline int __core_open(const char *pathname, int flags, mode_t mode)
    {
        return ::open(pathname, flags, mode);
    }

    inline unsigned int __core_open_flags_read_only()
    {
        return O_RDONLY;
    }

    inline unsigned int __core_open_flags_nonblock()
    {
        return O_NONBLOCK;
    }

    inline double __core_strtod(const char *nptr, char **endptr)
    {
        return ::strtod(nptr, endptr);
    }

    inline float __core_strtof(const char *nptr, char **endptr)
    {
        return ::strtof(nptr, endptr);
    }

    inline long int __core_strtol(const char *nptr, char **endptr, int base)
    {
        return ::strtol(nptr, endptr, base);
    }

    inline off_t __core_lseek(int fd, off_t offset, int whence)
    {
        return ::lseek(fd, offset, whence);
    }

    inline int __core_seek_cur_get()
    {
        return SEEK_CUR;
    }

    inline int __core_seek_end_get()
    {
        return SEEK_END;
    }

    inline int __core_seek_set_get()
    {
        return SEEK_SET;
    }

    inline unsigned long __core_stat_file_type(const char * path)
    {
        struct stat buf;
        if(::stat(path, &buf) == 0)
        {
            if(buf.st_mode & S_IFREG)
            {
                return 0x00000010UL;
            }
            else if(buf.st_mode & S_IFDIR)
            {
                return 0x00000004UL;
            }
            else
            {
                // CURRENT NOT SUPPORT
                return 0x00000001UL;
            }
        }
        return 0;
    }

    inline void * __core_opendir(const char * path)
    {
        return ::opendir(path);
    }
    inline char * __core_readdir_name(void * p, char * out)
    {
        struct dirent * ent = ::readdir((DIR *) p);
        if(ent)
        {
            ::strcpy(out, ent->d_name);
            return out;
        }
        return nullptr;
    }
    inline void __core_closedir(void * p)
    {
        if(p)
        {
            ::closedir((DIR *) p);
        }
    }

    inline char * __core_getcwd(char *buf, size_t size)
    {
        return ::getcwd(buf, size);
    }

    inline void __core_gettimeofday(long & second, long & micro)
    {
        struct timeval tv;
        gettimeofday(&tv, nullptr);

        second = tv.tv_sec;
        micro = tv.tv_usec;
    }
}

namespace x
{
    typedef __INT8_TYPE__       int8;
    typedef __INT16_TYPE__      int16;
    typedef __INT32_TYPE__      int32;
    typedef __INT64_TYPE__      int64;
    typedef __UINT8_TYPE__      uint8;
    typedef __UINT16_TYPE__     uint16;
    typedef __UINT32_TYPE__     uint32;
    typedef __UINT64_TYPE__     uint64;
    typedef char                character;
    typedef unsigned char       byte;
    typedef bool                boolean;
    typedef float               float32;
    typedef double              float64;
    typedef float               real;

    const x::int32 invalid = -1;
    const x::int32 fail = -1;
    const x::int32 success = 0;
    const x::int32 forward = 1;
    const x::int32 backward = -1;

    template <typename T> struct var { typedef T type; };

    template <typename T> using function = std::function<T>;
    template <typename T> using initializer = std::initializer_list<T>;

    template <typename T> struct __reference_remove_tag { typedef T type; };
    template <typename T> struct __reference_remove_tag<T &> { typedef T type; };
    template <typename T> struct __reference_remove_tag<T &&> { typedef T type; };

    template <typename T> constexpr typename __reference_remove_tag<T>::type && move(T && o) noexcept
    {
        return static_cast<typename __reference_remove_tag<T>::type &&>(o);
    }

    class exception : public std::exception
    {
    public:     template <typename T> static void safe(x::function<void (T)> f, T o)
                {
                    if(f)
                    {
                        try
                        {
                            f(o);
                        }
                        catch(const x::exception & e)
                        {

                        }
                    }
                }
    public:     template <typename T, typename U> static void safe(x::function<void (T, U)> f, T first, U second)
                {
                    if(f)
                    {
                        try
                        {
                            f(first, second);
                        }
                        catch(const x::exception & e)
                        {

                        }
                    }
                }
    public:     const char * what() const noexcept override { return "exception"; }
    public:     x::exception & operator=(const x::exception & o)
                {
                    return *this;
                }
    public:     x::exception & operator=(x::exception && o) noexcept
                {
                    return *this;
                }
    public:     exception()
                {
                }
    public:     exception(const x::exception & o)
                {
                }
    public:     exception(x::exception && o) noexcept
                {
                }
    public:     ~exception() override
                {
                }
    };

    class paging
    {
    public:     static const x::uint64 size = 64L;
    public:     static x::uint64 get(x::uint64 n)
                {
                    return n == 0 ? x::paging::size : n;
                }
    public:     static x::uint64 calculate(x::uint64 n, x::uint64 size)
                {
                    size = (size == 0 ? x::paging::size : size);
                    return (n / size + 1) * size;
                }
    public:     static x::uint64 calculate(x::uint64 n)
                {
                    return x::paging::calculate(n, x::paging::size);
                }
    public:     x::paging & operator=(const x::paging & o) = delete;
    public:     x::paging & operator=(x::paging && o) noexcept = delete;
    public:     paging() = delete;
    public:     paging(const paging & o) = delete;
    public:     paging(paging && o) noexcept = delete;
    public:     virtual ~paging() = delete;
    };

    namespace memory
    {
        template <typename T>
        T * allocate(x::uint64 n)
        {
            if(n > 0)
            {
                return reinterpret_cast<T *>(__core_malloc(sizeof(T) * n));
            }
            return nullptr;
        }

        template <typename T>
        T * deallocate(T * o)
        {
            if(o != nullptr)
            {
                __core_free(o);
            }
            return nullptr;
        }

        template <typename T>
        T * allocate(T * o, x::uint64 n)
        {
            if(n > 0)
            {
                if(o != nullptr)
                {
                    return reinterpret_cast<T *>(__core_realloc(o, sizeof(T) * n));
                }
                else
                {
                    return reinterpret_cast<T *>(__core_malloc(sizeof(T) * n));
                }
            }
            else
            {
                if(o)
                {
                    __core_free(o);
                }
                return nullptr;
            }
        }

        template <typename T>
        T * destruct(T * o)
        {
            if(o)
            {
                o->~T();
            }
            return o;
        }

        template <typename T>
        T * destruct(T * o, x::uint64 n)
        {
            if(o)
            {
                for(x::uint64 i = 0; i < n; i++)
                {
                    o[i].~T();
                }
            }
            return o;
        }

        template <typename T>
        T * construct(T * destination, const T & item)
        {
            if(destination)
            {
                new (destination) T(item);
            }
            return destination;
        }

        template <typename T>
        T * construct(T * destination, T && item)
        {
            if(destination)
            {
                new (destination) T(x::move(item));
            }
            return destination;
        }

        template <typename T>
        T * construct(T * destination, const T & item, x::uint64 n)
        {
            if(destination)
            {
                for(x::uint64 i = 0; i < n; i++)
                {
                    new (&destination[i]) T(item);
                }
            }
            return destination;
        }

        template <typename T>
        T * copy(T * destination, const x::initializer<T> & list)
        {
            if(destination)
            {
                T * o = destination;
                for(typename x::initializer<T>::iterator it = list.begin(); it != list.end(); ++it, ++o)
                {
                    new (o) T(*it);
                }
            }
            return destination;
        }

        template <typename T>
        T * copy(T * destination, const T * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                for(x::uint64 i = 0; i < n; i++)
                {
                    new (&destination[i]) T(source[i]);
                }
            }
            return destination;
        }

        template <typename T>
        T * move(T * destination, T * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                for(x::uint64 i = 0; i < n; i++)
                {
                    new (&destination[i]) T(x::move(source[i]));
                }
            }
            return destination;
        }
    }

    namespace keyboard
    {
        inline const x::uint32 unknown = -1U;
        inline const x::uint32 up = 1U;
        inline const x::uint32 down = 2U;
        inline const x::uint32 left = 3U;
        inline const x::uint32 right = 4U;
        inline const x::uint32 top = 5U;
        inline const x::uint32 bottom = 6U;
    }

    namespace memory
    {
        template <>
        inline void * allocate<void>(x::uint64 n)
        {
            if(n > 0)
            {
                return __core_malloc(n);
            }
            return nullptr;
        }

        template <>
        inline void * allocate<void>(void * o, x::uint64 n)
        {
            if(n > 0)
            {
                if(o != nullptr)
                {
                    return __core_realloc(o, n);
                }
                else
                {
                    return __core_malloc(n);
                }
            }
            else
            {
                if(o)
                {
                    __core_free(o);
                }
                return nullptr;
            }
        }

        template <> inline void * destruct<void>(void * o){ return o; }
        template <> inline signed char * destruct<signed char>(signed char * o){ return o; }
        template <> inline char * destruct<char>(char * o){ return o; }
        template <> inline unsigned char * destruct<unsigned char>(unsigned char * o){ return o; }
        template <> inline short * destruct<short>(short * o){ return o; }
        template <> inline unsigned short * destruct<unsigned short>(unsigned short * o){ return o; }
        template <> inline int * destruct<int>(int * o){ return o; }
        template <> inline unsigned int * destruct<unsigned int>(unsigned int * o){ return o; }
        template <> inline long * destruct<long>(long * o){ return o; }
        template <> inline unsigned long * destruct<unsigned long>(unsigned long * o){ return o; }
        template <> inline long long * destruct<long long>(long long * o){ return o; }
        template <> inline unsigned long long * destruct<unsigned long long>(unsigned long long * o){ return o; }
        template <> inline float * destruct<float>(float * o){ return o; }
        template <> inline double * destruct<double>(double * o){ return o; }
        template <> inline long double * destruct<long double>(long double * o){ return o; }
        template <> inline bool * destruct<bool>(bool * o){ return o; }

        template <> inline void * destruct<void>(void * o, x::uint64 n){ return o; }
        template <> inline signed char * destruct<signed char>(signed char * o, x::uint64 n){ return o; }
        template <> inline char * destruct<char>(char * o, x::uint64 n){ return o; }
        template <> inline unsigned char * destruct<unsigned char>(unsigned char * o, x::uint64 n){ return o; }
        template <> inline short * destruct<short>(short * o, x::uint64 n){ return o; }
        template <> inline unsigned short * destruct<unsigned short>(unsigned short * o, x::uint64 n){ return o; }
        template <> inline int * destruct<int>(int * o, x::uint64 n){ return o; }
        template <> inline unsigned int * destruct<unsigned int>(unsigned int * o, x::uint64 n){ return o; }
        template <> inline long * destruct<long>(long * o, x::uint64 n){ return o; }
        template <> inline unsigned long * destruct<unsigned long>(unsigned long * o, x::uint64 n){ return o; }
        template <> inline long long * destruct<long long>(long long * o, x::uint64 n){ return o; }
        template <> inline unsigned long long * destruct<unsigned long long>(unsigned long long * o, x::uint64 n){ return o; }
        template <> inline float * destruct<float>(float * o, x::uint64 n){ return o; }
        template <> inline double * destruct<double>(double * o, x::uint64 n){ return o; }
        template <> inline long double * destruct<long double>(long double * o, x::uint64 n){ return o; }
        template <> inline bool * destruct<bool>(bool * o, x::uint64 n){ return o; }

        template <> inline void * copy<void>(void * destination, const void * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memcpy(destination, source, n);
            }
            return destination;
        }

        template <> inline char * copy<char>(char * destination, const char * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memcpy(destination, source, n);
            }
            return destination;
        }

        template <> inline signed char * copy<signed char>(signed char * destination, const signed char * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memcpy(destination, source, n);
            }
            return destination;
        }

        template <> inline unsigned char * copy<unsigned char>(unsigned char * destination, const unsigned char * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memcpy(destination, source, n);
            }
            return destination;
        }

        template <> inline short * copy<short>(short * destination, const short * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memcpy(destination, source, sizeof(short) * n);
            }
            return destination;
        }

        template <> inline unsigned short * copy<unsigned short>(unsigned short * destination, const unsigned short * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memcpy(destination, source, sizeof(unsigned short) * n);
            }
            return destination;
        }

        template <> inline int * copy<int>(int * destination, const int * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memcpy(destination, source, sizeof(int) * n);
            }
            return destination;
        }

        template <> inline unsigned int * copy<unsigned int>(unsigned int * destination, const unsigned int * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memcpy(destination, source, sizeof(unsigned int) * n);
            }
            return destination;
        }

        template <> inline long * copy<long>(long * destination, const long * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memcpy(destination, source, sizeof(long) * n);
            }
            return destination;
        }

        template <> inline unsigned long * copy<unsigned long>(unsigned long * destination, const unsigned long * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memcpy(destination, source, sizeof(unsigned long) * n);
            }
            return destination;
        }

        template <> inline long long * copy<long long>(long long * destination, const long long * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memcpy(destination, source, sizeof(long long) * n);
            }
            return destination;
        }

        template <> inline unsigned long long * copy<unsigned long long>(unsigned long long * destination, const unsigned long long * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memcpy(destination, source, sizeof(unsigned long long) * n);
            }
            return destination;
        }

        template <> inline float * copy<float>(float * destination, const float * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memcpy(destination, source, sizeof(float) * n);
            }
            return destination;
        }

        template <> inline double * copy<double>(double * destination, const double * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memcpy(destination, source, sizeof(double) * n);
            }
            return destination;
        }

        template <> inline long double * copy<long double>(long double * destination, const long double * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memcpy(destination, source, sizeof(long double) * n);
            }
            return destination;
        }

        template <> inline bool * copy<bool>(bool * destination, const bool * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memcpy(destination, source, sizeof(bool) * n);
            }
            return destination;
        }

        template <> inline void * move<void>(void * destination, void * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memmove(destination, source, n);
            }
            return destination;
        }

        template <> inline char * move<char>(char * destination, char * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memmove(destination, source, n);
            }
            return destination;
        }

        template <> inline signed char * move<signed char>(signed char * destination, signed char * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memmove(destination, source, n);
            }
            return destination;
        }

        template <> inline unsigned char * move<unsigned char>(unsigned char * destination, unsigned char * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memmove(destination, source, n);
            }
            return destination;
        }

        template <> inline short * move<short>(short * destination, short * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memmove(destination, source, sizeof(short) * n);
            }
            return destination;
        }

        template <> inline unsigned short * move<unsigned short>(unsigned short * destination, unsigned short * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memmove(destination, source, sizeof(unsigned short) * n);
            }
            return destination;
        }

        template <> inline int * move<int>(int * destination, int * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memmove(destination, source, sizeof(int) * n);
            }
            return destination;
        }

        template <> inline unsigned int * move<unsigned int>(unsigned int * destination, unsigned int * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memmove(destination, source, sizeof(unsigned int) * n);
            }
            return destination;
        }

        template <> inline long * move<long>(long * destination, long * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memmove(destination, source, sizeof(long) * n);
            }
            return destination;
        }

        template <> inline unsigned long * move<unsigned long>(unsigned long * destination, unsigned long * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memmove(destination, source, sizeof(unsigned long) * n);
            }
            return destination;
        }

        template <> inline long long * move<long long>(long long * destination, long long * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memmove(destination, source, sizeof(long long) * n);
            }
            return destination;
        }

        template <> inline unsigned long long * move<unsigned long long>(unsigned long long * destination, unsigned long long * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memmove(destination, source, sizeof(unsigned long long) * n);
            }
            return destination;
        }

        template <> inline float * move<float>(float * destination, float * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memmove(destination, source, sizeof(float) * n);
            }
            return destination;
        }

        template <> inline double * move<double>(double * destination, double * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memmove(destination, source, sizeof(double) * n);
            }
            return destination;
        }

        template <> inline long double * move<long double>(long double * destination, long double * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memmove(destination, source, sizeof(long double) * n);
            }
            return destination;
        }

        template <> inline bool * move<bool>(bool * destination, bool * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __core_memmove(destination, source, sizeof(bool) * n);
            }
            return destination;
        }
    }
}

#define exceptional() do {                      \
    printf("%s:%d\n", __FILE__, __LINE__);      \
    throw x::exception();                       \
} while(0)

#define assertion(condition) do {               \
    if(condition) {                             \
        printf("%s:%d\n", __FILE__, __LINE__);  \
        throw x::exception();                   \
    }                                           \
} while(0)

#endif // __X__CORE__HH__
