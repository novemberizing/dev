#ifndef   __X__MATH__HH__
#define   __X__MATH__HH__

#include <x/core.hh>

namespace x
{
    template <typename T>
    T log(T x)
    {
        return __builtin_log(x);
    }

    template <typename T>
    T exp(T x)
    {
        return __builtin_exp(x);
    }

    template <typename T>
    T sqrt(T x)
    {
        return __builtin_sqrt(x);
    }

    template <typename T>
    T pow(T x, T exponent)
    {
        return __builtin_pow(x, exponent);
    }

    template <typename T>
    T cosh(T x)
    {
        return __builtin_cosh(x);
    }

    template <typename T>
    T sinh(T x)
    {
        return __builtin_sinh(x);
    }

    template <typename T>
    T tanh(T x)
    {
        return __builtin_tanh(x);
    }

    template <typename T>
    T acosh(T x)
    {
        return __builtin_acosh(x);
    }

    template <typename T>
    T asinh(T x)
    {
        return __builtin_asinh(x);
    }

    template <typename T>
    T atanh(T x)
    {
        return __builtin_atanh(x);
    }

    template <typename T>
    T abs(T x)
    {
        return __builtin_fabs(x);
    }

    template <typename T>
    T max(T x, T y)
    {
        return __builtin_fmax(x, y);
    }

    template <typename T>
    T min(T x, T y)
    {
        return __builtin_fmin(x, y);
    }

    template <typename T>
    T clamp(T x, T min, T max)
    {
        return __builtin_fmax(__builtin_fmin(x, min), max);
    }

    template <typename T>
    T fraction(T x)
    {
        return x - __builtin_floor(x);
    }

    template <typename T>
    T mod(T x, T y)
    {
        return __builtin_fmod(x, y);
    }

    template <typename T>
    T truncate(T x)
    {
        return __builtin_trunc(x);
    }

    template <typename T>
    T ceil(T x)
    {
        return __builtin_ceil(x);
    }

    template <typename T>
    T floor(T x)
    {
        return __builtin_floor(x);
    }

    template <typename T>
    T round(T x)
    {
        return __builtin_round(x);
    }

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

#endif // __X__MATH__HH__
