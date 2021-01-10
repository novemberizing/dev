#ifndef   __X__PAIR__HH__
#define   __X__PAIR__HH__

#include <x/single.hh>

namespace x
{
    template <typename A, typename B>
    class pair : public single<A>
    {
    protected:  B __second;
    public:     const B & second() const
                {
                    return this->__second;
                }
    public:     B & second()
                {
                    return this->__second;
                }
    public:     void second(const B & v)
                {
                    this->__second = v;
                }
    public:     void second(B && v)
                {
                    this->__second = x::move(v);
                }
    public:     pair<A, B> & operator=(const pair<A, B> & o)
                {
                    if(&o != this)
                    {
                        x::single<A>::operator=(o);
                        this->__second = o.__second;
                    }
                    return *this;
                }
    public:     pair<A, B> & operator=(pair<A, B> && o) noexcept
                {
                    if(&o != this)
                    {
                        x::single<A>::operator=(x::move(o));
                        this->__second = x::move(o.__second);
                    }
                    return *this;
                }
    public:     pair(const A & first) :
                    single<A>(first),
                    __second()
                {
                }
    public:     pair(A && first) :
                    single<A>(x::move(first)),
                    __second()
                {
                }
    public:     pair(const A & first, const B & second) :
                    single<A>(first),
                    __second(second)
                {
                }
    public:     pair(const A & first, B && second) :
                    single<A>(first),
                    __second(x::move(second))
                {
                }
    public:     pair(A && first, const B & second) :
                    single<A>(x::move(first)),
                    __second(second)
                {
                }
    public:     pair(A && first, B && second) :
                    single<A>(x::move(first)),
                    __second(x::move(second))
                {
                }
    public:     pair() :
                    single<A>(),
                    __second()
                {
                }
    public:     pair(const pair<A, B> & o) :
                    single<A>(o),
                    __second(o.__second)
                {
                }
    public:     pair(pair<A, B> && o) noexcept :
                    single<A>(x::move(o)),
                    __second(x::move(o.__second))
                {
                }
    public:     ~pair() override
                {
                }
    };
}

#endif // __X__PAIR__HH__
