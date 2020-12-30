#ifndef   __X__CONSOLE__HH__
#define   __X__CONSOLE__HH__

#include <x/descriptor.hh>
#include <x/input.stream.hh>
#include <x/output.stream.hh>
#include <x/string.hh>
#include <x/bytes.hh>

namespace x
{
    class console
    {
    public:     class output : public x::descriptor
                {
                public:     class stream : public x::output::stream,
                                           public x::event::object
                            {
                            protected:  inline static x::console::output::stream * __singleton = nullptr;
                            public:     static x::console::output::stream & get()
                                        {
                                            if(__singleton == nullptr)
                                            {
                                                static x::console::output::stream o;
                                                __singleton = &o;
                                            }
                                            return *__singleton;
                                        }
                            protected:  x::bytes __buffer;
                            public:     inline x::uint64 size() const
                                        {
                                            return __buffer.size();
                                        }
                            public:     inline const x::byte * data() const
                                        {
                                            return __buffer.data();
                                        }
                            public:     inline void erase(x::uint64 offset, x::uint64 n)
                                        {
                                            __buffer.erase(offset, n);
                                        }
                            public:     void engine(x::event::engine * o) override
                                        {
                                            x::event::object::engine(o);
                                            x::console::output & stream = x::console::output::get();
                                            stream.engine(o);
                                        }
                            public:     x::event::object * safe(x::uint32 type) override
                                        {
                                            if(x::event::type::io)
                                            {
                                                x::console::output & o = x::console::output::get();
                                                return &o;
                                            }
                                            exceptional();
                                        }
                            public:     virtual void on()
                                        {
                                            x::console::output & o = x::console::output::get();
                                            o.on();
                                        }
                            public:     virtual void off()
                                        {
                                            x::console::output & o = x::console::output::get();
                                            o.off();
                                        }
                            protected:  void on(x::uint32 id, x::event::engine * engine, x::event::generator * generator) override
                                        {
                                        }
                            public:     void push(const x::byte & item) override
                                        {
                                            __buffer.append(item);
                                            write();
                                        }
                            public:     void push(x::byte && item) override
                                        {
                                            __buffer.append(x::move(item));
                                            write();
                                        }
                            public:     void push(const x::byte & item, x::uint64 n) override
                                        {
                                            __buffer.append(item, n);
                                            write();
                                        }
                            public:     void push(const x::byte * source, x::uint64 n) override
                                        {
                                            __buffer.append(source, n);
                                            write();
                                        }
                            protected:  virtual void write()
                                        {
                                            x::console::output & o = x::console::output::get();
                                            o.write();
                                        }
                            public:     void flush() override
                                        {
                                            x::console::output & o = x::console::output::get();
                                            o.flush();
                                        }
                            public:     x::console::output::stream & operator=(const x::console::output::stream & o) = delete;
                            public:     x::console::output::stream & operator=(x::console::output::stream && o) noexcept = delete;
                            public:     stream()
                                        :   x::output::stream(),
                                            x::event::object()
                                        {
                                        }
                            public:     stream(const x::console::output::stream & o) = delete;
                            public:     stream(x::console::output::stream && o) noexcept = delete;
                            public:     ~stream() override
                                        {
                                        }
                            };
                protected:  inline static x::console::output * __singleton;
                public:     static x::console::output & get()
                            {
                                if(__singleton == nullptr)
                                {
                                    static x::console::output o;
                                    __singleton = &o;
                                }
                                return *__singleton;
                            }
                protected:  x::boolean __off;
                public:     void engine(x::event::engine * o) override
                            {
                                if(__engine == nullptr && o != nullptr)
                                {
                                    __status &= (~x::descriptor::status::writable);
                                    __core_nonblock(__value);
                                }
                                else if(o == nullptr)
                                {
                                    __status |= x::descriptor::status::writable;
                                    __core_block(__value);
                                }
                                x::event::object::engine(o);
                            }
                public:     x::boolean interest(x::uint32 type) override
                            {
                                if(__wait & type)
                                {
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
                public:     void open(x::boolean nonblocking) override
                            {
                            }
                public:     void close() override
                            {
                            }
                public:     void on(x::uint32 id, x::event::engine * engine, x::event::generator * generator) override
                            {
                                if(generator->type() == x::event::type::io)
                                {
                                    if(id == x::event::io::type::write)
                                    {
                                        __wait &= (~x::event::io::type::write);
                                        __status |= x::descriptor::status::writable;
                                        if(!__off)
                                        {
                                            flush();
                                        }
                                        // TODO SOMETHING
                                    }
                                    if(id == x::event::io::type::close)
                                    {
                                        __wait &= (~x::event::io::type::close);
                                        // TODO SOMETHING
                                    }
                                }
                            }
                public:     virtual void on()
                            {
                                __off = false;
                            }
                public:     virtual void off()
                            {
                                __off = true;
                            }
                public:     virtual void flush()
                            {
                                if(__value >= 0)
                                {
                                    console::output::stream & stream = console::output::stream::get();
                                    while(stream.size() > 0)
                                    {
                                        x::int64 n = __core_write(__value, stream.data(), stream.size());
                                        if(n > 0)
                                        {
                                            stream.erase(0, n);
                                        }
                                        else if(n < 0)
                                        {
                                            x::int32 error = __core_error_get();
                                            if(error != __core_error_again())
                                            {
                                                exceptional();
                                                // break;
                                                // TODO THIS
                                                // __engine->del(x::event::type::io, this);
                                            }
                                        }
                                    }
                                }
                            }
                public:     virtual void write()
                            {
                                if(__status & x::descriptor::status::writable)
                                {
                                    if(!__off)
                                    {
                                        if(__value >= 0)
                                        {
                                            console::output::stream & stream = console::output::stream::get();
                                            if(stream.size() > 0)
                                            {
                                                x::int64 n = __core_write(__value, stream.data(), stream.size());
                                                if(n > 0)
                                                {
                                                    stream.erase(0, n);
                                                }
                                                else if(n < 0)
                                                {
                                                    x::int32 error = __core_error_get();
                                                    if(error == __core_error_again())
                                                    {
                                                        __status &= (~x::descriptor::status::writable);
                                                        __engine->mod(x::event::type::io, this);
                                                    }
                                                    else
                                                    {
                                                        exceptional();
                                                        // TODO THIS
                                                        // __engine->del(x::event::type::io, this);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                public:     x::console::output & operator=(const x::console::output & o)
                            {
                                if(&o != this)
                                {
                                    x::descriptor::operator=(o);

                                    __off = o.__off;
                                }
                                return *this;
                            }
                public:     x::console::output & operator=(x::console::output && o) noexcept
                            {
                                if(&o != this)
                                {
                                    x::descriptor::operator=(x::move(o));

                                    __off = o.__off;

                                    o.__off = false;
                                }
                                return *this;
                            }
                public:     output()
                            :   x::descriptor(__core_stdout_fileno_get(), x::descriptor::status::writable),
                                __off(false)
                            {
                                if(__core_nonblock_status_get(__value))
                                {
                                    __core_block(__value);
                                }
                            }
                public:     output(const x::console::output & o)
                            :   x::descriptor(o),
                                __off(o.__off)
                            {
                            }
                public:     output(x::console::output && o) noexcept
                            :   x::descriptor(x::move(o)),
                                __off(o.__off)
                            {
                                o.__off = false;
                            }
                public:     ~output() override
                            {
                            }
                };
    public:     class input : public x::descriptor
                {
//                public:     typedef void (*callback)(const x::string &);
                public:     class stream : public x::input::stream,
                                           public x::event::object,
                                           protected x::bytes
                            {
                            protected:  inline static x::console::input::stream * __singleton = nullptr;
                            public:     static x::console::input::stream & get()
                                        {
                                            if(__singleton == nullptr)
                                            {
                                                static x::console::input::stream o;
                                                __singleton = &o;
                                            }
                                            return *__singleton;
                                        }
                            public:     void clear() override
                                        {
                                            x::bytes::clear();
                                        }
                            public:     x::event::object * safe(x::uint32 type) override
                                        {
                                            if(type == x::event::type::io)
                                            {
                                                x::console::input & i = x::console::input::get();
                                                return &i;
                                            }
                                            exceptional();
                                        }
                            public:     x::uint64 size() const override
                                        {
                                            return __size;
                                        }
                            public:     const x::byte * data() const override
                                        {
                                            return __container;
                                        }
                            public:     virtual x::byte * data()
                                        {
                                            return __container;
                                        }
                            public:     virtual x::string str()
                                        {
                                            x::string result(reinterpret_cast<const char *>(__container), __size);
                                            __size = 0;
                                            return result;
                                        }
                            public:     virtual void set(x::function<void (const x::string &)> f)
                                        {
                                            x::console::input & i = x::console::input::get();
                                            i.set(f);
                                        }
                            public:     virtual void move(x::uint64 n)
                                        {
                                            __size += n;
                                        }
                            public:     virtual x::uint64 remain() const
                                        {
                                            return __capacity - __size;
                                        }
                            public:     void engine(x::event::engine * o) override
                                        {
                                            x::event::object::engine(o);
                                            x::console::input & stream = x::console::input::get();
                                            stream.engine(o);
                                        }
                            protected:  void on(x::uint32 id, x::event::engine * engine, x::event::generator * generator) override
                                        {
                                        }
                            public:     x::byte pop() override
                                        {
                                            if(this->__size > 0)
                                            {
                                                x::byte c = this->__container[0];
                                                x::bytes::erase(0, 1);
                                                return c;
                                            }
                                            exceptional();
                                        }
                            public:     void push(const x::byte & item) override
                                        {
                                            exceptional();
                                            // TODO: IMPLEMENT THIS
                                        }
                            public:     void push(x::byte && item) override
                                        {
                                            exceptional();
                                            // TODO: IMPLEMENT THIS
                                        }
                            public:     void push(const x::byte & item, x::uint64 n) override
                                        {
                                            exceptional();
                                            // TODO: IMPLEMENT THIS
                                        }
                            public:     void push(const x::byte * source, x::uint64 n) override
                                        {
                                            exceptional();
                                            // __buffer.push(source, n);
                                        }
                            public:     x::console::input::stream & operator=(const x::console::input::stream & o) = delete;
                            public:     x::console::input::stream & operator=(x::console::input::stream && o) noexcept = delete;
                            public:     stream()
                                        :   x::input::stream(),
                                            x::event::object(),
                                            x::bytes(65536UL)
                                        {
                                        }
                            public:     stream(const x::console::input::stream & o) = delete;
                            public:     stream(x::console::input::stream && o) noexcept = delete;
                            public:     ~stream() override
                                        {
                                        }
                            };
                protected:  inline static x::console::input * __singleton = nullptr;
                public:     static x::console::input & get()
                            {
                                if(__singleton == nullptr)
                                {
                                    static x::console::input o;
                                    __singleton = &o;
                                }
                                return *__singleton;
                            }
                protected:  x::function<void (const x::string &)> __callback;
                public:     virtual void set(x::function<void (const x::string &)> f)
                            {
                                __callback = f;
                            }
                public:     void engine(x::event::engine * o) override
                            {
                                if(__engine == nullptr && o != nullptr)
                                {
                                    __status &= (~x::descriptor::status::readable);
                                    // printf("nonblock\n");
                                    __core_nonblock(__value);
                                }
                                else if(o == nullptr)
                                {
                                    __status |= x::descriptor::status::readable;
                                    __core_block(__value);
                                }
                                x::event::object::engine(o);
                            }
                public:     x::boolean interest(x::uint32 type) override
                            {
                                // printf("interest check\n");
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
                                return false;
                            }
                public:     void open(x::boolean nonblocking) override
                            {
                            }
                public:     void close() override
                            {
                            }
                public:     virtual void read()
                            {
                                if(__status & x::descriptor::status::readable)
                                {
                                    if(__value >= 0)
                                    {
                                        x::console::input::stream & i = x::console::input::stream::get();
                                        if(i.remain() == 0)
                                        {
                                            exceptional();
                                        }
                                        x::int64 n = __core_read(__value, &i.data()[i.size()], i.remain());
                                        if(n > 0)
                                        {
                                            i.move(n);
                                        }
                                        else if(n == 0)
                                        {
                                            exceptional();
                                        }
                                        else
                                        {
                                            int error = __core_error_get();
                                            if(error == __core_error_again())
                                            {
                                                __status &= (~x::descriptor::status::readable);
                                                __engine->mod(x::event::type::io, &i);
                                            }
                                            else
                                            {
                                                exceptional();
                                            }
                                        }
                                    }
                                }
                            }
                public:     void on(x::uint32 id, x::event::engine * engine, x::event::generator * generator) override
                            {
                                if(generator->type() == x::event::type::io)
                                {
                                    if(id == x::event::io::type::read)
                                    {
                                        __wait &= (~x::event::io::type::read);
                                        __status |= x::descriptor::status::readable;
                                        x::console::input::stream & i = x::console::input::stream::get();
                                        read();
                                        if(i.size() > 0)
                                        {
                                            if(__callback)
                                            {
                                                __callback(i.str());
                                            }
                                            else
                                            {
                                                i.clear();
                                            }
                                        }
                                        if(__status & x::descriptor::status::readable)
                                        {
                                            __engine->add(x::event(id, this,engine, generator));
                                        }
                                    }
                                }
                            }
                public:     x::console::input & operator=(const x::console::input & o) = delete;
                public:     x::console::input & operator=(x::console::input && o) noexcept = delete;
                public:     input()
                            :   x::descriptor(__core_stdin_fileno_get(), x::descriptor::status::readable),
                                __callback(nullptr)
                            {
                                if(__core_nonblock_status_get(__value))
                                {
                                    __core_block(__value);
                                }
                            }
                public:     input(const x::console::input & o) = delete;
                public:     input(x::console::input && o) noexcept = delete;
                public:     ~input() override
                            {
                            }
                };
    public:     inline static console::input::stream & in = console::input::stream::get();
    public:     inline static console::output::stream & out = console::output::stream::get();
    };
}

#endif // __X__CONSOLE__HH__
