#ifndef   __X__FILE__HH__
#define   __X__FILE__HH__

#include <x/descriptor.hh>
#include <x/input.stream.hh>
#include <x/output.stream.hh>
#include <x/string.hh>
#include <x/bytes.hh>
#include <x/list.hh>

namespace x
{
    class file
    {
    public:     static const x::uint64 page = 2UL * 4096UL;
    public:     class input : public x::descriptor
                {
                public:     class stream : public x::input::stream,
                                           public x::event::object,
                                           protected x::bytes
                            {
                            public:     static x::file::input::stream open(const x::string path)
                                        {
                                            x::file::input::stream result(path);
                                            result.open();
                                            return result;
                                        }
                            protected:  x::file::input * __input;
                            public:     virtual x::boolean finish() const
                                        {
                                            return __input ? __input->finish() : true;
                                        }
                            public:     virtual x::float32 float32()
                                        {
                                            x::float32 result = 0;
                                            if(__size < sizeof(x::float32))
                                            {
                                                __input->read(sizeof(x::float32) - __size);
                                            }
                                            assertion(__size < sizeof(x::float32));
                                            __core_memcpy(&result, __container, sizeof(x::float32));
                                            erase(0, sizeof(x::float32));
                                            return result;
                                        }
                            public:     virtual x::float64 float64()
                                        {
                                            x::float64 result = 0;
                                            if(__size < sizeof(x::float64))
                                            {
                                                __input->read(sizeof(x::float64) - __size);
                                            }
                                            assertion(__size < sizeof(x::float64));
                                            __core_memcpy(&result, __container, sizeof(x::float64));
                                            erase(0, sizeof(x::float64));
                                            return result;
                                        }
                            public:     virtual x::byte byte()
                                        {
                                            x::byte result = 0;
                                            if(__size < sizeof(x::byte))
                                            {
                                                __input->read(sizeof(x::byte) - __size);
                                            }
                                            assertion(__size < sizeof(x::byte));
                                            __core_memcpy(&result, __container, sizeof(x::byte));
                                            erase(0, sizeof(x::byte));
                                            return result;
                                        }
                            public:     virtual x::character character()
                                        {
                                            x::character result = 0;
                                            if(__size < sizeof(x::character))
                                            {
                                                __input->read(sizeof(x::character) - __size);
                                            }
                                            assertion(__size < sizeof(x::character));
                                            __core_memcpy(&result, __container, sizeof(x::character));
                                            erase(0, sizeof(x::character));
                                            return result;
                                        }
                            public:     virtual x::int16 int16()
                                        {
                                            x::int16 result = 0;
                                            if(__size < sizeof(x::int16))
                                            {
                                                __input->read(sizeof(x::int16) - __size);
                                            }
                                            assertion(__size < sizeof(x::int16));
                                            __core_memcpy(&result, __container, sizeof(x::int16));
                                            erase(0, sizeof(x::int16));
                                            return result;
                                        }
                            public:     virtual x::uint16 uint16()
                                        {
                                            x::uint16 result = 0;
                                            if(__size < sizeof(x::uint16))
                                            {
                                                __input->read(sizeof(x::uint16) - __size);
                                            }
                                            assertion(__size < sizeof(x::uint16));
                                            __core_memcpy(&result, __container, sizeof(x::uint16));
                                            erase(0, sizeof(x::uint16));
                                            return result;
                                        }
                            public:     virtual x::int32 int32()
                                        {
                                            x::int32 result = 0;
                                            if(__size < sizeof(x::int32))
                                            {
                                                __input->read(sizeof(x::int32) - __size);
                                            }
                                            assertion(__size < sizeof(x::int32));
                                            __core_memcpy(&result, __container, sizeof(x::int32));
                                            erase(0, sizeof(x::int32));
                                            return result;
                                        }
                            public:     virtual x::uint32 uint32()
                                        {
                                            x::uint32 result = 0;
                                            if(__size < sizeof(x::uint32))
                                            {
                                                __input->read(sizeof(x::uint32) - __size);
                                            }
                                            assertion(__size < sizeof(x::uint32));
                                            __core_memcpy(&result, __container, sizeof(x::uint32));
                                            erase(0, sizeof(x::uint32));
                                            return result;
                                        }
                            public:     virtual x::int64 int64()
                                        {
                                            x::int64 result = 0;
                                            if(__size < sizeof(x::int64))
                                            {
                                                __input->read(sizeof(x::int64) - __size);
                                            }
                                            assertion(__size < sizeof(x::int64));
                                            __core_memcpy(&result, __container, sizeof(x::int64));
                                            erase(0, sizeof(x::int64));
                                            return result;
                                        }
                            public:     virtual x::uint64 uint64()
                                        {
                                            x::uint64 result = 0;
                                            if(__size < sizeof(x::uint64))
                                            {
                                                __input->read(sizeof(x::uint64) - __size);
                                            }
                                            assertion(__size < sizeof(x::uint64));
                                            __core_memcpy(&result, __container, sizeof(x::uint64));
                                            erase(0, sizeof(x::uint64));
                                            return result;
                                        }
                            public:     virtual x::string str(x::uint64 n)
                                        {
                                            x::string result;
                                            if(__size < n)
                                            {
                                                __input->read(n - __size);
                                            }

                                            result.assign((const char *) __container, __size < n ? __size : n);
                                            erase(0, __size < n ? __size : n);
                                            return result;
                                        }
                            public:     virtual x::bytes data(x::uint64 n)
                                        {
                                            x::bytes result;
                                            if(__size < n)
                                            {
                                                __input->read(n - __size);
                                            }
                                            result.assign(__container, __size < n ? __size : n);
                                            erase(0, __size < n ? __size : n);
                                            return result;
                                        }
                            public:     virtual void open()
                                        {
                                            __input->open(false);
                                        }
                            public:     virtual void close()
                                        {
                                            __input->close();
                                        }
                            public:     virtual void reset()
                                        {
                                            __capacity = __page;
                                            __container = x::memory::allocate<x::byte>(__container, __capacity);
                                        }
                            public:     virtual x::uint64 remain() const
                                        {
                                            return __capacity - __size;
                                        }
                            public:     virtual void capacity(x::uint64 n)
                                        {
                                            n = x::paging::calculate(n, __page);

                                            assertion(n < __size);

                                            if(__capacity != n)
                                            {
                                                __capacity = n;
                                                __container = x::memory::allocate<x::byte>(__container, __capacity);
                                            }
                                        }
                            public:     x::event::object * safe(x::uint32 type) override
                                        {
                                            if(type == x::event::type::io)
                                            {
                                                return __input;
                                            }

                                            exceptional();
                                        }
                            public:     void on(x::uint32 id, x::event::engine * engine, x::event::generator * generator) override
                                        {
                                            exceptional();
                                        }
                            public:     void push(const x::byte & item) override
                                        {
                                            exceptional();
                                        }
                            public:     void push(x::byte && item) override
                                        {
                                            exceptional();
                                        }
                            public:     void push(const x::byte & item, x::uint64 n) override
                                        {
                                            exceptional();
                                        }
                            public:     void push(const x::byte * source, x::uint64 n) override
                                        {
                                            exceptional();
                                        }
                            public:     x::byte pop() override
                                        {
                                            assertion(__size == 0);

                                            x::byte result = __container[0];

                                            erase(0, 1);

                                            return result;
                                        }
                            public:     x::file::input::stream & operator=(const x::file::input::stream & o) = delete;
                            public:     x::file::input::stream & operator=(x::file::input::stream && o) noexcept = delete;
                            public:     stream(const x::string & path)
                                        :   x::input::stream(),
                                            x::event::object(),
                                            x::bytes(x::file::page),
                                            __input(nullptr)
                                        {
                                            __input = new x::file::input(this, path);
                                        }
                            public:     stream() = delete;
                            public:     stream(const x::file::input::stream & o) = delete;
                            public:     stream(x::file::input::stream && o) noexcept
                                        :   x::input::stream(x::move(o)),
                                            x::event::object(x::move(o)),
                                            x::bytes(x::move(o)),
                                            __input(o.__input)
                                        {
                                            o.__input = nullptr;
                                        }
                            public:     ~stream() override
                                        {
                                            if(__input)
                                            {
                                                delete __input;
                                                __input = nullptr;
                                            }
                                        }
                            public:     friend class x::file::input;
                            };
                protected:  x::file::input::stream * __stream;
                protected:  x::string __path;
                protected:  x::function<x::uint64 (const x::bytes &)> __callback;
                public:     virtual x::boolean finish() const
                            {
                                if(__value >= 0)
                                {
                                    uint64 offset = __core_lseek(__value, 0, __core_seek_cur_get());
                                    uint64 last   = __core_lseek(__value, 0, __core_seek_end_get());
                                    __core_lseek(__value, offset, __core_seek_set_get());
                                    return offset == last;
                                }
                                return true;

                            }
                protected:  virtual void read(x::uint64 total)
                            {
                                if(__value >= 0)
                                {
                                    if(__status & x::descriptor::status::readable)
                                    {
                                        if(__stream->remain() < total)
                                        {
                                            __stream->capacity(__stream->size() + total);
                                        }
                                        while(0 < total)
                                        {
                                            x::int64 n = __core_read(__value, &__stream->__container[__stream->__size], total);
                                            if(n > 0)
                                            {
                                                __stream->__size = __stream->__size + n;
                                                total = total - n;
                                            }
                                            else if(n == 0)
                                            {
                                                if(__stream->finish())
                                                {
                                                    break;
                                                }
                                                else
                                                {
                                                    exceptional();
                                                }
                                            }
                                            else
                                            {
                                                x::int32 error = __core_error_get();
                                                if(error == __core_error_again())
                                                {
                                                }
                                                else
                                                {
                                                    exceptional();
                                                }
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    exceptional();
                                }
                            }
                public:     virtual void read()
                            {
                                read(__stream->remain());
                            }
                public:     void engine(x::event::engine * o) override
                            {
                                x::event::engine * engine = __engine;
                                x::event::object::engine(o);
                                __stream->engine(o);
                                if(engine == nullptr && o != nullptr)
                                {
                                    __core_nonblock(__value);
                                    __status &= (~x::descriptor::status::readable);
                                }
                                else if(engine != nullptr && o == nullptr)
                                {
                                    __core_block(__value);
                                    __status |= (x::descriptor::status::readable);
                                }
                            }
                public:     x::event::object * safe(x::uint32 type) override
                            {
                                if(type == x::event::type::io)
                                {
                                    return this;
                                }
                                else
                                {
                                    exceptional();
                                }
                            }
                public:     void on(x::uint32 id, x::event::engine * engine, x::event::generator * generator) override
                            {
                                if(generator)
                                {
                                    if(generator->type() == x::event::type::io)
                                    {
                                        if(id == x::event::io::type::read)
                                        {
                                            __wait &= (~x::event::io::type::read);
                                            __status |= x::descriptor::status::readable;
                                            read();
                                            if(__callback)
                                            {
                                                x::uint64 n = __callback(*__stream);
                                                if(n > 0)
                                                {
                                                    __stream->__size = __stream->__size - n;
                                                }
                                            }
                                            if(__status & x::descriptor::status::readable)
                                            {
                                                engine->mod(x::event::type::io, this);
                                            }
                                        }
                                        else if(id == x::event::io::type::close)
                                        {
                                            close();
                                        }
                                        else
                                        {
                                            exceptional();
                                        }
                                    }
                                    else
                                    {
                                        exceptional();
                                    }
                                }
                                else
                                {
                                    exceptional();
                                }
                            }
                public:     x::boolean interest(x::uint32 type) override
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
                                return false;
                            }
                public:     void open(x::boolean nonblocking) override
                            {
                                if(__value == x::invalid)
                                {
                                    x::uint32 flags = __core_open_flags_read_only();
                                    if(nonblocking)
                                    {
                                        flags |= __core_open_flags_nonblock();
                                    }
                                    __value = __core_open(__path.str(), flags);

                                    assertion(__value == x::invalid);

                                    if(__engine)
                                    {
                                        // TODO: ADD NEW OBJECT
                                    }
                                    else
                                    {
                                        __status |= x::descriptor::status::readable;
                                    }
                                }
                                else
                                {
                                    exceptional();
                                }
                            }
                public:     void close() override
                            {
                                x::descriptor::close();
                                __stream->reset();
                            }
                public:     x::file::input & operator=(const x::file::input & o) = delete;
                public:     x::file::input & operator=(x::file::input && o) noexcept = delete;
                protected:  input(x::file::input::stream * stream, const x::string & path)
                            :   x::descriptor(),
                                __stream(stream),
                                __path(path),
                                __callback(nullptr)
                            {
                            }
                protected:  input() = delete;
                protected:  input(const x::file::input & o) = delete;
                protected:  input(x::file::input && o) noexcept = delete;
                protected:  ~input() override
                            {
                                close();
                            }
                public:     friend class x::file::input::stream;
                };
    public:     static x::string text(const x::string & path)
                {
                    x::string result;
                    x::file::input::stream stream = x::file::input::stream::open(path);
                    while(!stream.finish())
                    {
                        x::string data = stream.str(x::file::page);
                        if(data.size() > 0)
                        {
                            result.append(data);
                        }
                    }
                    stream.close();
                    return result;
                }
    public:     static x::string text(const x::file & f)
                {
                    return x::file::text(f.path());
                }
    public:     static x::bytes data(const x::string & path)
                {
                    x::bytes result;
                    x::file::input::stream stream = x::file::input::stream::open(path);
                    while(!stream.finish())
                    {
                        x::bytes data = stream.data(x::file::page);
                        if(data.size() > 0)
                        {
                            result.append(data);
                        }
                    }
                    stream.close();
                    return result;
                }
    public:     class type
                {
                public:     static const x::uint64 regular = 0x00000010UL;
                public:     static const x::uint64 directory = 0x00000004UL;
                };
    protected:  x::uint64 __type;
    protected:  x::string __directory;
    protected:  x::string __name;
    protected:  x::string __extension;
    public:     x::array<x::file> children;
    public:     inline const x::file & find(x::function<x::boolean (const x::file &)> f) const
                {
                    if(__type == x::file::type::directory)
                    {
                        for(x::uint64 i = 0; i < children.size(); i++)
                        {
                            if(f(children[i]))
                            {
                                return children[i];
                            }
                        }
                        exceptional();
                    }
                    else
                    {
                        exceptional();
                    }
                }
    public:     inline x::uint64 type() const { return __type; }
    public:     inline x::string path() const { return __directory + (__directory.size() > 0 ? "/" : "") + __name + (__extension.size() ? "." : "") + __extension; }
    public:     inline x::string name() const { return __name + (__extension.size() > 0 ? "." : "") + __extension; }
    public:     inline const x::string & title() const { return __name; }
    public:     const x::string & extension() const { return __extension; }
    public:     virtual void get(x::function<void (const x::file &)> f) const
                {
                    if(f)
                    {
                        f(*this);
                        children.each([&f](const x::file & child){
                            child.get(f);
                        });
                    }
                }
    protected:  virtual void retrieve()
                {
                    x::string fullpath = path();
                    __type = __core_stat_file_type(fullpath.str());

                    if(__type == 0x00000004UL)
                    {
                        void * h = __core_opendir(fullpath.str());
                        if(h != nullptr)
                        {
                            char buf[256];
                            char * name = nullptr;
                            while((name = __core_readdir_name(h, buf)) != nullptr)
                            {
                                if(__core_strcmp(name, ".") != 0 && __core_strcmp(name, "..") != 0)
                                {
                                    children.append(x::file(fullpath + "/" + name));
                                }
                            }
                            __core_closedir(h);
                        }
                    }
                }
    public:     x::file & operator=(const x::file & o)
                {
                    if(&o != this)
                    {
                        __type = o.__type;
                        __directory = o.__directory;
                        __name = o.__name;
                        __extension = o.__extension;
                        children = o.children;
                    }
                    return *this;
                }
    public:     x::file & operator=(x::file && o) noexcept
                {
                    if(&o != this)
                    {
                        __type = o.__type;
                        __directory = x::move(o.__directory);
                        __name = x::move(o.__name);
                        __extension = x::move(o.__extension);
                        children = x::move(o.children);

                        o.__type = 0;
                    }
                    return *this;
                }
    public:     file(const x::string & fullpath)
                :   __type(0LU),
                    __directory(),
                    __name(),
                    __extension(),
                    children()
                {
                    if(fullpath.size() > 0)
                    {
                        x::uint64 index = fullpath.find([](x::character c){ return c=='/' || c == '.'; }, fullpath.size() - 1, x::backward);
                        if(index != -1LU)
                        {
                            if(fullpath[index] == '.')
                            {
                                __extension = fullpath.sub(index + 1, fullpath.size() - index - 1);
                                x::uint64 start = fullpath.find('/', index, x::backward);
                                if(start != -1LU)
                                {
                                    __directory = fullpath.sub(0, start);
                                    __name = fullpath.sub(start + 1, index - start - 1);
                                }
                                else
                                {
                                    __name = fullpath.sub(0, index);
                                }
                            }
                            else
                            {
                                __name = fullpath.sub(index + 1, fullpath.size() - index - 1);
                                __directory = fullpath.sub(0, index);
                            }
                        }
                        else
                        {
                            __name = fullpath;
                        }
                    }
                    retrieve();
                }
    public:     file()
                :   __type(0LU),
                    __directory(),
                    __name(),
                    __extension(),
                    children()
                {
                }
    public:     file(const x::file & o)
                :   __type(o.__type),
                    __directory(o.__directory),
                    __name(o.__name),
                    __extension(o.__extension),
                    children(o.children)
                {
                }
    public:     file(x::file && o) noexcept
                :   __type(o.__type),
                    __directory(x::move(o.__directory)),
                    __name(x::move(o.__name)),
                    __extension(x::move(o.__extension)),
                    children(x::move(o.children))
                {
                    o.__type = 0LU;
                }
    public:     virtual ~file()
                {
                    __type = 0LU;
                }
    };
}

#endif // __X__FILE__HH__
