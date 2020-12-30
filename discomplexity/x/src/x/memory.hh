#ifndef   __X__MEMORY__HH__
#define   __X__MEMORY__HH__

#include <x/type.hh>
#include <x/initializer.hh>

namespace x
{
    namespace memory
    {
        template <typename T>
        T * allocate(x::uint64 n)
        {
            if(n > 0)
            {
                return reinterpret_cast<T *>(__malloc(sizeof(T) * n));
            }
            return nullptr;
        }

        template <typename T>
        T * allocate(T * destination, x::uint64 n)
        {
            if(n > 0)
            {
                if(destination)
                {
                    return reinterpret_cast<T *>(__realloc(destination, sizeof(T) * n));
                }
                else
                {
                    return reinterpret_cast<T *>(__malloc(sizeof(T) * n));
                }
            }
            else
            {
                if(destination)
                {
                    ::free(destination);
                }
                return nullptr;
            }
        }

        template <typename T>
        T * deallocate(T * destination)
        {
            if(destination)
            {
                ::free(destination);
            }
            return nullptr;
        }

        template <typename T>
        T * set(T * destination, const T & value)
        {
            if(destination)
            {
                new (destination) T(value);
            }
            return destination;
        }

        template <typename T>
        T * set(T * destination, T && value)
        {
            if(destination)
            {
                new (destination) T(x::move(value));
            }
            return destination;
        }

        template <typename T>
        T * set(T * destination, const T & value, x::uint64 n)
        {
            if(destination)
            {
                for(x::uint64 i = 0; i < n; i++)
                {
                    new (&destination[i]) T(value);
                }
            }
            return destination;
        }

        template <typename T>
        T * copy(T * destination, const x::initializer<T> & list)
        {
            if(destination && list.size() > 0)
            {
                T * pointer = destination;
                for(typename x::initializer<T>::iterator it = list.begin(); it != list.end(); ++it, ++pointer)
                {
                    new (pointer) T(*it);
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
                for(uint64 i = 0; i < n; i++)
                {
                    new (&destination[i]) T(x::move(source[i]));
                }
            }
            return destination;
        }

        template <typename T>
        T * del(T * destination)
        {
            if(destination)
            {
                destination->~T();
            }
            return destination;
        }

        template <typename T>
        T * del(T * destination, x::uint64 n)
        {
            if(destination)
            {
                for(x::uint64 i = 0; i < n; i++)
                {
                    destination[i].~T();
                }
            }
            return destination;
        }

        template <>
        inline void * allocate<void>(void * destination, x::uint64 n)
        {
            if(n > 0)
            {
                if(destination)
                {
                    return __realloc(destination, n);
                }
                else
                {
                    return __malloc(n);
                }
            }
            else
            {
                if(destination)
                {
                    ::free(destination);
                }
                return nullptr;
            }
        }

        template <>
        inline void * allocate<void>(x::uint64 n)
        {
            if(n > 0)
            {
                return __malloc(n);
            }
            return 0;
        }

        template <>
        inline void * copy<void>(void * destination, const void * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, n);
            }
            return destination;
        }

