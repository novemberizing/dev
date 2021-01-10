#ifndef   __X_MATH__EXPONENTIAL__HH__
#define   __X_MATH__EXPONENTIAL__HH__

namespace x
{
    namespace math
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
    }
}

#endif // __X_MATH__EXPONENTIAL__HH__
