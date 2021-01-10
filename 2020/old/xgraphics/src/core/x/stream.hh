#ifndef   __X__STREAM__HH__
#define   __X__STREAM__HH__

#include <x/core.hh>

namespace x
{
    template <typename IN, typename OUT>
    class stream
    {
    public:     virtual void push(const IN & item) = 0;
    public:     virtual void push(IN && item) = 0;
    public:     virtual void push(const IN & item, x::uint64 n) = 0;
    public:     virtual void push(const IN * source, x::uint64 n) = 0;
    public:     virtual OUT pop() = 0;
    public:     stream<IN, OUT> & operator=(const stream<IN, OUT> & o)
                {
                    if(&o != this)
                    {
                    }
                    return *this;
                }
    public:     stream<IN, OUT> & operator=(stream<IN, OUT> && o) noexcept
                {
                    if(&o != this)
                    {
                    }
                    return *this;
                }
    public:     stream()
                {
                }
    public:     stream(const stream<IN, OUT> & o)
                {
                }
    public:     stream(stream<IN, OUT> && o) noexcept
                {
                }
    public:     virtual ~stream()
                {
                }
    };
}

#endif // __X__STREAM__HH__
