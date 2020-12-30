#ifndef   __X_MATH__ROUNDING__HH__
#define   __X_MATH__ROUNDING__HH__

#include <x/exception.hh>

namespace x
{
    namespace math
    {
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
    }
}

#endif // __X_MATH__ROUNDING__HH__
