#ifndef   __X__COMMAND__HH__
#define   __X__COMMAND__HH__

#include <x/request.hh>

namespace x
{
    class command : public request
    {
    public:     command & operator=(const command & o)
                {
                    if(&o != this)
                    {
                        x::request::operator=(o);
                    }
                    return *this;
                }
    public:     command & operator=(command && o) noexcept
                {
                    if(&o != this)
                    {
                        x::request::operator=(x::move(o));
                    }
                    return *this;
                }
    public:     command()
                :   x::request()
                {
                }
    public:     command(const command & o)
                :   x::request(o)
                {
                }
    public:     command(command && o) noexcept
                :   x::request(x::move(o))
                {
                }
    public:     ~command() override
                {
                }
    };
}

#endif // __X__COMMAND__HH__
