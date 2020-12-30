#ifndef   __X__VARIABLE__HH__
#define   __X__VARIABLE__HH__

#include <x/string.hh>

namespace x
{
    class variable
    {
    public:     static const x::uint64 unknown_type    = 0;
    public:     static const x::uint64 integer8_type   = 1;
    public:     static const x::uint64 integer16_type  = 2;
    public:     static const x::uint64 integer32_type  = 3;
    public:     static const x::uint64 integer64_type  = 4;
    public:     static const x::uint64 uinteger8_type  = 5;
    public:     static const x::uint64 uinteger16_type = 6;
    public:     static const x::uint64 uinteger32_type = 7;
    public:     static const x::uint64 uinteger64_type = 8;
    private:    x::string __name;
    private:    x::uint64 __type;
    public:     virtual x::uint64 type() const
                {
                    return __type;
                }
    public:     virtual const x::string & name() const
                {
                    return __name;
                }
    protected:  variable & operator=(const variable & o)
                {
                    if(&o != this)
                    {
                        __name = o.__name;
                        __type = o.__type;
                    }
                    return *this;
                }
    protected:  variable & operator=(variable && o) noexcept
                {
                    if(&o != this)
                    {
                        __name = x::move(o.__name);
                        __type = o.__type;
                    }
                    return *this;
                }
    protected:  variable(const x::string & name, x::uint64 type) :
                    __name(name),
                    __type(type)
                {
                }
    protected:  variable(x::string && name, x::uint64 type) :
                    __name(x::move(name)),
                    __type(type)
                {
                }
    protected:  variable() = delete;
    protected:  variable(const variable & o) :
                    __name(o.__name),
                    __type(o.__type)
                {
                }
    protected:  variable(variable && o) noexcept :
                    __name(x::move(o.__name)),
                    __type(o.__type)
                {
                }
    public:     virtual ~variable()
                {
                }
    };
}

#endif // __X__VARIABLE__HH__
