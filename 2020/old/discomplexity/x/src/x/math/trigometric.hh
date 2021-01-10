#ifndef   __X_MATH__TRIGONOMETRIC__HH__
#define   __X_MATH__TRIGONOMETRIC__HH__

#include <x/type.hh>
#include <x/exception.hh>

namespace x
{
    namespace math
    {

        template <typename T>
        T radian(T degree)
        {
            return degree * 0.01745329251994329576923690768489f;
        }

        template <typename T>
        T degree(T radian)
        {
            return radian * 57.295779513082320876798154814105f;
        }

        template <typename T>
        T cos(T x)
        {
            return __builtin_cos(x);
        }

        template <typename T>
        T sin(T x)
        {
            return __builtin_sin(x);
        }

        template <typename T>
        T tan(T x)
        {
            return __builtin_tan(x);
        }

        template <typename T>
        T acos(T x)
        {
            return __builtin_acos(x);
        }

        template <typename T>
        T asin(T x)
        {
            return __builtin_asin(x);
        }

        template <typename T>
        T atan(T x)
        {
            return __builtin_atan(x);
        }

        const x::float32 pi = 3.141592f;
    }
}

#endif // __X_MATH__TRIGONOMETRIC__HH__
