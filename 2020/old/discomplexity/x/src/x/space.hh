#ifndef   __X__SPACE__HH__
#define   __X__SPACE__HH__

#include <x/type.hh>
#include <x/exception.hh>

namespace x
{
    template <typename T>
    class space
    {
    protected:  T __value;
    protected:  x::int64 __count;
    public:     inline x::int64 count() const
                {
                    return __count;
                }
    public:     inline x::int64 increase()
                {
                    __count = __count + 1;
                    return __count;
                }
    public:     inline x::int64 decrease()
                {
                    __count = __count - 1;
                    return __count;
                }
    public:     inline const T & get() const
                {
                    return __value;
                }
    public:     inline T & get()
                {
                    return __value;
                }
    public:     inline void set(const T & value)
                {
                    __value = value;
                }
    public:     inline void set(T && value)
                {
                    __value = x::move(value);
                }
    public:     x::space<T> & operator=(const x::space<T> & o) = delete;
    public:     x::space<T> & operator=(x::space<T> && o) noexcept = delete;
    public:     space()
                :   __value(),
                    __count(0)
                {
                }
    public:     space(const T & value)
                :   __value(value),
                    __count(0)
                {
                }
    public:     space(T && value)
                :   __value(x::move(value)),
                    __count(0)
                {

                }
    public:     space(const space<T> & o) = delete;
    public:     space(space<T> && o) noexcept = delete;
    public:     virtual ~space()
                {
                }
    };
}

#endif // __X__SPACE__HH__
