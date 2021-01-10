#ifndef   __X__REQUEST__HH__
#define   __X__REQUEST__HH__

#include <x/type.hh>

namespace x
{
    class request
    {
    public:     request & operator=(const request & o)
                {
                    return *this;
                }
    public:     request & operator=(request && o) noexcept
                {
                    return *this;
                }
    public:     request()
                {
                }
    public:     request(const request & o)
                {
                }
    public:     request(request && o) noexcept
                {
                }
    public:     virtual ~request()
                {
                }
    };
}

#endif // __X__REQUEST__HH__
