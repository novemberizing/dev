#ifndef   __X__COLLECTION__HH__
#define   __X__COLLECTION__HH__

#include <x/function.hh>
#include <x/container.hh>

namespace x
{
    template <typename T>
    class collection : public x::container
    {
    public:     virtual void add(const T & item) = 0;
    public:     virtual void add(T && item) = 0;
    public:     virtual void clear() = 0;
    public:     virtual void clear(x::function<void (T &&)> f) = 0;
    public:     virtual void each(x::function<void (const T &)> f) const = 0;
    public:     x::collection<T> & operator=(const x::collection<T> & o) = delete;
    public:     x::collection<T> & operator=(x::collection<T> && o) noexcept = delete;
    protected:  collection() : container()
                {
                }
    public:     collection(const x::collection<T> & o) = delete;
    public:     collection(x::collection<T> && o) noexcept = delete;
    public:     ~collection() override
                {
                }
    };
}

#endif // __X__COLLECTION__HH__
