#ifndef   __X__CONTAINER__HH__
#define   __X__CONTAINER__HH__

#include <x/core.hh>

namespace x
{
    class container
    {
    public:     virtual x::uint64 size() const = 0;
    public:     virtual x::boolean empty() const = 0;
    public:     virtual void clear() = 0;
    public:     x::container & operator=(const x::container & o) = delete;
    public:     x::container & operator=(x::container && o) noexcept = delete;
    public:     container()
                {
                }
    public:     container(const x::container & o) = delete;
    public:     container(x::container && o) noexcept = delete;
    public:     virtual ~container()
                {
                }
    };
}

#endif // __X__CONTAINER__HH__
