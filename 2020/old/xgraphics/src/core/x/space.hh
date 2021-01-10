#ifndef   __X__SPACE__HH__
#define   __X__SPACE__HH__

#include <x/core.hh>

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
    public:     inline T & get()
                {
                    return __value;
                }
    public:     inline const T & get() const
                {
                    return __value;
                }
    public:     inline void set(const T & v)
                {
                    __value = v;
                }
    public:     inline void set(T && v)
                {
                    __value = x::move(v);
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
