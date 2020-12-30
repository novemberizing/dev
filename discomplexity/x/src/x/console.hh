#ifndef   __X__CONSOLE__HH__
#define   __X__CONSOLE__HH__

#include <x/descriptor.hh>
#include <x/input/stream.hh>
#include <x/output/stream.hh>
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
                            protected:  inline static stream * __singleton = nullptr;
                            public:     static stream & get()
                                        {
                                            if(__singleton == nullptr)
                                            {
                                                static stream o;
                                                __singleton = &o;
                                            }
                                            return *__singleton;
                                        }
                            protected:  x::bytes __buffer;
                            public:     virtual void flush()
                                        {
                                            console::output & output = console::output::get();
                                            output.flush();
                                        }
                            public:     x::boolean need(x::uint32 id)
                                        {
                                            console::output & output = console::output::get();
                                            return output.need(id);
                                        }
                            public:     void on(x::uint32 id, x::event::engine * engine, x::event::generator * generator, x::event::processor * processor) override
                                        {
                                            console::output & output = console::output::get();
                                            output.on(id, engine, generator, processor);
                                        }
                            public:     void off(x::uint32 id, x::event::engine * engine, x::event::generator * generator) override
                                        {
                                            console::output & output = console::output::get();
                                            output.off(id, engine, generator);
                                        }
                            public:     virtual void off()
                                        {
                                            console::output & output = console::output::get();
                                            output.off();
                                        }
                            public:     virtual void on()
                                        {
                                            console::output & output = console::output::get();
                                            output.on();
                                        }
                            public:     x::event::engine * engine() const override
                                        {
                                            console::output & output = console::output::get();
                                            return output.engine();
                                        }
                            public:     void engine(x::event::engine * o) override
                                        {
                                            console::output & output = console::output::get();
                                            return output.engine(o);
                                        }
                            public:     x::int32 id() const override
                                        {
                                            console::output & output = console::output::get();
                                            return output.id();
                                        }
                            public:     x::uint32 status() const override
                                        {
                                            console::output & output = console::output::get();
                                            return output.status();
                                        }
                            public:     inline void erase(x::uint64 offset, x::uint64 n)
                                        {
                                            __buffer.erase(offset, n);
                                        }
                            public:     inline const x::byte * data() const
                                        {
                                            return __buffer.data();
                                        }
                            public:     inline x::uint64 size() const
                                        {
                                            return __buffer.size();
                                        }
                            protected:  virtual void write()
                                        {
                                            console::output & output = console::output::get();
                                            output.write();
                                        }
                            public:     void push(const x::byte & item) override
                                        {
                                            __buffer.push(item);
                                            this->write();
                                        }
                            public:     void push(x::byte && item) override
                                        {
                                            __buffer.push(x::move(item));
                                            this->write();
                                        }
                            public:     void push(const x::byte & item, x::uint64 n) override
                                        {
                                            __buffer.push(item, n);
                                            this->write();
                                        }
                            public:     void push(const x::byte * source, x::uint64 n) override
                                        {
                                            __buffer.push(source, n);
                                            this->write();
                                        }
                            public:     stream & operator=(const stream & o) = delete;
                            public:     stream & operator=(stream && o) noexcept = delete;
                            protected:  stream()
                                        :   x::output::stream(),
                                            __buffer()
                                        {
                                        }
                            public:     stream(const stream & o) = delete;
                            public:     stream(stream && o) noexcept = delete;
                            public:     ~stream() override
                                        {
                                        }
                            };
                protected:  inline static console::output * __singleton = nullptr;
                public:     static console::output & get()
                            {
                                if(__singleton == nullptr)
                                {
                                    static console::output o;
                                    __singleton = &o;
                                }
                                return *__singleton;
                            }
                protected:  console::output::stream & __stream;
                public:     void on(x::uint32 id, x::event::engine * engine, x::event::generator * generator, x::event::processor * processor) override
                            {
                                x::descriptor::on(id, engine, generator, processor);
                            }
                public:     virtual void on()
                            {
                                __status |= x::event::object::status::on::write;
                            }
                public:     void off(x::uint32 id, x::event::engine * engine, x::event::generator * generator) override
                            {
                                x::descriptor::off(id, engine, generator);
                            }
                public:     virtual void off()
                            {
                                __status &= (~x::event::object::status::on::write);
                            }
                public:     void open() override
                            {
                                exceptional();
                            }
                public:     void close() override
                            {
                                exceptional();
                            }
                public:     void read() override
                            {
                                exceptional();
                            }
                public:     virtual void flush()
                            {
                                __status |= x::event::object::status::on::write;
                                this->write();
                                __status &= (~x::event::object::status::on::write);
                            }
                protected:  x::int64 write(const x::byte * buffer, x::uint64 length) override
                            {
                                return x::descriptor::write(buffer, length);
                            }
                public:     virtual void write()
                            {
                                x::int64 n = this->write(__stream.data(), __stream.size());
                                if(n > 0)
                                {
                                    __stream.erase(0, n);
                                }
                            }
                public:     bool need(x::uint32 id) override
                            {
                                if(id == x::event::type::write)
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
                                return false;
                            }
                public:     output & operator=(const output & o) = delete;
                public:     output & operator=(output && o) noexcept = delete;
                public:     output()
                            :   x::descriptor(__stdout_fileno_get()),
                                __stream(console::output::stream::get())
                            {
                                __status = x::event::object::status::writable | x::event::object::status::on::write;
                                if(__nonblock_status_get(__descriptor))
                                {
                                    __block(__descriptor);
                                }
                            }
                public:     output(const output & o) = delete;
                public:     output(output && o) noexcept = delete;
                public:     virtual ~output()
                            {
                            }
                };
    public:     class input : public x::descriptor
                {
                public:     typedef void (*callback)(const x::string &);
                public:     class stream : public x::input::stream,
                                           public x::event::object,
                                           protected x::bytes
                            {
                            protected:  inline static stream * __singleton = nullptr;
                            public:     static stream & get()
                                        {
                                            if(__singleton == nullptr)
                                            {
                                                static stream o;
                                                __singleton = &o;
                                            }
                                            return *__singleton;
                                        }
                            // protected:  x::bytes __buffer;
                            public:     void clear() override
                                        {
                                            x::bytes::clear();
                                        }
                            public:     virtual void set(x::console::input::callback f)
                                        {
                                            if(f != nullptr)
                                            {
                                                console::input & input = console::input::get();
                                                input.set(f);
                                            }
                                        }
                            public:     x::string str()
                                        {
                                            x::string result((const char *) __container, __size);
                                            __size = 0;
                                            return result;
                                        }
                            public:     x::uint64 size() const override
                                        {
                                            return __size;
                                        }
                            public:     const x::byte * data() const override
                                        {
                                            return __container;
                                        }
                            public:     void move(x::uint64 n)
                                        {
                                            __size += n;
                                        }
                            public:     virtual x::byte * data()
                                        {
                                            return __container;
                                        }
                            public:     virtual x::uint64 remain() const
                                        {
                                            return __capacity - __size;
                                        }
                            public:     x::int32 id() const override
                                        {
                                            console::input & input = console::input::get();
                                            return input.id();
                                        }
                            public:     x::uint32 status() const override
                                        {
                                            console::input & input = console::input::get();
                                            return input.status();
                                        }
                            public:     x::event::engine * engine() const override
                                        {
                                            console::input & input = console::input::get();
                                            return input.engine();
                                        }
                            public:     void engine(x::event::engine * o) override
                                        {
                                            console::input & input = console::input::get();
                                            input.engine(o);
                                        }
                            public:     x::boolean need(x::uint32 id)
                                        {
                                            console::input & input = console::input::get();
                                            return input.need(id);
                                        }
                            public:     void on(x::uint32 id, x::event::engine * engine, x::event::generator * generator, x::event::processor * processor) override
                                        {
                                            console::input & input = console::input::get();
                                            input.on(id, engine, generator, processor);
                                        }
                            public:     void off(x::uint32 id, x::event::engine * engine, x::event::generator * generator) override
                                        {
                                            console::input & input = console::input::get();
                                            input.off(id, engine, generator);
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
                                            // TODO: IMPLEMENT THIS
                                        }
                            public:     void push(x::byte && item) override
                                        {
                                            // TODO: IMPLEMENT THIS
                                        }
                            public:     void push(const x::byte & item, x::uint64 n) override
                                        {
                                            // TODO: IMPLEMENT THIS
                                        }
                            public:     void push(const x::byte * source, x::uint64 n) override
                                        {
                                            // __buffer.push(source, n);
                                        }
                            public:     stream & operator=(const stream & o) = delete;
                            public:     stream & operator=(stream && o) noexcept = delete;
                            protected:  stream()
                                        :   x::input::stream(),
                                            x::event::object(),
                                            x::bytes(65536UL)
                                        {
                                        }
                            public:     stream(const stream & o) = delete;
                            public:     stream(stream && o) noexcept = delete;
                            public:     ~stream() override
                                        {
                                        }
                            };
                protected:  inline static console::input * __singleton;
                public:     static console::input & get()
                            {
                                if(__singleton == nullptr)
                                {
                                    static console::input o;
                                    __singleton = &o;
                                }
                                return *__singleton;
                            }
                protected:  console::input::stream & __stream;
                protected:  x::console::input::callback __callback;
                public:     virtual void set(x::console::input::callback f)
                            {
                                __callback = f;
                            }
                public:     void on(x::uint32 id, x::event::engine * engine, x::event::generator * generator, x::event::processor * processor) override
                            {
                                if(id == x::event::type::read)
                                {
                                    __status |= x::event::object::status::readable;
                                    __status &= (~x::event::object::status::wait::read);
                                    while(__status & x::event::object::status::readable)
                                    {
                                        this->read();
                                        if(__stream.size() > 0)
                                        {
                                            x::console::input::callback func = __callback;
                                            if(func)
                                            {
                                                func(__stream.str());
                                            }
                                            else
                                            {
                                                __stream.clear();
                                            }
                                            // console::out << __stream.str();
                                            // TODO: SERIALIZER & DESERIALIZER
                                        }
                                        // 
                                    }
                                }
                                else
                                {
                                    exceptional();
                                }
                            }
                public:     void open() override
                            {
                            }
                public:     x::int64 write(const x::byte * buffer, x::uint64 length) override
                            {
                            }
                public:     void close() override
                            {
                            }
                public:     void read() override
                            {
                                if(__descriptor >= 0)
                                {
                                    if(__stream.remain() == 0)
                                    {
                                        printf("need to resize\n");
                                    }
                                    // __console_out(__stream.remain());
                                    x::int64 n = __read(__descriptor, __stream.data(), __stream.remain());
                                    if(n > 0)
                                    {
                                        __stream.move(n);
                                    }
                                    else if(n == 0)
                                    {
                                        exceptional();  // closed
                                    }
                                    else
                                    {
                                        if(__error_number_get() == __error_number_again_get())
                                        {
                                            __status &= (~x::event::object::status::readable);
                                            __engine->mod(x::event::generator::type::io, &__stream);
                                        }
                                        else
                                        {
                                            exceptional();
                                        }
                                    }
                                }
                                // _read(__descriptor, )
                                // TODO IMPLEMENT THIS
                            }
                public:     bool need(x::uint32 id) override
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
                                return false;
                            }
                public:     input & operator=(const input & o) = delete;
                public:     input & operator=(input && o) noexcept = delete;
                public:     input()
                            :   x::descriptor(__stdin_fileno_get()),
                                __stream(console::input::stream::get())
                            {
                                __status = x::event::object::status::readable;
                                if(__nonblock_status_get(__descriptor))
                                {
                                    __block(__descriptor);
                                }
                            }
                public:     input(const input & o) = delete;
                public:     input(input && o) noexcept = delete;
                public:     virtual ~input()
                            {
                            }
                };
    public:     inline static console::output::stream & out = console::output::stream::get();
    public:     inline static console::input::stream & in = console::input::stream::get();
    };
}

#endif // __X__CONSOLE__HH__
