#ifndef   __X__RESPONSE__HH__
#define   __X__RESPONSE__HH__

#include <x/type.hh>

namespace x
{
    class response
    {
    public:     response & operator=(const response & o)
                {
                    return *this;
                }
    public:     response & operator=(response && o) noexcept
                {
                    return *this;
                }
    public:     response()
                {
                }
    public:     response(const response & o)
                {
                }
    public:     response(response && o) noexcept
                {
                }
    public:     virtual ~response()
                {
                }
    };
}

#endif // __X__RESPONSE__HH__
