#ifndef   __X__QUEUE__HH__
#define   __X__QUEUE__HH__

#include <x/list.hh>

namespace x
{
    template <typename T>
    class queue : public x::list<T>
    {
    protected:  void each(x::function<void (const T &)> f) const override
                {
                    x::list<T>::each(f);
                }
    protected:  void each(x::function<void (T &)> f) override
                {
                    x::list<T>::each(f);
                }
    public:     x::queue<T> & operator=(const x::queue<T> & o)
                {
                    if(&o != this)
                    {
                        x::list<T>::operator=(o);
                    }
                    return *this;
                }
    public:     x::queue<T> & operator=(x::queue<T> && o) noexcept
                {
                    if(&o != this)
                    {
                        x::list<T>::operator=(x::move(o));
                    }
                    return *this;
                }
    public:     queue()
                :   x::list<T>()
                {
                }
    public:     queue(const x::queue<T> & o)
                :   x::list<T>(o)
                {
                }
    public:     queue(x::queue<T> && o) noexcept
                :   x::list<T>(x::move(o))
                {
                }
    public:     ~queue() override
                {
                }
    };
}

#endif // __X__QUEUE__HH__
