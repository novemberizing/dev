#ifndef   __X_MATH__HYPERBOLIC__HH__
#define   __X_MATH__HYPERBOLIC__HH__

namespace x
{
    namespace math
    {
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
    }
}

#endif // __X_MATH__HYPERBOLIC__HH__
