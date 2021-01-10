#ifndef   __X__COLLECTION__HH__
#define   __X__COLLECTION__HH__

#include <x/container.hh>

namespace x
{
    template <typename T>
    class collection : public x::container
    {
    public:     virtual void clear(x::function<void (T&&)> f) = 0;
    public:     virtual void each(x::function<void (const T &)> f) const = 0;
    public:     virtual void each(x::function<void (T &)> f) = 0;
    public:     x::collection<T> & operator=(const x::collection<T> & o) = delete;
    public:     x::collection<T> & operator=(x::collection<T> & o) = delete;
    public:     collection()
                :   x::container()
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
