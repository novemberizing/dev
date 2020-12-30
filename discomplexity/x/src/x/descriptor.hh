#ifndef   __X__DESCRIPTOR__HH__
#define   __X__DESCRIPTOR__HH__

#include <x/type.hh>
#include <x/event.hh>

namespace x
{
    class descriptor : protected x::event::object
    {
    protected:  x::int32 __descriptor;
    protected:  x::uint32 __status;
    protected:  x::event::engine * __engine;
    public:     void on(x::uint32 id, x::event::engine * engine, x::event::generator * generator, x::event::processor * processor) override
                {
                    if(id == x::event::type::read)
                    {
                        __status |= x::event::object::status::readable;
                        __status &= (~x::event::object::status::wait::read);
                        this->read();
                    }
                    else if(id == x::event::type::write)
                    {
                        __status |= x::event::object::status::writable;
                        __status &= (~x::event::object::status::wait::write);
                    }
                    else
                    {
                        exceptional();
                    }
                }
    public:     void off(x::uint32 id, x::event::engine * engine, x::event::generator * generator) override
                {
                    if(id == x::event::type::read)
                    {
                        __status &= (~x::event::object::status::readable);
                    }
                    else if(id == x::event::type::write)
                    {
                        __status &= (~x::event::object::status::writable);
                    }
                    else
                    {
                        exceptional();
                    }
                }
    public:     x::event::engine * engine() const override
                {
                    return __engine;
                }
    public:     void engine(x::event::engine * o) override
                {
                    if(o != nullptr)
                    {
                        if(__engine == nullptr)
                        {
                            __engine = o;
                        }
                        else
                        {
                            exceptional();
                        }
                    }
                    else
                    {
                        __engine = o;
                    }
                }
    public:     x::int32 id() const override
                {
                    return __descriptor;
                }
    public:     virtual x::boolean need(x::uint32 id)
                {
                    if(id == x::event::type::read)
                    {
                        if(__status & x::event::object::status::wait::read)
                        {
                            return true;
                        }
                        if((__status & x::event::object::status::readable) != x::event::object::status::readable)
                        {
                            return true;
                        }
                    }
                    else if(id == x::event::type::write)
                    {
                        if(__status & x::event::object::status::wait::write)
                        {
                            return true;
                        }
                        if((__status & x::event::object::status::writable) != x::event::object::status::writable)
                        {
                            return true;
                        }
                    }
                    else if(id == x::event::type::open)
                    {
                        exceptional();
                    }
                    else if(id == x::event::type::close)
                    {
                        exceptional();
                    }
                    else
                    {
                        exceptional();
                    }
                    return false;
                }
    public:     x::uint32 status() const override
                {
                    return __status;
                }
    public:     virtual void block()
                {
                }
    public:     virtual void nonblock()
                {
                }
    public:     virtual void open()
                {
                }
    public:     virtual void read() = 0;
    public:     virtual x::int64 write(const x::byte * buffer, x::uint64 length)
                {
                    if(__descriptor >= 0)
                    {
                        if(length > 0)
                        {
                            if(buffer != nullptr)
                            {
                                if(__status & x::event::object::status::on::write)
                                {
                                    if(__status & x::event::object::status::writable)
                                    {
                                        x::int64 n = __write(__descriptor, buffer, length);
                                        if(n > 0)
                                        {
                                            return n;
                                        }
                                        else if(n == 0)
                                        {
                                            exceptional();
                                        }
                                        else
                                        {
                                            if(__error_number_get() == __error_number_again_get())
                                            {
                                                __status &= (~x::event::object::status::writable);
                                                if(__engine)
                                                {
                                                    __console_out("need to register write event\n");
                                                }
                                            }
                                            else
                                            {
                                                exceptional();
                                            }
                                        }
                                    }
                                    else
                                    {
                                        return 0;
                                    }
                                }
                                else
                                {
                                    return 0;
                                }
                            }
                            else
                            {
                                exceptional();
                            }
                        }
                    }
                    else
                    {
                        exceptional();
                    }
                    return 0;
                }
    public:     virtual void close()
                {
                }
    public:     descriptor & operator=(const descriptor & o)
                {
                    if(&o != this)
                    {
                        x::event::object::operator=(o);

                        __descriptor = o.__descriptor;
                        __status = o.__status;
                        __engine = o.__engine;
                    }
                    return *this;
                }
    public:     descriptor & operator=(descriptor && o) noexcept
                {
                    if(&o != this)
                    {
                        x::event::object::operator=(x::move(o));

                        __descriptor = o.__descriptor;
                        __status = o.__status;
                        __engine = o.__engine;

                        o.__descriptor = invalid;
                        o.__status = x::event::object::status::none;
                        o.__engine = nullptr;
                    }
                    return *this;
                }
    protected:  descriptor(x::int32 id)
                :   x::event::object(),
                    __descriptor(id),
                    __status(x::event::object::status::none),
                    __engine(nullptr)
                {
                }
    public:     descriptor()
                :   x::event::object(),
                    __descriptor(invalid),
                    __status(x::event::object::status::none),
                    __engine(nullptr)
                {
                }
    public:     descriptor(const descriptor & o)
                :   x::event::object(o),
                    __descriptor(o.__descriptor),
                    __status(o.__status),
                    __engine(o.__engine)
                {
                }
    public:     descriptor(descriptor && o) noexcept
                :   x::event::object(std::move(o)),
                    __descriptor(o.__descriptor),
                    __status(o.__status),
                    __engine(o.__engine)
                {
                    o.__descriptor = invalid;
                    o.__status = x::event::object::status::none;
                    o.__engine = nullptr;
                }
    public:     ~descriptor() override
                {
                    __descriptor = invalid;
                    __status = x::event::object::status::none;
                    __engine = nullptr;
                }


