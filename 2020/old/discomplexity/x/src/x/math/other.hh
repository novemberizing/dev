#ifndef   __X_MATH__OTHER__HH__
#define   __X_MATH__OTHER__HH__

namespace x
{
    namespace math
    {
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
    }
}

#endif // __X_MATH__OTHER__HH__
