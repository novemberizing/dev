#ifndef   __X__SINGLE__HH__
#define   __X__SINGLE__HH__

#include <x/core.hh>

namespace x
{
    template <typename A>
    class single
    {
    protected:  A __first;
    public:     inline A & first()
                {
                    return __first;
                }
    public:     inline const A & first() const
                {
                    return __first;
                }
    public:     inline void first(const A & v)
                {
                    __first = v;
                }
    public:     inline void first(A && v)
                {
                    __first = x::move(v);
                }
    public:     x::single<A> & operator=(const x::single<A> & o)
                {
                    if(&o != this)
                    {
                        __first = o.__first;
                    }
                    return *this;
                }
    public:     x::single<A> & operator=(x::single<A> && o) noexcept
                {
                    if(&o != this)
                    {
                        __first = x::move(o.__first);
                    }
                    return *this;
                }
    public:     single(const A & v)
                :   __first(v)
                {
                }
    public:     single(A && v)
                :   __first(x::move(v))
                {
                }
    public:     single()
                :   __first()
                {
                }
    public:     single(const x::single<A> & o)
                :   __first(o.__first)
                {
                }
    public:     single(x::single<A> && o) noexcept
                :   __first(x::move(o.__first))
                {
                }
    public:     virtual ~single()
                {
                }
    };
}

#endif // __X__SINGLE__HH__
