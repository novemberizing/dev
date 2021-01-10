#ifndef   __X_CORE__MOVE__HH__
#define   __X_CORE__MOVE__HH__

namespace x
{
    template <typename T> struct __reference_remove_tag { typedef T type; };
    template <typename T> struct __reference_remove_tag<T &> { typedef T type; };
    template <typename T> struct __reference_remove_tag<T &&> { typedef T type; };

    template <typename T> constexpr typename __reference_remove_tag<T>::type && move(T && o) noexcept
    {
        return static_cast<typename __reference_remove_tag<T>::type &&>(o);
    }
}

#endif // __X_CORE__MOVE__HH__