        template <>
        inline char * copy<char>(char * destination, const char * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, n);
            }
            return destination;
        }

        template <>
        inline signed char * copy<signed char>(signed char * destination, const signed char * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, n);
            }
            return destination;
        }

        template <>
        inline unsigned char * copy<unsigned char>(unsigned char * destination, const unsigned char * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, n);
            }
            return destination;
        }

        template <>
        inline x::int16 * copy<x::int16>(x::int16 * destination, const x::int16 * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, sizeof(x::int16) * n);
            }
            return destination;
        }

        template <>
        inline x::int32 * copy<x::int32>(x::int32 * destination, const x::int32 * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, sizeof(x::int32) * n);
            }
            return destination;
        }

        template <>
        inline x::int64 * copy<x::int64>(x::int64 * destination, const x::int64 * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, sizeof(x::int64) * n);
            }
            return destination;
        }

        template <>
        inline x::uint16 * copy<x::uint16>(x::uint16 * destination, const x::uint16 * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, sizeof(x::uint16) * n);
            }
            return destination;
        }

        template <>
        inline x::uint32 * copy<x::uint32>(x::uint32 * destination, const x::uint32 * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, sizeof(x::uint32) * n);
            }
            return destination;
        }

        template <>
        inline x::uint64 * copy<x::uint64>(x::uint64 * destination, const x::uint64 * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, sizeof(x::uint64) * n);
            }
            return destination;
        }

        template <>
        inline x::float32 * copy<x::float32>(x::float32 * destination, const x::float32 * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, sizeof(x::float32) * n);
            }
            return destination;
        }

        template <>
        inline x::float64 * copy<x::float64>(x::float64 * destination, const x::float64 * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, sizeof(x::float64) * n);
            }
            return destination;
        }

        template <>
        inline void * move<void>(void * destination, void * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, n);
            }
            return destination;
        }

        template <>
        inline char * move<char>(char * destination, char * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, n);
            }
            return destination;
        }

        template <>
        inline signed char * move<signed char>(signed char * destination, signed char * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, n);
            }
            return destination;
        }

        template <>
        inline unsigned char * move<unsigned char>(unsigned char * destination, unsigned char * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, n);
            }
            return destination;
        }

        template <>
        inline x::int16 * move<x::int16>(x::int16 * destination, x::int16 * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, sizeof(x::int16) * n);
            }
            return destination;
        }

        template <>
        inline x::int32 * move<x::int32>(x::int32 * destination, x::int32 * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, sizeof(x::int32) * n);
            }
            return destination;
        }

        template <>
        inline x::int64 * move<x::int64>(x::int64 * destination, x::int64 * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, sizeof(x::int64) * n);
            }
            return destination;
        }

        template <>
        inline x::uint16 * move<x::uint16>(x::uint16 * destination, x::uint16 * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, sizeof(x::uint16) * n);
            }
            return destination;
        }

        template <>
        inline x::uint32 * move<x::uint32>(x::uint32 * destination, x::uint32 * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, sizeof(x::uint32) * n);
            }
            return destination;
        }

        template <>
        inline x::uint64 * move<x::uint64>(x::uint64 * destination, x::uint64 * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, sizeof(x::uint64) * n);
            }
            return destination;
        }

        template <>
        inline x::float32 * move<x::float32>(x::float32 * destination, x::float32 * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, sizeof(x::float32) * n);
            }
            return destination;
        }

        template <>
        inline x::float64 * move<x::float64>(x::float64 * destination, x::float64 * source, x::uint64 n)
        {
            if(destination && source && n)
            {
                __memcpy(destination, source, sizeof(x::float64) * n);
            }
            return destination;
        }

        template <>
        inline char * set<char>(char * destination, const char & value, x::uint64 n)
        {
            if(destination && n)
            {
                __memset(destination, value, n);
            }
            return destination;
        }

        template <>
        inline signed char * set<signed char>(signed char * destination, const signed char & value, x::uint64 n)
        {
            if(destination && n)
            {
                __memset(destination, value, n);
            }
            return destination;
        }

        template <>
        inline unsigned char * set<unsigned char>(unsigned char * destination, const unsigned char & value, x::uint64 n)
        {
            if(destination && n)
            {
                __memset(destination, value, n);
            }
            return destination;
        }

        template <> inline char * del<char>(char * destination){ return destination; }
        template <> inline signed char * del<signed char>(signed char * destination){ return destination; }
        template <> inline unsigned char * del<unsigned char>(unsigned char * destination){ return destination; }
        template <> inline x::int16 * del<x::int16>(x::int16 * destination){ return destination; }
        template <> inline x::int32 * del<x::int32>(x::int32 * destination){ return destination; }
        template <> inline x::int64 * del<x::int64>(x::int64 * destination){ return destination; }
        template <> inline x::uint16 * del<x::uint16>(x::uint16 * destination){ return destination; }
        template <> inline x::uint32 * del<x::uint32>(x::uint32 * destination){ return destination; }
        template <> inline x::uint64 * del<x::uint64>(x::uint64 * destination){ return destination; }
        template <> inline x::float32 * del<x::float32>(x::float32 * destination){ return destination; }
        template <> inline x::float64 * del<x::float64>(x::float64 * destination){ return destination; }

        template <> inline char * del<char>(char * destination, x::uint64 n){ return destination; }
        template <> inline signed char * del<signed char>(signed char * destination, x::uint64 n){ return destination; }
        template <> inline unsigned char * del<unsigned char>(unsigned char * destination, x::uint64 n){ return destination; }
        template <> inline x::int16 * del<x::int16>(x::int16 * destination, x::uint64 n){ return destination; }
        template <> inline x::int32 * del<x::int32>(x::int32 * destination, x::uint64 n){ return destination; }
        template <> inline x::int64 * del<x::int64>(x::int64 * destination, x::uint64 n){ return destination; }
        template <> inline x::uint16 * del<x::uint16>(x::uint16 * destination, x::uint64 n){ return destination; }
        template <> inline x::uint32 * del<x::uint32>(x::uint32 * destination, x::uint64 n){ return destination; }
        template <> inline x::uint64 * del<x::uint64>(x::uint64 * destination, x::uint64 n){ return destination; }
        template <> inline x::float32 * del<x::float32>(x::float32 * destination, x::uint64 n){ return destination; }
        template <> inline x::float64 * del<x::float64>(x::float64 * destination, x::uint64 n){ return destination; }
    }
}

#endif // __X__MEMORY__HH__
