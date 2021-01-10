#ifndef   __X__QUEUE__HH__
#define   __X__QUEUE__HH__

#include <x/list.hh>

namespace x
{
    template <typename T>
    class queue : public x::list<T>
    {
    public:     void push(const T & v) override
                {
                    x::list<T>::push(v);
                }
    public:     void push(T && v) override
                {
                    x::list<T>::push(x::move(v));
                }
    public:     bool pop(function<void (T &&)> f) override
                {
                    return x::list<T>::pop(f);
                }
    public:     T pop() override
                {
                    return x::list<T>::pop();
                }
    public:     queue<T> & operator=(const queue<T> & o)
                {
                    if(&o != this)
                    {
                        x::list<T>::operator=(o);
                    }
                    return *this;
                }
    public:     queue<T> & operator=(queue<T> && o) noexcept
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
    public:     queue(const queue<T> & o)
                :   x::list<T>(o)
                {
                }
    public:     queue(queue<T> && o) noexcept
                :   x::list<T>(x::move(o))
                {
                }
    public:     ~queue() override
                {
                }
    };
}

#endif // __X__QUEUE__HH__
