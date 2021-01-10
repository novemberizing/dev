#ifndef   __X__PAIR__HH__
#define   __X__PAIR__HH__

#include <x/single.hh>

namespace x
{
    template <typename A, typename B>
    class pair : public single<A>
    {
    protected:  B __second;
    public:     inline B & second()
                {
                    return __second;
                }
    public:     inline const B & second() const
                {
                    return __second;
                }
    public:     inline void second(const B & v)
                {
                    __second = v;
                }
    public:     inline void second(B && v)
                {
                    __second = x::move(v);
                }
    public:     x::pair<A, B> & operator=(const x::pair<A, B> & o)
                {
                    if(&o != this)
                    {
                        x::single<A>::operator=(o);
                        __second = o.__second;
                    }
                    return *this;
                }
    public:     x::pair<A, B> & operator=(x::pair<A, B> && o) noexcept
                {
                    if(&o != this)
                    {
                        x::single<A>::operator=(x::move(o));
                        __second = x::move(o.__second);
                    }
                    return *this;
                }
    public:     pair(const A & first)
                :   x::single<A>(first),
                    __second()
                {
                }
    public:     pair(A && first)
                :   x::single<A>(x::move(first)),
                    __second()
                {
                }
    public:     pair(const A & first, const B & second)
                :   x::single<A>(first),
                    __second(second)
                {
                }
    public:     pair(const A & first, const B && second)
                :   x::single<A>(first),
                    __second(x::move(second))
                {
                }
    public:     pair(A && first, const B & second)
                :   x::single<A>(x::move(first)),
                    __second(second)
                {
                }
    public:     pair(A && first, const B && second)
                :   x::single<A>(x::move(first)),
                    __second(x::move(second))
                {
                }
    public:     pair()
                :   x::single<A>(),
                    __second()
                {
                }
    public:     pair(const x::pair<A, B> & o)
                :   x::single<A>(o),
                    __second(o.__second)
                {
                }
    public:     pair(x::pair<A, B> && o) noexcept
                :   x::single<A>(x::move(o)),
                    __second(x::move(o.__second))
                {
                }
    public:     ~pair() override
                {
                }
    };
}

#endif // __X__PAIR__HH__