    // public:     inline void status(x::uint32 v)
    //             {
    //                 __status = v;
    //             }
    // public:     inline x::uint32 status() const
    //             {
    //                 return __status;
    //             }
    // public:     inline bool is(x::uint32 v)
    //             {
    //                 return (__status & v) == v;
    //             }
    // public:     inline x::int32 value() const
    //             {
    //                 return __value;
    //             }
    // public:     void on(x::uint32 id, x::event::engine * engine) override
    //             {
    //                 switch(id)
    //                 {
    //                     case x::event::type::read: __console_out("read\n"); break;
    //                     case x::event::type::write: __console_out("write\n"); break;
    //                     case x::event::type::close: __console_out("close\n"); break;
    //                     case x::event::type::open: __console_out("open\n"); break;
    //                     default:                    __console_out("unknown\n"); break;
    //                 }
    //             }
    // public:     virtual bool need(x::uint32 ev)
    //             {
    //                 return false;
    //             }
    // public:     virtual void open() = 0;
    // public:     virtual void read() = 0;
    // public:     virtual void write() = 0;
    // public:     virtual void close()
    //             {
    //                 if(__value != invalid)
    //                 {
    //                     __close(__value);
    //                     __value = invalid;
    //                     // on(descriptor::event::close);
    //                 }
    //             }
    // public:     virtual void nonblock()
    //             {
    //                 if(__value != invalid)
    //                 {
    //                     if((__status & descriptor::status::nonblock) != descriptor::status::nonblock)
    //                     {
    //                         __nonblock(__value);
    //                         __status |= descriptor::status::nonblock;
    //                     }
    //                 }
    //             }
    // public:     virtual void block()
    //             {
    //                 if(__value != invalid)
    //                 {
    //                     if(__status & descriptor::status::nonblock)
    //                     {
    //                         __block(__value);
    //                         __status &= (~descriptor::status::nonblock);
    //                     }
    //                 }
    //             }
    // public:     x::descriptor & operator=(const x::descriptor & o)
    //             {
    //                 if(&o != this)
    //                 {
    //                     this->close();
    //
    //                     __value = o.__value;
    //                     __status = o.__status;
    //                 }
    //                 return *this;
    //             }
    // public:     x::descriptor & operator=(x::descriptor && o) noexcept
    //             {
    //                 if(&o != this)
    //                 {
    //                     this->close();
    //
    //                     __value = o.__value;
    //                     __status = o.__status;
    //
    //                     o.__value = invalid;
    //                     o.__status = descriptor::status::none;
    //                 }
    //                 return *this;
    //             }
    // public:     descriptor(x::int32 value)
    //             :   __value(value),
    //                 __status((value >=0 ? descriptor::status::opened : descriptor::status::none))
    //             {
    //             }
    // public:     descriptor(x::int32 value, x::uint32 status)
    //             :   __value(value),
    //                 __status(status)
    //             {
    //             }
    // public:     descriptor()
    //             :   __value(invalid),
    //                 __status(descriptor::status::none)
    //             {
    //             }
    // public:     descriptor(const x::descriptor & o)
    //             :   __value(o.__value),
    //                 __status(o.__status)
    //             {
    //             }
    // public:     descriptor(x::descriptor && o) noexcept
    //             :   __value(o.__value),
    //                 __status(o.__status)
    //             {
    //                 o.__value = invalid;
    //                 o.__status = descriptor::status::none;
    //             }
    // public:     virtual ~descriptor()
    //             {
    //                 if(__value != invalid)
    //                 {
    //                     this->close();
    //                     __value = invalid;
    //                 }
    //                 __status = descriptor::status::none;
    //             }
    };
}

#endif // __X__DESCRIPTOR__HH__
