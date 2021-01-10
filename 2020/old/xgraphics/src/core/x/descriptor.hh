#ifndef   __X__DESCRIPTOR__HH__
#define   __X__DESCRIPTOR__HH__

#include <x/event.hh>

namespace x
{
    class descriptor : public x::event::object
    {
    public:     class status
                {
                public:     static const x::uint32 none     = 0x00000000U <<  0U;
                public:     static const x::uint32 readable = 0x00000001U <<  0U;
                public:     static const x::uint32 writable = 0x00000001U <<  1U;
                };
    protected:  x::int32 __value;
    protected:  x::uint32 __wait;
    protected:  x::uint32 __status;
    public:     inline x::int32 value() const
                {
                    return __value;
                }
    public:     inline void value(x::int32 v)
                {
                    __value = v;
                }
    public:     virtual x::boolean interest(x::uint32 type)
                {
                    if(__wait & type)
                    {
                        return true;
                    }
                    if(type == x::event::io::type::read)
                    {
                        if(__status & x::descriptor::status::readable)
                        {
                            return false;
                        }
                        return true;
                    }
                    if(type == x::event::io::type::write)
                    {
                        if(__status & x::descriptor::status::writable)
                        {
                            return false;
                        }
                        return true;
                    }
                    return false;
                }
    public:     virtual void wait(x::uint32 type)
                {
                    __wait |= type;
                }
    public:     virtual void open(x::boolean nonblocking) = 0;
    public:     virtual void close()
                {
                    if(__value >= 0)
                    {
                        __core_close(__value);
                        __value = x::invalid;
                    }
                }
    public:     x::event::object * safe(x::uint32 type) override
                {
                    if(type == x::event::type::io)
                    {
                        return this;
                    }
                    return nullptr;
                }
    public:     void on(x::uint32 id, x::event::engine * engine, x::event::generator * generator) override
                {
                    if(generator->type() == x::event::type::io)
                    {
                        if(id == x::event::io::type::read)
                        {
                            __wait &= (~x::event::io::type::read);
                            // TODO SOMETHING
                        }
                        if(id == x::event::io::type::write)
                        {
                            __wait &= (~x::event::io::type::write);
                            // TODO SOMETHING
                        }
                        if(id == x::event::io::type::close)
                        {
                            __wait &= (~x::event::io::type::close);
                            // TODO SOMETHING
                        }
                    }
                }
    public:     x::descriptor & operator=(const x::descriptor & o)
                {
                    if(&o != this)
                    {
                        x::event::object::operator=(o);

                        __value = o.__value;
                        __wait = o.__wait;
                        __status = o.__status;
                    }
                    return *this;
                }
    public:     x::descriptor & operator=(x::descriptor && o) noexcept
                {
                    if(&o != this)
                    {
                        x::event::object::operator=(x::move(o));

                        __value = o.__value;
                        __wait = o.__wait;
                        __status = o.__status;

                        o.__value = x::invalid;
                        o.__wait = x::event::type::none;
                        o.__status = x::event::type::none;
                    }
                    return *this;
                }
    protected:  descriptor(x::int32 value, x::uint32 status)
                :   x::event::object(),
                    __value(value),
                    __wait(x::event::type::none),
                    __status(status)
                {
                }
    public:     descriptor()
                :   x::event::object(),
                    __value(x::invalid),
                    __wait(x::event::type::none),
                    __status(x::event::type::none)
                {
                }
    public:     descriptor(const x::descriptor & o)
                :   x::event::object(o),
                    __value(o.__value),
                    __wait(o.__wait),
                    __status(o.__status)
                {
                }
    public:     descriptor(x::descriptor && o) noexcept
                :   x::event::object(x::move(o)),
                    __value(o.__value),
                    __wait(o.__wait),
                    __status(o.__status)
                {
                    o.__value = x::invalid;
                    o.__wait = x::event::type::none;
                    o.__status = x::event::type::none;
                }
    public:     ~descriptor() override
                {
                    close();

                    __value = x::invalid;
                    __wait = x::event::type::none;
                    __status = x::event::type::none;
                }
    };
}

#endif // __X__DESCRIPTOR__HH__
